#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// https://paiza.jp/poh/kirishima

typedef struct {
    int num;
    int cost;
} Company;

int *buf;
int main(int argc, char **argv) {
    int m; // 必要な人員数
    int n; // 会社数
    int i, j, buf_size, prev, now;
    int num, cost, total_num;
    Company *companies;

    scanf("%d", &m);
    scanf("%d", &n);
    companies = (Company*)malloc(sizeof(Company) * (n + 1));
    memset(companies, 0, sizeof(Company));
    total_num = 0;
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &(companies[i].num), &(companies[i].cost));
        total_num += companies[i].num;
    }

    buf_size = sizeof(int) * (n + 1) * total_num;
    buf = malloc(buf_size);
    memset(buf, -1, buf_size);

    // ナップザックにデータを入れる
    buf[0] = 0;
    for (i = 1; i <= n; i++) {
        for (j = 0; j < total_num; j++) {
            // 1つ前のバッファでデータがあるものに対して、有り無しを考える
            prev = (i-1)*total_num+j;
            if (buf[prev] >= 0) {
                now = i*total_num+j;

                // 無しデータ
                if (buf[now] >= 0) {
                    // 既にデータがあったら、少ないほうを優先
                    if (buf[prev] < buf[now]) {
                        buf[now] = buf[prev];
                    }
                } else {
                    buf[now] = buf[prev];
                }

                // 有りデータ
                buf[now+companies[i].num] = buf[prev] + companies[i].cost;
            }
        }
    }

    // 必要な人数を満たしたデータからコストが最小のものを探す
    cost = -1;
    for (i = 1; i <= n; i++) {
        for (j = m; j < total_num; j++) {
            prev = buf[i*total_num+j];
            if (cost < 0 || (prev > 0 && prev < cost)) cost = prev;
        }
    }

    if (cost == -1) cost = companies[1].cost;
    printf("%d\n", cost);

//     for (i = 0; i <= n; i++) {
//         for (j = 0; j < total_num; j++) {
//             if (buf[i*total_num+j] >= 0) {
//                 printf("%d(%d, %d), ", buf[i*total_num+j], i, j);
//             }
//         }
//         printf("\n");
//     }

    free(buf);
    free(companies);

    return 0;
}
