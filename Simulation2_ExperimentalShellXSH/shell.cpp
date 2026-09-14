// ------------------------------------------------------------
// Group: Alejandro Alvarez, Bashar Makani
// Class Accounts: cssc3106, cssc3133
// Class: CS480, Summer 2026
// Assignment: Assignment #2, Experimental Shell (xsh)
// Filename: shell.cpp
// ------------------------------------------------------------

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// prints the prompt using the USER environment variable
// so it shows up like "bashar " or whatever the username is
void prompt()
{
    char *username = getenv("USER");
    // just in case USER isn't set for some reason
    if (username == NULL)
        username = (char *)"xsh";
    printf("%s ", username);
    fflush(stdout); // make sure it prints right away
}

// reads one line of input from the user into input
// returns 0 if ctrl+d is pressed (end of input), 1 if we got a line
int read_line(char *input)
{
    if (fgets(input, MAX_LINE, stdin) == NULL)
        return 0;
    // get rid of the newline at the end
    input[strcspn(input, "\n")] = '\0';
    return 1;
}

// splits the command line by pipe characters
// fills commands with each command and its argument (one arg max)
// returns how many commands there are, or -1 if input is invalid
static int parse(char *input, char *commands[][3])
{
    int num_commands = 0;
    char *remaining = input;
    char *chunk;

    // go through each section split by |
    while ((chunk = strsep(&remaining, "|")) != NULL)
    {
        // too many pipes
        if (num_commands >= MAX_STAGES)
            return -1;

        int num_args = 0;
        char *word = strtok(chunk, " \t");
        while (word != NULL)
        {
            // we only allow one argument per command
            if (num_args >= 2)
                return -1;
            commands[num_commands][num_args] = word;
            num_args++;
            word = strtok(NULL, " \t");
        }
        // a pipe section can't be empty
        if (num_args == 0)
            return -1;
        commands[num_commands][num_args] = NULL; // null terminate the args
        num_commands++;
    }
    return num_commands;
}

// forks a child process for each command and connects them with pipes
static void run_pipeline(char *commands[][3], int num_commands)
{
    int last_read_end = -1; // read end of the last pipe we made
    pid_t child_pids[MAX_STAGES];

    for (int i = 0; i < num_commands; i++)
    {
        int pipe_fds[2];
        // make a pipe between this command and the next one
        if (i < num_commands - 1)
            pipe(pipe_fds);

        pid_t child = fork();
        if (child == 0)
        {
            // we are in the child process
            // if there was a previous pipe, read from it
            if (last_read_end != -1)
            {
                dup2(last_read_end, 0); // stdin = read end of last pipe
                close(last_read_end);
            }
            // if there is a next command, write output into the pipe
            if (i < num_commands - 1)
            {
                dup2(pipe_fds[1], 1); // stdout = write end of this pipe
                close(pipe_fds[0]);
                close(pipe_fds[1]);
            }
            // run the command
            // if it starts with / it is a full path, otherwise search PATH
            if (commands[i][0][0] == '/')
                execv(commands[i][0], commands[i]);
            else
                execvp(commands[i][0], commands[i]);
            // if we get here, exec failed
            perror(commands[i][0]);
            _exit(1);
        }

        // back in the parent - save the child's pid
        child_pids[i] = child;
        // close the old pipe read end, we dont need it anymore
        if (last_read_end != -1)
            close(last_read_end);
        // save the read end of the new pipe for the next child
        if (i < num_commands - 1)
        {
            close(pipe_fds[1]);
            last_read_end = pipe_fds[0];
        }
    }

    // wait for every child to finish before showing the next prompt
    for (int i = 0; i < num_commands; i++)
        waitpid(child_pids[i], NULL, 0);
}

// this is called from main to handle one line of input
// it skips blank lines, parses the command, and runs it
void execute(char *input)
{
    // skip over any leading spaces or tabs
    char *start = input;
    while (*start == ' ' || *start == '\t')
        start++;
    // if the line was empty just go back to the prompt
    if (*start == '\0')
        return;

    char *commands[MAX_STAGES][3];
    int num_commands = parse(input, commands);

    // if parse returned -1 the format was invalid
    if (num_commands < 0)
    {
        fprintf(stderr, "xsh: invalid command\n");
        return;
    }

    run_pipeline(commands, num_commands);
}
