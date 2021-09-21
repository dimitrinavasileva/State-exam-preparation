#include <iostream>

constexpr int ROWS{ 4 };
constexpr int COLS{ 6 };

int explore(char matrix[ROWS][COLS], int i, int j)
{
    if (i < 0 || i > ROWS || j < 0 || j > COLS || matrix[i][j] != '4') return 0;
    matrix[i][j] = { 'X' };

    return 1 + explore(matrix, i - 1, j) + explore(matrix, i, j - 1) + explore(matrix, i + 1, j) + explore(matrix, i, j + 1);
}

int maxArea(char matrix[ROWS][COLS])
{
    int maxArea{ 0 };
    for (int i{ 0 }; i < ROWS; i++)
    {
        for (int j{ 0 }; j < COLS; j++)
        {
            if (matrix[i][j] == '4')
            {
                int size{ explore(matrix, i, j) };
                if (size > maxArea)
                    maxArea = { size };
            }
        }
    }

    return maxArea;
}

int main()
{
    char map[ROWS][COLS] = { {'2','4','4','1','R','2'},
                       {'1','4','4','R','4','2'},
                       {'4','R','R','4','4','4'},
                       {'R','R','S','4','4','4'} };
    std::cout << maxArea(map);

    return 0;
}
