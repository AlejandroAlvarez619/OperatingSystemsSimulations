// ------------------------------------------------------------
// Group: Alejandro Alvarez, Bashar Makani
// Class Accounts: cssc3106, cssc3133
// Class: CS480, Summer 2026
// Assignment: Assignment #1, Chat Bots
// Filename: bots.cpp
// ------------------------------------------------------------

#include "bots.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// Makes sure only one thread writes to the file at once
sem_t FLAG;

// Function that will be ran by each thread
void* bot(void* arg) {
    // Gets the thread number that was passed into the function
    int num = *(int*)arg;

    // Runs each thread 8 times
    for (int i = 0; i < 8; i++) {
        // Even numbered threads sleep for 2 seconds and odd numbered threads sleep for 3 seconds
        if (num % 2 == 0)
            sleep(2);
        else
            sleep(3);

        // Locks the semaphore so only one thread can write at a time
        sem_wait(&FLAG);

        // Opens the quote file in append mode so new lines are added to the end
        FILE* fp = fopen("QUOTE.txt", "a");

        // Even numbered threads write the Brian Kernighan quote
        if (num % 2 == 0)
            fprintf(fp, "Thread ID %d: \"Controlling complexity is the essence of computer programming.\" -Brian Kernighan\r\n", num);

        // Odd numbered threads write the Edsger Dijkstra quote
        else
            fprintf(fp, "Thread ID %d: \"Computer science is no more about computers than astronomy is about telescopes.\" -Edsger Dijkstra\r\n", num);

        // Closes the file after writing
        fclose(fp);

        // Prints which thread is currently running
        printf("Thread %d is running\n", num);

        // Unlocks the semaphore so another thread can write
        sem_post(&FLAG);
    }

    // Ends the thread
    return NULL;
}

int main() {
    // Opens the quote file in write mode and clears old contents
    FILE* fp = fopen("QUOTE.txt", "w");

    // Writes the process ID at the top of the file
    fprintf(fp, "Process ID: %d\r\n", getpid());

    // Closes the file after writing the process ID
    fclose(fp);

    // Initializes the semaphore with a value of 1
    sem_init(&FLAG, 0, 1);

    // Creates an array to store the thread IDs
    pthread_t threads[NUM_THREADS];

    // Creates an array to store the thread numbers
    int nums[NUM_THREADS];

    // Creates each thread
    for (int i = 0; i < NUM_THREADS; i++) {
        // Sets the thread number
        nums[i] = i + 1;

        // Prints a message before creating each thread
        printf("Creating thread, in main(): %d\n", nums[i]);

        // Creates the thread and sends it to the bot function
        pthread_create(&threads[i], NULL, bot, &nums[i]);
    }

    // Waits for each thread to finish before continuing
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    // Destroys the semaphore after all threads are done
    sem_destroy(&FLAG);

    // Prints final message when the program is finished
    printf("All threads done. Goodbye!\n");

    // Ends the program
    return 0;
}
