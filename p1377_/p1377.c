// 버블 소트
/*
 * 주어진 버블 소트 알고리즘에 대해서, 해당 알고리즘이 출력하는 값을 구하여라.
 */
// https://www.acmicpc.net/problem/1377

#include <stdio.h>
#include <stdlib.h>

int is_end(int arr[], int size, int index)
{
    for (int i = index + 1; i < size; i++)
    {
        if (arr[i] != -1)
            return 0;
    }

    return 1;
}

int get_unsorted_count(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        int max_index = 0;
        for (int j = 0; j < size; j++)
        {
            if (arr[j] != -1 && arr[j] > arr[max_index])
                max_index = j;
        }

        if (is_end(arr, size, max_index))
            return i;

        arr[max_index] = -1;
    }

    return size - 1;
}

int main()
{
    int N;
    scanf("%d", &N);

    int* arr = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);

    printf("%d\n", get_unsorted_count(arr, N) + 1);

    return 0;
}
