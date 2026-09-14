// ------------------------------------------------------------
// Group: Alejandro Alvarez, Bashar Makani
// Class Accounts: cssc3106, cssc3133
// Class: CS480, Summer 2026
// Assignment: Assignment #2, Experimental Shell (xsh)
// Filename: main.cpp
// ------------------------------------------------------------

#include "shell.h"
#include <stdio.h>
#include <string.h>

int main()
{
    char input[MAX_LINE]; // holds what the user types

    while (1)
    {
        prompt(); // print the username prompt

        // read what the user typed, if they hit ctrl+d we stop
        if (read_line(input) == 0)
            break;

        // if they typed exit, quit the shell
        if (strcmp(input, "exit") == 0)
            break;

        // otherwise try to run the command
        execute(input);
    }

    printf("Exiting xsh. Goodbye!\n");
    
    return 0;
}
