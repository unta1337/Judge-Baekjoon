// 8958: OX퀴즈
/*
 * OX 퀴즈의 정답 현황이 주어졌을 때, 점수의 총합을 구하여라.
 */
// https://www.acmicpc.net/problem/7568

// 메모리: 1112 KB
// 시간: 0 ms
// 코드 길이: 550 bytes
// http://boj.kr/55108737131d4a95a59f9b76cd644cdf

#include <stdio.h>

int main(void)
{
    int N;
    scanf("%d", &N);
    fflush(stdin);

    for (int i = 0; i < N; i++)
    {
        char input[81] = "";
        scanf("%s", input);

        int score = 0, score_gain = 1;
        for (int i = 0; input[i] != '\0'; i++)
            score += input[i] == 'O' ? score_gain++ : (score_gain = 1, 0);
        printf("%d\n", score);
    }

    return 0;
}