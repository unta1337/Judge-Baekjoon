// 12865: 평범한 배낭
/*
 * 물품의 무게와 가치, 배낭의 최대 적재 용량이 주어졌을 때, 가능한 가치의 최댓값을 구하여라.
 */
// https://www.acmicpc.net/problem/12865

#include <stdio.h>
#include <stdlib.h>

typedef struct item
{
    int weight;
    int value;
} item;

int main()
{
    // 입력.
    int N, K;
    scanf("%d %d", &N, &K);

    // DP.
    int** table = (int**)calloc(N + 1, sizeof(int*));
    for (int i = 0; i <= N; i++)
        table[i] = (int*)calloc(K + 1, sizeof(int));

    // 사용자 입력.
    item** items = (item**)calloc(N + 1, sizeof(item*));
    items[0] = (item*)calloc(1, sizeof(item));
    for (int i = 1; i <= N; i++)
    {
        int W, V;
        scanf("%d %d", &W, &V);

        items[i] = (item*)calloc(1, sizeof(item));
        items[i]->weight = W;
        items[i]->value = V;
    }

    // 주요 로직.
    int max_value = 0;
    for (int item_index = 1; item_index <= N; item_index++)
    {
        for (int weight_index = 1; weight_index <= K; weight_index++)
        {
            // 가방에 물건을 넣을 수 있는 경우.
            if (items[item_index]->weight <= weight_index)
            {
                // 현재 물건의 가치 + 남은 공간에 담을 수 있는 최대 가치.
                int current_max_value = items[item_index]->value + table[item_index - 1][weight_index - items[item_index]->weight];

                // 이전 선택 중 최적의 경우.
                int alt_max_value = table[item_index - 1][weight_index];

                // 위의 두 경우 중 더 나은 선택을 대입.
                table[item_index][weight_index] = current_max_value > alt_max_value ? current_max_value : alt_max_value;
            }

            // 가방에 물건을 넣을 수 없는 경우.
            else
            {
                // 이전 선택 중 최적의 경우를 대입.
                int alt_max_value = table[item_index - 1][weight_index];
                table[item_index][weight_index] = alt_max_value;
            }

            max_value = table[item_index][weight_index] > max_value ? table[item_index][weight_index] : max_value;
        }
    }

    // 출력.
    printf("%d\n", max_value);

    // 동적할당 해제.
    for (int i = 0; i <= N; i++)
        free(items[i]);
    free(items);
    for (int i = 0; i <= N; i++)
        free(table[i]);
    free(table);

    return 0;
}