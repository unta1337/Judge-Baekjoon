// 1152: 단어의 개수
/*
 * 주어진 문자열에 포함된 단어의 개수를 구하여라.
 */
// https://www.acmicpc.net/problem/1152

// 메모리: 1116 KB
// 시간: 16 ms
// 코드 길이: 592 bytes
// http://boj.kr/368c2ad8b8b342a9ac5a928004878a90

#include <stdio.h>

int main(void)
{
    char current_input = getchar();
    char next_input = getchar();
    if (current_input == ' ' && next_input == '\n') { printf("0\n"); return 0; }

    int count = 0;
    while (next_input != '\n')
    {
        count += current_input != ' ' && next_input == ' ';

        current_input = next_input;
        next_input = getchar();
    }

    printf("%d\n", count + (current_input != ' '));

    return 0;
}