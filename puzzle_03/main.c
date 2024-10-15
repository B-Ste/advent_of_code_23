#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define LINE_LENGTH 142
#define SPECIAL_CHAR(x) ((x) != 0 && (x) != '.' && ((x) < 48 || (x) > 57))

int main(int argc, char const *argv[])
{
    FILE *f = fopen("/Users/benjaminsteeg/advent_of_code_23/puzzle_03/input.txt", "r");
    char *line_above = malloc(LINE_LENGTH);
    char *line = malloc(LINE_LENGTH);
    char *line_below = malloc(LINE_LENGTH);
    if (!line_above || !line_below) return 1;

    for (int i = 0; i < LINE_LENGTH; i++) {
        line_above[i] = '.';
        line[i] = '.';
    }
    line_above[LINE_LENGTH - 2] = 0;
    line[LINE_LENGTH - 2] = 0;

    int done = 0;
    int sum_1 = 0;
    while (1) {
        if (!fgets(line_below, LINE_LENGTH, f)) {
            for (int i = 0; i < LINE_LENGTH; i++) {
                line_below[i] = '.';
            }
            done = 1;
        }
        line_below[LINE_LENGTH - 2] = 0;

        // Calculates solution of part 1
        int left_bound = -1;
        int right_bound = -1;
        for (int i = 0; i < LINE_LENGTH - 1; i++) {
            if (line[i] >= 48 && line[i] <= 57) {
                if (left_bound < 0) {
                    left_bound = i;
                    right_bound = i;
                } else right_bound = i;
            } else if (left_bound >= 0 && right_bound >= 0) {
                int takeNum = 0;
                if ((left_bound - 1 >= 0 && SPECIAL_CHAR(line[left_bound - 1])) || SPECIAL_CHAR(line[right_bound + 1])) {
                    takeNum = 1;
                    goto found;
                }
                for (int u = left_bound - 1; u <= right_bound + 1; u++) {
                    if (u >= 0 && (SPECIAL_CHAR(line_above[u]) || SPECIAL_CHAR(line_below[u]))) {
                        takeNum = 1;
                        break;
                    }
                }
                found:
                if (takeNum) {
                    char num[LINE_LENGTH] = {0};
                    memcpy(num, line + left_bound, right_bound - left_bound + 1);
                    sum_1 += atoi(num);
                }
                takeNum = 0;
                left_bound = -1;
                right_bound = -1;
            }
        }

        if (done) break;
        memcpy(line_above, line, LINE_LENGTH);
        memcpy(line, line_below, LINE_LENGTH);
    }
    
    printf("Solution 1: %i\n", sum_1);

    fclose(f);
    free(line_above);
    line_above = NULL;
    free(line);
    line = NULL;
    free(line_below);
    line_below = NULL;
    return 0;
}
