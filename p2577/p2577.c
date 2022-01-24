// 2577: 숫자의 개수
/*
 * 세 개의 자연수가 주어졌을 때, 세 수를 곱한 결과의 자릿수에 쓰인 수의 개수를 구하여라.
 */
// https://www.acmicpc.net/problem/2562

// 메모리: 1112 KB
// 시간: 0 ms
// 코드 길이: 534 bytes
// http://boj.kr/3e55d2a1450f417f985648cab48f7821

#include <stdio.h>

int main(void)
{
    int A, B, C;
    scanf("%d %d %d", &A, &B, &C);

    long long int result = A * B * C * 10LL;
    int digit_counts[10] = { 0, };

    while (result /= 10, result > 0)
        digit_counts[result % 10]++;

    for (int i = 0; i < 10; i++)
        printf("%d\n", digit_counts[i]);

    return 0;
}