#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 256

int max(int *arr, int len) {
    int max = arr[0];
    for (int i = 1; i < len; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main()
{
    FILE* f = fopen("input", "r");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    int sum = 0;
    char line[MAX_LINE_LENGTH];
    int top3[3] = {0, 0, 0};

    while (fgets(line, MAX_LINE_LENGTH , f)) {
        sum += atoi(line);
        if (line[0] == '\n' || feof(f)) {
            int smallest = top3[0];
            int smallest_idx = 0;
            bool found = false;
            for (int i = 0; i < 3; i++) {
                if (sum > top3[i] && top3[i] <= smallest) {
                    smallest_idx = i;
                    smallest = top3[i];
                    found = true;
                }
            }
            if (found)
                top3[smallest_idx] = sum;
            sum = 0;
        }
    }
    // solution 1
    printf("Max 1: %d\n", max(top3, 3));

    //solution 2
    for (int i = 0; i < 3; i++) {
        sum += top3[i];
    }
    printf("Max 2: %d\n", sum);

    fclose(f);
    return 0;
}
