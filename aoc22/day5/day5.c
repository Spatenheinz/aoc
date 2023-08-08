#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

int main()
{
    FILE* f = fopen("input", "r");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];

    int sum = 0;
    int sum2 = 0;
    while (fgets(line, MAX_LINE_LENGTH , f)) {
    }
    // solution 1
    printf("%d\n", sum);

    //solution 2
    printf("%d\n", sum2);

    fclose(f);
    return 0;
}
