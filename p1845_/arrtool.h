#ifndef _ARR_TOOL_H
#define _ARR_TOOL_H

#include <stdio.h>
#include <stdlib.h>

void rotate_array(int arr[], int size, int begin_, int end_)
{
    int begin = begin_ - 1;
    int end = end_ - 1;

    if (!(0 <= begin && begin < size))
    {
        printf("rotate_array: invalid begin index. (invalid index: %d)\n", begin);
        exit(1);
    }
    if (!(0 <= end && end < size))
    {
        printf("rotate_array: invalid end index. (invalid index: %d)\n", end);
        exit(1);
    }
    if (!(begin <= end))
    {
        printf("rotate_array: invalid range. (invalid range: [%d, %d])\n", begin, end);
        exit(1);
    }

    while (begin <= end)
    {
        int temp = -arr[begin];
        arr[begin] = -arr[end];
        arr[end] = temp;

        begin++;
        end--;
    }
}

#endif
