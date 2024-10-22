#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdint.h>

#define NUMBER(x) ((x) >= 48 && (x) <= 57)

typedef struct {
    uint64_t dest_start;
    uint64_t src_start;
    uint64_t length;
} Map;

uint64_t *parse_numbers(char *str) {
    uint64_t number_numbers = 1;
    uint64_t array_size = 32;
    uint64_t *array = malloc(array_size * sizeof(uint64_t));
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
    uint64_t *seed = parse_numbers(line + 7);
    uint64_t *seed_2 = malloc(32 * sizeof(uint64_t));
    memcpy(seed_2, seed, 32 * sizeof(uint64_t));
    int cur_mapping = 0;
    int map_size[7];
    Map mappings[7][64];
    while (fgets(line, 256, f)) {
        if (NUMBER(line[0])) {
            int num_mappings = 0;
            while (NUMBER(line[0])) {
                uint64_t *numbers = parse_numbers(line);
                mappings[cur_mapping][num_mappings].dest_start = numbers[1];
                mappings[cur_mapping][num_mappings].src_start = numbers[2];
                mappings[cur_mapping][num_mappings].length = numbers[3];
                num_mappings++;
                fgets(line, 256, f);
                free(numbers);
            }
            for (int i = 1; i < seed[0] + 1; i++) {
                for (int j = 0; j < num_mappings; j++) {
                    if (seed[i] >= mappings[cur_mapping][j].src_start 
                        && seed[i] < (mappings[cur_mapping][j].src_start + mappings[cur_mapping][j].length)) {
                            seed[i] = mappings[cur_mapping][j].dest_start + (seed[i] - mappings[cur_mapping][j].src_start);
                            break;
                    }
                }
            }
            map_size[cur_mapping] = num_mappings;
            cur_mapping++; 
        }
    }
    uint64_t min_1 = INT32_MAX;
    for (int i = 1; i < seed[0] + 1; i++) {
        if (seed[i] < min_1) min_1 = seed[i];
    }
    printf("Solution 1: %llu\n", min_1);
    uint64_t min_2 = UINT64_MAX;
    for (int i = 1; i < seed_2[0] + 1; i += 2) {
        for (int k = seed_2[i]; k < seed_2[i] + seed_2[i + 1]; k++) {
            uint64_t spec_seed = k;
            for (int j = 0; j < 7; j++) {
                for (int l = 0; l < map_size[j]; l++) {
                    if (spec_seed >= mappings[j][l].src_start 
                        && spec_seed < (mappings[j][l].src_start + mappings[j][l].length)) {
                            spec_seed = mappings[j][l].dest_start + (spec_seed - mappings[j][l].src_start);
                            break;
                    }
                }
            }
            if ((uint64_t) spec_seed < min_2) min_2 = (uint64_t) spec_seed;
        }
    }
    printf("Solution 2: %llu\n", min_2);
    free(seed);
    fclose(f);
    return 0;
}
