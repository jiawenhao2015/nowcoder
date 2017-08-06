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


// C++�����ķ���ֵ�D�D������������&����������
// http://www.cnblogs.com/fly1988happy/archive/2011/12/14/2286908.html

int main2()
{
	//����"hello world"Ϊconst char*����string&������
	//����string��string(const char*)���캯���������������һ����ʱ������
	//���Խ������ʱ�������Ϊ������
	//more efficient c++ 19�ڣ�
	//bar�Ĳ���Ϊstring& s��˵��bar���ܻ����޸�s���ð󶨵Ķ���
	//�����ʱ������ķ���������һ����ʱ��������s�󶨣���ôbarֻ�ܶ������ʱ����������������programmer��ͼ��
	//���Ա�������ֹ�˽� ��ʱ���� ���ݸ� һ����const����ȥ�󶨡�
	//bar("hello world"); //�����

	//foo��������ʱ����a��copy��
	//�ٵ���string��string(const char*)���캯�����������������һ����ʱ����
	//barOK�Ĳ����ٰ󶨵������ʱ������
	barOK(foo());



	//��foo3�еľֲ�����������bar2��const����ȥ�󶨡�
	//��ôfoo3�еľֲ���������foo3������û�б����١����������gcc���Ż���
	//�����ʾfoo3�еľֲ����� �� bar2��s��ͬһ��ַ����foo3�ľֲ���������bar2����ʱ�����ġ�
	//���ﲢû�д���һ����ʱ���������������gcc���Ż���
	/*
	��������ʱ�Ĺ����������ģ��� �����п��ܲ�������ʱ�����ģ����������gcc���Ż��� ��
	����������ϣ�ִ�е�return���ʱ�������ڴ����Զ�����һ����ʱ������return��ֵ��ʼ�����������������ͣ������������ͣ�
	֮����ִ����ϣ��ֲ������ͷţ�ע���ʱ��ʱ���������ڣ�
	Ȼ���û�������Ҫ���ʻ��߲�������ʱ������
	�ȵ�ִ����һ����䣬��ʱ�����Զ����١�
	���Բ��ܷ��ؾֲ����������ã���Ϊ��ʱ����ָ����ڴ��Ѿ��ͷţ�
	*/
	bar3(foo3());
	return 0;
}
