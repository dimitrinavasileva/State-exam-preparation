#include <iostream>
#include <vector>
using namespace std;

// September 2019, ex. 1

// А) find използва алгоритъма за двоично търсене (binary search), за да
// провери дали value се съдържа в масива arr, състоящ се от size елемента.
// Функцията връща true ако това е така и false в противен случай.
bool find(int value, int* arr, size_t size)
{
    if (size == 0) return false;

    size_t mid = size / 2;

    if (value == arr[mid]) return true;

    if (value < arr[mid])
        return find(value, arr, mid);
    else
        return find(value, arr + mid + 1, size - mid);
}

// Б) fold_left изпълнява ляво свиване (left fold) върху масива arr, съдържащ size елемента,
// прилагайки операцията op. Началната стойност е nil.
// Функцията връща стойността op(...op(op(nil, a[0]), a[1]), ..., a[size-1]).
template <typename ReturnType, typename InputType, typename OpType>
ReturnType fold_left(InputType* arr, size_t size, OpType op, ReturnType nil)
{
    ReturnType result = nil;
    for (size_t i = 0; i < size; ++i)
    {
        result = op(arr[i], result);
    }

    return result;
}


int op(char Digit, int Result)
{
    return (Result * 10) + (Digit - '0');
}

// Преобразува символен низ от десетични цифри до величина от тип int
int str_to_int(const char* str)
{
    return (str == nullptr) ? 0 : fold_left(str, strlen(str), op, 0);
}


int main()
{
    int arr[] = { 1,2,3,4,5, 6 };
    int size = sizeof(arr) / sizeof(arr[0]);
    cout << boolalpha << find(1, arr, size) << endl;
    cout << boolalpha << find(2, arr, size) << endl;
    cout << boolalpha << find(3, arr, size) << endl;
    cout << boolalpha << find(4, arr, size) << endl;
    cout << boolalpha << find(5, arr, size) << endl;
    cout << boolalpha << find(6, arr, size) << endl;
    cout << boolalpha << find(7, arr, size) << endl;
    cout << boolalpha << find(0, arr, size) << endl;
    cout << boolalpha << find(-1, arr, size) << endl;

    cout << fold_left("123456", 6, op, 0) << endl;
    cout << str_to_int("123456");

}