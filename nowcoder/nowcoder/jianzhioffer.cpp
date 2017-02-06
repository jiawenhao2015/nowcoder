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
	/*请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。
	例如，字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。
	但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是。*/
	bool isNumeric(char* string)
	{

	}
	/*///网上说用双端队列~~~~~~~....待优化
	给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值。
	例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，那么一共存在6个滑动窗口，
	他们的最大值分别为{4,4,6,6,6,5}； 针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个：
	{[2,3,4],2,6,2,5,1}， {2,[3,4,2],6,2,5,1}， {2,3,[4,2,6],2,5,1}，
	{2,3,4,[2,6,2],5,1}， {2,3,4,2,[6,2,5],1}， {2,3,4,2,6,[2,5,1]}。
	*/
	vector<int> maxInWindows(const vector<int>& num, unsigned int size)
	{
		vector<int> maxInWindow;
		if (size > num.size()|| size == 0) return maxInWindow;
		
		for (int i = 0; i < num.size() + 1 - size;i++)
		{
			//在下标范围为[i  i+1 ...i+size-1]找最大值
			int max = num[i];

			for (int j = 0; j < size;j++)
			{
				if (max < num[i+j])
				{
					max = num[i+j];
				}
			}
			maxInWindow.push_back(max);
		}

		return maxInWindow;
	}
	/*在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，
	重复的结点不保留，返回链表头指针。 
	例如，链表1->2->3->3->4->4->5 处理后为 1->2->5*/
	ListNode* deleteDuplication(ListNode* pHead)
	{//参考别人的思路改写的。。牛客网id ：Charles_Lee
		
		if (pHead == NULL) return NULL;

		//定义一个临时头结点，防止头结点被删除
		ListNode* pTempHead = new ListNode(0);
		pTempHead->next = pHead;

		
		ListNode* pCur = pHead, *pLast = pTempHead;//ptemp
		int toDeleteVal = 0;
		while (pCur && pCur->next)
		{
			if (pCur->val == pCur->next->val)//当前值和下一个相等 往后移动 知道不相等或空
			{
				toDeleteVal = pCur->val;
				while (pCur && pCur->val == toDeleteVal)
				{													
					pCur = pCur->next;
				}
				pLast->next = pCur;
			}
			else//当前和下一个不相等，则当前肯定不被删除 判断下一个
			{
				pLast = pCur;
				pCur = pCur->next;
			}

		}
		
		return pTempHead->next;
		
		
	}
	/*统计一个数字在排序数组中出现的次数。网上好多二分查找 递归什么的。。。待优化*/
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
	/*将一个字符串转换成一个整数，要求不能使用字符串转换整数的库函数。
	数值为0或者字符串不是一个合法的数值则返回0
	输入描述:	输入一个字符串,包括数字字母符号,可以为空
	输出描述:	如果是合法的数值表达则返回该数字，否则返回0
	输入例子:	+2147483647	1a33
	输出例子:	2147483647	0
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
		strcpy_s(temp,strlen(temp), str.c_str());*//////牛客网上编译不通过 因为strcpy_s()没有
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
		return 0;////这儿在牛客网上必须写 否则编译不通过。

	}
	/*用两个栈来实现一个队列，完成队列的Push和Pop操作。
	队列中的元素为int类型。*/
	void push(int node)
	{
		stack1.push(node);
	}

	int pop()
	{
		int result, temp;
		while (!stack1.empty())//将所有元素放到stack2里
		{
			temp = stack1.top();
			stack1.pop();
			stack2.push(temp);
		}
		result = stack2.top();//保存一下要弹出队列的第一个元素
		stack2.pop();
		while (!stack2.empty())
		{
			temp = stack2.top();
			stack2.pop();
			stack1.push(temp);
		}
		return result;

	}

	/*在一个长度为n的数组里的所有数字都在0到n-1的范围内。
	数组中某些数字是重复的，但不知道有几个数字是重复的。
	也不知道每个数字重复几次。请找出数组中任意一个重复的数字。
	例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，
	那么对应的输出是重复的数字2或者3。*/
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
	/*一个整型数组里除了两个数字之外，其他的数字都出现了两次。
	请写程序找出这两个只出现一次的数字。
	网上说用异或的方法。。。没太明白好处在哪*/
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
		*num2 = result[1];////////////////这样写num1 = &result[0];  结果不对


	}
	/*求1+2+3+...+n，要求不能使用乘除法、for、while、if、else、switch、case
	等关键字及条件判断语句（A?B:C）。*/
	int Sum_Solution(int n)
	{
		//参考别人的方法，利用&&操作 666
		int sum = n;
		(n>0) && (sum += Sum_Solution(n - 1));

		return sum;
	}

	/*给定一个数组A[0,1,...,n-1],
	请构建一个数组B[0,1,...,n-1],其中B中的元素B[i]=A[0]*A[1]*...*A[i-1]*A[i+1]*...*A[n-1]。
	不能使用除法。*/
	//待优化
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

	/*写一个函数，求两个整数之和，
	要求在函数体内不得使用+、-、*、/四则运算符号。*/
	int Add(int num1, int num2)
	{
		/*1.异或为不带进位的加法
		2.进位的求法可以通过 两数相与： 1 1才会得1，然后左移1位
		3.将步骤2和步骤1的值相加*/
		//if (num2 == 0)
		//	return num1;
		//int temp = num1^num2;	
		//int carry = (num1&num2) << 1;		
		//return Add(temp, carry);

		//非递归版本
		while (num2 != 0)
		{
			int temp = num1^num2;
			num2 = (num1&num2) << 1;
			num1 = temp;
		}
		return num1;

	}
	/*输入一个正整数数组，把数组里所有数字拼接起来排成一个数，
	打印能拼接出的所有数字中最小的一个。
	例如输入数组{ 3，32，321 }，
	则打印出这三个数字能排成的最小数字为321323。*/
	string PrintMinNumber(vector<int> numbers)
	{

	}

	/*把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
	输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素。
	例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。
	NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。
	//网上说是2分查找最好*/

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

	/*输入一个链表，输出该链表中倒数第k个结点。*/
	ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
	{
		if (pListHead == NULL || k <= 0)
		{
			return NULL;
		}

		//首先从头结点开始  算上头结点在内访问k 个结点 然后从头结点和此节点一起向前推进
		//直到前边那个结点到最后一个结点  此时前边那个结点即为所求
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
	/*输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，
	所有的偶数位于位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。*/
	void reOrderArray(vector<int> &array)
	{
		//扫描一趟，分别记录奇数 和偶数
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
	/*我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。
	请问用n个2*1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？*/
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
	/*给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。*/
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
	/*输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示*/
	int  NumberOf1(int n) {
		//每一位均需判断
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
	ListNode node0(1),node1(2),node2(2),node3(3);
	node0.next = &node1;
	node1.next = &node2;
	node2.next = &node3;

	vector<int> test, result;
	
	test.push_back(2);
	test.push_back(3);
	test.push_back(4);
	test.push_back(2);
	test.push_back(6);
	test.push_back(2);
	test.push_back(5);
	test.push_back(1);


	Solution sl;

	result = sl.maxInWindows(test,0);
	
	for (int i = 0; i < result.size();i++)
	{
		cout << result[i] << " ";
	}
	

	getchar();
	return 0;
}