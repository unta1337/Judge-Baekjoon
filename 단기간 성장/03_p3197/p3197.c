#include <stdio.h>
#include <stdlib.h>

// 백조의 호수의 그리드 구조체.
typedef struct grid
{
    int rows;
    int cols;
    char** grid;
} grid_t;

grid_t* create_grid(int rows, int cols);
void delete_grid(grid_t* this);
void print_grid(grid_t* grid);

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
void q_pop(queue_t* this);
void q_print(queue_t* this);

// 호수 갱신용 함수.
char get_next_cell(grid_t* grid, int location[2]);      // 특정 셀의 다음 상태를 반환.
void next_grid(grid_t* grid);                           // 모든 셀을 다음 상태로 갱신.

int main(void)
{
    char test_grid[8][17] =
    {
        { '.', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.', 'X', 'X', '.', 'X', 'X', 'X' },
        { '.', '.', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '.', 'X', 'X', 'X' },
        { '.', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.' },
        { '.', '.', 'X', 'X', 'X', 'X', 'X', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.' },
        { '.', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.' },
        { 'X', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.', '.', 'X', 'X', 'X', 'X', '.', '.', '.' },
        { '.', '.', 'X', 'X', 'X', 'X', 'X', '.', '.', '.', 'X', 'X', 'X', '.', '.', '.', '.' },
        { '.', '.', '.', '.', 'X', 'X', 'X', 'X', 'X', '.', 'X', 'X', 'X', '.', '.', '.', '.' }
    };

    grid_t* grid = create_grid(8, 17);
    for (int row = 0; row < grid->rows; row++)
    {
        for (int col = 0; col < grid->cols; col++)
        {
            grid->grid[row][col] = test_grid[row][col];
        }
    }

    print_grid(grid);

    next_grid(grid);
    printf("\n");

    print_grid(grid);

    next_grid(grid);
    printf("\n");

    print_grid(grid);

    delete_grid(grid);

    return 0;
}

grid_t* create_grid(int rows, int cols)
{
    grid_t* this = (grid_t*)malloc(sizeof(grid_t));

    this->rows = rows;
    this->cols = cols;
    this->grid = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++)
        this->grid[i] = (char*)malloc(cols * sizeof(char));

    return this;
}

void delete_grid(grid_t* this)
{
    for (int i = 0; i < this->rows; i++)
        free(this->grid[i]);
    free(this->grid);
    free(this);
}

void print_grid(grid_t* grid)
{
    for (int row = 0; row < grid->rows; row++)
    {
        for (int col = 0; col < grid->cols; col++)
            printf("%c", grid->grid[row][col]);
        printf("\n");
    }
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

void q_pop(queue_t* this)
{
    if (this->size == 0)
        return;

    free(this->pairs[--this->size]);

    if (this->size < this->capacity / 2)
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

char get_next_cell(grid_t* grid, int location[2])
{
    int row = location[0], col = location[1];

    char cell = grid->grid[row][col];
    if (cell != 'X')
        return cell;

    for (int row_diff = -1; row_diff <= 1; row_diff++)
    {
        int row_index = row + row_diff;
        if (!(0 <= row_index && row_index < grid->rows))
            continue;

        if (grid->grid[row_index][col] == '.')
            return '.';
    }

    for (int col_diff = -1; col_diff <= 1; col_diff++)
    {
        int col_index = col + col_diff;
        if (!(0 <= col_index && col_index < grid->cols))
            continue;

        if (grid->grid[row][col_index] == '.')
            return '.';
    }

    return 'X';
}

void next_grid(grid_t* grid)
{
    grid_t* next = create_grid(grid->rows, grid->cols);
    for (int row = 0; row < grid->rows; row++)
        for (int col = 0; col < grid->cols; col++)
            next->grid[row][col] = get_next_cell(grid, (int[2]){ row, col });

    for (int row = 0; row < grid->rows; row++)
        for (int col = 0; col < grid->cols; col++)
            grid->grid[row][col] = next->grid[row][col];
    
    delete_grid(next);
}