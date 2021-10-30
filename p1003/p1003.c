// 1003: 피보나치 함수
/*
 * 피보나치 수열을 재귀적으로 구현한 함수에서 base case인 0과 1이 호출되는 횟수를 구하여라.
 */
// https://www.acmicpc.net/problem/1003

#include <stdio.h>

const int** fibonacci_rec(int n)
{
    static int zero_count[50] = { 1, 0, };
    static int one_count[50] = { 0, 1, };
    static const int* ret[2] = { zero_count, one_count };

    if (zero_count[n] != 0 || n == 0 || n ==1)
        return ret;

    fibonacci_rec(n - 1);
    fibonacci_rec(n - 2);

    zero_count[n] = zero_count[n - 1] + zero_count[n - 2];
    one_count[n] = one_count[n - 1] + one_count[n - 2];

    return ret;
}

int* fibonacci(int n)
{
    static int ret[2];

    const int** result = fibonacci_rec(n);
    ret[0] = result[0][n];
    ret[1] = result[1][n];

    return ret;
}

int main(void)
{
    int* result = fibonacci(3);
    printf("%d %d\n", result[0], result[1]);

    return 0;
}