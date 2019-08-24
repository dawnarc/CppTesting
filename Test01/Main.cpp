
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

	for (std::list<int>::const_iterator i = lis.begin(); i != lis.end(); i++)
	{
		int val = *i;
	}

	clock_t end2 = clock();
	printf("list++++++ %dms\n", end2 - start2);		//2700ms
}

int main(int argc, char* [])
{
	_20190824();

	system("pause");

	return 0;
}
