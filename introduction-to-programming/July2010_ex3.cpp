#include<iostream>
#include<algorithm>
using namespace std;

// July 2010, Ex.3

bool areAnagrams(string str1, string str2)
{
    if (str1.size() != str2.size()) return false;

    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());

    return str1 == str2;
}

int countAnagrams(const char* word, int size, const char* words[])
{
    int result = 0;
    for (int i = 0; i < size; i++)
    {
        if (areAnagrams(word, words[i])) ++result;
    }

    return result;
}

int longestAnagramsCount(int size, const char* words[])
{
    int maxAnagrams = 0;

    for (int i = 0; i < size; i++)
    {
        const int anagramsCount = countAnagrams(words[i], size, words);
        if (anagramsCount > maxAnagrams)
        {
            maxAnagrams = anagramsCount;
        }
    }

    return maxAnagrams;
}

int main()
{
    const char* input[]{ "string", "ginrts", "ringst", "strong", "spong",  "shpong", "pongs" };

    cout << longestAnagramsCount(7, input) << endl;
}