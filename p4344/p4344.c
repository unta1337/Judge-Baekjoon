// 4344: 평균은 넘겠지
/*
 * 학생의 수와 점수가 주어졌을 때, 학생들에게 슬픈 진실을 알려주어라.
 */
// https://www.acmicpc.net/problem/2798

// 메모리: 1116 KB
// 시간: 0 ms
// 코드 길이: 829 bytes
// http://boj.kr/c4f539c4b49d458daf0721d25b6da2e7

#include <stdio.h>
#include <stdlib.h>

float get_avg(int* arr, int size)
{
    float avg = 0.0f;
    for (int i = 0; i < size; i++) avg += arr[i];

    return avg / size;
}

int main(void)
{
    int C;
    scanf("%d", &C);

    for (int i = 0 ; i < C; i++)
    {
        int N;
        scanf("%d", &N);

        int* scores = (int*)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) scanf("%d", &scores[j]);
        float avg = get_avg(scores, N);

        int above_avg = 0;
        for (int j = 0; j < N; j++) above_avg += scores[j] > avg;
        printf("%.3f%%\n", (float)above_avg / N * 100);

        free(scores);
    }

    return 0;
}