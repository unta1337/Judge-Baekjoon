#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <utility>

std::size_t pair_hash(std::pair<int, int> pair)
{
    return pair.first * 10000 + pair.second;
}

std::pair<int, int> pair_hash_rev(std::size_t hash)
{
    return std::pair<int, int>{hash / 10000, hash % 10000};
}

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
char get_next_state(std::vector<std::vector<char>>& grid, std::pair<int, int> location)
{
    int row = location.first;
    int col = location.second;

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
std::vector<std::vector<char>> get_next_iteration(std::vector<std::vector<char>>& grid)
{
    // 임시 그리드를 생성하여 다음 세대 그리드 작성.
    std::vector<std::vector<char>> next_grid;
    for (int row = 0; row < grid.size(); row++)
    {
        std::vector<char> new_col;
        for (int col = 0; col < grid[row].size(); col++)
            new_col.push_back(get_next_state(grid, std::pair<int, int>{row, col}));
        next_grid.push_back(new_col);
    }

    return next_grid;
}

// 처음으로 백조가 나타나는 셀 좌표 반환.
std::pair<int, int> find_swan(std::vector<std::vector<char>>& grid)
{
    for (int row = 0; row < grid.size(); row++)
        for (int col = 0; col < grid[row].size(); col++)
            if (grid[row][col] == 'L')
                return std::pair<int, int>{row, col};
    return std::pair<int, int>{-1, -1};
}

bool can_they_meet(std::vector<std::vector<char>>& grid, std::pair<int, int> location, std::unordered_set<std::size_t> path, std::size_t swan_hash)
{
    // 그리드를 벗어나면 false.
    if (location.first < 0 || location.first >= grid.size())
        return false;
    if (location.second < 0 || location.second >= grid[0].size())
        return false;

    std::size_t location_hash = pair_hash(location);

    // 이미 들렀던 셀이면 false.
    if (path.count(location_hash))
        return false;

    // 빙판을 만나면 false.
    if (grid[location.first][location.second] == 'X')
        return false;

    // 다른 백조를 만나면 true.
    if (location_hash != swan_hash && grid[location.first][location.second] == 'L')
        return true;

    path.insert(location_hash);

    // 사방으로 탐색.
    return can_they_meet(grid, std::pair<int, int>{location.first + 1, location.second}, path, swan_hash)
        || can_they_meet(grid, std::pair<int, int>{location.first, location.second - 1}, path, swan_hash)
        || can_they_meet(grid, std::pair<int, int>{location.first - 1, location.second}, path, swan_hash)
        || can_they_meet(grid, std::pair<int, int>{location.first, location.second + 1}, path, swan_hash);
}

int how_many_iterations_to_meet(std::vector<std::vector<char>>& grid, std::pair<int, int> swan_location)
{
    std::size_t swan_hash = pair_hash(swan_location);

    int count = 0;
    while (!can_they_meet(grid, swan_location, std::unordered_set<std::size_t>{}, swan_hash))
    {
        grid = get_next_iteration(grid);
        count++;
    }

    return count;
}

int main(void)
{
    // std::vector<std::vector<char>> test_grid =
    // {
    //     { '.', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.', 'X', 'X', '.', 'X', 'X', 'X' },
    //     { '.', '.', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '.', 'X', 'X', 'X' },
    //     { '.', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.' },
    //     { '.', '.', 'X', 'X', 'X', 'X', 'X', '.', 'L', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.' },
    //     { '.', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.' },
    //     { 'X', 'X', 'X', 'X', 'X', 'X', 'X', '.', '.', '.', 'X', 'X', 'X', 'X', '.', '.', '.' },
    //     { '.', '.', 'X', 'X', 'X', 'X', 'X', '.', '.', '.', 'X', 'X', 'X', '.', '.', '.', '.' },
    //     { '.', '.', '.', '.', 'X', 'X', 'X', 'X', 'X', '.', 'X', 'X', 'X', 'L', '.', '.', '.' }
    // };

    // std::vector<std::vector<char>> test_grid_2 =
    // {
    //     { '.', 'L' },
    //     { '.', '.' },
    //     { 'X', 'X' },
    //     { 'X', 'X' },
    //     { 'X', 'X' },
    //     { 'X', 'X' },
    //     { 'X', 'X' },
    //     { 'X', 'X' },
    //     { '.', '.' },
    //     { '.', 'L' },
    // };

    // std::vector<std::vector<char>> test_grid_3 =
    // {
    //     { '.', '.', 'X', 'X', 'X', '.', '.', '.', 'X', '.', '.' },
    //     { '.', 'X', '.', 'X', 'X', 'X', '.', '.', '.', 'L', '.' },
    //     { '.', '.', '.', '.', 'X', 'X', 'X', '.', '.', 'X', '.' },
    //     { 'X', '.', 'L', '.', '.', 'X', 'X', 'X', '.', '.', '.' },
    // };

    // print_grid(test_grid);
    // std::cout << how_many_iterations_to_meet(test_grid, find_swan(test_grid)) << "\n\n";

    // print_grid(test_grid_2);
    // std::cout << how_many_iterations_to_meet(test_grid_2, find_swan(test_grid_2)) << "\n\n";

    // print_grid(test_grid_3);
    // std::cout << how_many_iterations_to_meet(test_grid_3, find_swan(test_grid_3)) << "\n\n";

    int rows, cols;
    std::vector<std::vector<char>> input_grid;

    std::cin >> rows >> cols;
    for (int row = 0; row < rows; row++)
    {
        std::vector<char> new_col;

        std::string col_string;
        std::cin >> col_string;

        for (int i = 0; i < col_string.size(); i++)
            new_col.push_back(col_string[i]);

        input_grid.push_back(new_col);
    }

    std::cout << how_many_iterations_to_meet(input_grid, find_swan(input_grid)) << "\n";

    return 0;
}