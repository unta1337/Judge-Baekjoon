#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "priority_queue.h"

int main()
{
    srand((unsigned int)time(NULL));

    priority_queue* max_heap = create_priority_queue(max);
    int size = 100;

    for (int i = 0; i < 100; i++)
        priority_queue_push(max_heap, rand() % size);

    for (int i = 0; i < 100; i++)
        printf("%d\n", priority_queue_pop(max_heap));

    return 0;
}
