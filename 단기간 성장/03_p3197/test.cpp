#include <iostream>
#include <queue>
#include <utility>
#include <vector>

void print_grid(std::vector<std::vector<char>> grid)
{
    for (std::vector<char> row : grid)
    {
        for (char col : row)
            std::cout << col;
        std::cout << "\n";
    }
}

std::pair<int, int> find_swan(std::vector<std::vector<char>>& grid)
{
    for (int row = 0; row < grid.size(); row++)
        for (int col = 0; col < grid[row].size(); col++)
            if (grid[row][col] == 'L')
                return std::pair<int, int>{ row, col };
    return std::pair<int, int>{ -1, -1 };
}

void next_grid(std::vector<std::vector<char>>& grid, std::queue<std::pair<int, int>>& starts)
{
    std::queue<std::pair<int, int>> next_water;

    int iterations = starts.size();
    for (int i = 0; i < iterations; i++)
    {
        std::pair<int, int> current_cell = starts.front();
        starts.pop();

        if (grid[current_cell.first][current_cell.second] != '.')
            continue;

        for (int row_diff = -1; row_diff <= 1; row_diff++)
        {
            int row_index = current_cell.first + row_diff;

            if (!(0 <= row_index && row_index < grid.size()))
                continue;
            if (grid[row_index][current_cell.second] == 'X')
            {
                next_water.push(std::pair<int, int>{ row_index, current_cell.second });
                starts.push(std::pair<int, int>{ row_index, current_cell.second });
            }
        }

        for (int col_diff = -1; col_diff <= 1; col_diff++)
        {
            int col_index = current_cell.second + col_diff;

            if (!(0 <= col_index && col_index < grid[current_cell.first].size()))
                continue;
            if (grid[current_cell.first][col_index] == 'X')
            {
                next_water.push(std::pair<int, int>{ current_cell.first, col_index });
                starts.push(std::pair<int, int>{ current_cell.first, col_index });
            }
        }
    }

    while (next_water.size())
    {
        std::pair<int, int> current_cell = next_water.front();
        next_water.pop();

        grid[current_cell.first][current_cell.second] = '.';
    }
}

bool can_they_meet(std::vector<std::vector<char>>& grid, std::queue<std::pair<int, int>>& starts, std::vector<std::vector<bool>>& visited)
{
    int iterations = starts.size();
    for (int i = 0; i < iterations; i++)
    {
        std::queue<std::pair<int, int>> path;
        path.push(starts.front());
        starts.pop();

        bool is_first = true;
        while (path.size() > 0)
        {
            std::pair<int, int> current_cell = path.front();
            path.pop();

            if (is_first)
                is_first = false;
            else
            {
                if (!(0 <= current_cell.first && current_cell.first < grid.size()) || !(0 <= current_cell.second && current_cell.second < grid[current_cell.first].size()))
                    continue;
                if (visited[current_cell.first][current_cell.second])
                    continue;

                switch (grid[current_cell.first][current_cell.second])
                {
                case 'X':
                    starts.push(std::pair<int, int>{ current_cell.first, current_cell.second });
                    continue;
                case 'L':
                    return true;
                }
            }

            visited[current_cell.first][current_cell.second] = true;
            path.push(std::pair<int, int>{ current_cell.first - 1, current_cell.second });
            path.push(std::pair<int, int>{ current_cell.first + 1, current_cell.second });
            path.push(std::pair<int, int>{ current_cell.first, current_cell.second - 1 });
            path.push(std::pair<int, int>{ current_cell.first, current_cell.second + 1 });
        }
    }

    return false;
}

int main(void)
{
    int rows, cols;
    std::cin >> rows >> cols;

    std::vector<std::vector<char>> grid;
    std::queue<std::pair<int, int>> water_starts;
    for (int row = 0; row < rows; row++)
    {
        std::vector<char> new_col;
        std::string col_string;
        std::cin >> col_string;

        for (int col = 0; col < col_string.size(); col++)
        {
            new_col.push_back(col_string[col]);
            if (col_string[col] == '.')
                water_starts.push(std::pair<int, int>{ row, col });
        }
        grid.push_back(new_col);
    }

    std::queue<std::pair<int, int>> swan_starts;
    swan_starts.push(find_swan(grid));

    std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), false));

    int day_count = 0;
    while (!can_they_meet(grid, swan_starts, visited))
    {
        next_grid(grid, water_starts);
        day_count++;
    }
    std::cout << day_count << "\n";

    return 0;
}