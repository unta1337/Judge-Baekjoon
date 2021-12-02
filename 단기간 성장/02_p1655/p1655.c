#include <stdio.h>

#include "priority_queue.h"

int main()
{
    priority_queue* max_heap = create_priority_queue(max);
    priority_queue* min_heap = create_priority_queue(min);

    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        int M;
        scanf("%d", &M);

        if (max_heap->size == 0)
        {
            priority_queue_push(max_heap, M);
        }
        else
        {
            if (max_heap->size > min_heap->size)
                priority_queue_push(min_heap, M);
            else
                priority_queue_push(max_heap, M);

            if (priority_queue_top(max_heap) > priority_queue_top(min_heap))
            {
                int max_top = priority_queue_pop(max_heap);
                int min_top = priority_queue_pop(min_heap);

                priority_queue_push(max_heap, min_top);
                priority_queue_push(min_heap, max_top);
            }
        }

        printf("%d\n", priority_queue_top(max_heap));
    }

    delete_priority_queue(max_heap);
    delete_priority_queue(min_heap);

    return 0;
}
