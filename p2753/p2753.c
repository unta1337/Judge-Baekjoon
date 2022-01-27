// 2753: 윤년
/*
 * 연도가 주어졌을 때, 윤년 여부를 구하여라.
 */
// https://www.acmicpc.net/problem/2753

// 메모리: 1112 KB
// 시간: 0 ms
// 코드 길이: 306 bytes
// http://boj.kr/9fe6f03ff5c84468a07c540c54815104

#include <stdio.h>

int main(void)
{
    int year;
    scanf("%d", &year);

    printf("%d\n", (!(year % 4) && year % 100) || !(year % 400));

    return 0;
}