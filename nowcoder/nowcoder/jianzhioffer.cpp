#include <iostream>
#include<vector>
#include <stack>
#include<map>
#include<list>
#include <sstream>
#include <algorithm>//里边有好多现成的函数
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

	/*输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。*/
	ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
	{//别人写的
		//ListNode* result = NULL;
		//ListNode* current = NULL;

		//if (pHead1 == NULL)return pHead2;
		//if (pHead2 == NULL)return pHead1;
		///*if (pHead1->val <= pHead2->val)//递归版本
		//{
		//	result = pHead1;
		//	result->next = Merge(pHead1->next, pHead2);
		//}
		//else
		//{
		//	result = pHead2;
		//	result->next = Merge(pHead1, pHead2->next);
		//}*/
		//	  
		//while (pHead1 != NULL && pHead2 != NULL){
		//	if (pHead1->val <= pHead2->val){
		//		if (result == NULL){
		//			current = result = pHead1;
		//		}
		//		else {
		//			current->next = pHead1;
		//			current = current->next;
		//		}
		//		pHead1 = pHead1->next;
		//	}
		//	else {
		//		if (result == NULL){
		//			current = result = pHead2;
		//		}
		//		else {
		//			current->next = pHead2;
		//			current = current->next;
		//		}
		//		pHead2 = pHead2->next;
		//	}
		//}

		//if (pHead1 == NULL)	current->next = pHead2;		
		//if (pHead2 == NULL)	current->next = pHead1;		
		//return result;

		if (pHead1 == NULL)return pHead2;
		if (pHead2 == NULL)return pHead1;

		ListNode* head = pHead2;
		ListNode* tempNode = pHead1->next;
		ListNode* tempNode2= pHead2;		
		while (pHead1)	//将list1中结点挨个插入到list2中的合适位置
		{
			bool isHead = true;//用来标记是否将list1的结点插入到list2的头部
			while (pHead2 && pHead1->val > pHead2->val)//找到合适位置 大于当前 
			{
				tempNode2 = pHead2;//tempNode2用来保存phead2前边结点
				pHead2 = pHead2->next;
				isHead = false;
			}
			if (isHead)//插入头部
			{				
				tempNode = pHead1->next;//保存list1中下一个结点
				pHead1->next = pHead2;
				//tempNode2->next = pHead1;
				head = pHead1;				
			}
			else//非头部
			{
				if (pHead2)//插入结点 此时list2中存在结点
				{
					tempNode = pHead1->next;//保存list1中下一个结点
					pHead1->next = pHead2;
					tempNode2->next = pHead1;					
				}
				else//插到list2最后
				{
					tempNode = pHead1->next;
					tempNode2->next = pHead1;
					pHead1->next = pHead2;//此时pHead2==NULL
				}
			}
			pHead1 = tempNode;//开始list1中的下一结点
			if (tempNode)
			{tempNode = tempNode->next;	
			}
			
			pHead2 = head; //从list2 的头开始遍历
		}

		return head;
	}
	/*数组中的逆序对：在数组中的两个数字，如果前面一个数字大于后面的数字，
	则这两个数字组成一个逆序对。输入一个数组,
	求出这个数组中的逆序对的总数P。并将P对1000000007取模的结果输出。
	即输出P%1000000007 
	题目保证输入的数组中没有的相同的数字
	输入例子:	1,2,3,4,5,6,7,0 
	输出例子:	7 */
	//：出处http://blog.csdn.net/ns_code/article/details/27520535
	long long MergePairsBetweenArray(int *arr, int *brr, int start, int mid, int end)
	{
		int i = mid;
		int j = end;
		int k = end;  //辅助数组的最后一位  
		long long count = 0;

		//设置两个指针i,j分别从右往左依次比较，  
		//将较大的依次放入辅助数组的右边  
		while (i >= start && j >= mid + 1)
		{
			if (arr[i] > arr[j])
			{
				count += j - mid;
				brr[k--] = arr[i--];
			}
			else
				brr[k--] = arr[j--];
		}

		//将其中一个数组中还剩下的元素拷贝到辅助数组中，  
		//两个循环只会执行其中的一个  
		while (i >= start)
			brr[k--] = arr[i--];
		while (j >= mid + 1)
			brr[k--] = arr[j--];

		//从辅助数组中将元素拷贝到原数组中，使其有序排列  
		for (i = end; i > k; i--)
			arr[i] = brr[i];

		return count;
	}
	long long CountMergePairs(int *arr, int *brr, int start, int end)
	{
		long long PairsNum = 0;
		if (start < end)
		{
			int mid = (start + end) >> 1;
			PairsNum += CountMergePairs(arr, brr, start, mid); //统计左边子数组的逆序对  
			PairsNum += CountMergePairs(arr, brr, mid + 1, end); //统计右边子数组的逆序对  
			PairsNum += MergePairsBetweenArray(arr, brr, start, mid, end); //统计左右子数组间的逆序对  
		}
		return PairsNum;
	}
	int InversePairs(vector<int> data)
	{
		if (data.size() == 0)return 0;
		long long count = 0;
		//for (int i = 0; i < data.size() - 1;i++)//时间复杂度太大 不通过
		//for (int j = i + 1; j < data.size(); j++)
		//if (data[i]>data[j])count++;
		
		//vector<int> temp(data.size());//初始化向量的大小
	
		int *brr = new int[data.size()];
		for (int i = 0; i < data.size();i++)
		{
			brr[i] = data[i];
		}
		int *temp = new int[data.size()];

		count = CountMergePairs(brr, temp, 0, data.size() - 1);


		return count % 1000000007;
	}
	/*在一个字符串(1<=字符串长度<=10000，全部由大写字母组成)
	中找到第一个只出现一次的字符,并返回它的位置*/
	int FirstNotRepeatingChar(string str)
	{
		if (str.size() == 0)return -1;
		//构造一个hash表 统计出现次数
		map<char, int> table;
		for (char i = 'A'; i <= 'Z';i++) table[i] = 0;
		char *p = new char[str.size()+1];  
		str.copy(p, str.size(), 0);
		
		for (int i = 0; i < str.size();i++)	table[str[i]]++;
		map<char, int>::iterator it;
		int pos = str.size();
		for (it = table.begin(); it != table.end();it++)
		{
			if (it->second == 1 && pos>str.find_first_of(it->first))//只出现一次
			{
				pos = str.find_first_of(it->first);
			}
		}
		if (pos == str.size())
		{
			return -1;
		}
		else
			return pos;
		
	}
	/*{6,-3,-2,7,-15,1,2,2},连续子向量的最大和为8(从第0个开始,到第3个为止(子向量的长度至少是1)*/
	int FindGreatestSumOfSubArray(vector<int> array)
	{
		if (array.size() < 1) return 0;
		int max = array[0],sum = 0;
		//int result = array[0];//作为记录单次遍历最大和
		
		//如果左边总和为负数 那么从下一个值开始 O(n)复杂度 效率高
		for (int i = 0; i < array.size();i++)
		{
			if (sum < 0)
			{
				sum = array[i];
			}
			else
			{
				sum += array[i];
			}
			if (max < sum)max = sum;
			
		}

		//for (int i = 0; i < array.size();i++) //效率低
		//{
		//	result = array[i];
		//	sum = 0;
		//	for (int j = i; j < array.size(); j++)
		//	{
		//		sum += array[j];
		//		if (result < sum)
		//		{
		//			result = sum;
		//		}
		//	}
		//	if (max<result)
		//	{
		//		max = result;
		//	}

		//}
		
		return max;
	}

	/*约瑟夫环 让编号为0的小朋友开始报数。每次喊到m-1的那个小朋友要出列,
	下一个继续0...m-1报,问最后剩下谁*/
	int LastRemaining_Solution(int n, int m)
	{
		if (n == 0)
			return -1;
		if (n == 1)
			return 0;
		else
			return (LastRemaining_Solution(n - 1, m) + m) % n;//参考的别人的

		if (m <= 0||n<1)return -1;
		list<int>* table = new list<int>();
		for (int i = 1; i <= n;i++)	table->push_back(i);
		
		int count = 1;
		for (list<int>::iterator it = table->begin(); table->size() != 1;)
		{			
			if (count == m)
			{
				cout << " " <<*it;
				it = table->erase(it);				
				count = 0;
			}
			else
			{
				it++;
			}
			if (it == table->end())
			{
				it = table->begin();
			}
			count++;
		}
		//cout << endl<<"The last one is:";
		cout << *table->begin() << endl;

		return *table->begin();
		return 0;

	}
	//堆排序，root为根节点下标
	void heapSort(vector<int> &input, int root, int end)
	{
		for (int j = end - 1; j >= root; j--)
		{
			int parent = (j + root - 1) / 2;
			if (input[parent] > input[j])
			{
				int temp = input[j];
				input[j] = input[parent];
				input[parent] = temp;
			}
		}
	}
	/*输入n个整数，找出其中最小的K个数。
	例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4,*/
	vector<int> GetLeastNumbers_Solution(vector<int> input, int k)
	{
		vector<int> result;
		if (input.size() < k||k<=0)return result;
		sort(input.begin(), input.end());
		for (int i = 0; i < k;i++)
		{
			result.push_back(input[i]);
		}
		return result;
	}
	/*输入一个字符串,按字典序打印出该字符串中字符的所有排列。
	例如输入字符串abc,则打印出由字符a,b,c所能排列出来的所有字符串
	abc,acb,bac,bca,cab和cba。输入一个字符串,长度不超过9(可能有字符重复),
	字符只包括大小写字母。*/
	void digui(char *sortStr, int begin, int end, vector<string>& result)
	{
		if (begin == end)
		{
			string str;
			//for (int i = 0; i < end; i++) str += sortStr[i];
			str = sortStr;
			result.push_back(str);
			//result.push_back(sortStr);//其实可以直接这样
			return;
		}
		else
		{
			for (int i = begin; i < end;i++)
			{	
				swap(sortStr[begin],sortStr[i]);
				digui(sortStr, begin+1, end, result);
				swap(sortStr[begin], sortStr[i]);
			}
		}

	}
	vector<string> Permutation(string str)
	{
		vector<string> result;
		if (str.size() == 0) return result;
	//	const char* tempStr = new char[str.size() + 1];tempStr = str.c_str();		
		char* sortStr = new char[str.size() + 1];//有了这个就可以啦
		//for (int i = 0; i < str.size(); i++) sortStr[i] = tempStr[i];
		str.copy(sortStr, str.size(),0);
		sortStr[str.size()] = '\0';
		cout << sortStr << endl;
		//递归
		digui(sortStr, 0, str.size(), result);
		sort(result.begin(), result.end());
		//for (int i = 0; i < str.size()-1;i++)//排序		
		//	for (int j = 0; j<str.size()-i-1;j++)			
		//		if (sortStr[j]>sortStr[j + 1]){ char temp = sortStr[j];	sortStr[j] = sortStr[j+1]; sortStr[j+1] = temp; }
			
		//去除重复项
		for (auto  it = result.begin() + 1; it != result.end();)
		{
			if (*it == *(it - 1))
				it = result.erase(it);
			else
				it++;
		}	

		return result;
		
	}
	vector<string> Permutation2(string str) {//网上看别人写的 LuL
		vector<string> out;
		int len = str.length();
		if (len == 0)
			return out;
		char* p = (char *)malloc((len + 1)*sizeof(char));
		str.copy(p, len, 0);

		//全排列，迭代
		myPermutation(p, 0, len, out);
		//字典序排序
		sort(out.begin(), out.end());
		//去除重复项
		for (auto it = out.begin() + 1; it != out.end();){
			if (*it == *(it - 1))
				it = out.erase(it);
			else
				it++;
		}
		return out;
	}

	void myPermutation(char* p, int k, int m, vector<string>& out){
		if (k == m){
			//将结果存入out中
			string s;
			for (int i = 0; i < m; ++i)
				s += p[i];
			out.push_back(s);
			return;
		}
		for (int i = k; i < m; ++i){
			swap(p[k], p[i]);
			myPermutation(p, k + 1, m, out);
			swap(p[k], p[i]);
		}
	}
	/*汇编语言中有一种移位指令叫做循环左移（ROL），现在有个简单的任务，就是用字符串模拟这个指令的运算结果。
	对于一个给定的字符序列S，请你把其循环左移K位后的序列输出。
	例如，字符序列S=”abcXYZdef”,要求输出循环左移3位后的结果，即“XYZdefabc”。*/
	string LeftRotateString(string str, int n)
	{
		if (str.size()==0 || n<0)	return "";
		if (n>str.size()) n %= str.size();
		const char*  sequence = str.c_str();
		char* roateStr = new char[str.size() + 1];
		char* doubleSeq = new char[2 * str.size()+1];  //建立一个双倍的字符串类似 abcXYZdefabcXYZdef可直接返回结果 
		for (int i = 0; i < str.size();i++)
		{
			doubleSeq[i] = sequence[i];
			doubleSeq[i+str.size()] = sequence[i];
		}
		doubleSeq[2 * str.size()] = '\0';
		for (int i = 0; i < str.size(); i++)///这种情况不需要开辟一个双倍空间了 复杂度为O（n）
		{
			//roateStr[i] = doubleSeq[i+n];
			if ((i+n)<str.size())
			{
				roateStr[i] = sequence[i + n];
			}
			else
			{
				roateStr[i] = sequence[i+n-str.size()];
			}
			
		}
		roateStr[str.size() + 1] = '\0';
		//cout << doubleSeq << endl;
		//cout << roateStr << endl;
		return roateStr;
	}
	/*数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
	例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。
	由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。*/
	int MoreThanHalfNum_Solution(vector<int> numbers)
	{//用map hash存储关键字 统计出现次数  看到别人用 map.count() 作为查找 good~
		if (numbers.size() == 0)
		{
			return 0;
		}
		map<int, int> mapValue;
		map<int, int>::iterator iter;
		for (int i = 0; i < numbers.size(); i++)
		{
			mapValue[numbers[i]] = 0;//初始化
		}
		for (int i = 0; i < numbers.size(); i++)//统计出现次数
		{		
			mapValue[numbers[i]]++;
		}
		for (iter = mapValue.begin(); iter != mapValue.end(); iter++)
		{
			if (iter->second*2 > numbers.size())
			{
				return iter->first;
			}
		}
		return 0;

	}
	/*牛客最近来了一个新员工Fish，每天早晨总是会拿着一本英文杂志，
	写些句子在本子上。同事Cat对Fish写的内容颇感兴趣，有一天他向Fish借来翻看，
	但却读不懂它的意思。例如，“student. a am I”。
	后来才意识到，这家伙原来把句子单词的顺序翻转了，
	正确的句子应该是“I am a student.”。
	Cat对一一的翻转这些单词顺序可不在行，你能帮助他么？*/
	string ReverseSentence(string str)
	{//下面6行是马克(Mark)的方法。。。够简洁。。学习了
		/*string res = "", tmp = "";
		for (unsigned int i = 0; i < str.size(); ++i){
			if (str[i] == ' ') res = " " + tmp + res, tmp = "";
			else tmp += str[i];
		}
		if (tmp.size()) res = tmp + res;
		return res;*/
		if (str.size() == 0) return str;///这块儿不能返回NULL 返回""就行
		
		//首先分出单词 然后统计单词个数 
		string reverse = "";
		const char *temp = str.c_str();
		cout << temp << endl;

		//split word
		int i = 0,wordStart = 0,wordEnd = 0;	
		vector<string> strVec;//保存所有单词
		while (temp[i] != '\0')
		{		
			if (temp[i] ==' ')//先假设单词间都是1个空格 结尾没有空格
			{
				wordEnd = i - 1;
				char word[128];
				int k = 0;
				for (int j = wordStart; j <= wordEnd;j++)//
				{					
					word[k] = temp[j];
					k++;
				}				
				word[k] = '\0';				
				strVec.push_back(word);				
				wordStart = i + 1;
			}			
			i++;
		}
		wordEnd = i - 1;	
		char word[128];
		int k = 0;
		for (int j = wordStart; j <= wordEnd; j++)//
		{			
			word[k] = temp[j];
			k++;
		}		
		word[k] = '\0';		
		strVec.push_back(word);		

		for (int i = 0; i < strVec.size()/2;i++)
		{
			string temp = strVec[i];
			strVec[i] = strVec[strVec.size() - 1 - i];
			strVec[strVec.size() - 1 - i] = temp;
		}

		for (int i = 0; i < strVec.size();i++)
		{
			//cout << strVec[i].c_str() << " ";
			if (i != strVec.size()-1)  reverse = reverse + strVec[i].c_str() + " ";
			else	reverse = reverse + strVec[i].c_str();
		}

		return reverse;
	}
	/*请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。
	例如，字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。
	但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是。*/
	bool isNumeric(char* string)
	{
		int i = 0;
		if (string[i] == '+' || string[i] == '-'||isdigit(string[i]))//判断第一位
		{
			while (string[++i] != '\0'&&isdigit(string[i]));//检测到第一个非数字符号
			
			if (string[i]=='.')
			{
				if (isdigit(string[++i]))//小数点后下一位是否是数字
				{
					while (string[++i] != '\0'&&isdigit(string[i]));//检测到第一个非数字符号

					if (string[i] == 'e' || string[i] == 'E')
					{
						i++;
						if (string[i] == '+' || string[i] == '-' || isdigit(string[i]))
						{
							while (string[++i] != '\0' && isdigit(string[i]));
							if (string[i] == '\0') return true;
							else return false;
						}
						else return false;
					}
					else if (string[i] == '\0')
					{
						return true;
					}
					else return false;
				}
				else
					return false;
			}
			else if (string[i] == 'e' || string[i] == 'E')
			{
				i++;
				if (string[i] == '+' || string[i] == '-' || isdigit(string[i]))
				{
					while (string[++i] != '\0' && isdigit(string[i]));
					if (string[i] == '\0') return true;
					else return false;
				}
				else return false;
			}
			else if (string[i] == '\0')
			{
				return true;
			}
			else
				return false;//其他情况 非数字
		}
		else
		{
			return false;
		}
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

		int *flags = new int[length];//标记数组
		for (int i = 0; i < length; i++)
		{
			flags[i] = 0;//初始化为0
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
	static bool compare(string str1,string str2)///需要加上static 修饰符
	{
		string s1 = str1 + str2;
		string s2 = str2 + str1;
		return s1 < s2;
	}
	string PrintMinNumber(vector<int> numbers)
	{
		string result;
		if (numbers.size() == 0)return result;

		vector<string> allResult;
		for (int i = 0; i < numbers.size();i++)
		{
			stringstream  ss;
			ss<<numbers[i];//将不同类型的值转换成string类型的好方法
			allResult.push_back(ss.str());
		}
		sort(allResult.begin(),allResult.end(),compare);
		for (int i = 0; i < numbers.size();i++)
		{
			result.append(allResult[i]);//值得学习的方法 
		}
		return result;
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
	ListNode node1(1), node2(2), node3(3), node4(4), node5(9),node6(5);
	ListNode* resultNode;
	node1.next = &node3;
	node2.next = &node4;
	node3.next = &node5;
	node4.next = &node6;

	vector<int> test;
	
	test.push_back(3);
	test.push_back(32);
	test.push_back(321);
	/*test.push_back(4);
	test.push_back(5);
	test.push_back(6);
	test.push_back(7);
	test.push_back(0);*/
	//test.push_back(2);


	Solution sl;
	vector<int> result;
	resultNode =sl.Merge(&node1,&node2);
	while (resultNode)
	{
		cout << resultNode->val << " ";
		resultNode = resultNode->next;
	}

	
	for (int i = 0; i < result.size();i++)
	{
		//cout << result[i] << endl;
	}
	

	getchar();
	return 0;
}