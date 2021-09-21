#include <iostream>
#include <string>
#include <vector>

bool isNormalSymbol(const char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || (c == '_');
}

bool isPunctuationSymbol(const char c)
{
    return !isNormalSymbol(c);
}

void reverseWords(const char* text)
{
    if (*text == '\0') return;

    static std::vector<std::vector<char>> vecPunctuationSymbols;

    std::string buff;
    while (*text != '\0' && isNormalSymbol(*text))
    {
        buff += *text;
        ++text;
    }

    if (*text != '\0')
    {
        std::vector<char> punctuationSymbols;
        while (*text != '\0' && isPunctuationSymbol(*text))
        {
            punctuationSymbols.push_back(*text);
            ++text;
        }
        vecPunctuationSymbols.push_back(punctuationSymbols);
    }

    reverseWords(text);
    std::cout << buff;
    if (!vecPunctuationSymbols.empty())
    {
        // print punctuation symbol
        static std::vector<std::vector<char>>::iterator it { vecPunctuationSymbols.begin() };
        const std::vector<char>& currPunctSymbols{ *it };
        for (char punctSymbol : currPunctSymbols)
        {
            std::cout << punctSymbol;
        }
        ++it;
    }
}

int main()
{
    reverseWords("1;;2;3;4;;5.");  // prints "5;;4;3;2;;1."

    return 0;
}