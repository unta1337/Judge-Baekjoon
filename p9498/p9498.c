// 9498: 시험 성적
/*
 * 시험 점수가 주어졌을 때, 성적을 구하여라.
 */
// https://www.acmicpc.net/problem/9498

// 메모리: 1116 KB
// 시간: 0 ms
// 코드 길이: 511 bytes
// http://boj.kr/dc847922705347f49c4703a09084a9bc

#include <stdio.h>

int main(void)
{
    int score;
    scanf("%d", &score);

    if (score >= 90)
    {
        printf("A\n");
    }
    else if (score >= 80)
    {
        printf("B\n");
    }
    else if (score >= 70)
    {
        printf("C\n");
    }
    else if (score >= 60)
    {
        printf("D\n");
    }
    else
    {
        printf("F\n");
    }

    return 0;
}