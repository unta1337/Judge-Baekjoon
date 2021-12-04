#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
    int** arr;
    int size;
    int capacity;
} list;

void list_push(list* this, int* value)
{
    if (this->size == this->capacity)
    {
        this->capacity *= 2;
        this->arr = (int**)realloc(this->arr, this->capacity * sizeof(int*));
    }

    this->arr[this->size] = (int*)malloc(2 * sizeof(int));
    this->arr[this->size][0] = value[0];
    this->arr[this->size][1] = value[1];

    this->size++;
}

list* create_list()
{
    list* this = (list*)malloc(sizeof(list));

    this->arr = (int**)calloc(1, sizeof(int*));
    this->size = 0;
    this->capacity = 1;

    return this;
}

void delete_list(list* this)
{
    for (int i = 0; i < this->size; i++)
        free(this->arr[i]);
    free(this->arr);
    free(this);
}

int main()
{
    list* lst = create_list();

    for (int i = 0; i < 100; i++)
        list_push(lst, (int[]){ i, i + 1 });

    for (int i = 0; i < 100; i++)
        printf("%d %d\n", lst->arr[i][0], lst->arr[i][1]);

    return 0;
}
