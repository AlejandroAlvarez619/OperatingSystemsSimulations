// ------------------------------------------------------------
// Group: Alejandro Alvarez, Bashar Makani
// Class Accounts: cssc3106, cssc3133
// Class: CS480, Summer 2026
// Assignment: Assignment #3, Disk Arm Scheduling (simarm)
// Filename: sim.h
// ------------------------------------------------------------

#ifndef SIM_H
#define SIM_H

#define DISK_MAX  999   // highest cylinder number
#define START_CYL 500   // cylinder the arm starts on

// fill seq with num_reqs random cylinders (0..DISK_MAX)
void make_sequence(int *seq, int num_reqs);

// each returns the total cylinders the arm moves to service seq
int fcfs(int *seq, int num_reqs);
int ssf(int *seq, int num_reqs);
int elevator(int *seq, int num_reqs);

#endif
