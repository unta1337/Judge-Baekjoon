#include <stdio.h>

#include "arrtool.h"

int main()
{
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    int size = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    rotate_array(arr, size, 1, 4);
    rotate_array(arr, size, 3, 5);

    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
