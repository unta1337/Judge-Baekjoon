#ifndef _P_QUEUE_H
#define _P_QUEUE_H

#include <stdlib.h>

typedef struct priority_queue
{
    int* heap;
    int size;
    int capacity;

    int (*comp)(int p, int q);
} priority_queue;

int max(int p, int q)
{
    return p > q;
}

int min(int p, int q)
{
    return p < q;
}

void priority_queue_push(priority_queue* this, int value)
{
    if (this->size == this->capacity)
    {
        this->capacity *= 2;
        this->heap = (int*)realloc(this->heap, this->capacity * sizeof(int));
    }

    if (this->size == 0)
    {
        this->heap[0] = value;
    }
    else
    {
        int index = this->size;
        int parent_index = (index - 1) / 2;

        this->heap[index] = value;

        while (index > 0 && this->comp(this->heap[index], this->heap[parent_index]))
        {
            int temp = this->heap[index];
            this->heap[index] = this->heap[parent_index];
            this->heap[parent_index] = temp;

            index = parent_index;
            parent_index = (index - 1) / 2;
        }
    }

    this->size++;
}

void reheap_down(priority_queue* this)
{
    int index = 0;
    int left_child_index = index * 2 + 1;
    int right_child_index = index * 2 + 2;

    while (left_child_index < this->size)
    {
        int next_index = index;
        if (right_child_index < this->size)
        {
            if (this->comp(this->heap[left_child_index], this->heap[index]) || this->comp(this->heap[right_child_index], this->heap[index]))
                next_index = this->comp(this->heap[left_child_index], this->heap[right_child_index]) ? left_child_index : right_child_index;
            else
                break;
        }
        else
        {
            if (this->comp(this->heap[left_child_index], this->heap[index]))
                next_index = left_child_index;
            else
                break;
        }

        int temp = this->heap[index];
        this->heap[index] = this->heap[next_index];
        this->heap[next_index] = temp;

        index = next_index;
        left_child_index = index * 2 + 1;
        right_child_index = index * 2 + 2;
    }
}

int priority_queue_pop(priority_queue* this)
{
    if (this->size == 0)
        return 0;

    if (this->capacity > 1 && this->size == this->capacity)
    {
        this->capacity /= 2;
        this->heap = (int*)realloc(this->heap, this->capacity * sizeof(int));
    }

    int ret = this->heap[0];

    if (this->size == 1)
    {
    }
    else
    {
        this->heap[0] = this->heap[this->size - 1];
        reheap_down(this);
    }

    this->size--;

    return ret;
}

int priority_queue_top(priority_queue* this)
{
    if (this->size == 0)
        return 0;

    return this->heap[0];
}

priority_queue* create_priority_queue(int (*comp)(int p, int q))
{
    priority_queue* this = (priority_queue*)calloc(1, sizeof(priority_queue));

    this->heap = (int*)calloc(1, sizeof(int));
    this->size = 0;
    this->capacity = 1;

    this->comp = comp;

    return this;
}

void delete_priority_queue(priority_queue* this)
{
    free(this->heap);
    free(this);
}

#endif
