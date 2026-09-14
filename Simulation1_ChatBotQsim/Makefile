# ------------------------------------------------------------
# Group: Alejandro Alvarez, Bashar Makani
# Class Accounts: cssc3106, cssc3133
# Class: CS480, Summer 2026
# Assignment: Assignment #1, Chat Bots
# Filename: Makefile
# ------------------------------------------------------------

###########################################################
# Makefile for CS480 Assignment #1
###########################################################

EXEC = bots
FILES = bots.cpp
HEADERS = bots.h
CC = g++
LFLAGS = -g -pthread
CFLAGS = -g -c -pthread

OBJECTS = $(FILES:.cpp=.o)

$(EXEC): $(OBJECTS)
	$(CC) $(LFLAGS) -o $(EXEC) $(OBJECTS)
	rm -f *.o

.cpp.o:
	$(CC) $(CFLAGS) $<

clean: 
	rm -f *.o $(EXEC) QUOTE.txt

###########################################################
# EOF: Makefile
###########################################################
