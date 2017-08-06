#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdio.h>


using namespace std;

class test
{
public:
	test(int input) : i(input)
	{
		cout << "In constructor test." << endl;
	}
	~test()
	{
		cout << "In disconstructor ~test." << endl;
	}

	test(const test &t)
	{
		i = t.i;
		cout << "In copy ----------- test." << endl;
	}
private:
	int i;
};



string foo()
{
	char *a = "haha";
	printf("In foo, address of haha: %d\n", a);
	return a;
}

void barOK(const string & s)
{
	printf("In barOK, address of s: %d\n", &s);
	return;
}

void bar(string & s)
{
	return;
}



test foo3()
{
	test ret(1);
	printf("In foo3, address of ret: %d\n", &ret);
	return ret;
}

void bar3(const test & s)
{
	printf("In bar3, address of s: %d\n", &s);
	//sleep( 3 );
	return;
}


// C++函数的返回值――返回引用类型&非引用类型
// http://www.cnblogs.com/fly1988happy/archive/2011/12/14/2286908.html

int main2()
{
	//首先"hello world"为const char*，与string&不符，
	//调用string的string(const char*)构造函数，这个函数生成一个临时变量，
	//可以将这个临时变量理解为常量。
	//more efficient c++ 19节，
	//bar的参数为string& s，说明bar可能会想修改s引用绑定的对象
	//如果这时按上面的方法生成了一个临时变量并用s绑定，那么bar只能对这个临时变量操作，不符合programmer意图。
	//所以编译器禁止了将 临时变量 传递给 一个非const引用去绑定。
	//bar("hello world"); //会出错

	//foo返回了临时对象即a的copy，
	//再调用string的string(const char*)构造函数，这个函数生成另一个临时变量
	//barOK的参数再绑定到这个临时变量上
	barOK(foo());



	//将foo3中的局部变量，传给bar2的const引用去绑定。
	//那么foo3中的局部变量，在foo3结束后，没有被销毁。这个可能是gcc的优化了
	//输出显示foo3中的局部变量 和 bar2的s是同一地址，且foo3的局部变量是在bar2结束时析构的。
	//这里并没有创建一个临时变量。这个可能是gcc的优化了
	/*
	函数返回时的过程是这样的：（ 还是有可能不创建临时变量的，这个可能是gcc的优化了 ）
	函数计算完毕，执行到return语句时，会在内存中自动定义一个临时变量以return的值初始化，（不管是类类型，还是内置类型）
	之后函数执行完毕，局部变量释放，注意此时临时变量还存在！
	然后用户根据需要访问或者不访问临时变量，
	等到执行下一条语句，临时变量自动销毁。
	所以不能返回局部变量的引用，因为临时变量指向的内存已经释放！
	*/
	bar3(foo3());
	return 0;
}
