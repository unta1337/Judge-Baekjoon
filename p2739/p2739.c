// 2739: 구구단
/*
 * 구구단의 n단을 출력하시오.
 */
// https://www.acmicpc.net/problem/2739

// 메모리: 1112 KB
// 시간: 0 ms
// 코드 길이: 274 bytes
// http://boj.kr/2a67cc6e8da44ef4844d08b0bfe0ab3d

#include <stdio.h>

int main(void)
{
    int N;
    scanf("%d", &N);

    for (int i = 1; i <= 9; i++)
        printf("%d * %d = %d\n", N, i, N * i);

    return 0;
}