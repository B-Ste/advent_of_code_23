#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void init_index(char *index, char *winning_numbers) {
    char *tk;
    while ((tk = strsep(&winning_numbers, " "))) {
        if (*tk != 0) index[atoi(tk)] = 1;
    }
}

int evaluate_on_index(char *index, char *numbers_gotten) {
    int i = 0;
    char *tk;
    while ((tk = strsep(&numbers_gotten, " \n"))) {
        if (*tk != 0 && index[atoi(tk)]) i++; 
    }
    return i;
}

int pow(int x, int y) {
    int res = 1;
    for (int i = 0; i < y; i++) {
        res *= x;
    }
    return res;
}

int main(int argc, char const *argv[])
{
    FILE *f = fopen("/Users/benjaminsteeg/advent_of_code_23/puzzle_04/input.txt", "r");
    if (!f) exit(1);

    char line[256];
    int sum = 0;
    while (fgets(line, 256, f)) {
        char *winning_numbers = line + 10;
        *(winning_numbers + 29) = 0;
        char *numbers_gotten = winning_numbers + 32;
        char win_index[100] = {0};
        init_index(win_index, winning_numbers);
        int result = evaluate_on_index(win_index, numbers_gotten);
        sum += (result > 0) ? pow(2, result - 1) : 0;
    }
    printf("Solution 1: %i\n", sum);
    return 0;
}
