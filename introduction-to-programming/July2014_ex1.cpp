#include<iostream>
#include<vector>
using namespace std;

constexpr int ROWS = 3;
constexpr int COLS = 3;


bool walk(int matrix[ROWS][COLS], int i, int j, const char* str, bool result)
{
    if (*str == '\0' && i == ROWS - 1 && j == COLS - 1) return true;
    if (i < 0 || j < 0 || i > ROWS - 1 || j > COLS - 1 || matrix[i][j] == 0) return false;

    if (*str == 'S')
    {
        result = walk(matrix, i + 1, j, str + 1, result);
    }
    if (*str == 'N')
    {
        result = walk(matrix, i - 1, j, str + 1, result);
    }
    if (*str == 'E')
    {
        result = walk(matrix, i, j + 1, str + 1, result);
    }
    if (*str == 'W')
    {
        result = walk(matrix, i, j - 1, str + 1, result);
    }

    return result;
}


bool check(int matrix[ROWS][COLS], const char* str)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (matrix[i][j] == 1)
            {
                if (walk(matrix, i, j, str, false)) return true;
            }
        }
    }
    return false;
}

int main()
{
    int matrix[ROWS][COLS] = { {1, 0 ,0},
                        {1, 0, 1},
                        {1, 1, 1} };

    const char* str = "SSEE";
    const char* str1 = "SSEES";
    const char* str2 = "S";
    const char* str3 = "SS";
    const char* str4 = "EE";

    cout << boolalpha << check(matrix, str) << endl; //true
    cout << boolalpha << check(matrix, str1) << endl; //false
    cout << boolalpha << check(matrix, str2) << endl; //true
    cout << boolalpha << check(matrix, str3) << endl; //false
    cout << boolalpha << check(matrix, str4) << endl; //true

    return 0;
}