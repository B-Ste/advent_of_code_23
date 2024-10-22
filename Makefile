CC := gcc
NUM := 1
W := $(wildcard ./puzzle_*)

all: puzzle_*/main

puzzle_%/main: puzzle_%/main.c
	$(CC) $^ -o $@

clean:
	rm -rf puzzle_*/main.dSYM
	rm puzzle_*/main