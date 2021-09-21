#include<iostream>
using namespace std;

constexpr int N = 4;
constexpr int M = 6;

bool validCoordinates(int row, int col, int M, int N)
{
    return 0 <= row && row <= N - 1 && 0 <= col && col <= M - 1;
}

void after100Years(char forest[N][M])
{
    cout << "Initial forest:\n";
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            cout << forest[row][col] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';

    for (int i = 0; i < 10; i++)
    {
        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < M; col++)
            {
                if ('1' <= forest[row][col] && forest[row][col] <= '3')
                {
                    forest[row][col]++;
                }
                else if (forest[row][col] == '4')
                {
                    int fours = 0;

                    for (int row_change = 0; row_change <= 1; row_change++)
                    {
                        for (int col_change = 0; col_change <= 1; col_change++)
                        {
                            if (validCoordinates(row + row_change, col + col_change, N, M) &&
                                forest[row + row_change][col + col_change] == '4')
                            {
                                fours++;
                            }
                        }
                    }

                    fours--;  // for the current terrain
                    if (fours >= 3)
                    {
                        forest[row][col] = '3';
                    }
                }
            }
        }

        cout << "After 100 years:\n";
        for (int row = 0; row < M; row++)
        {
            for (int col = 0; col < N; col++)
            {
                cout << forest[row][col] << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
    }
}


int main()
{

    char map[N][M] = { {'R','R','1','1','2','2'},
                        {'1','R','R','R','1','2'},
                        {'S','1','R','R','2','3'},
                        {'4','4','S','S','R','R'} };
    after100Years(map);

    return 0;
}