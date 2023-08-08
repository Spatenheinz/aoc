#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TO_INT(c) ((int)c - (int)'a')

/* #define INDEX(c) (1 << TO_INT(c)) */

#define WINDOW_SIZE 4
#define WINDOW_SIZE_2 14

/* void set_bit(int *c, unsigned char bit) { */
/*     *c |= INDEX(bit); */
/* } */

/* int get_bit(int c, unsigned char bit) { */
/*     return 1 & (c >> TO_INT(bit)); */
/* } */

/* void toggle_bit(int *c, unsigned char bit) { */
/*     *c ^= INDEX(bit); */
/* } */

int find_packet(FILE *f, char *window, int size, char *seen) {
    int i = 0;
    char c;
    while ((c = fgetc(f))) {
    if (c == '\n') {
        break;
    }

    if (i < size) {
        window[i] = c;
    }
    seen[TO_INT(c)] += 1;
     if (i >= size) {
         bool pass = true;
         for (int j = 0; j < size; j++) {
             if (seen[TO_INT(window[j])] != 1) {
                 pass = false;
                 break;
             }
         }

         if (pass) {
             return i + 1;
         }

         seen[TO_INT(window[0])] -= 1;
         for (int j = 0; j < size - 1; j++) {
             window[j] = window[j + 1];
         }
         window[size - 1] = c;
     }
     i++;
    }
    return i;
}

int main()
{
    FILE* f = fopen("input", "r");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    char window[WINDOW_SIZE];
    char window2[WINDOW_SIZE_2];

    char seen[26];

    memset(seen, 0, 26);

    // solution 1
    printf("%d\n", find_packet(f, window, WINDOW_SIZE - 1, seen));

    //solution 2
    fseek(f, 0, SEEK_SET);
    memset(seen, 0, 26);
    printf("%d\n", find_packet(f, window2, WINDOW_SIZE_2 - 1, seen));

    fclose(f);
    return 0;
}
