#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LINE_LENGTH 512
#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14
#define GAME_TOKEN ":;"
#define SET_TOKEN " ,\n"

int possible_set(char* str, int *red_p, int *green_p, int* blue_p) {
    char *set_token = strtok(str, SET_TOKEN);
    int ret = 1;
    while (set_token) {
        int n = atoi(set_token);
        char *color = strtok(NULL, SET_TOKEN);
        if (!strcmp(color, "red")) {
            if (n > *red_p) *red_p = n;
            if (n > MAX_RED) ret = 0;
        } else if (!strcmp(color, "green")) {
            if (n > *green_p) *green_p = n;
            if (n > MAX_GREEN) ret = 0;
        } else if (!strcmp(color, "blue")) {
            if (n > *blue_p) *blue_p = n;
            if (n > MAX_BLUE) ret = 0;
        }
        set_token = strtok(NULL, SET_TOKEN);
    }
    return ret;
}

int possible_game(char *str, int *cube_power_p) {
    char *game_token = strsep(&str, GAME_TOKEN);
    game_token = strsep(&str, GAME_TOKEN);
    int ret = 1;
    int red = 0;
    int green = 0;
    int blue = 0;
    while (game_token) {
        if (!possible_set(game_token, &red, &green, &blue)) ret = 0;
        game_token = strsep(&str, GAME_TOKEN);
    }
    *cube_power_p = red * green * blue;
    return ret;
}

int main(int argc, char const *argv[])
{
    FILE *f = fopen("/Users/benjaminsteeg/advent_of_code_23/puzzle_2/input.txt", "r");
    int line_num = 0;
    int possible_sum = 0;
    int cube_power_sum = 0;
    while (!feof(f)) {
        line_num++;
        char line[LINE_LENGTH] = {0};
        fgets(line, LINE_LENGTH, f);
        int cube_power = 0;
        if (possible_game(line, &cube_power)) possible_sum += line_num;
        cube_power_sum += cube_power;
    }
    printf("Solution 1: %i\n", possible_sum);
    printf("Solution 2: %i\n", cube_power_sum);
    return 0;
}
