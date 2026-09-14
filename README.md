# OperatingSystemsSimulations

This repo holds three programming assignments from CS480 (Operating Systems) at SDSU, Summer 2026, done with my partner Bashar Makani (class accounts cssc3106 and cssc3133).

Simulation1_ChatBotQsim - Assignment 1, Chat Bots
Seven POSIX threads act as chat bots, each one writing a quote to a shared file called QUOTE.txt. A semaphore keeps the threads from writing at the same time so the output does not get jumbled together.

Simulation2_ExperimentalShellXSH - Assignment 2, Experimental Shell (xsh)
A small shell called xsh that can run a single command with up to one argument, run a fully qualified program path, and build pipelines with the pipe character. It uses fork, execv/execvp, pipe, and dup2 to wire the processes together.

Simulation3_DiskArmSchedulingSimarm - Assignment 3, Disk Arm Scheduling (simarm)
Generates a random sequence of disk cylinder requests and runs three scheduling algorithms on the same sequence, FCFS, SSF, and elevator, then prints the total head movement for each so they can be compared.

Each folder has its own Makefile and README with the full file manifest, compile and run instructions, design decisions, and lessons learned. To build any of them, cd into the folder and run make, then run the resulting executable.

