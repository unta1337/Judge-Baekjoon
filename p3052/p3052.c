// 3052: 나머지
/*
 * 자연수 열 개가 주어졌을 때, 해당 자연수들을 42로 나눴을 때의 서로 다른 나머지의 개수를 구하여라.
 */
// https://www.acmicpc.net/problem/3052

// 메모리: 1112 KB
// 시간: 0 ms
// 코드 길이: 604 bytes
// http://boj.kr/b3445275c4b147fbb9b9851a0724ccf8        

#include <stdio.h>

int main(void)
{
    int unique_remainder[42] = { 0, };

    for (int i = 0; i < 10; i++)
    {
        int input;
        scanf("%d", &input);

        unique_remainder[input % 42]++;
    }

    int unique_remainder_count = 0;
    for (int i = 0; i < 42; i++)
        unique_remainder_count += unique_remainder[i] > 0;
    printf("%d", unique_remainder_count);

    return 0;
}