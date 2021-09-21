#include <iostream>
#include <string>

bool isInMatrix(int x, int y, int rows, int cols)
{
    return 0 <= x && x <= rows - 1 && 0 <= y && y <= cols - 1;
}

void subsample(float img[][10], int rows, int cols)
{
    const int sM = (rows + 1) / 2;
    const int sN = (cols + 1) / 2;

    for (int i = 0; i < sM; i++)
    {
        for (int j = 0; j < sN; j++)
        {
            int countElems = 0;
            float sum = 0;
            for (int y = i * 2; y <= i * 2 + 1; y++)
            {
                for (int x = j * 2; x <= j * 2 + 1; x++)
                {
                    if (isInMatrix(y, x, rows, cols))
                    {
                        countElems++;
                        sum += img[y][x];
                    }
                }
            }
            std::cout << static_cast<double>(sum) / countElems << ' ';
        }
        std::cout << '\n';
    }
}

int main()
{
    float img[10][10]{ {1.0, 2.0, 3.0}, {4.5, 6.5, 7.5} };

    subsample(img, 2, 3);

    return 0;
}