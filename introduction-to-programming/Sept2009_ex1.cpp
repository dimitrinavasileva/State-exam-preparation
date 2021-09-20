#include<iostream>
#include<vector>
using namespace std;

bool isSubstring(string str1, string str2)
{
	int sizeStr = str1.length();
	int sizeSubStr = str2.length();

	if (sizeStr < sizeSubStr) return false;

	return str1.find(str2) != std::string::npos;
}

void check(vector<string> v)
{
	int min = 0;
	for (int i = 0; i < v.size(); i++)
	{
		if ((v.at(i)).size() < min)
		{
			min = i;
		}
	}

	int count = 0;
	for (int i = 0; i < v.size(); i++)
	{
		if (isSubstring(v.at(i), v.at(min)))
		{
			count++;
		}
	}

	if (count == 5)
	{
		cout << "YES" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}

}

int main()
{
	int i = 0;
	string str;
	vector<string> v;
	while (i < 5)
	{
		cin >> str;
		if (str.length() > 50) 
		{
			throw "Too many symbols";
		}
		v.push_back(str);
		i++;
	}
	check(v);
}