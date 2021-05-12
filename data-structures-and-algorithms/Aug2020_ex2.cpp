#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;


// August 2020, Ex. 2
struct Node
{
	string text;
	Node* next;
};

void unite(Node* list)
{
	Node* cur = list->next;
	while (cur != list)
	{
		if (cur->text[cur->text.length() - 1] == cur->next->text[0])
		{
			cur->text.append("-").append(cur->next->text);
			Node* curNext = cur->next;
			cur->next = curNext->next;
			if (curNext == list)
			{
				list = cur;
			}
			delete curNext;
		}
		else
		{
			cur = cur->next;
		}
	}

	while (cur == list)
	{
		if (cur->text[cur->text.length() - 1] == cur->next->text[0])
		{
			cur->text.append("-").append(cur->next->text);
			Node* curNext = cur->next;
			cur->next = curNext->next;
			if (curNext == list)
			{
				list = cur;
			}
			delete curNext;
		}
		else
		{
			cur = cur->next;
		}
	}
}

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

int main()
{
	Node* pass = new Node{ "pass", nullptr };
	Node* tall = new Node{ "tall", pass };
	Node* eat = new Node{ "eat", tall };
	Node* smile = new Node{ "smile", eat };
	Node* dog = new Node{ "dog", smile };
	Node* ink = new Node{ "ink", dog };
	Node* taxi = new Node{ "taxi", ink };
	Node* street = new Node{ "street", taxi };
	pass->next = street;

	unite(street);
	vector<string> v;
	Node* it = pass;
	do 
	{
		v.push_back(it->text);
		it = it->next;
	} while (it != pass);

	sort(v);
	for (string& str : v)
	{
		cout << str << endl;
	}

	return 0;
}
