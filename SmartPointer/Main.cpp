#include <iostream>
#include "SmartPointer.h"
using namespace std;
class Test
{
public:
	Test(){ cout << "Test()" << endl; };
	~Test(){ cout << "~Test()" << endl; };
	void fun(){};
};

void fun1()
{
	SmartPointer<Test> sp(new Test);
}
void fun2(SmartPointer<Test>& sp)
{
	SmartPointer<Test> sp1 = sp;
}
int main()
{

	fun1();
	{
		SmartPointer<Test> sp(new Test);
		fun2(sp);
	}
	SmartPointer<Test> sp1(new Test);
	sp1 = sp1;
	SmartPointer<Test> sp2(new Test);
	sp1 = sp2;

	system("pause");
	return 0;
}