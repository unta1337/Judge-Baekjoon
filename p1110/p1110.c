// 1110: 더하기 사이클
/*
 * 어떤 수 N이 주어졌을 때, N의 더하기 사이클을 구하여라.
 * (더하기 사이클은 문제 참조)
 */
// https://www.acmicpc.net/problem/1110

// 메모리: 1112 KB
// 시간: 0 ms
// 코드 길이: 554 bytes
// http://boj.kr/452bc61857ea4439a48fc425ad3d2929

#include <stdio.h>

int main(void)
{
    int N;
    scanf("%d", &N);

    const int original_N = N;       // while 문의 종료 조건 설정.

    int count = 0;
    do
    {
        // 더하기 사이클 수행.
        int upper = N / 10;
        int lower = N % 10;
        int result = upper + lower;

        N = lower * 10 + result % 10;
        count++;
    } while (N != original_N);

    printf("%d\n", count);

    return 0;
}