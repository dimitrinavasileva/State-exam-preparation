#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;


// August 2020, Ex. 1
void print_backwards(const char* begin, const char* end)
{
	if (begin >= end)
	{
		return;
	}
	if (*begin <= 32)
	{
		print_backwards(begin + 1, end);
	}
	else
	{
		const char* word_end;
		for (word_end = begin; *word_end > 32 && word_end < end; ++word_end);

		print_backwards(word_end, end);

		if (word_end < end)
		{
			cout << " ";
		}

		for (const char* it = begin; it < word_end; it++)
		{
			cout << *it;
		}
	}
}

void print_backwards(const char* string)
{
	print_backwards(string, string + strlen(string));
}

int main()
{
	const char* sentence = "I\tneed a break!";
	print_backwards(sentence);
	return 0;
}