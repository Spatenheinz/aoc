#include <stdio.h>
#include <stdlib.h>

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
        int hand = line[2] - 'W';
        int opponent = line[0] - '@';
        int res = line[2] - line[0];
        sum += hand;
        if (res == 'X' - 'A')
            sum += 3;
        // only if res is not 0 will i win.
        else if (!(res % 3))
            sum += 6;

        // given x we need to lose, so 3 if opponent is Rock or 1 less otherwise
        if (line[2] == 'X')
            sum2 += (line[0] == 'A') ? 3 : opponent - 1;
        // given y, we need a draw, so same score as opponent + draw points
        if (line[2] == 'Y')
            sum2 += opponent + 3;
        /* given z, we need to win, so 6 + win points */
        if (line[2] == 'Z')
            sum2 += 6 + (line[0] == 'C' ? 1 : opponent + 1);
    }
    // solution 1
    printf("%d\n", sum);

    //solution 2
    printf("%d\n", sum2);

    fclose(f);
    return 0;
}
