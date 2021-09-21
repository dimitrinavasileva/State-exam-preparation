#include<iostream>

bool is_subordinate(const char* employee, const char* manager, const char* leaders[][2], int n)
{
    for (int i{ 0 }; i < n; i++)
    {
        if (strcmp(leaders[i][0], employee) == 0)
        {
            if (strcmp(leaders[i][1], manager) == 0)
            {
                return true;
            }
            return is_subordinate(leaders[i][1], manager, leaders, n);
        }
    }
    return false;
}

const char* the_big_boss(const char* leaders[][2], int n)
{
    int maxcount{ 0 };
    const char* boss{ "" };
    for (int i{ 0 }; i < n; i++)
    {
        const char* manager{ leaders[i][1] };
        int count{ 0 };
        for (int j{ 0 }; j < n; j++)
        {
            if (is_subordinate(leaders[j][0], manager, leaders, n))
            {
                count++;
                if (count > maxcount)
                {
                    maxcount = { count };
                    boss = { manager };
                }
            }
        }
    }
    return boss;
}

int main()
{
    const char* leaders[][2] = {
        {"Ivan Ivanov", "Mariq Ivanova"},
        {"Ivan Draganov", "Stoqn Petrov"},
        {"Mariq Ivanova", "Ivan Draganov"}
    };

    std::cout << std::boolalpha << is_subordinate("Ivan Draganov", "Stoqn Petrov", leaders, 3) << std::endl;
    std::cout << std::boolalpha << the_big_boss(leaders, 3) << std::endl;

    return 0;
}