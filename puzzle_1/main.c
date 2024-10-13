#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int parseNumber(char* p, int mode) {
    char *t = p;
    if (mode) {
        while (*t) t++;
        t--;
    }
    while (*t) {
        for (int i = 0; i < strlen(p); i++) {
            char substr[i + 2];
            memcpy(substr, t - ((mode) ? i : 0), i + 1);
            substr[i + 1] = 0;
            if (!strcmp(substr, "one")) return 1;
            else if (!strcmp(substr, "two")) return 2;
            else if (!strcmp(substr, "three")) return 3;
            else if (!strcmp(substr, "four")) return 4;
            else if (!strcmp(substr, "five")) return 5;
            else if (!strcmp(substr, "six")) return 6;
            else if (!strcmp(substr, "seven")) return 7;
            else if (!strcmp(substr, "eight")) return 8;
            else if (!strcmp(substr, "nine")) return 9;
        }
        t += (mode) ? -1 : 1;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    FILE *f = fopen("/Users/benjaminsteeg/advent_of_code_23/puzzle_1/input.txt", "r");
    int c;
    char str[128] = {0};
    int len;
    int sum = 0;
    while (c != EOF) {
        c = fgetc(f);
        int i1 = -1;
        int i2 = -1;
        while (c != '\n' && c != EOF) {
            if (c >= 48 && c <= 57) {
                if (i1 < 0) i1 = c - 48;
                else i2 = c - 48;
                memset(str, 0, 64);
                len = 0;
            } else str[len++] = c;
            int str_num = (i1 < 0) ? parseNumber(str, 0) : parseNumber(str, 1);
            if (str_num) {
                if (i1 < 0) i1 = str_num;
                else i2 = str_num;
            }
            c = fgetc(f);
        }
        memset(str, 0, 64);
        len = 0;
        if (i2 > 0) {
            sum += i1 * 10 + i2;
        } else if (i1 > 0) {
            sum += i1 * 10 + i1;
        }
    }
    printf("%i\n", sum);
    fclose(f);
    return 0;
}
