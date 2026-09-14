# ------------------------------------------------------------
# Group: Alejandro Alvarez, Bashar Makani
# Class Accounts: cssc3106, cssc3133
# Class: CS480, Summer 2026
# Assignment: Assignment #3, Disk Arm Scheduling (simarm)
# Filename: Makefile
# ------------------------------------------------------------

###########################################################
# Makefile for CS480 Assignment #3
###########################################################

EXEC = simarm
FILES = main.cpp sim.cpp
HEADERS = sim.h
CC = g++
LFLAGS = -g
CFLAGS = -g -c

OBJECTS = $(FILES:.cpp=.o)

$(EXEC): $(OBJECTS)
	$(CC) $(LFLAGS) -o $(EXEC) $(OBJECTS)
	rm -f *.o

.cpp.o:
	$(CC) $(CFLAGS) $<

clean: 
	rm -f *.o $(EXEC)

###########################################################
# EOF: Makefile
###########################################################

