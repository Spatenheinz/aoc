#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_LINE_LENGTH 256
#define DIMENTION 1000

void next_greater(char* arr, char* res, int len) {
    char stack[len];
    char* ptr = stack;
    for (int i = 0; i < len; i++) {
        res[i] = -1;
        while (ptr != stack && arr[i] > arr[*ptr]) {
            res[*ptr] = arr[i];
            ptr--;
        }
        *ptr++ = i;
    }
}

void prev_greater(char* arr, char* res, int len) {
    char stack[len];
    char* ptr = stack;
    for (int i = 0; i < len; i++) {
        res[i] = -1;
        while (ptr != stack && arr[i] > arr[*ptr]) {
            ptr--;
        }
        if (ptr != stack)
            res[i] = arr[*ptr];
        *++ptr = i;
    }
}

int main()
{
    FILE* f = fopen("input", "r");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];

    int answer = 0, answer2 = 0;

    char grid[DIMENTION * DIMENTION];
    memset(grid, 0, sizeof(grid));
    char* ptr = grid;
    int len;

    while (fgets(line, MAX_LINE_LENGTH, f)) {
        len = strlen(line);
        memcpy(ptr, line, len);
        ptr += len;
    }
    char col[len];
    char working[len];
    char is_seen[len*len];

    // rows
    for (int i = 0; i < len; i++) {
        next_greater(grid, working, len);
        is_seen[i*len+j] = working[j];
        prev_greater(grid, working, len);
        is_seen[i*len+j] |= working[j];
    }
    // cols
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {

            next_greater(col, working, len);
            is_seen[i+j*len] |= working[j];
            prev_greater(col, working, len);
            is_seen[i+j*len] |= working[j];
        }
    }
    for (int i = 0; i < len*len; i++) {
        if (is_seen[i] == -1)
            answer++;
    }

    // solution 1
    printf("%d\n", answer);

    //solution 2
    printf("%d\n", answer2);

    fclose(f);
    return 0;
}
