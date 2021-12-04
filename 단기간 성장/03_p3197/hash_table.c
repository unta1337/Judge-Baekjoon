#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
    int** arr;
    int size;
    int capacity;
} list;

int list_contains(list* this, int* value)
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->arr[i][0] == value[0] && this->arr[i][1] == value[1])
            return 1;
    }

    return 0;
}

void list_push(list* this, int value1, int value2)
{
    if (this->size == this->capacity)
    {
        this->capacity *= 2;
        this->arr = (int**)realloc(this->arr, this->capacity * sizeof(int*));
    }

    this->arr[this->size] = (int*)malloc(2 * sizeof(int));
    this->arr[this->size][0] = value1;
    this->arr[this->size][1] = value2;

    this->size++;
}

void list_print(list* this)
{
    if (this->size == 0)
        return;

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

typedef struct hash_table
{
    list** table;
    int size;

    int (*hash)(struct hash_table* this, int* value);
} hash_table;

int hash(hash_table* this, int* value)
{
    int hash = value[0] * 37633 + value[1] * 10093 + 22198;
    hash = hash < 0 ? -hash : hash;

    return hash % this->size;
}

void hash_table_push(hash_table* this, int value1, int value2)
{
    int* value = (int*)malloc(2 * sizeof(int));
    value[0] = value1;
    value[1] = value2;

    int index = this->hash(this, value);

    if (list_contains(this->table[index], value))
            return;
    list_push(this->table[index], value1, value2);

    free(value);
}

int hash_table_contains(hash_table* this, int* value)
{
    int index = this->hash(this, value);
    return list_contains(this->table[index], value);
}

void hash_table_print(hash_table* this)
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->table[i]->size != 0)
            printf("# %d ", i);
        list_print(this->table[i]);
    }
}

hash_table* create_hash_table(int (*hash)(hash_table* this, int* value))
{
    hash_table* this = (hash_table*)malloc(sizeof(hash_table));

    int default_size = 1000000;

    this->table = (list**)malloc(default_size * sizeof(list*));
    for (int i = 0; i < default_size; i++)
        this->table[i] = create_list();
    this->size = default_size;

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

    int size = 10;

    for (int i = 0; i < size; i++)
        hash_table_push(table, i, i + 1);

    hash_table_print(table);

    for (int i = 0; i < size; i++)
        printf("{ %d, %d } %d\n", i, i + 1, hash_table_contains(table, (int[]){ i, i + 1 }));
    printf("\n");

    for (int i = 0; i < size; i++)
        printf("{ %d, %d } %d\n", i + 1, i, hash_table_contains(table, (int[]){ i + 1, i }));

    delete_hash_table(table);

    return 0;
}
