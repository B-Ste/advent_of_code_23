#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define LINE_LENGTH 142
#define NUMBER(x) ((x) >= 48 && (x) <= 57)
#define SPECIAL_CHAR(x) ((x) != 0 && (x) != '.' && ((x) < 48 || (x) > 57))
#define FREE(x) free(x); (x) = NULL;

int lower_bound(char *line, int in) {
    int i = in;
    while (i >= 0) {
        if (!NUMBER(line[i])) break;
        i--;
    }
    return ++i;
}

int upper_bound(char *line, int in) {
    int j = in;
    while (1) {
        if (!NUMBER(line[j])) break;
        j++;
    }
    return --j;
}

int *parseNumbers(char *line, int index) {
    int *nums = (int *) malloc(3 * sizeof(int));
    if (!nums) exit(1);
    nums[1] = 1;
    nums[2] = 1;
    if (NUMBER(line[index])) {
        int j = upper_bound(line, index);
        int i = lower_bound(line, index);
        char num[LINE_LENGTH] = {0};
        memcpy(num, line + i, j - i + 1);
        nums[0] = 1;
        nums[1] = atoi(num);
    } else {
        if (index - 1 >= 0 && NUMBER(line[index - 1])) {
            int i = lower_bound(line, index - 1);
            char num[LINE_LENGTH] = {0};
            memcpy(num, line + i, index - i);
            nums[0] = 1;
            nums[1] = atoi(num);
        }
        if (NUMBER(line[index + 1])) {
            int j = upper_bound(line, index + 1);
            char num[LINE_LENGTH] = {0};
            memcpy(num, line + index + 1, j - index);
            nums[0]++;
            nums[2] = atoi(num);
        }
    }
    return nums;
}

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
    int sum_2 = 0;
    while (1) {
        if (!fgets(line_below, LINE_LENGTH, f)) {
            for (int i = 0; i < LINE_LENGTH; i++) {
                line_below[i] = '.';
            }
            done = 1;
        }
        line_below[LINE_LENGTH - 2] = 0;

        int left_bound = -1;
        int right_bound = -1;
        for (int i = 0; i < LINE_LENGTH - 1; i++) {



            // Calculates solution of part 1
            if (NUMBER(line[i])) {
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



            
            // Calculates solution of part 2
            if (line[i] == '*') {
                int *num_above = parseNumbers(line_above, i);
                int *num_curr = parseNumbers(line, i);
                int *num_below = parseNumbers(line_below, i);
                if (num_above[0] + num_curr[0] + num_below[0] == 2) {
                    int gear_ratio = 1;
                    gear_ratio *= num_above[1];
                    gear_ratio *= num_above[2];
                    gear_ratio *= num_curr[1];
                    gear_ratio *= num_curr[2];
                    gear_ratio *= num_below[1];
                    gear_ratio *= num_below[2];
                    sum_2 += gear_ratio;
                }
                FREE(num_above);
                FREE(num_curr);
                FREE(num_below);
            }
        }

        if (done) break;
        memcpy(line_above, line, LINE_LENGTH);
        memcpy(line, line_below, LINE_LENGTH);
    }
    
    printf("Solution 1: %i\n", sum_1);
    printf("Solution 2: %i\n", sum_2);

    fclose(f);
    free(line_above);
    line_above = NULL;
    free(line);
    line = NULL;
    free(line_below);
    line_below = NULL;
    return 0;
}
