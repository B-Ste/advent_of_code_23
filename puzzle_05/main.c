#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define NUMBER(x) ((x) >= 48 && (x) <= 57)

typedef struct {
    unsigned int dest_start;
    unsigned int src_start;
    unsigned int length;
} Map;

unsigned int *parse_numbers(char *str) {
    int number_numbers = 1;
    int array_size = 16;
    unsigned int *array = malloc(array_size * sizeof(int));
    if (!array) exit(1);
    char *tk;
    while((tk = strsep(&str, " "))) {
        array[number_numbers++] = atoi(tk);
    }
    array[0] = number_numbers - 1;
    return array;
}

int main(int argc, char const *argv[]) {
    FILE *f = fopen("/Users/benjaminsteeg/advent_of_code_23/puzzle_05/input.txt", "r");
    if (!f) exit(1);
    char line[256];
    fgets(line, 256, f);
    unsigned int *seed = parse_numbers(line + 7);
    while (fgets(line, 256, f)) {
        if (NUMBER(line[0])) {
            int num_mappings = 0;
            Map mapping[64];
            while (NUMBER(line[0])) {
                unsigned int *numbers = parse_numbers(line);
                mapping[num_mappings].dest_start = numbers[1];
                mapping[num_mappings].src_start = numbers[2];
                mapping[num_mappings].length = numbers[3];
                num_mappings++;
                fgets(line, 256, f);
            }
            for (int i = 1; i < seed[0] + 1; i++) {
                for (int j = 0; j < num_mappings; j++) {
                    if (seed[i] >= mapping[j].src_start && seed[i] < (mapping[j].src_start + mapping[j].length)) {
                        seed[i] = mapping[j].dest_start + (seed[i] - mapping[j].src_start);
                        break;
                    }
                }
            } 
        }
    }
    unsigned int min = INT32_MAX;
    for (int i = 1; i < seed[0] + 1; i++) {
        if (seed[i] < min) min = seed[i];
    }
    printf("Solution 1: %u\n", min);
    fclose(f);
    return 0;
}
