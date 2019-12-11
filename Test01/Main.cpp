
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

class C5
{
	char a;
	char b;
	int c;

	virtual void fun1() = 0;
};

//Byte Alignment
void _20190905()
{
	printf("C1 size:%zd\n", sizeof(C1));
	printf("C2 size:%zd\n", sizeof(C2));
	printf("C3 size:%zd\n", sizeof(C3));
	printf("C4 size:%zd\n", sizeof(C4));
	printf("C5 size:%zd\n", sizeof(C5));

	/*output(x64):
	C1 size:8
	C2 size:12
	C3 size:8
	C4 size:16
	C5 size:16
	*/

	/*output(x86):
	C1 size:8
	C2 size:12
	C3 size:8
	C4 size:12
	C5 size:12
	*/
}

class CA01
{
	int a;
};

class CA02 : public CA01
{
	char* b;
};

class CA03 : public CA01
{
	float c;
};

class CB01
{
	char d;
};

class CC01
{
public:

	long e;

	virtual void fun01() {}
};

void _20190908()
{
	CA02 obj01;

	CA02* ptr01 = &obj01;

	CA03* ptr02 = (CA03*)(ptr01);
	printf("%d\n", ptr02 ? 1 : 0);	//output:1

	//error C2440:  'static_cast': cannot convert from 'CA02 *' to 'CA03 *'
	//CA03* ptr03 = static_cast<CA03*>(ptr01);

	//error C2683:  'dynamic_cast': 'CA02' is not a polymorphic type
	//CA03* ptr04 = dynamic_cast<CA03*>(ptr01);
	
	CA01* ptr05 = dynamic_cast<CA01*>(ptr01);
	printf("%d\n", ptr05 ? 1 : 0);	//output:1

	CA03* ptr06 = static_cast<CA03*>(ptr05);
	printf("%d\n", ptr06 ? 1 : 0);	//output:1

	CC01 obj02;
	CC01* ptr07 = &obj02;

	CA01* ptr08 = dynamic_cast<CA01*>(ptr07);
	printf("%d\n", ptr08 ? 1 : 0);	//output:0

	//error C2440:  'static_cast': cannot convert from 'CC01 *' to 'CA01 *'
	//CA01* ptr09 = static_cast<CA01*>(ptr07);

	CA01* ptr10 = (CA01*)ptr07;
	printf("%d\n", ptr10 ? 1 : 0);	//output:1
}

void _20190924()
{
	int n[5];
	int* p = n;
	for (int i = 0; i < 5; ++i, ++p)
	{
		*p = i;
		//p[i] = i;
	}

	for (int j = 0; j < 5; j++)
	{
		printf("%d\n", n[j]);
	}

	/* output (*p = i;):
	0
	1
	2
	3
	4
	*/

	/* output (p[i] = i;):
	0
	-858993460
	1
	-858993460
	2
	*/
}

class CD01
{
public:

	void Watch()
	{
		printf("CC01 Watch\n");
	}

	virtual void Listen()
	{
		printf("CC01 Listen\n");
	}

	virtual void Read()
	{
		printf("CC01 Read\n");
	}
};

class CD02 : public CD01
{
public:

	void Watch()
	{
		printf("CC02 Watch\n");
	}

	void Listen()
	{
		printf("CC02 Listen\n");
	}

	virtual void Read()
	{
		printf("CC02 Listen\n");
	}
};

class CD03 : public CD02
{
public:

	void Listen()
	{
		printf("CC03 Listen\n");
	}

	virtual void Read()
	{
		printf("CC03 Listen\n");
	}
};

void _20191101()
{
	CC01 a1;
	CC01 a2;
	CC01& ref = a1;
	ref.e = 11L;
	ref = a2;
	ref.e = 33L;

	printf("output: %d  %d\n", a1.e, a2.e);
	//output: 33  -858993460
}

void _20191212()
{
	CD02 C1;
	C1.Watch();
	C1.Listen();
	C1.Read();

	/* output:

	CC02 Watch
	CC02 Listen
	CC02 Listen

	*/

	CD02* C2 = new CD02;
	C2->Watch();
	C2->Listen();
	C2->Read();
	delete C2;

	/* output:

	CC02 Watch
	CC02 Listen
	CC02 Listen

	*/

	CD01* C3 = new CD02;
	C3->Watch();
	C3->Listen();
	C3->Read();
	delete C3;

	/* output:

	CC01 Watch
	CC02 Listen
	CC02 Listen

	*/

	CD02* C4 = new CD03;
	C4->Watch();
	C4->Listen();
	C4->Read();
	delete C4;

	/* output:
	
	CC02 Watch
	CC03 Listen
	CC03 Listen

	*/
}

int main(int argc, char* args[])
{
	//_20190824();
	//_20190905();
	//_20190908();
	//_20190924();
	//_20191101();
	_20191212();

	system("pause");

	return 0;
}
