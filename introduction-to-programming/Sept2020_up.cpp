#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;


// September 2020, Ex. 1
bool is_subordinate_iterative(const char* employee, const char* manager, const char* leaders[][2], size_t n)
{
	unordered_map<string, string> map;

	for (int i = 0; (size_t) i < n; ++i)
	{
		map.insert(std::pair<string, string>(leaders[i][0], leaders[i][1]));
	}

	string temp_employee{ employee };

	for (int i = 0; (size_t) i < n; ++i)
	{
		auto it = map.find(temp_employee);
		if (it == map.end())
		{
			return false;
		}
		string temp_manager{ it->second };
		if (strcmp(manager, temp_manager.c_str()) == 0)
		{
			return true;
		}

		temp_employee = temp_manager;
	}

	return false;
}

bool is_subordinate_recursive(const char* employee, const char* manager, const char* leaders[][2], size_t n)
{
	size_t i;
	for (i = 0; i < n && strcmp(employee, leaders[i][0]); ++i) { }
	if (i >= n)
	{
		return false;
	}

	const char* employee_manager = leaders[i][1];
	if (strcmp(employee_manager, manager) == 0)
	{
		return true;
	}

	return is_subordinate_recursive(employee_manager, manager, leaders, n);
}

const char* the_big_boss(const char* leaders[][2], size_t n)
{
	int index = 0;
	const char* manager = leaders[index][1];

	for (size_t i = 0; i < n; ++i)
	{
		size_t j;
		for (j = 0; j < n && strcmp(manager, leaders[j][0]); ++j) { }
		if (j == n) 
		{
			return manager;
		}
		manager = leaders[j][1];
	}
}

int main()
{
	const char* leaders[][2] = {
		{"Ivan Ivanov", "Mariq Ivanova"},
		{"Ivan Draganov", "Stoqn Petrov"},
		{"Mariq Ivanova", "Ivan Draganov"}
	};

	cout << the_big_boss(leaders, 3) << endl;
	return 0;
}
