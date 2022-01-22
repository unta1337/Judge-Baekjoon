#include <iostream>
#include <vector>

void print_grid(std::vector<std::vector<char>>& grid)
{
    for (std::vector<char> col : grid)
    {
        for (char elem : col)
            std::cout << elem;
        std::cout << "\n";
    }
}

// 그리드 위 특정 셀의 다음 상태 반환.
char get_next_state(std::vector<std::vector<char>>& grid, int row, int col)
{
    // 얼음이 아닌 경우, 녹음 여부를 확인할 필요가 없으므로 해당 셀에 있는 내용 반환.
    if (grid[row][col] != 'X')
        return grid[row][col];

    // 열 방향
    for (int offset = -1; offset <= 1; offset++)
    {
        int index = col + offset;
        if (index < 0 || index >= grid[row].size())
            continue;

        if (grid[row][index] == '.')
            return '.';
    }

    // 행 방향
    for (int offset = -1; offset <= 1; offset++)
    {
        int index = row + offset;
        if (index < 0 || index >= grid.size())
            continue;

        if (grid[index][col] == '.')
            return '.';
    }

    // 어느 곳에도 해당되지 않으면 얼음이 녹지 않는다.
    return 'X';
}

// 그리드 전체를 다음 세대로 업데이트.
void get_next_iteration(std::vector<std::vector<char>>& grid)
{
    // 임시 그리드를 생성하여 다음 세대 그리드 작성.
    std::vector<std::vector<char>> next_grid;
    for (int row = 0; row < grid.size(); row++)
    {
        std::vector<char> new_col;
        for (int col = 0; col < grid[row].size(); col++)
            new_col.push_back(get_next_state(grid, row, col));
        next_grid.push_back(new_col);
    }

    // 기존 그리드를 다음 그리드로 업데이트.
    for (int row = 0; row < grid.size(); row++)
        for (int col = 0; col < grid[row].size(); col++)
            grid[row][col] = next_grid[row][col];
}

int main(void)
{
    std::vector<std::vector<char>> test_grid =
    {{
        { '.', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.', 'X', 'X', '.', 'X', 'X', 'X' },
        { '.', '.', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '.', 'X', 'X', 'X' },
        { '.', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.' },
        { '.', '.', 'X', 'X', 'X', 'X', 'X', '.', 'L', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.' },
        { '.', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.' },
        { 'X', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.', '.', 'X', 'X', 'X', 'X', '.', '.', '.' },
        { '.', '.', 'X', 'X', 'X', 'X', 'X', '.', '.', '.', 'X', 'X', 'X', '.', '.', '.', '.' },
        { '.', '.', '.', '.', 'X', 'X', 'X', 'X', 'X', '.', 'X', 'X', 'X', 'L', '.', '.', '.' }
    }};

    print_grid(test_grid);

    get_next_iteration(test_grid);

    std::cout << "\n";

    print_grid(test_grid);

    return 0;
}