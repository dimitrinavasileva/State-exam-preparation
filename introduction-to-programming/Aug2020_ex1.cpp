#include<iostream>

void print_backwards(const char* begin, const char* end)
{
    if (end < begin) return;

    const char* iter_begin{ begin };
    int n{ 0 };

    while (*begin != '\0' && *begin > 32 && begin != end)
    {
        begin++;
        n++;
    }
    begin++;

    print_backwards(begin, end);
    for (int i = 0; i < n; i++)
    {
        std::cout << *iter_begin;
        iter_begin++;
    }
    std::cout << " ";
}

void print_backwards(const char* string)
{
    size_t size{ strlen(string) };
    print_backwards(string, string + size);
}

int main()
{
    const char* sentence{ "I\tneed a break!" };
    print_backwards(sentence);
    return 0;
}
