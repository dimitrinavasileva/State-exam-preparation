#include <iostream>

struct Position
{
    size_t x{ 0 };
    size_t y{ 0 };
};

void maxDistance(const char* str)
{
    size_t size{ strlen(str) };
    Position p;
    size_t distance{ 0 };
    size_t maxDistance{ 0 };

    for (size_t i{ 0 }; i < size; i++)
    {
        char curr{ str[i] };
        for (size_t j{ i + 1 }; j < size; j++)
        {
            if (curr == str[j])
            {
                distance = { j - i };
                if (distance > maxDistance)
                {
                    maxDistance = { distance };
                    p.x = { i };
                    p.y = { j };
                }
            }
        }
    }

    std::cout << "Left position: " << p.x << " " << "Right position: " << p.y << std::endl;
    std::cout << "Distance: " << maxDistance << std::endl;
}

int main()
{
    // Return value should be pair <4, 21>, the symbol space ' ' is on position 4
    // and 21, with distance 17 between them, which is the longest in our example
    const char* str{ "this is just a simple example" };
    maxDistance(str);
}
