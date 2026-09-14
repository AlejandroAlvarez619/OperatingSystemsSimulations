# ------------------------------------------------------------
# Group: Alejandro Alvarez, Bashar Makani
# Class Accounts: cssc3106, cssc3133
# Class: CS480, Summer 2026
# Assignment: Assignment #2, Experimental Shell (xsh)
# Filename: Makefile
# ------------------------------------------------------------

###########################################################
# Makefile for CS480 Assignment #2
###########################################################

EXEC = xsh
FILES = main.cpp shell.cpp
HEADERS = shell.h
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
