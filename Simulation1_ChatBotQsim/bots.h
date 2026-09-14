// ------------------------------------------------------------
// Group: Alejandro Alvarez, Bashar Makani
// Class Accounts: cssc3106, cssc3133
// Class: CS480, Summer 2026
// Assignment: Assignment #1, Chat Bots
// Filename: bots.h
// ------------------------------------------------------------

#ifndef BOTS_H
#define BOTS_H

#include <semaphore.h>

#define NUM_THREADS 7

extern sem_t FLAG;

void *bot(void *arg);

#endif
