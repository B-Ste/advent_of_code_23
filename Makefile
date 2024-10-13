CC := gcc
NUM := 1
W := $(wildcard ./puzzle_*)

all: puzzle_*

puzzle_%: puzzle_%/main.c
	$(CC) $^ -o $@/main