#include<iostream>
#include<algorithm>
using namespace std;

bool isAnagram(string str1, string str2)
{
    int sizeStr1 = str1.size();
    int sizeStr2 = str2.size();

    if (sizeStr1 != sizeStr2) return false;

    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());

    return str1 == str2;
}

int longestAnagramsCount(const char* input[], int n)
{
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        int currMax = 0;
        for (int j = 0; j < n; j++)
        {
            if (isAnagram(input[i], input[j]))
            {
                currMax++;
                if (currMax > max)
                {
                    max = currMax;
                }
            }
        }
    }

    return max;
}

int main()
{
    const char* input[] = { "string", "ginrts", "ringst", "strong", "spong",  "shpong", "pongs" };

    cout << longestAnagramsCount(input, 7) << endl; // 3
}