// 1655: 가운데를 말해요
/*
 * 원소가 한 개씩 연속해서 주어지는 임의의 배열에 대해, 해당 배열의 중간값을 구하시오.
 */
// https://www.acmicpc.net/problem/1655

// 메모리: 1796 KB
// 시간: 44 ms
// 코드 길이: 5919 bytes
// http://boj.kr/8707185ad34b4802be7c28c081654c27

#include <stdio.h>
#include <stdlib.h>

// 우선순위 큐.
typedef struct priority_queue
{
    int* heap;
    int size;
    int capacity;

    int (*comp)(int p, int q);
} priority_queue;

// min_heap 비교 함수.
int comp_min(int p, int q)
{
    return p < q;
}

// max_heap 비교 함수.
int comp_max(int p, int q)
{
    return p > q;
}

void priority_queue_reheap_down(priority_queue* this)
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

void priority_queue_push(priority_queue* this, int value)
{
    // 공간이 부족하면 확장.
    if (this->size == this->capacity)
    {
        this->capacity *= 2;
        this->heap = (int*)realloc(this->heap, this->capacity * sizeof(int));
    }

    // 최초 원소 삽입.
    if (this->size == 0)
    {
        this->heap[0] = value;
    }

    // 나머지 경우 삽입.
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

int priority_queue_pop(priority_queue* this)
{
    if (this->size == 0)
        return 0;

    // 공간이 낭비되면 축소.
    if (this->capacity > 1 && this->size == this->capacity / 2)
    {
        this->capacity /= 2;
        this->heap = (int*)realloc(this->heap, this->capacity * sizeof(int));
    }

    // 반환값 저장.
    int ret = this->heap[0];

    // reheap_down.
    if (this->size != 0)
    {
        this->heap[0] = this->heap[this->size - 1];
        priority_queue_reheap_down(this);
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

int main()
{
    // 중간값을 취하기 위해 입력을 큰 부분(min_heap에 저장)과 작은 부분(max_heap에 저장)으로 나눔.
    // max_heap에 들어가는 원소가 하나 더 많게 구성.
    /*
     * max_heap [ 3, 2, 1, 0 ]
     * min_heap [ 4, 5, 6 ]
     * => max_heap(입력 중 작은 부분)의 최댓값이 전체 입력의 중간값이 됨.
     * 
     * max_heap [ 3, 2, 1 ]
     * min_heap [ 4, 5, 6 ]
     * => 입력의 개수가 짝수일 때도 중간 두 개의 값 중 더 작은 값을 취하므로 max_heap의 최솟값이 전체 입력의 중간값이 됨.
     */
    priority_queue* max_heap = create_priority_queue(&comp_max);
    priority_queue* min_heap = create_priority_queue(&comp_min);

    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        int M;
        scanf("%d", &M);

        // 최초 입력은 max_heap에 저장. (max_heap의 원소의 개수가 min_heap의 원소의 개수보다 1 커야 하므로)
        if (max_heap->size == 0)
        {
            priority_queue_push(max_heap, M);
        }
        else
        {
            // max_heap의 원소의 개수가 더 많으면 min_heap에 원소를 삽입하여 개수를 맞춰줌.
            if (max_heap->size > min_heap->size)
                priority_queue_push(min_heap, M);
            
            // max_heap의 원소의 개수가 min_heap의 원소의 개수보다 1 많도록 유지.
            else
                priority_queue_push(max_heap, M);

            // max_heap에는 작은 입력이, min_heap에는 큰 입력이 들어가야 함.
            // 이 속성이 위배되었을 때 이를 교정하는 작업이 필요함.
            /*
             * max_heap [ 4, 2, 1 ]
             * min_heap [ 3, 5, 6 ]
             * => 위와 같은 경우, 4과 3의 위치 변경이 필요.
             */
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