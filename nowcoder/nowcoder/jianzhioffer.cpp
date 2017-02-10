#include <iostream>
#include<vector>
#include <stack>
#include<map>
#include<list>
#include <sstream>
#include <algorithm>//����кö��ֳɵĺ���
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
	/*�����е�����ԣ��������е��������֣����ǰ��һ�����ִ��ں�������֣�
	���������������һ������ԡ�����һ������,
	�����������е�����Ե�����P������P��1000000007ȡģ�Ľ�������
	�����P%1000000007 
	��Ŀ��֤�����������û�е���ͬ������
	��������:	1,2,3,4,5,6,7,0 
	�������:	7 */
	//������http://blog.csdn.net/ns_code/article/details/27520535
	long long MergePairsBetweenArray(int *arr, int *brr, int start, int mid, int end)
	{
		int i = mid;
		int j = end;
		int k = end;  //������������һλ  
		long long count = 0;

		//��������ָ��i,j�ֱ�����������αȽϣ�  
		//���ϴ�����η��븨��������ұ�  
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

		//������һ�������л�ʣ�µ�Ԫ�ؿ��������������У�  
		//����ѭ��ֻ��ִ�����е�һ��  
		while (i >= start)
			brr[k--] = arr[i--];
		while (j >= mid + 1)
			brr[k--] = arr[j--];

		//�Ӹ��������н�Ԫ�ؿ�����ԭ�����У�ʹ����������  
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
			PairsNum += CountMergePairs(arr, brr, start, mid); //ͳ�����������������  
			PairsNum += CountMergePairs(arr, brr, mid + 1, end); //ͳ���ұ�������������  
			PairsNum += MergePairsBetweenArray(arr, brr, start, mid, end); //ͳ�������������������  
		}
		return PairsNum;
	}
	int InversePairs(vector<int> data)
	{
		if (data.size() == 0)return 0;
		long long count = 0;
		//for (int i = 0; i < data.size() - 1;i++)//ʱ�临�Ӷ�̫�� ��ͨ��
		//for (int j = i + 1; j < data.size(); j++)
		//if (data[i]>data[j])count++;
		
		//vector<int> temp(data.size());//��ʼ�������Ĵ�С
	
		int *brr = new int[data.size()];
		for (int i = 0; i < data.size();i++)
		{
			brr[i] = data[i];
		}
		int *temp = new int[data.size()];

		count = CountMergePairs(brr, temp, 0, data.size() - 1);


		return count % 1000000007;
	}
	/*��һ���ַ���(1<=�ַ�������<=10000��ȫ���ɴ�д��ĸ���)
	���ҵ���һ��ֻ����һ�ε��ַ�,����������λ��*/
	int FirstNotRepeatingChar(string str)
	{
		if (str.size() == 0)return -1;
		//����һ��hash�� ͳ�Ƴ��ִ���
		map<char, int> table;
		for (char i = 'A'; i <= 'Z';i++) table[i] = 0;
		char *p = new char[str.size()+1];  
		str.copy(p, str.size(), 0);
		
		for (int i = 0; i < str.size();i++)	table[str[i]]++;
		map<char, int>::iterator it;
		int pos = str.size();
		for (it = table.begin(); it != table.end();it++)
		{
			if (it->second == 1 && pos>str.find_first_of(it->first))//ֻ����һ��
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
	/*{6,-3,-2,7,-15,1,2,2},����������������Ϊ8(�ӵ�0����ʼ,����3��Ϊֹ(�������ĳ���������1)*/
	int FindGreatestSumOfSubArray(vector<int> array)
	{
		if (array.size() < 1) return 0;
		int max = array[0],sum = 0;
		//int result = array[0];//��Ϊ��¼���α�������
		
		//�������ܺ�Ϊ���� ��ô����һ��ֵ��ʼ O(n)���Ӷ� Ч�ʸ�
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

		//for (int i = 0; i < array.size();i++) //Ч�ʵ�
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

	/*Լɪ�� �ñ��Ϊ0��С���ѿ�ʼ������ÿ�κ���m-1���Ǹ�С����Ҫ����,
	��һ������0...m-1��,�����ʣ��˭*/
	int LastRemaining_Solution(int n, int m)
	{
		if (n == 0)
			return -1;
		if (n == 1)
			return 0;
		else
			return (LastRemaining_Solution(n - 1, m) + m) % n;//�ο��ı��˵�

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
	//������rootΪ���ڵ��±�
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
	/*����n���������ҳ�������С��K������
	��������4,5,1,6,2,7,3,8��8�����֣�����С��4��������1,2,3,4,*/
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
	/*����һ���ַ���,���ֵ����ӡ�����ַ������ַ����������С�
	���������ַ���abc,���ӡ�����ַ�a,b,c�������г����������ַ���
	abc,acb,bac,bca,cab��cba������һ���ַ���,���Ȳ�����9(�������ַ��ظ�),
	�ַ�ֻ������Сд��ĸ��*/
	void digui(char *sortStr, int begin, int end, vector<string>& result)
	{
		if (begin == end)
		{
			string str;
			//for (int i = 0; i < end; i++) str += sortStr[i];
			str = sortStr;
			result.push_back(str);
			//result.push_back(sortStr);//��ʵ����ֱ������
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
		char* sortStr = new char[str.size() + 1];//��������Ϳ�����
		//for (int i = 0; i < str.size(); i++) sortStr[i] = tempStr[i];
		str.copy(sortStr, str.size(),0);
		sortStr[str.size()] = '\0';
		cout << sortStr << endl;
		//�ݹ�
		digui(sortStr, 0, str.size(), result);
		sort(result.begin(), result.end());
		//for (int i = 0; i < str.size()-1;i++)//����		
		//	for (int j = 0; j<str.size()-i-1;j++)			
		//		if (sortStr[j]>sortStr[j + 1]){ char temp = sortStr[j];	sortStr[j] = sortStr[j+1]; sortStr[j+1] = temp; }
			
		//ȥ���ظ���
		for (auto  it = result.begin() + 1; it != result.end();)
		{
			if (*it == *(it - 1))
				it = result.erase(it);
			else
				it++;
		}	

		return result;
		
	}
	vector<string> Permutation2(string str) {//���Ͽ�����д�� LuL
		vector<string> out;
		int len = str.length();
		if (len == 0)
			return out;
		char* p = (char *)malloc((len + 1)*sizeof(char));
		str.copy(p, len, 0);

		//ȫ���У�����
		myPermutation(p, 0, len, out);
		//�ֵ�������
		sort(out.begin(), out.end());
		//ȥ���ظ���
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
			//���������out��
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
	/*�����������һ����λָ�����ѭ�����ƣ�ROL���������и��򵥵����񣬾������ַ���ģ�����ָ�����������
	����һ���������ַ�����S���������ѭ������Kλ������������
	���磬�ַ�����S=��abcXYZdef��,Ҫ�����ѭ������3λ��Ľ��������XYZdefabc����*/
	string LeftRotateString(string str, int n)
	{
		if (str.size()==0 || n<0)	return "";
		if (n>str.size()) n %= str.size();
		const char*  sequence = str.c_str();
		char* roateStr = new char[str.size() + 1];
		char* doubleSeq = new char[2 * str.size()+1];  //����һ��˫�����ַ������� abcXYZdefabcXYZdef��ֱ�ӷ��ؽ�� 
		for (int i = 0; i < str.size();i++)
		{
			doubleSeq[i] = sequence[i];
			doubleSeq[i+str.size()] = sequence[i];
		}
		doubleSeq[2 * str.size()] = '\0';
		for (int i = 0; i < str.size(); i++)///�����������Ҫ����һ��˫���ռ��� ���Ӷ�ΪO��n��
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
	/*��������һ�����ֳ��ֵĴ����������鳤�ȵ�һ�룬���ҳ�������֡�
	��������һ������Ϊ9������{1,2,3,2,2,2,5,4,2}��
	��������2�������г�����5�Σ��������鳤�ȵ�һ�룬������2����������������0��*/
	int MoreThanHalfNum_Solution(vector<int> numbers)
	{//��map hash�洢�ؼ��� ͳ�Ƴ��ִ���  ���������� map.count() ��Ϊ���� good~
		if (numbers.size() == 0)
		{
			return 0;
		}
		map<int, int> mapValue;
		map<int, int>::iterator iter;
		for (int i = 0; i < numbers.size(); i++)
		{
			mapValue[numbers[i]] = 0;//��ʼ��
		}
		for (int i = 0; i < numbers.size(); i++)//ͳ�Ƴ��ִ���
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
	/*ţ���������һ����Ա��Fish��ÿ���糿���ǻ�����һ��Ӣ����־��
	дЩ�����ڱ����ϡ�ͬ��Cat��Fishд�������ĸ���Ȥ����һ������Fish����������
	��ȴ������������˼�����磬��student. a am I����
	��������ʶ������һ�ԭ���Ѿ��ӵ��ʵ�˳��ת�ˣ�
	��ȷ�ľ���Ӧ���ǡ�I am a student.����
	Cat��һһ�ķ�ת��Щ����˳��ɲ����У����ܰ�����ô��*/
	string ReverseSentence(string str)
	{//����6�������(Mark)�ķ�������������ࡣ��ѧϰ��
		/*string res = "", tmp = "";
		for (unsigned int i = 0; i < str.size(); ++i){
			if (str[i] == ' ') res = " " + tmp + res, tmp = "";
			else tmp += str[i];
		}
		if (tmp.size()) res = tmp + res;
		return res;*/
		if (str.size() == 0) return str;///�������ܷ���NULL ����""����
		
		//���ȷֳ����� Ȼ��ͳ�Ƶ��ʸ��� 
		string reverse = "";
		const char *temp = str.c_str();
		cout << temp << endl;

		//split word
		int i = 0,wordStart = 0,wordEnd = 0;	
		vector<string> strVec;//�������е���
		while (temp[i] != '\0')
		{		
			if (temp[i] ==' ')//�ȼ��赥�ʼ䶼��1���ո� ��βû�пո�
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
	/*��ʵ��һ�����������ж��ַ����Ƿ��ʾ��ֵ������������С������
	���磬�ַ���"+100","5e2","-123","3.1416"��"-1E-16"����ʾ��ֵ��
	����"12e","1a3.14","1.2.3","+-5"��"12e+4.3"�����ǡ�*/
	bool isNumeric(char* string)
	{
		int i = 0;
		if (string[i] == '+' || string[i] == '-'||isdigit(string[i]))//�жϵ�һλ
		{
			while (string[++i] != '\0'&&isdigit(string[i]));//��⵽��һ�������ַ���
			
			if (string[i]=='.')
			{
				if (isdigit(string[++i]))//С�������һλ�Ƿ�������
				{
					while (string[++i] != '\0'&&isdigit(string[i]));//��⵽��һ�������ַ���

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
				return false;//������� ������
		}
		else
		{
			return false;
		}
	}
	/*///����˵��˫�˶���~~~~~~~....���Ż�
	����һ������ͻ������ڵĴ�С���ҳ����л�����������ֵ�����ֵ��
	���磬�����������{2,3,4,2,6,2,5,1}���������ڵĴ�С3����ôһ������6���������ڣ�
	���ǵ����ֵ�ֱ�Ϊ{4,4,6,6,6,5}�� �������{2,3,4,2,6,2,5,1}�Ļ�������������6����
	{[2,3,4],2,6,2,5,1}�� {2,[3,4,2],6,2,5,1}�� {2,3,[4,2,6],2,5,1}��
	{2,3,4,[2,6,2],5,1}�� {2,3,4,2,[6,2,5],1}�� {2,3,4,2,6,[2,5,1]}��
	*/
	vector<int> maxInWindows(const vector<int>& num, unsigned int size)
	{
		vector<int> maxInWindow;
		if (size > num.size()|| size == 0) return maxInWindow;
		
		for (int i = 0; i < num.size() + 1 - size;i++)
		{
			//���±귶ΧΪ[i  i+1 ...i+size-1]�����ֵ
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
	/*��һ������������У������ظ��Ľ�㣬��ɾ�����������ظ��Ľ�㣬
	�ظ��Ľ�㲻��������������ͷָ�롣 
	���磬����1->2->3->3->4->4->5 �����Ϊ 1->2->5*/
	ListNode* deleteDuplication(ListNode* pHead)
	{//�ο����˵�˼·��д�ġ���ţ����id ��Charles_Lee
		
		if (pHead == NULL) return NULL;

		//����һ����ʱͷ��㣬��ֹͷ��㱻ɾ��
		ListNode* pTempHead = new ListNode(0);
		pTempHead->next = pHead;

		
		ListNode* pCur = pHead, *pLast = pTempHead;//ptemp
		int toDeleteVal = 0;
		while (pCur && pCur->next)
		{
			if (pCur->val == pCur->next->val)//��ǰֵ����һ����� �����ƶ� ֪������Ȼ��
			{
				toDeleteVal = pCur->val;
				while (pCur && pCur->val == toDeleteVal)
				{													
					pCur = pCur->next;
				}
				pLast->next = pCur;
			}
			else//��ǰ����һ������ȣ���ǰ�϶�����ɾ�� �ж���һ��
			{
				pLast = pCur;
				pCur = pCur->next;
			}

		}
		
		return pTempHead->next;
		
		
	}
	/*ͳ��һ�����������������г��ֵĴ��������Ϻö���ֲ��� �ݹ�ʲô�ġ��������Ż�*/
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

		int *flags = new int[length];//�������
		for (int i = 0; i < length; i++)
		{
			flags[i] = 0;//��ʼ��Ϊ0
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
	static bool compare(string str1,string str2)///��Ҫ����static ���η�
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
			ss<<numbers[i];//����ͬ���͵�ֵת����string���͵ĺ÷���
			allResult.push_back(ss.str());
		}
		sort(allResult.begin(),allResult.end(),compare);
		for (int i = 0; i < numbers.size();i++)
		{
			result.append(allResult[i]);//ֵ��ѧϰ�ķ��� 
		}
		return result;
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
	ListNode node0(1),node1(2),node2(2),node3(3);
	node0.next = &node1;
	node1.next = &node2;
	node2.next = &node3;

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
	cout << sl.isNumeric("1a3.14");
	
	for (int i = 0; i < result.size();i++)
	{
		//cout << result[i] << endl;
	}
	

	getchar();
	return 0;
}