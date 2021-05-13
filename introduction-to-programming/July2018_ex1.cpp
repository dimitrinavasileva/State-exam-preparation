#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Sept 2018, ex. 1

//Using STL
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

int main()
{
	int arr[] = { 13, 14, 7, 2018, 9, 0 };
    int arrSize = sizeof arr / sizeof arr[0];

    sortLex(arr, arrSize);
}
