// 10818: 최소, 최대
/*
 * n개의 정수가 주어질 때, 최솟값과 최댓값을 구하여라.
 */
// https://www.acmicpc.net/problem/10818

// 메모리: 1112 KB
// 시간: 184 ms
// 코드 길이: 510 bytes
// http://boj.kr/a88011746d764671b02bdeaf139c3b2c

#include <stdio.h>
#include <limits.h>

int main(void)
{
    int min = INT_MAX;
    int max = -INT_MAX;

    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        int input;
        scanf("%d", &input);

        min = input < min ? input : min;
        max = input > max ? input : max;
    }

    printf("%d %d", min, max);

    return 0;
}