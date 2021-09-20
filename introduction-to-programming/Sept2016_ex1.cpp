#include <iostream>
using namespace std;

//Solution 1
#include<iostream>
using namespace std;

struct Position
{
    int x = 0;
    int y = 0;
};

void maxDistance(const char* str)
{
    int size = strlen(str);
    Position p;
    int distance = 0;
    int maxDistance = 0;

    for (int i = 0; i < size; i++)
    {
        char curr = str[i];
        for (int j =  i + 1; j < size; j++)
        {
            if (curr == str[j])
            {
                distance = j - i;
                if (distance > maxDistance)
                {
                    maxDistance = distance;
                    p.x = i;
                    p.y = j;
                }
            }
        }
    }

    cout << "Left position: " << p.x << " " << "Right position: " << p.y << endl;
    cout << "Distance: " << maxDistance << endl;
}

//Solution 2
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
	
	maxDistance(str);
	
    pair<int, int> testPositions = getPositionsOfMostDistantEqualSymbols("this is just a simple example");

    std::cout << "Result: <" << testPositions.first << ", " << testPositions.second << ">\n";
}
