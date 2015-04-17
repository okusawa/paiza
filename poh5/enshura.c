#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// https://paiza.jp/poh/enshura

#define BUFFER_SIZE (256)

int main(int argc, char **argv) {
    char buf[BUFFER_SIZE];
    int cnt = 0;

    scanf("%[^\n]", buf);

    while (buf[cnt] != '\0') {
        if ((cnt + 1) & 0x01) printf("%c",  buf[cnt]);
        cnt++;
    }
    printf("\n");

    return 0;
}
