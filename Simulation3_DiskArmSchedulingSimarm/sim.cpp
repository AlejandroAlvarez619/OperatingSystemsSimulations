// ------------------------------------------------------------
// Group: Alejandro Alvarez, Bashar Makani
// Class Accounts: cssc3106, cssc3133
// Class: CS480, Summer 2026
// Assignment: Assignment #3, Disk Arm Scheduling (simarm)
// Filename: sim.cpp
// ------------------------------------------------------------

#include "sim.h"
#include <stdlib.h>   // rand, abs, qsort

// fill seq with num_reqs random cylinders in 0..DISK_MAX
void make_sequence(int *seq, int num_reqs)
{
    for (int i = 0; i < num_reqs; i++)
        seq[i] = rand() % (DISK_MAX + 1);
}

// FCFS: visit the requests in order, adding the distance to each one
int fcfs(int *seq, int num_reqs)
{
    int total = 0;
    int head_pos = START_CYL;
    for (int i = 0; i < num_reqs; i++)
    {
        total += abs(seq[i] - head_pos); // distance to this request
        head_pos = seq[i];               // move head there
    }
    return total;
}

// SSF: each step, move to the closest request not yet serviced
int ssf(int *seq, int num_reqs)
{
    bool *done = new bool[num_reqs];     // marks serviced requests
    for (int i = 0; i < num_reqs; i++)
        done[i] = false;

    int total = 0;
    int head_pos = START_CYL;
    for (int step = 0; step < num_reqs; step++)
    {
        // find the nearest request still pending
        int near_idx = -1;
        int near_dist = 0;
        for (int i = 0; i < num_reqs; i++)
        {
            if (done[i])
                continue;
            int dist = abs(seq[i] - head_pos);
            if (near_idx == -1 || dist < near_dist)
            {
                near_idx = i;
                near_dist = dist;
            }
        }
        done[near_idx] = true;           // mark it serviced
        total += near_dist;              // add the distance moved
        head_pos = seq[near_idx];        // move head there
    }

    delete[] done;
    return total;
}

// sort ints ascending (used by qsort)
static int cmp_int(const void *a, const void *b)
{
    return *(const int *)a - *(const int *)b;
}

// ELEVATOR: keep moving up servicing requests until none are left above,
// then reverse and service the rest going down (stops at the last request,
// never runs to the edge of the disk)
int elevator(int *seq, int num_reqs)
{
    int *sorted = new int[num_reqs];     // sorted copy of the requests
    for (int i = 0; i < num_reqs; i++)
        sorted[i] = seq[i];
    qsort(sorted, num_reqs, sizeof(int), cmp_int);

    // split_idx = index of the first request at or above the start cylinder
    int split_idx = num_reqs;
    for (int i = 0; i < num_reqs; i++)
        if (sorted[i] >= START_CYL)
        {
            split_idx = i;
            break;
        }

    int total = 0;
    int head_pos = START_CYL;

    // sweep up through the requests at/above the start (low to high)
    for (int i = split_idx; i < num_reqs; i++)
    {
        total += sorted[i] - head_pos;
        head_pos = sorted[i];
    }
    // reverse and sweep down through the lower requests (high to low)
    for (int i = split_idx - 1; i >= 0; i--)
    {
        total += head_pos - sorted[i];
        head_pos = sorted[i];
    }

    delete[] sorted;
    return total;
}
