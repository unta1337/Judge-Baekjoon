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

typedef struct hash_table
{
    list** table;
    int size;

    int (*hash)(struct hash_table* this, int value);
} hash_table;

int hash(hash_table* this, int value)
{
    int hash = value % this->size;

    return hash;
}

void hash_table_push(hash_table* this, int* value)
{
    int index = this->hash(this, value[0]);

    list_push(this->table[index], value);
}

hash_table* create_hash_table(int (*hash)(hash_table* this, int value))
{
    hash_table* this = (hash_table*)malloc(sizeof(hash_table));

    this->table = (list**)malloc(32 * sizeof(list*));
    for (int i = 0; i < 32; i++)
        this->table[i] = create_list();
    this->size = 32;

    this->hash = hash;

    return this;
}

void delete_hash_table(hash_table* this)
{
    for (int i = 0; i < this->size; i++)
        delete_list(this->table[i]);
    free(this->table);
    free(this);
}

int main()
{
    hash_table* table = create_hash_table(&hash);

    hash_table_push(table, (int[]){ 1, 2 });
    hash_table_push(table, (int[]){ 1, 2 });

    printf("%d %d\n", table->table[table->hash(table, 1)]->arr[0][0], table->table[table->hash(table, 1)]->arr[0][1]);
    printf("%d %d\n", table->table[table->hash(table, 1)]->arr[1][0], table->table[table->hash(table, 1)]->arr[1][1]);

    return 0;
}
