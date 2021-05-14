#include <iostream>

using namespace std;

// September 2008, Ex. 2

class Set
{
public:
	virtual ~Set() {}
	virtual bool isMember(int) const = 0;
};

class DivSet : public Set
{
	int d;
public:
	DivSet(int div) :d(div)
	{
		if (!div) throw "Bad input";
	}

	bool isMember(int x) const override
	{
		return x % d == 0;
	}
};

class ElemSet : public Set
{
	unsigned size;
	int* data;

	void copyData(const int* d, unsigned size)
	{
		data = new int[size];
		this->size = size;
		for (int i = 0; i < size; ++i)
			data[i] = d[i];
	}

public:
	ElemSet(const int* d, unsigned size)
	{
		copyData(d, size);
	}
	ElemSet(const ElemSet& e)
	{
		copyData(e.data, e.size);
	}

	~ElemSet()
	{
		delete[] data;
	}

	ElemSet& operator=(const ElemSet& e)
	{
		if (this == &e) return *this;
		int* tmp = data;
		copyData(e.data, e.size);
		delete[] tmp;
	}

	bool isMember(int x) const override
	{
		for (int i = 0; i < size; ++i)
			if (data[i] == x) return true;
		return false;
	}
};


bool isUnionMember(Set* sets[], unsigned cnt, int x)
{
	for (int i = 0; i < cnt; ++i)
		if (!sets[i]->isMember(x)) return false;
	return true;
}

int main()
{
	DivSet ds(3), ds2(24);
	int data[] = { 1, 2, 3, 4 };
	ElemSet elem(data, 4);
	Set* sets[3] = { &ds, &elem, &ds2 };

	for (int i = 0; i < 5; ++i)
	{
		int x;
		cin >> x;
		if (isUnionMember(sets, 3, x)) cout << "DA";
		else cout << "NE";
	}

	return 0;
}