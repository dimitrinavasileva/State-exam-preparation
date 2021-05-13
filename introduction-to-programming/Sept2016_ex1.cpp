#include <iostream>
using namespace std;

// Sept 2016, ex. 1

int findPositionOfMostDistantEqualSymbol(int startPos, const char* str)
{
    const int size = strlen(str);
    char symbol = str[startPos];

    int result = startPos;

    for (int i = startPos; i < length; i++)
	{
        char currentSymbol = str[i];
        if (symbol == currentSymbol)
		{
            result = i;
        }
    }

    return result;
}

pair<int, int> getPositionsOfMostDistantEqualSymbols(const char* str)
{
    int size = strlen(str);
    int firstPos = 0;
    int secondPos = 0;

    for (int pos = 0; pos < size; pos++)
	{
        char currentSymbol = str[pos];

        int mostDistantEqualSymbolPos = findPositionOfMostDistantEqualSymbol(pos, str);

        if (mostDistantEqualSymbolPos - pos > secondPos - firstPos)
		{
            firstPos = pos;
            secondPos = mostDistantEqualSymbolPos;
        }
    }

    return { firstPos, secondPos };
}

int main()
{
    // Return value should be pair <4, 21>, the symbol space ' ' is on position 4
    // and 21, with distance 17 between them, which is the longest in our example
    pair<int, int> testPositions = getPositionsOfMostDistantEqualSymbols("this is just a simple example");

    std::cout << "Result: <" << testPositions.first << ", " << testPositions.second << ">\n";
}
