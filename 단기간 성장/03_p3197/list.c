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

int list_contains(list* this, int* value)
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->arr[i][0] == value[0] && this->arr[i][1] == value[1])
            return 1;
    }

    return 0;
}

void list_print(list* this)
{
    printf("List: \n");
    for (int i = 0; i < this->size; i++)
    {
        printf("\t{ %d, %d }\n", this->arr[i][0], this->arr[i][1]);
    }
    printf("\n");
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
    int size = 10;

    for (int i = 0; i < size; i++)
        list_push(lst, (int[]){ i, i + 1 });

    list_print(lst);

    for (int i = 0; i < size; i++)
        printf("{ %d, %d } is %s.\n", i, i + 1, list_contains(lst, (int[]){ i, i + 1 }) ? "exits" : "not exits");

    printf("\n");

    for (int i = 0; i < size; i++)
        printf("{ %d, %d } is %s.\n", i + 1, i, list_contains(lst, (int[]){ i + 1, i }) ? "exits" : "not exits");

    return 0;
}
