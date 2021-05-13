// Example program
#include <iostream>
#include <string>

// July 2015, Ex. 1

bool isInMatrix(int x, int y, int m, int n)
{
    return 0 <= x && x <= m - 1 && 0 <= y && y <= n - 1;
}

void subsample(float img[][10], int m, int n)
{
    const int sM = (m + 1) / 2;
    const int sN = (n + 1) / 2;

    for (int i = 0; i < sM; i++)
    {
        for (int j = 0; j < sN; j++)
        {
            int countElems = 0;
            float sum = 0;
            for (int y : {i * 2, i * 2 + 1})
            {
                for (int x : {j * 2, j * 2 + 1})
                {
                    if (isInMatrix(y, x, m, n))
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

int main() {
    float img[10][10]{ {1.0, 2.0, 3.0}, {4.5, 6.5, 7.5} };

    subsample(img, 2, 3);
}
