#include <iostream>
using namespace std;

constexpr int N = 4;
constexpr int M = 6;

int explore(char matrix[N][M], int i, int j)
{
    if (i < 0 || i > N || j < 0 || j > M || matrix[i][j] != '4') return 0;
    matrix[i][j] = 'X';

    return 1 + explore(matrix, i - 1, j) + explore(matrix, i, j - 1) + explore(matrix, i + 1, j) + explore(matrix, i, j + 1);
}

int maxArea(char matrix[N][M])
{
    int maxArea = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (matrix[i][j] == '4')
            {
                int size = explore(matrix,i,j);
                if (size > maxArea)
                    maxArea = size;
            }
        }
    }

    return maxArea;
}

int main()
{
    char map[N][M] = { {'2','4','4','1','R','2'},
                       {'1','4','4','R','4','2'},
                       {'4','R','R','4','4','4'},
                       {'R','R','S','4','4','4'} };
    cout << maxArea(map);


    return 0;
}
