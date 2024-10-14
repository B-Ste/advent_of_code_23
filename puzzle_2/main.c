#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LINE_LENGTH 512
#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14
#define GAME_TOKEN ":;"
#define SET_TOKEN " ,\n"

int possible_set(char* str) {
    char *set_token = strtok(str, SET_TOKEN);
    while (set_token) {
        int n = atoi(set_token);
        char *color = strtok(NULL, SET_TOKEN);
        if (!strcmp(color, "red")) {
            if (n > MAX_RED) return 0;
        } else if (!strcmp(color, "green")) {
            if (n > MAX_GREEN) return 0;
        } else if (!strcmp(color, "blue")) {
            if (n > MAX_BLUE) return 0;
        }
        set_token = strtok(NULL, SET_TOKEN);
    }
    return 1;
}

int possible_game(char *str) {
    char *game_token = strsep(&str, GAME_TOKEN);
    game_token = strsep(&str, GAME_TOKEN);
    while (game_token) {
        if (!possible_set(game_token)) return 0;
        game_token = strsep(&str, GAME_TOKEN);
    }
    return 1;
}

int main(int argc, char const *argv[])
{
    FILE *f = fopen("/Users/benjaminsteeg/advent_of_code_23/puzzle_2/input.txt", "r");
    int line_num = 0;
    int sum = 0;
    while (!feof(f)) {
        line_num++;

        char line[LINE_LENGTH] = {0};
        fgets(line, LINE_LENGTH, f);

        if (possible_game(line)) sum += line_num;
    }
    printf("Solution: %i\n", sum);
    return 0;
}
