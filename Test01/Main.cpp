
#include <iostream>
#include <list>
#include <vector>
#include <time.h>

//performace testing for iterating between vector and list.
void _20190824()
{
	const size_t cap = 1000000;
	std::vector<int> vec(cap);
	std::list<int> lis(cap);

	for (int i = 0; i < cap; i++)
	{
		vec.push_back(i);
		lis.push_back(i);
	}

	clock_t start1 = clock();
	
	for (int i = 0; i < vec.size(); i++)
	{
		int val = vec[i];
	}

	clock_t end1 = clock();
	printf("vector++++++ %dms\n", end1 - start1);	//90ms

	clock_t start2 = clock();

	/*for (std::list<int>::const_iterator i = lis.begin(); i != lis.end(); i++)
	{
		int val = *i;
	}*/

	for (std::list<int>::const_iterator i = lis.begin(); i != lis.end(); i++)
	{
		int val = *i;
	}

	clock_t end2 = clock();
	printf("list++++++ %dms\n", end2 - start2);		//2700ms
}

class C1
{
	char a;
	char b;
	int c;
};

class C2
{
	char a;
	int c;
	char b;
};

class C3
{
	char a;
	char b;
	int c;

	void fun1() {}
};

class C4
{
	char a;
	char b;
	int c;

	virtual void fun1() {}
};

//Byte Alignment
void _20190905()
{
	int size1 = sizeof(C1);
	printf("C1 size:%d\n", size1);

	int size2 = sizeof(C2);
	printf("C2 size:%d\n", size2);

	int size3 = sizeof(C3);
	printf("C3 size:%d\n", size3);

	int size4 = sizeof(C4);
	printf("C4 size:%d\n", size4);

	/*output:
	C1 size : 8
	C2 size : 12
	C3 size : 8
	C4 size : 16
	*/
}

int main(int argc, char* [])
{
	//_20190824();
	_20190905();

	system("pause");

	return 0;
}
