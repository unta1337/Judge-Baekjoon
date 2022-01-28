#include <stdio.h>
#include <stdlib.h>

// BFS 로직을 위한 큐 구조체.
typedef struct queue
{
    int size;
    int capacity;
    int** pairs;
} queue_t;

queue_t* create_queue();
void delete_queue(queue_t* this);
void q_push(queue_t* this, int pair[2]);
void q_pop(queue_t* this, int ret[2]);
void q_print(queue_t* this);

int main()
{
    int temp[2];
    queue_t* q = create_queue();

    for (int i = 0; i < 50; i++)
        q_push(q, (int[2]){ i, i + 1 });
    //q_print (q);

    for (int i = 0; i < 10; i++)
        q_pop(q, temp);
    q_print (q);

    return 0;
}

queue_t* create_queue()
{
    queue_t* this = (queue_t*)malloc(sizeof(queue_t));

    this->size = 0;
    this->capacity = 1;
    this->pairs = (int**)malloc(sizeof(int**));

    return this;
}

void delete_queue(queue_t* this)
{
    for (int i = 0; i < this->size; i++)
        free(this->pairs[i]);
    free(this->pairs);
    free(this);
}

void q_push(queue_t* this, int pair[2])
{
    if (this->size == this->capacity)
    {
        this->capacity *= 2;
        this->pairs = (int**)realloc(this->pairs, this->capacity * sizeof(int*));
    }

    this->pairs[this->size] = (int*)malloc(2 * sizeof(int*));
    this->pairs[this->size][0] = pair[0];
    this->pairs[this->size][1] = pair[1];

    this->size++;
}

void q_pop(queue_t* this, int ret[2])
{
    if (this->size == 0)
        return;

    ret[0] = this->pairs[0][0];
    ret[1] = this->pairs[0][1];

    for (int i = 1; i < this->size; i++)
    {
        this->pairs[i - 1][0] = this->pairs[i][0];
        this->pairs[i - 1][1] = this->pairs[i][1];
    }
    this->size--;

    if (this->size > 1 && this->size < this->capacity / 2)
    {
        this->capacity /= 2;
        this->pairs = (int**)realloc(this->pairs, this->capacity * sizeof(int*));
    }
}

void q_print(queue_t* this)
{
    for (int i = 0; i < this->size; i++)
        printf("(%d, %d) \n", this->pairs[i][0], this->pairs[i][1]);
}