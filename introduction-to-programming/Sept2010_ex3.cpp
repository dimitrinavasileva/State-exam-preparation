#include<iostream>
#include<vector>

using namespace std;

// September 2010, Ex. 3

bool isNormalSymbol(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || (c == '_');
}

bool isPunctuationSymbol(char c)
{
    return !isNormalSymbol(c);
}

void reverseWords(const char* text)
{
    if (*text == '\0') return;

    static vector<vector<char>> vecPunctuationSymbols;

    string buff;
    while (*text != '\0' && isNormalSymbol(*text))
    {
        buff += *text;
        ++text;
    }

    if (*text != '\0')
    {
        vector<char> punctuationSymbols;
        while (*text != '\0' && isPunctuationSymbol(*text))
        {
            punctuationSymbols.push_back(*text);
            ++text;
        }
        vecPunctuationSymbols.push_back(punctuationSymbols);
    }

    reverseWords(text);
    cout << buff;
    if (!vecPunctuationSymbols.empty())
    {
        static auto it = vecPunctuationSymbols.begin();
        const auto& currPunctSymbols = *it;
        for (char punctSymbol : currPunctSymbols)
        {
            cout << punctSymbol;
        }
        ++it;
    }
}


int main()
{
    reverseWords("Hello world, baby!");  // prints "baby world, Hello!"
    cout << endl;
    reverseWords("1;;2;3;4;;5.");  // prints "5;;4;3;2;;1."
}