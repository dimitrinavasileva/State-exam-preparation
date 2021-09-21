#include <iostream>

// July 2016, Ex.1

bool isBelowMainDiagonal(int x, int y)
{
    return x >= y;
}

bool isAboveSecondaryDiagonal(int x, int y, int size)
{
    return x + y <= size;
}

void updateMatrixWithAverageSymmetricValue(int x, int y, double** matrix, int size)
{
    double& s1 = matrix[y][x];
    double& s2 = matrix[size - 1 - x][size - 1 - y];
    double& s3 = matrix[size - 1 - y][size - 1 - x];

    const double average = (matrix[x][y] + s1 + s2 + s3) / 4;
    matrix[x][y] = s1 = s2 = s3 = average;
}

void modifyMatrix(double** matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (isBelowMainDiagonal(i, j) && isAboveSecondaryDiagonal(i, j, size))
            {
                updateMatrixWithAverageSymmetricValue(i, j, matrix, size);
            }
        }
    }
}

void printMatrix(double** matrix, int size)
{
    for (int i = 0; i < size; i++)
	{
        for (int j = 0; j < size; j++)
		{
            std::cout << matrix[i][j] << ' ';
        }
		
        std::cout << '\n';
    }
}

int main()
{
    std::cout << "\nBefore modification:\n";

    double** testMatrix = new double* [3]{
                            new double[3]{1, 9, 10},
                            new double[3]{1, 7, 8},
                            new double[3]{8, 6, 5}
    };

    printMatrix(testMatrix, 3);

    std::cout << "\nAfter modification:\n";

    modifyMatrix(testMatrix, 3);

    printMatrix(testMatrix, 3);

    std::cout << "\n";

    /*
    Before modification:
        1 9 10
        1 7 8
        8 6 5

    After modification:
        3 6 9
        6 7 6
        9 6 3
    */
}