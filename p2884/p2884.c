// 2884: 알람 시계
/*
 * 특정한 시각이 주어졌을 때, 이를 45분 앞당겨 알람이 울릴 시각을 구하여라.
 */
// https://www.acmicpc.net/problem/2884

// 메모리: 1112 KB
// 시간: 0 ms
// 코드 길이: 371 bytes
// http://boj.kr/36b256aadb4d42c6a7c104cb2c219a1f

#include <stdio.h>

int main(void)
{
    int h, m;
    scanf("%d %d", &h, &m);

    m -= 45;
    h = m < 0 ? m = 60 + m, h - 1 < 0 ? 23 : h - 1 : h;

    printf("%d %d\n", h, m);

    return 0;
}