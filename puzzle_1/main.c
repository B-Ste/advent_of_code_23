#include<stdio.h>
#include<stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *f = fopen("/Users/benjaminsteeg/advent_of_code_23/puzzle_1/input.txt", "r");
    int c;
    int sum = 0;
    while (c != EOF) {
        c = fgetc(f);
        int i1 = -1;
        int i2 = -1;
        while (c != '\n' && c != EOF) {
            if (c >= 48 && c <= 57) {
                if (i1 < 0) i1 = c - 48;
                else i2 = c - 48;
            }
            c = fgetc(f);
        }
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
