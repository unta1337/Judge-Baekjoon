// 1003: 피보나치 함수
/*
 * 피보나치 수열을 재귀적으로 구현한 함수에서 base case인 0과 1이 호출되는 횟수를 구하여라.
 */
// https://www.acmicpc.net/problem/1003

// 메모리: 1116 KB
// 시간: 0 ms
// 코드 길이: 1374 bytes
// http://boj.kr/cc340b2609994463bde2f74034b1ccca

#include <stdio.h>
#include <stdlib.h>

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
    int T;
    scanf("%d", &T);

    int** results = (int**)malloc(T * sizeof(int*));

    for (int i = 0; i < T; i++)
    {
        int N;
        scanf("%d", &N);

        int* result = fibonacci(N);

        results[i] = (int*)malloc(2 * sizeof(int));
        results[i][0] = result[0];
        results[i][1] = result[1];
    }

    for (int i = 0; i < T; i++)
        printf("%d %d\n", results[i][0], results[i][1]);

    for (int i = 0; i < T; i++)
        free(results[i]);
    free(results);

    return 0;
}
