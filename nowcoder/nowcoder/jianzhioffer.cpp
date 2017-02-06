#include <iostream>
#include<vector>
#include <stack>
using namespace std;


struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {
	}
};

class Solution {
public:
	/*ͳ��һ�����������������г��ֵĴ�����*/
	int GetNumberOfK(vector<int> data, int k)
	{
		int count = 0;
		for (int i = 0; i < data.size(); i++)
		{
			if (data[i] == k)
			{
				count++;
			}
		}
		return count;

	}
	/*��һ���ַ���ת����һ��������Ҫ����ʹ���ַ���ת�������Ŀ⺯����
	��ֵΪ0�����ַ�������һ���Ϸ�����ֵ�򷵻�0
	��������:	����һ���ַ���,����������ĸ����,����Ϊ��
	�������:	����ǺϷ�����ֵ����򷵻ظ����֣����򷵻�0
	��������:	+2147483647	1a33
	�������:	2147483647	0
	*/
	int StrToInt(string str)
	{
		if (str.size() == 0)
		{
			return 0;
		}
		int  value = 0;

		//char* temp;
		/*temp = new char[str.size() + 1];
		strcpy_s(temp,strlen(temp), str.c_str());*//////ţ�����ϱ��벻ͨ�� ��Ϊstrcpy_s()û��
		const char * temp;
		temp = str.c_str();

		cout << temp << endl;

		if (temp[0] == '+' || temp[0] == '-')
		{
			for (int i = 1; temp[i] != '\0'; i++)
			{
				if (temp[i] >= '0' && temp[i] <= '9')
				{
					value = value * 10 + temp[i] - '0';
				}
				else
				{
					return 0;
				}
			}
			if (temp[0] == '+')
			{
				return value;
			}
			else
			{
				return -value;
			}

		}
		else if (temp[0] >= '0'&&temp[0] <= '9')
		{
			for (int i = 0; temp[i] != '\0'; i++)
			{
				if (temp[i] >= '0' && temp[i] <= '9')
				{
					value = value * 10 + temp[i] - '0';
				}
				else
				{
					return 0;
				}
			}
			return value;
		}
		return 0;////�����ţ�����ϱ���д ������벻ͨ����

	}
	/*������ջ��ʵ��һ�����У���ɶ��е�Push��Pop������
	�����е�Ԫ��Ϊint���͡�*/
	void push(int node)
	{
		stack1.push(node);
	}

	int pop()
	{
		int result, temp;
		while (!stack1.empty())//������Ԫ�طŵ�stack2��
		{
			temp = stack1.top();
			stack1.pop();
			stack2.push(temp);
		}
		result = stack2.top();//����һ��Ҫ�������еĵ�һ��Ԫ��
		stack2.pop();
		while (!stack2.empty())
		{
			temp = stack2.top();
			stack2.pop();
			stack1.push(temp);
		}
		return result;

	}

	/*��һ������Ϊn����������������ֶ���0��n-1�ķ�Χ�ڡ�
	������ĳЩ�������ظ��ģ�����֪���м����������ظ��ġ�
	Ҳ��֪��ÿ�������ظ����Ρ����ҳ�����������һ���ظ������֡�
	���磬������볤��Ϊ7������{2,3,1,0,2,5,3}��
	��ô��Ӧ��������ظ�������2����3��*/
	// Parameters:
	//        numbers:     an array of integers
	//        length:      the length of array numbers
	//        duplication: (Output) the duplicated number in the array number
	// Return value:       true if the input is valid, and there are some duplications in the array number
	//                     otherwise false
	bool duplicate(int numbers[], int length, int* duplication)
	{

		int *flags = new int[length];//
		for (int i = 0; i < length; i++)
		{
			flags[i] = 0;
		}
		for (int i = 0; i < length; i++)
		{
			flags[numbers[i]]++;
		}
		for (int i = 0; i < length; i++)
		{
			if (flags[i] >= 2)
			{
				*duplication = i;
			}

		}
		if (*duplication >= 0 && *duplication<length)
		{
			return true;
		}
		return false;


	}
	/*һ�����������������������֮�⣬���������ֶ����������Ρ�
	��д�����ҳ�������ֻ����һ�ε����֡�
	����˵�����ķ���������û̫���׺ô�����*/
	void FindNumsAppearOnce(vector<int> data, int* num1, int *num2)
	{
		if (data.size() < 2)
		{
			return;
		}
		bool flag = false;
		vector<int> result;
		for (int i = 0; i < data.size(); i++)
		{
			flag = false;
			for (int j = 0; j < data.size(); j++)
			{
				if (!flag && i != j && data[i] == data[j])
				{
					flag = true;
				}
			}
			if (!flag)
			{
				result.push_back(data[i]);
			}
		}
		*num1 = result[0];
		*num2 = result[1];////////////////����дnum1 = &result[0];  �������


	}
	/*��1+2+3+...+n��Ҫ����ʹ�ó˳�����for��while��if��else��switch��case
	�ȹؼ��ּ������ж���䣨A?B:C����*/
	int Sum_Solution(int n)
	{
		//�ο����˵ķ���������&&���� 666
		int sum = n;
		(n>0) && (sum += Sum_Solution(n - 1));

		return sum;
	}

	/*����һ������A[0,1,...,n-1],
	�빹��һ������B[0,1,...,n-1],����B�е�Ԫ��B[i]=A[0]*A[1]*...*A[i-1]*A[i+1]*...*A[n-1]��
	����ʹ�ó�����*/
	//���Ż�
	vector<int> multiply(const vector<int>& A)
	{
		int b = 1;
		vector<int> B;
		for (int i = 0; i < A.size(); i++)
		{
			b = 1;
			for (int j = 0; j < A.size(); j++)
			{
				if (j != i)
				{
					b *= A[j];
				}

			}
			B.push_back(b);
		}
		return B;
	}

	/*дһ������������������֮�ͣ�
	Ҫ���ں������ڲ���ʹ��+��-��*��/����������š�*/
	int Add(int num1, int num2)
	{
		/*1.���Ϊ������λ�ļӷ�
		2.��λ���󷨿���ͨ�� �������룺 1 1�Ż��1��Ȼ������1λ
		3.������2�Ͳ���1��ֵ���*/
		//if (num2 == 0)
		//	return num1;
		//int temp = num1^num2;	
		//int carry = (num1&num2) << 1;		
		//return Add(temp, carry);

		//�ǵݹ�汾
		while (num2 != 0)
		{
			int temp = num1^num2;
			num2 = (num1&num2) << 1;
			num1 = temp;
		}
		return num1;

	}
	/*����һ�����������飬����������������ƴ�������ų�һ������
	��ӡ��ƴ�ӳ���������������С��һ����
	������������{ 3��32��321 }��
	���ӡ���������������ųɵ���С����Ϊ321323��*/
	string PrintMinNumber(vector<int> numbers)
	{

	}

	/*��һ�������ʼ�����ɸ�Ԫ�ذᵽ�����ĩβ�����ǳ�֮Ϊ�������ת��
	����һ���ǵݼ�����������һ����ת�������ת�������СԪ�ء�
	��������{3,4,5,1,2}Ϊ{1,2,3,4,5}��һ����ת�����������СֵΪ1��
	NOTE������������Ԫ�ض�����0���������СΪ0���뷵��0��
	//����˵��2�ֲ������*/

	int minNumberInRotateArray(vector<int> rotateArray)
	{
		int size = rotateArray.size();
		if (size == 0)
		{
			return 0;
		}
		int min = rotateArray[0];
		for (int i = 0; i < size; i++)
		{

			if ((i + 1 < size) && (rotateArray[i]> rotateArray[i + 1]))
			{
				min = rotateArray[i + 1];
			}
		}
		return min;

	}

	/*����һ����������������е�����k����㡣*/
	ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
	{
		if (pListHead == NULL || k <= 0)
		{
			return NULL;
		}

		//���ȴ�ͷ��㿪ʼ  ����ͷ������ڷ���k ����� Ȼ���ͷ���ʹ˽ڵ�һ����ǰ�ƽ�
		//ֱ��ǰ���Ǹ���㵽���һ�����  ��ʱǰ���Ǹ���㼴Ϊ����
		ListNode *resultNode = pListHead;
		ListNode *currentNode = pListHead;
		for (int i = 0; i < k - 1; i++)
		{
			if (currentNode->next == NULL)
			{
				return NULL;
			}
			currentNode = currentNode->next;
		}

		while (currentNode->next != NULL)
		{
			resultNode = resultNode->next;
			currentNode = currentNode->next;
		}

		return resultNode;

	}
	/*����һ���������飬ʵ��һ�����������������������ֵ�˳��ʹ�����е�����λ�������ǰ�벿�֣�
	���е�ż��λ��λ������ĺ�벿�֣�����֤������������ż����ż��֮������λ�ò��䡣*/
	void reOrderArray(vector<int> &array)
	{
		//ɨ��һ�ˣ��ֱ��¼���� ��ż��
		vector<int> odd, even;

		for (int i = 0; i < array.size(); i++)
		{
			if (array[i] % 2 == 1)
			{
				odd.push_back(array[i]);
			}
			else
			{
				even.push_back(array[i]);
			}
		}
		int oddSize = odd.size();
		int evenSize = even.size();

		for (int i = 0; i < oddSize; i++)
		{
			array[i] = odd[i];
		}
		for (int j = oddSize; j < oddSize + evenSize; j++)
		{
			array[j] = even[j - oddSize];
		}

	}
	/*���ǿ�����2*1��С���κ��Ż�������ȥ���Ǹ���ľ��Ρ�
	������n��2*1��С�������ص��ظ���һ��2*n�Ĵ���Σ��ܹ��ж����ַ�����*/
	int rectCover(int number)
	{
		if (number == 1 || number == 2)
		{
			return number;
		}
		else
		{
			return rectCover(number - 1) + rectCover(number - 2);
		}
	}
	/*����һ��double���͵ĸ�����base��int���͵�����exponent����base��exponent�η���*/
	double Power(double base, int exponent)
	{
		double result = 1.0;

		if (exponent == 0)
		{
			return 1.0;
		}
		else if (exponent > 0)
		{
			for (int i = 0; i < exponent; i++)
			{
				result *= base;
			}
			return result;
		}
		else
		{
			exponent = -exponent;
			for (int i = 0; i < exponent; i++)
			{
				result *= base;
			}
			return 1 / result;
		}


	}
	/*����һ��������������������Ʊ�ʾ��1�ĸ��������и����ò����ʾ*/
	int  NumberOf1(int n) {
		//ÿһλ�����ж�
		int count = 0;
		int flag = 1;
		while (flag != 0) {
			if ((n & flag) != 0) {
				count++;
			}

			flag = flag << 1;
		}


		return count;
	}
private:
	stack<int> stack1;
	stack<int> stack2;
};

int main()
{
	//ListNode node0(0),node1(1),node2(2),node3(3);
	//node0.next = &node1;
	//node1.next = &node2;
	//node2.next = &node3;

	vector<int> test, result;
	for (int i = 1; i < 6; i++)
	{
		test.push_back(i);
	}
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);



	Solution sl;

	cout << sl.StrToInt("1a33");

	getchar();
	return 0;
}