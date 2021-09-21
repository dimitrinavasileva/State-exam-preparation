#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Solution 1 : Without using STL
constexpr int N = 6;

int countDigits(int number)
{
    if (number == 0) return 1;

    int size = 0;
    while (number > 0)
    {
        size++;
        number /= 10;
    }

    return size;
}

void intArrrayToCharArray(int arr[N], char matrix[N][N])
{
    for (int i = 0; i < N; i++)
    {
        if (arr[i] == 0) matrix[i][0] = '0';

        int currDigit = countDigits(arr[i]) - 1;
        matrix[i][currDigit + 1] = '\0';

        while (arr[i] > 0)
        {
            int digit = arr[i] % 10;
            arr[i] /= 10;
            matrix[i][currDigit] = digit + '0';
            currDigit--;
        }
    }
}

//strlen
int size(const char* str)
{
    int size = 0;
    const char* temp = str;

    while (*temp != '\0')
    {
        temp++;
        size++;
    }

    return size;
}

//strcmp
int compare(const char* str1, const char* str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] < str2[i]) return -1;
        if (str1[i] > str2[i]) return 1;

        i++;
    }

    if (str1[i] != '\0') return 1;
    if (str2[i] != '\0') return -1;

    return 0;
}

//strcmp
void strcopy(char* str1, char* str2)
{
    int i = 0;
    while (str2[i] != '\0')
    {
        str1[i] = str2[i];
        i++;
    }
    str1[i] = '\0';
}

void insertionSort(char matrix[N][N])
{
    for (int i = 0; i < N; i++)
    {
        int curr = i;
        for (int j = i + 1; j < N; j++)
        {
            if (compare(matrix[curr], matrix[j]) != -1)
            {
                curr = j;
            }
        }

        char temp[100];
        strcopy(temp, matrix[curr]);
        strcopy(matrix[curr], matrix[i]);
        strcopy(matrix[i], temp);
    }
}

//Solution 2 : Using STL
void sort(vector<string>& v)
{
    for (int i = 0; i < v.size() - 1; i++)
    {
        int index = i;
        for (int j = i + 1; j < v.size(); j++)
        {
            if (v[index].compare(v[j]) == 1)
            {
                index = j;
            }
        }
        string temp = v[index];
        v[index] = v[i];
        v[i] = temp;
    }
}

void sortLex(int arr[], int arrSize)
{
    vector<string> v;
    for (int i = 0; i < arrSize; i++)
    {
        v.push_back(to_string(arr[i]));
    }

    sort(v);

    for (string& str : v)
    {
        cout << str << " ";
    }
}

template<typename T>
void printMatrix(T arr[N])
{
    for (int i = 0; i < N; i++)
    {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

int main()
{
    int arr[N] = { 13, 14, 7, 2018, 9, 0 };
    char matrix[N][N];

    intArrrayToCharArray(arr, matrix);
    insertionSort(matrix);
    printMatrix(matrix);

    //sortLex(arr, N);

    return 0;
}
