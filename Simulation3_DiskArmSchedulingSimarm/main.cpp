// ------------------------------------------------------------
// Group: Alejandro Alvarez, Bashar Makani
// Class Accounts: cssc3106, cssc3133
// Class: CS480, Summer 2026
// Assignment: Assignment #3, Disk Arm Scheduling (simarm)
// Filename: main.cpp
// ------------------------------------------------------------

#include "sim.h"
#include <stdio.h>
#include <stdlib.h>   // atoi, srand
#include <time.h>     // time

int main(int argc, char *argv[])
{
    if (argc != 2) return 1;      // need exactly one argument
    int num_reqs = atoi(argv[1]); // how many requests to generate
    if (num_reqs <= 0) return 1;  // need a positive count    
    srand(time(NULL));            // seed the random generator

    int *seq = new int[num_reqs]; // the request sequence
    make_sequence(seq, num_reqs);

    // run each algorithm and print its total head movement
    printf("FCFS: %d\n", fcfs(seq, num_reqs));
    printf("SSF: %d\n", ssf(seq, num_reqs));
    printf("ELEVATOR: %d\n", elevator(seq, num_reqs));

    delete[] seq;
    return 0;
}
