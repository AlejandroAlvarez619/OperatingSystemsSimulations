// ------------------------------------------------------------
// Group: Alejandro Alvarez, Bashar Makani
// Class Accounts: cssc3106, cssc3133
// Class: CS480, Summer 2026
// Assignment: Assignment #2, Experimental Shell (xsh)
// Filename: shell.h
// ------------------------------------------------------------

#ifndef SHELL_H
#define SHELL_H

#define MAX_LINE   1024   // longest command the user can type
#define MAX_STAGES 16     // max number of commands in a pipeline

// show the prompt like "bashar "
void prompt();

// read one line of input from the user
// returns 0 if end of file (ctrl+d), 1 otherwise
int read_line(char *input);

// parse and run a command line
void execute(char *input);

#endif
