#include <string.h>
#include <iostream>
#include <string>
using namespace std;


void validate(const char** library[], int m, int n)
{
    if (m > 20) throw "Too many rows";
    if (n > 30) throw "Too many books in a row";

    for (int row = 0; row < m; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (strlen(library[row][col]) > 100) throw "Too many symbols in title";
        }
    }
}

bool isSorted(const char* books[], int booksCnt)
{
    for (int i = 0; i < booksCnt - 1; ++i)
    {
        if (strcmp(books[i], books[i + 1]) > 0) return false;
    }

    return true;
}

string processTitle(const char* title)
{
    string result;
    int cnt = 0;
    while (*title != '\0')
    {
        if (*title == ' ')
        {
            result += to_string(cnt).append(" ");
            cnt = 0;
        }
        else
        {
            ++cnt;
        }
        ++title;
    }

    result += to_string(cnt);

    return result;
}

void revealPassword(const char** library[], int mRows, int nBooksInRow)
{
    validate(library, mRows, nBooksInRow);

    string password;
    const int middle = (nBooksInRow % 2 == 0) ? (nBooksInRow - 1) / 2 : nBooksInRow / 2;

    for (int row = 0; row < mRows; row++)
    {
        if (isSorted(library[row], nBooksInRow))
        {
            password += processTitle(library[row][middle]);
            password += " ";
        }
    }

    cout << password << endl;
}

int main()
{
    const char* row1[] = { "Algebra", "Analytical Geometry", "Mathematical analysis" };
    const char* row2[] = { "Data structures", "Introduction to programming", "Object oriented programming" };
    const char* row3[] = { "Data bases", "Artifical intelligence", "Functional programming" };
    const char** library[] = { row1, row2, row3 };

    revealPassword(library, 3, 3);
}