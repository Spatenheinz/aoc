#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

#define CHARS 53

#define GROUP_SIZE 3

#define PRIORITY(i) (((line[i] ^ 0x20) - '@') - (line[i] <= 'Z' ? 6 : 0))

int main()
{
    FILE* f = fopen("input", "r");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char lookups[CHARS * GROUP_SIZE];

    int sum = 0;
    int sum2 = 0;
    int len = 0;
    int idx = 0;
    while (fgets(line, MAX_LINE_LENGTH , f)) {

        char *lookup = &lookups[idx*CHARS];
        memset(lookup, 0, CHARS);
        //
        // dont want the newline
        len = strlen(line) - 1;

        int val;
        for (int i = 0; i < len/2; i++) {
            val = PRIORITY(i);
            lookup[val] = val;
        }
        // this block to solve task 1
        for(int i = len/2; i < len; i++) {
            val = PRIORITY(i);
            if (lookup[val] == val) {
                sum += val;
                break;
            }
        }

        // rest is task 2 stuff
        if (idx == 2) {
            for(int i = 0; i < len; i++) {
                val = PRIORITY(i);
                if (val == lookups[(idx-2)*CHARS + val]
                    && val == lookups[(idx-1) * CHARS + val]) {
                    sum2 += val;
                    break;
                }
            }
        } else {
            for(int i = 0; i < len; i++) {
                val = (line[i] ^ 0x20) - '@';
                if (line[i] <= 'Z')
                    val -= 6;
                lookup[val] = val;
            }
        }
        idx = (idx + 1) % GROUP_SIZE;
    }
    // solution 1
    printf("%d\n", sum);

    //solution 2
    printf("%d\n", sum2);

    fclose(f);
    return 0;
}
