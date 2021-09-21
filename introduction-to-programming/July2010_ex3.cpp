#include<iostream>
#include<algorithm>

bool isAnagram(std::string str1, std::string str2)
{
    size_t sizeStr1{ str1.size() };
    size_t sizeStr2{ str2.size() };

    if (sizeStr1 != sizeStr2) return false;

    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());

    return str1 == str2;
}

int longestAnagramsCount(const char* input[], const int n)
{
    int max{ 0 };
    for (int i{ 0 }; i < n; i++)
    {
        int currMax{ 0 };
        for (int j{ 0 }; j < n; j++)
        {
            if (isAnagram(input[i], input[j]))
            {
                currMax++;
                if (currMax > max)
                {
                    max = { currMax };
                }
            }
        }
    }

    return max;
}

int main()
{
    const int num{ 7 };
    const char* input[num] { "string", "ginrts", "ringst", "strong", "spong",  "shpong", "pongs" };
    std::cout << longestAnagramsCount(input, num) << std::endl; // 3
}