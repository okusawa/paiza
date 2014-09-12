#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// https://paiza.jp/challenges/24/page/problem

// フレーム毎の情報
typedef struct {
    int beat_num[3];
    int score;
} Frame;

int calc_score(int a, int b, int frame, Frame *p)
{
    int score = 0;
    int i;
    if (frame == a - 1) {
        // 最終フレーム
        if (p->beat_num[0] + p->beat_num[1] == b) {
            // スペアを取った場合は３投目を2回足す
            score = b + p->beat_num[2] + p->beat_num[2];
        } else if (p->beat_num[0] == b) {
            // 1投目にストライク
            score = b + p->beat_num[1] + p->beat_num[1]; // 2投目は2回足す
            if (p->beat_num[1] == b) {
                // 2投目もストライク
                score += p->beat_num[2] + p->beat_num[2] + p->beat_num[2]; // 3投目は3回足す
            } else {
                score += p->beat_num[2] + p->beat_num[2]; // 3投目は2回足す
            }

        } else {
            for (i = 0; i < 2; i++) {
                score += p->beat_num[i];
            }
        }

    } else {
        if (p->beat_num[0] == b) {
            // ストライク
            if ((p+1)->beat_num[0] == b) {
                // 次もストライク
                if (frame == a - 2) {
                    score = b + (p+1)->beat_num[0] + (p+1)->beat_num[1];
                } else {
                    score = b + (p+1)->beat_num[0] + (p+2)->beat_num[0];
                }
            } else {
                score = b + (p+1)->beat_num[0] + (p+1)->beat_num[1];
            }
        } else if (p->beat_num[0] + p->beat_num[1] == b) {
            // スペア
            score = b + (p+1)->beat_num[0];
        } else {
            for (i = 0; i < 2; i++) {
                score += p->beat_num[i];
            }
        }
    }
    p->score = score;
    return p->score;
}

int main(int argc, char **argv) {

    int a; // フレーム数
    int b; // ピン数
    int n; // ボールを投げた回数

    scanf("%d %d %d\n", &a, &b, &n);

    Frame *frames;
    frames = (Frame *)malloc(sizeof(Frame) * n);
    memset(frames, 0, sizeof(Frame) * n);

    fflush(stdin);
    char str[4096*4];
    char *token;
    fgets(str, sizeof(str), stdin);

    int i;
    int frame = 0;
    int cnt = 0;
    int num;
    for (i = 0; i < n; i++) {
        if (i) {
            token = strtok(NULL, " ");
        } else {
            token = strtok(str, " ");
        }
        num = atoi(token);

        frames[frame].beat_num[cnt] = num;

        if (!cnt && num == b && frame < a - 1) cnt++;
        cnt++;

        if (cnt == 2 && frame < a - 1) {
            cnt = 0;
            frame++;
        }
    }

    frame++;
    int total = 0;
    for (i = 0; i < frame; i++) {
        total += calc_score(a, b, i, &frames[i]);
        printf("[%02d] %d %d %d [score:] %d\n",
               i+1, frames[i].beat_num[0], frames[i].beat_num[1], frames[i].beat_num[2], frames[i].score);
    }

    printf("%d\n", total);

    free(frames);

    return 0;
}
