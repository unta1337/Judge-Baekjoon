// 3197: 백조의 호수
/*
 * 호수와 백조의 위치가 주어졌을 때, 백조가 만나는 일수를 구하여라.
 */
// https://www.acmicpc.net/problem/1655

/*
 * 일반적인 BFS를 이용한 방법으로 시간 초과.
 * 빙하가 녹는 매 호수마다 백조의 경로를 계산하여 시간 증가.
 * 진행 방향에 빙하가 있을 때만 다음 호수를 계산하는 최적화 시도 요함.
 */
// 메모리: - KB
// 시간: 시간 초과 ms
// 코드 길이: 7260 bytes
// http://boj.kr/9c315ffd5c644d398ba5c43863feb42c

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
void q_pop(queue_t* this, int ret[2]);
void q_print(queue_t* this);

// 호수 갱신용 함수.
char get_next_cell(grid_t* grid, int location[2]);      // 특정 셀의 다음 상태를 반환.
void next_grid(grid_t* grid);                           // 모든 셀을 다음 상태로 갱신.

// 다른 백조 찾기 함수.
void find_swan(grid_t* grid, int ret[2]);               // 백조1 찾기.
int can_they_meet(grid_t* grid, int swan[2]);           // 백조1이 백조2를 만날 수 있는가?

int main(void)
{
    int rows, cols;
    scanf("%d %d", &rows, &cols);

    grid_t* grid = create_grid(rows, cols);
    for (int row = 0; row < grid->rows; row++)
    {
        char* temp = (char*)malloc((cols + 1) * sizeof(char));
        scanf("%s", temp);

        for (int col = 0; col < cols; col++)
            grid->grid[row][col] = temp[col];

        free(temp);
    }

    int swan[2];
    find_swan(grid, swan);

    int day_count = 0;
    while (!can_they_meet(grid, swan))
    {
        next_grid(grid);
        day_count++;
    }

    printf("%d\n", day_count);

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
    this->pairs = (int**)malloc(sizeof(int*));

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

    this->pairs[this->size] = (int*)malloc(2 * sizeof(int));
    this->pairs[this->size][0] = pair[0];
    this->pairs[this->size][1] = pair[1];

    this->size++;
}

void q_pop(queue_t* this, int ret[2])
{
    if (this->size == 0)
        return;

    ret[0] = this->pairs[0][0];
    ret[1] = this->pairs[0][1];

    for (int i = 1; i < this->size; i++)
    {
        this->pairs[i - 1][0] = this->pairs[i][0];
        this->pairs[i - 1][1] = this->pairs[i][1];
    }
    free(this->pairs[--this->size]);

    if (this->size > 1 && this->size < this->capacity / 2)
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

    // 빙하가 아니면 다음 상태를 볼 필요가 없음.
    if (cell != 'X')
        return cell;

    for (int row_diff = -1; row_diff <= 1; row_diff++)
    {
        int row_index = row + row_diff;

        // 셀이 범위를 벗어나면 무시.
        if (!(0 <= row_index && row_index < grid->rows))
            continue;

        // 주변에 물이 하나라도 있으면 녹음.
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

    // 아무 것에도 해당하지 않으면 빙하는 녹지 않는다.
    return 'X';
}

void next_grid(grid_t* grid)
{
    // 임시 그리드에 다음 상태 저장.
    grid_t* next = create_grid(grid->rows, grid->cols);
    for (int row = 0; row < grid->rows; row++)
        for (int col = 0; col < grid->cols; col++)
            next->grid[row][col] = get_next_cell(grid, (int[2]){ row, col });

    // 그리드 갱신.
    for (int row = 0; row < grid->rows; row++)
        for (int col = 0; col < grid->cols; col++)
            grid->grid[row][col] = next->grid[row][col];
    
    delete_grid(next);
}

void find_swan(grid_t* grid, int ret[2])
{
    for (int row = 0; row < grid->rows; row++)
        for (int col = 0; col < grid->cols; col++)
            if (grid->grid[row][col] == 'L')
            {
                ret[0] = row;
                ret[1] = col;
                return;
            }
}

int can_they_meet(grid_t* grid, int swan[2])
{
    // BFS를 위한 큐 생성.
    queue_t* path = create_queue();
    q_push(path, swan);

    // 이미 방문한 셀 저장.
    int** visited = (int**)calloc(grid->rows, sizeof(int*));
    for (int i = 0; i < grid->rows; i++)
        visited[i] = (int*)calloc(grid->cols, sizeof(int));
    visited[swan[0]][swan[1]] = 1;

    int is_first = 1;
    int found = 0;
    while (path->size > 0)
    {
        int current_cell[2];
        q_pop(path, current_cell);

        if (is_first)
        {
            is_first = 0;
            goto push;
        }

        // 셀이 범위를 벗어나면 무시.
        if (!(0 <= current_cell[0] && current_cell[0] < grid->rows) || !(0 <= current_cell[1] && current_cell[1] < grid->cols))
            continue;

        // 셀을 이미 방문했으면 무시.
        if (visited[current_cell[0]][current_cell[1]])
            continue;
        visited[current_cell[0]][current_cell[1]] = 1;

        char cell = grid->grid[current_cell[0]][current_cell[1]];

        if (cell == 'X')
            continue;
        else if (cell == 'L')
        {
            found = 1;
            break;
        }

        push:
        q_push(path, (int[2]){ current_cell[0] - 1, current_cell[1] });
        q_push(path, (int[2]){ current_cell[0] + 1, current_cell[1] });
        q_push(path, (int[2]){ current_cell[0], current_cell[1] - 1 });
        q_push(path, (int[2]){ current_cell[0], current_cell[1] + 1 });
    }

    delete_queue(path);
    for (int i = 0; i < grid->rows; i++)
        free(visited[i]);
    free(visited);
    return found;
}