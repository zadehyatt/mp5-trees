# Makefile for lab5 - Binary Search Tree
# ECE 2230, Fall 2025
# Zade Hyatt
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11
LDFLAGS = -lm

all: lab5

lab5: lab5.o tree.o
	$(CC) $(CFLAGS) -o lab5 lab5.o tree.o $(LDFLAGS)

lab5.o: lab5.c tree.h
	$(CC) $(CFLAGS) -c lab5.c -o lab5.o

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c -o tree.o

clean:
	rm -f lab5.o tree.o lab5

