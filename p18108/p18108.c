// 18108: 1988년생인 내가 태국에서는 2541년생?!
/*
 * 불기 연도에 대응하는 서기 연도를 구하여라.
 */
// https://www.acmicpc.net/problem/18108

// 메모리: 1112 KB
// 시간: 0 ms
// 코드 길이: 341 bytes
// http://boj.kr/522277e4b6e544998a283e9bbfa586b6

#include <stdio.h>

int main(void)
{
    const int ref = 2541 - 1998;

    int year;
    scanf("%d", &year);
    year -= ref;

    printf("%d\n", year);

    return 0;
}