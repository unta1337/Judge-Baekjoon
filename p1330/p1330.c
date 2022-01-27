// 1330: 두 수 비교하기
/*
 * 두 정수가 주어졌을 때, 이 둘을 비교하라.
 */
// https://www.acmicpc.net/problem/1330

// 메모리: 1116 KB
// 시간: 0 ms
// 코드 길이: 289 bytes
// http://boj.kr/a1f07de0f4214b918f9394a3840db240

#include <stdio.h>

int main(void)
{
    int A, B;
    scanf("%d %d", &A, &B);

    printf("%s\n", A > B ? ">" : A == B ? "==" : "<");

    return 0;
}