#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define MAX_LINE_LENGTH 256
#define MAX_STACK 1096
#define FILE_LENGTH 1096

#define TASK1_LIMIT 100000

#define AVAILABLE_SPACE 70000000
#define UNUSED_NEEDED 30000000

int main()
{
    FILE* f = fopen("input", "r");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];

    int answer = 0;
    int answer2 = 0;

    int stack[MAX_STACK];
    int* stack_ptr;
    stack_ptr = stack;

    int sizes[FILE_LENGTH];
    memset(sizes, 0, FILE_LENGTH * sizeof(int));


    int i = 0;
    int size = 0;

    while (fgets(line, MAX_LINE_LENGTH , f)) {
        i++;
        if (strncmp(line, "$ ls", 4) == 0) {
            continue;
        }
        if (strncmp(line, "$ cd ..", 7) == 0) {
            stack_ptr--;
            continue;
        }
        if (strncmp(line, "$ cd", 4) == 0) {
            *stack_ptr++ = i;
            // print stack
            continue;
        }
        // dir will be 0, prob faster to not have dir included but
        sscanf(line, "%d", &size);
        for (int j = 0; j < stack_ptr - stack; j++) {
            sizes[stack[j]] += size;
        }
        size = 0;
    }

    // solution 1
    for (int j = 0; j < FILE_LENGTH; j++) {
        if (sizes[j] <= TASK1_LIMIT) {
            answer += sizes[j];
        }
    }
    printf("%d\n", answer);

    //solution 2
    int unused = AVAILABLE_SPACE - sizes[1];
    int needed = UNUSED_NEEDED - unused;
    answer2 = INT_MAX;
    for (int j = 0; j < FILE_LENGTH; j++) {
        if (sizes[j] >= needed && sizes[j] < answer2) {
            answer2 = sizes[j];
        }
    }
    printf("%d\n", answer2);

    fclose(f);
    return 0;
}
