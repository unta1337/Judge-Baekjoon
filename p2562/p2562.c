// 2562: 최댓값
/*
 * 9개의 서로 다른 자연수가 주어졌을 때, 최댓값과 그 값이 들어온 순서를 구하여라.
 */
// https://www.acmicpc.net/problem/2562

// 메모리: 1112 KB
// 시간: 0 ms
// 코드 길이: 512 bytes
// http://boj.kr/7fb316d13e934b2e8a83ab4f0c16c0cd

#include <stdio.h>
#include <limits.h>

int main(void)
{
    int max = -INT_MAX;
    int max_index = 0;

    for (int i = 0; i < 9; i++)
    {
        int input;
        scanf("%d", &input);

        max = input > max ? max_index = i + 1, input : max;
    }

    printf("%d\n", max);
    printf("%d\n", max_index);

    return 0;
}