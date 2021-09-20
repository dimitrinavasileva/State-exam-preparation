#include <iostream>
#include<vector>
#include <algorithm>
using namespace std;

//Prince coordinates and path from Eli to Prince
//(2,7) 9 (4,1) 9 (4,8) 16

const int N = 5;
const int M = 11;

struct Prince
{
	int x, y, distance;
};

bool compare(const Prince& p1, const Prince& p2)
{
	return p1.distance < p2.distance;
}

void insertionSortVector(vector<Prince>& v)
{
	int vectorSize = v.size();
	for (int i = 0; i < vectorSize; i++)
	{
		int index = i;
		for (int j = i + 1; j < vectorSize; j++)
		{
			if (compare(v.at(j),v.at(index)))
			{
				index = j;
			}
		}
		Prince temp = v.at(index);
		v.at(index) = v.at(i);
		v.at(i) = temp;
	}
}

void getAllPathsToPrince(char map[N][M], int i, int j, int currDistance,vector<Prince>& v)
{
	if (i<0 || j<0 || i>N - 1 || j>M - 1 || map[i][j] == '#') return;
	if (map[i][j] == 'P')
	{
		Prince p = { i,j,currDistance };
		v.push_back(p);
		map[i][j] = '#';
		return;
	}

	map[i][j] = '#';
	getAllPathsToPrince(map, i + 1, j, currDistance + 1, v);
	getAllPathsToPrince(map, i - 1, j, currDistance + 1, v);
	getAllPathsToPrince(map, i, j + 1, currDistance + 1, v);
	getAllPathsToPrince(map, i, j - 1, currDistance + 1, v);
}

void findPathsToPrince(char map[N][M], vector<Prince>& v)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (map[i][j] == 'E')
			{
				getAllPathsToPrince(map, i, j, 0,v);
			}
		}
	}
}

int main()
{
	char map[N][M] = { {'#', '.', '.', '.', '.', '#', '.', '.', '.', '.', '.'},
					{'.', '.', '.', 'E', '.', '.', '.', '.', '#', '.', '.'},
					{'.', '#', '#', '#', '#', '#', '#', 'P', '#', '#', '.'},
					{'.', '#', '#', '#', '#', '#', '#', '#', '#', '.', '.'},
					{'.', 'P', '.', '#', '.', '.', '.', '.', 'P', '.', '.'} };

	vector<Prince> v;
	findPathsToPrince(map, v);
	insertionSortVector(v);
	//sort(v.begin(), v.end(), compare);
	int i = 1;
	for (const Prince& p : v)
	{
		cout << "(" << p.x << "," << p.y << ") " << p.distance << " ";
	}
	cout << endl;
}
