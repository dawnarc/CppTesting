
#include <iostream>
#include <list>
#include <vector>
#include <time.h>
#include <atomic>
#include <queue>
#include <mutex>
#include <memory>


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

//virtual function memory model
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

//re-assign for reference
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
		printf("CC02 Read\n");
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
		printf("CC03 Read\n");
	}
};

//virtual function usage cases
void _20191212()
{
	CD02 C1;
	C1.Watch();
	C1.Listen();
	C1.Read();

	/* output:

	CC02 Watch
	CC02 Listen
	CC02 Read

	*/

	printf("\n");

	CD02* C2 = new CD02;
	C2->Watch();
	C2->Listen();
	C2->Read();
	delete C2;

	/* output:

	CC02 Watch
	CC02 Listen
	CC02 Read

	*/

	printf("\n");

	CD01* C3 = new CD02;
	C3->Watch();
	C3->Listen();
	C3->Read();
	delete C3;

	/* output:

	CC01 Watch
	CC02 Listen
	CC02 Read

	*/

	printf("\n");

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

//base variable type value range
void _20191212_02()
{
	unsigned char a = 25U - 50;
	printf("%d", a);	//output: 231
}

void _20200610()
{
	char* data = (char*)malloc(2000);

	for(int i = 0; i < 8000; i++)
	{
		char val = data[i];
	}
}

void _20200625()
{
	const int32_t count = 10000000;
	
	/*volatile*/ int32_t val1 = 0;
	
	clock_t start1 = clock();
	for(int i = 0; i < count; i++)
	{
		val1++;
	}
	clock_t end1 = clock();

	printf("cost1: %dms\n", end1 - start1);

	std::atomic<std::int32_t> val2 = 0;

	clock_t start2 = clock();
	for (int i = 0; i < count; i++)
	{
		val2++;
	}
	clock_t end2 = clock();
	printf("cost2: %dms\n", end2 - start2);
}

struct TestStruct001
{
	TestStruct001()
	{
		printf("constructor\n");
	}
	
	TestStruct001(const TestStruct001& Ref)
	{
		printf("copy constructor\n");
		val = Ref.val;
	}

	int val;
};

void TestFun001(TestStruct001& Ref)
{
	TestStruct001 Stru001;
	Stru001.val = 2222;
	
	printf("aaaa\n");
	Ref = Stru001;
	printf("bbbb\n");
}

void _20200626()
{
	TestStruct001 Stru;
	Stru.val = 1111;

	printf("cccc %d\n", Stru.val);
	TestFun001(Stru);
	printf("dddd %d\n", Stru.val);

	TestStruct001 Stru2 = Stru;
}

void _20200626_2()
{
	TestStruct001 Stru;
	std::queue<TestStruct001> que;
	que.push(Stru);
}

class baz
{
	//virtual void fun() {}
public:

	int i = 0;
};

baz baz_val;

class c4
{
	//virtual void fun() {}
public:

	int i = 0;
	bool b = false;
};

class foo //: public base
{
public:

	std::mutex lock;

	int a;
	/*float arr1[1024] = { 0.f };
	int b;
	int c;
	float arr2[1024] = { 0.f };
	int d;
	float arr3[1024] = { 0.f };*/

	void fun1(std::string str)
	{
		//std::lock_guard<std::mutex> scope_lock(lock);
		printf("fun1");
	}

	void fun2()
	{
		//std::lock_guard<std::mutex> scope_lock(lock);

		//int a = 2;

		printf("fun2");
	}

	int b = 1;

	void fun3()
	{
		b = 444;
		printf("%f", b);
	}
};

class bar //: public base
{
	std::mutex lock2;

	//float arr[1024] = { 0.f };

public:

	void fun3()
	{
	}

	void fun4(baz& b)
	{
		float arr1[1024] = { 0.f };
		std::lock_guard<std::mutex> scope_lock(lock2);
		b.i = 111;
		printf("%d", b.i);
	}
};

std::shared_ptr<bar> bar_ptr2;

foo* initfun()
{
	float arr[1024] = { 0.f };
	int a = 1;
	return (foo*)&a;
}

void _20200703()
{
	//foo* f = new foo();
	//foo f;
	/*std::shared_ptr<foo> x(f);

	bar_ptr2 = std::shared_ptr<bar>((bar*)x.get());

	bar_ptr2->fun4(baz_val);*/

	foo* f = initfun();
	f->fun3();
}

int main(int argc, char* args[])
{
	//_20190824();
	//_20190905();
	//_20190908();
	//_20190924();
	//_20191101();
	//_20191212();
	//_20191212_02();
	//_20200610();
	//_20200625();
	//_20200626();
	//_20200626_2();	
	//_20200703();

	system("pause");

	return 0;
}

