#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_grid(char** grid, int rows, int cols)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 17; j++)
            printf("%c", grid[i][j]);
        printf("\n");
    }
}

int* find_swan(char** grid, int rows, int cols)
{
    static int result[2];

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            if (grid[row][col] == 'L')
            {
                result[0] = row;
                result[1] = col;

                return (int*)&result;
            }
        }
    }

    return NULL;
}

int is_melted(char** grid, int rows, int cols)
{
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            if (grid[row][col] == 'X')
                return 0;
        }
    }

    return 1;
}

int am_i_melt(char** grid, int rows, int cols, int row, int col)
{
    if (grid[row][col] == '.')
        return 1;
    if (grid[row][col] == 'L')
        return 0;

    for (int row_diff = -1; row_diff <= 1; row_diff++)
    {
        int row_index = row + row_diff;

        if (row_index < 0 || row_index >= rows)
            continue;

        if (grid[row_index][col] == '.')
            return 1;
    }

    for (int col_diff = -1; col_diff <= 1; col_diff++)
    {
        int col_index = col + col_diff;

        if (col_index < 0 || col_index >= cols)
            continue;

        if (grid[row][col_index] == '.')
            return 1;
    }

    return 0;
}

void next_iteration(char** grid, int rows, int cols)
{
    char** next_grid = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++)
    {
        next_grid[i] = (char*)malloc(cols * sizeof(char));
        memcpy(next_grid[i], grid[i], cols * sizeof(char));
    }

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            if (am_i_melt(grid, rows, cols, row, col))
                next_grid[row][col] = '.';
        }
    }

    for (int i = 0; i < rows; i++)
    {
        memcpy(grid[i], next_grid[i], cols * sizeof(char));
        free(next_grid[i]);
    }
    free(next_grid);
}

int main()
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

    int rows = 8;
    int cols = 17;

    char** grid = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++)
        grid[i] = test_grid[i];

    int* swan = find_swan(grid, 8, 17);
    printf("Swan: [%d][%d]\n\n", swan[0], swan[1]);

    while (!is_melted(grid, rows, cols))
    {
        print_grid(grid, 8, 17);
        printf("\n");

        next_iteration(grid, 8, 17);
    }

    print_grid(grid, 8, 17);

    free(grid);

    return 0;
}
