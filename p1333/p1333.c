// 1333: 부재중 전화
/*
 * 음악의 나오는 횟수, 음악의 길이, 전화벨이 울리는 주기가 각각 N, L, D로 주어졌을 때, 전화벨을 들을 수 있는 최초 시각을 구하여라.
 */
// https://www.acmicpc.net/problem/1333

// 메모리: 1112 KB
// 시간: 0 ms
// 코드 길이: 1428 bytes
// http://boj.kr/e1f0b8d6f6ab42bf835e0cc87e7259f8

#include <stdio.h>

int main()
{
    int N, L, D;
    scanf("%d %d %d", &N, &L, &D);

    int time = 0;
    int end_time = (L + 5) * N - 5;

    while (1)
    {
        int result = 0;


        // 음악이 나오는 시간 동안 실행.
        if (time < end_time)
        {
            int song_index = time % (L + 5);

            // 현재 시각이 음악이 나오는 구간이면 결과에 -1 적용.
            if (0 <= song_index && song_index < L) 
                result -= 1;
        }

        // 전화벨은 계속해서 울리므로 항상 실행.
        int ring_index = time % D;

        // 현재 시각이 전화벨이 울리는 구간이면 결과에 +1 적용.
        if (0 <= ring_index && ring_index < 1) 
            result += 1;

        // result 변수에 따른 상황.
        // 0: 음악과 전화벨이 둘 다 나오고 울리거나 둘 다 나오지 않고 울리지 않는 구간.
        // -1: 음악만 나오는 구간.
        // +1: 전화벨만 울리는 구간.
        // 전화벨만 울리는 시간에 break.
        if (result == 1)
            break;

        time++;
    }

    printf("%d\n", time);

    return 0;
}
