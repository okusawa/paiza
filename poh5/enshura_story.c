#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int _x, _y;
    int x, y, i, yy, index1, index2;
    int *buf, size;

    scanf("%d", &_x);
    scanf("%d", &_y);
    size = _x * _y;
    buf = (int*)malloc(sizeof(int) * size);
    memset(buf, 0, sizeof(int) * size);

    for (y = 0; y < _y; y++) {
        for (x = 0; x < _x; x++) {
            scanf("%d", &buf[(y * _x) + x]);
        }
    }

    i = 0;
    while(i < size) {
        if (buf[i] == 2) buf[i] = 0;
        i++;
    }

    for (y = 0; y < _y - 1; y++) {
        for (x = 0; x < _x; x++) {
            index1 = (y * _x) + x;
            if (buf[index1]) {
                for (yy = y + 1; yy < _y; yy++) {
                    index2 = (yy * _x) + x;
                    if (!buf[index2]) {
                        buf[index1] = 0;
                        buf[index2] = 1;
                        index1 = index2;
                    }
                }
            }
        }
    }

    for (y = 0; y < _y; y++) {
        for (x = 0; x < _x; x++) {
            printf("%d", buf[(y * _x) + x]);
            if (x < _x - 1) printf(" ");
        }
        printf("\n");
    }

    free(buf);

    return 0;
}
