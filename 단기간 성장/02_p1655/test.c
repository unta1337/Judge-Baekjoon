#include <stdio.h>
#include <stdlib.h>

#include "priority_queue.h"

int main()
{
    priority_queue* heap = create_priority_queue(max);

    int size = 10000;

    for (int i = 0; i < size; i++)
    {
        printf("%d\n", i + 1);

        priority_queue_push(heap, rand() % size);
    }

    printf("================\n");

    for (int i = 0; i < size; i++)
        printf("%d\n", priority_queue_pop(heap)); 

    return 0;
}
