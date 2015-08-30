#include <iostream>
#include "TraceLeakMarco.h"
#include <thread>
#include <string>
#include <chrono>
#include "Test.h"
using namespace std;
using namespace TraceLeak;

bool threadFlag = true;
void treadFun()
{
	while (threadFlag)
	{
		string* ps = new string();
		if (rand() % 2 == 0)
			delete ps;
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}
int main()
{
	//init();
	srand(time(NULL));
	int* i = new int;
	int* ii = new int[10];
	delete[] ii;
	addNode(nullptr,"",0);
	thread t1(treadFun);
	this_thread::sleep_for(chrono::milliseconds(30));
	thread t2(treadFun);
	this_thread::sleep_for(chrono::milliseconds(40));
	thread t3(treadFun);
	this_thread::sleep_for(chrono::milliseconds(20));

	this_thread::sleep_for(chrono::seconds(3));
	threadFlag = false;

	t1.join();
	t2.join();
	t3.join();

	::function();

	print();
	output("output.txt");
	system("pause");
	return 0;
}


/*
allocated memory without release:
file:e:\vs2013_projects\memorylearning\traceleak\test.cpp--line:6
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:15
file:e:\vs2013_projects\memorylearning\traceleak\main.cpp--line:25
请按任意键继续. . .

*/