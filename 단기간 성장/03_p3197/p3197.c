#include <stdio.h>
#include <stdlib.h>

typedef struct grid
{
    int rows;
    int cols;
    char** grid;
} grid_t;

grid_t* create_grid(int rows, int cols);
void delete_grid(grid_t* this);
void print_grid(grid_t* grid);

int main(void)
{
    char test_grid[8][17] =
    {
        { '.', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.', 'X', 'X', '.', 'X', 'X', 'X' },
        { '.', '.', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '.', 'X', 'X', 'X' },
        { '.', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.' },
        { '.', '.', 'X', 'X', 'X', 'X', 'X', '.', 'L', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.' },
        { '.', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.' },
        { 'X', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.', '.', 'X', 'X', 'X', 'X', '.', '.', '.' },
        { '.', '.', 'X', 'X', 'X', 'X', 'X', '.', '.', '.', 'X', 'X', 'X', '.', '.', '.', '.' },
        { '.', '.', '.', '.', 'X', 'X', 'X', 'X', 'X', '.', 'X', 'X', 'X', 'L', '.', '.', '.' }
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