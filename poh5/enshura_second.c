#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int n; // 日数(必ず7の倍数)
    int *buf;
    int i, s;
    int totals[7];

    scanf("%d", &n);
    buf = (int *)malloc(sizeof(int) * n);
    memset(buf, 0, sizeof(int) * n);
    memset(totals, 0, sizeof(int) * 7);

    for (i = 0; i < n; i++) {
        scanf("%d", &s);
        totals[i % 7] += s;
    }

    free(buf);

    for (i = 0; i < 7; i++) printf("%d\n", totals[i]);
    printf("\n");

    return 0;
}
