// 1546: 평균
/*
 * 시험 점수가 주어졌을 때, 조작된 평균을 구하여라.
 */
// https://www.acmicpc.net/problem/1436

// 메모리: 1112 KB
// 시간: 0 ms
// 코드 길이: 520 bytes
// http://boj.kr/df0e16fddfba43d4b8066681ec8ae409

#include <stdio.h>
#include <limits.h>

int main(void)
{
    int N;
    scanf("%d", &N);

    int index;
    float avg = 0.0f;
    int max = -INT_MAX;

    for (index = 0; index < N; index++)
    {
        int input;
        avg += (scanf("%d", &input), input);
        max = input > max ? input : max;
    }

    avg *= 100.0f / (index * max);
    printf("%f", avg);

    return 0;
}