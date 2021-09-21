#include<iostream>

constexpr int ROWS{ 4 };
constexpr int COLS{ 6 };

struct Area
{
    int x{ 0 };
    int y{ 0 };
    int sum{ 0 };
    int count{ 0 };
    float avg{ 0.0 };
};

bool compare(const Area& a1, const Area& a2)
{
    return a1.avg < a2.avg;
}

void insertionSortVector(Area* arr, int& size)
{
    for (int i{ 0 }; i < size; i++)
    {
        int index{ i };

        for (int j{ i + 1 }; j < size; j++)
        {
            if (compare(arr[j], arr[index]))
            {
                index = { j };
            }
        }

        Area temp{ arr[index] };
        arr[index] = { arr[i] };
        arr[i] = { temp };
    }
}

void getAvg(int map[ROWS][COLS], int i, int j, Area& a)
{
    if (i < 0 || j < 0 || i > ROWS - 1 || j > COLS - 1 || map[i][j] == 0) return;
    a.count++;
    a.sum += map[i][j];
    map[i][j] = { 0 };

    getAvg(map, i + 1, j, a);
    getAvg(map, i - 1, j, a);
    getAvg(map, i, j + 1, a);
    getAvg(map, i, j - 1, a);

    getAvg(map, i + 1, j + 1, a);
    getAvg(map, i + 1, j - 1, a);
    getAvg(map, i - 1, j - 1, a);
    getAvg(map, i - 1, j + 1, a);
}

void findAvg(int map[ROWS][COLS], Area* arr, int& size)
{
    for (int i{ 0 }; i < ROWS; i++)
    {
        for (int j{ 0 }; j < COLS; j++)
        {
            if (map[i][j] != 0)
            {
                Area a;
                a.x = { i };
                a.y = { j };
                getAvg(map, i, j, a);
                a.avg = { (float)a.sum / (float)a.count };
                arr[size] = { a };
                size++;
            }
        }
    }
}

int main()
{
    int map[ROWS][COLS] = { {10,0,1,1,0,1},
                      {1,1,1,0,0,1},
                      {1,0,0,1,0,2},
                      {0,1,0,0,0,1} };

    Area arr[ROWS * COLS];
    int size{ 0 };
    findAvg(map, arr, size);
    insertionSortVector(arr, size);
    //sort(v.begin(), v.end(), compare);

    for (int i{ 0 }; i < size; i++)
    {
        std::cout << "(" << arr[i].x << "," << arr[i].y << ") " << arr[i].avg << std::endl;
    }

    return 0;
}
