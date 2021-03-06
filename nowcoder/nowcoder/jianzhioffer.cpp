﻿#include <iostream>
#include<vector>
#include <stack>
#include<map>
#include<list>
#include <sstream>
#include <algorithm>//里边有好多现成的函数
#include <queue>

using namespace std;

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {
	}
};
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {
	}
};
struct RandomListNode {
	int label;
	struct RandomListNode *next, *random;
	RandomListNode(int x) :
		label(x), next(NULL), random(NULL) {
	}
};
struct TreeLinkNode {
	int val;
	struct TreeLinkNode *left;
	struct TreeLinkNode *right;
	struct TreeLinkNode *next;
	TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
	}
};
class Solution {
public:
	/*请实现两个函数，分别用来序列化和反序列化二叉树*/
	TreeNode* decode(char *&str) {
		if (*str == '#'){
			str++;
			return NULL;
		}
		int num = 0;
		while (*str != ',')
			num = num * 10 + (*(str++) - '0');
		str++;
		TreeNode *root = new TreeNode(num);
		root->left = decode(str);
		root->right = decode(str);
		return root;
	}
	char* Serialize2(TreeNode *root) {
		if (!root) return "#";
		string r = to_string(root->val);
		r.push_back(',');
		char *left = Serialize(root->left);
		char *right = Serialize(root->right);
		char *ret = new char[strlen(left) + strlen(right) + r.size()];
		strcpy_s(ret, sizeof(r.c_str()),r.c_str());
		strcat(ret, left);
		strcat(ret, right);
		return ret;
	}
	TreeNode* Deserialize2(char *str) {
		return decode(str);
	}

	char* Serialize(TreeNode *root)
	{
		//先序遍历 中序遍历 保存结果
		if (root == NULL) return NULL;
		vector<TreeNode*>preOrder, inOrder;
		PreOrder(root, preOrder);
		InOrderTraverse(root, inOrder);
		
		char * combine = new char[preOrder.size()+inOrder.size()+1];
		for (int i = 0; i < preOrder.size();i++)
		{
			combine[i] = preOrder[i]->val;
		}
		for (int i = preOrder.size(); i < preOrder.size() + inOrder.size(); i++)
		{
			combine[i] = inOrder[i - preOrder.size()]->val;
		}
		combine[preOrder.size() + inOrder.size()] = '\0';
		return combine;
	}
	TreeNode* Deserialize(char *str)
	{
		int len = strlen(str);
		vector<int>preOrder, inOrder;
		for (int i = 0; i < len / 2;i++)
		{
			preOrder.push_back((int)str[i]);
		}
		for (int i = len/2; i < len; i++)
		{
			inOrder.push_back((int)str[i]);
		}

		return reConstructBinaryTree(preOrder, inOrder);
	}
	/*请实现一个函数用来匹配包括'.'和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（包含0次）。
		在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，
		但是与"aa.a"和"ab*a"均不匹配http://www.voidcn.com/blog/huzhigenlaohu/article/p-6087740.html*/	
	bool matchCore(char* str, int strIndex, char* pattern, int patternIndex)
	{
		//str到尾，pattern到尾，匹配成功
		if (strIndex == strlen(str) && patternIndex == strlen(pattern))return true;
		//str未到尾，pattern到尾，匹配失败
		if (strIndex != strlen(str) && patternIndex == strlen(pattern))	return false;

		//str到尾，pattern未到尾(不一定匹配失败，因为a*可以匹配0个字符)
		if (strIndex == strlen(str) && patternIndex != strlen(pattern)) {
			//只有pattern剩下的部分类似a*b*c*的形式，才匹配成功
			if (patternIndex + 1 < strlen(pattern) && pattern[patternIndex + 1] == '*') {
				return matchCore(str, strIndex, pattern, patternIndex + 2);
			}
			return false;
		}

		//str未到尾，pattern未到尾
		if (patternIndex + 1 < strlen(pattern) && pattern[patternIndex + 1] == '*')
		{
			if (pattern[patternIndex] == str[strIndex] || (pattern[patternIndex] == '.' && strIndex != strlen(str)))
			{
				return matchCore(str, strIndex, pattern, patternIndex + 2)//*匹配0个，跳过
					|| matchCore(str, strIndex + 1, pattern, patternIndex + 2)//*匹配1个，跳过
					|| matchCore(str, strIndex + 1, pattern, patternIndex);//*匹配1个，再匹配str中的下一个
			}
			else
			{
				//直接跳过*（*匹配到0个）
				return matchCore(str, strIndex, pattern, patternIndex + 2);
			}
		}
	}
	bool match(char* str, char* pattern)
	{
		if (strlen(str) == 0 || strlen(pattern) == 0)
		{
			return false;
		}
		int strIndex = 0;
		int patternIndex = 0;
		return matchCore(str, strIndex, pattern, patternIndex);
	}
	/*地上有一个m行和n列的方格。一个机器人从坐标0,0的格子开始移动，每一次只能向左，右，上，下四个方向移动一格，
	但是不能进入行坐标和列坐标的数位之和大于k的格子。 例如，当k为18时，机器人能够进入方格（35,37），
	因为3+5+3+7 = 18。但是，它不能进入方格（35,38），因为3+5+3+8 = 19。请问该机器人能够达到多少个格子？*/
	int sumOfDigits(int n)
	{
		int sum = 0;
		while (n>0)
		{
			sum += n % 10;
			n /= 10;
		}
		return sum;
	}
	int count(int threshold, int rows, int cols, int *flag,int i,int j)
	{
		if (i < 0 || i >= rows || j < 0 || j >= cols || sumOfDigits(i) + sumOfDigits(j) > threshold || flag[i*cols + j] == 1)
			return 0;
		flag[i*cols + j] = 1;

		return 1 + count(threshold, rows, cols, flag, i + 1, j) +
			       count(threshold, rows, cols, flag, i - 1, j) +
			       count(threshold, rows, cols, flag, i, j + 1) +
			       count(threshold, rows, cols, flag, i, j - 1);

	}
	int movingCount(int threshold, int rows, int cols)
	{		
		int* flag = new int[rows*cols];
		for (int i = 0; i < rows*cols;i++)
		{
			flag[i] = 0;
		}
		return count(threshold,rows,cols,flag,0,0);
	}
	/*请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一个格子开始，
	每一步可以在矩阵中向左，向右，向上，向下移动一个格子。如果一条路径经过了矩阵中的某一个格子，则该路径不能再进入该格子。
	例如 a b c e s f c s a d e e 矩阵中包含一条字符串"bccced"的路径，
	但是矩阵中不包含"abcb"路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入该格子。*/	
	/*这是一个可以用回朔法解决的典型题。http://www.voidcn.com/blog/huzhigenlaohu/article/p-6090898.html
	首先，在矩阵中任选一个格子作为路径的起点。如果路径上的第i个字符不是ch，那么这个格子不可能处在路径上的第i个位置。
	如果路径上的第i个字符正好是ch，那么往相邻的格子寻找路径上的第i+1个字符。除在矩阵边界上的格子之外，其他格子都有4个相邻的格子。
	重复这个过程直到路径上的所有字符都在矩阵中找到相应的位置。
	由于回朔法的递归特性，路径可以被开成一个栈。当在矩阵中定位了路径中前n个字符的位置之后，
	在与第n个字符对应的格子的周围都没有找到第n+1个字符，这个时候只要在路径上回到第n-1个字符，重新定位第n个字符。
	由于路径不能重复进入矩阵的格子，还需要定义和字符矩阵大小一样的布尔值矩阵，用来标识路径是否已经进入每个格子。
	当矩阵中坐标为（row,col）的格子和路径字符串中相应的字符一样时，从4个相邻的格子(row,col-1),(row-1,col),(row,col+1)
	以及(row+1,col)中去定位路径字符串中下一个字符如果4个相邻的格子都没有匹配字符串中下一个的字符，
	表明当前路径字符串中字符在矩阵中的定位不正确，我们需要回到前一个，然后重新定位。
	一直重复这个过程，直到路径字符串上所有字符都在矩阵中找到合适的位置*/
	bool isHasPath(char* matrix,int rows,int cols,int i,int j,char* str,int k,bool* flag)
	{
		int index = i*cols + j;
		if (i < 0 || i >= rows || j < 0 || j >= cols || matrix[index] != str[k] || flag[index]) return false;

		if (k == strlen(str) - 1) return true;
		
		flag[index] = true;

		if (isHasPath(matrix, rows, cols, i, j + 1, str, k + 1, flag) ||
			isHasPath(matrix, rows, cols, i, j - 1, str, k + 1, flag) ||
			isHasPath(matrix, rows, cols, i + 1, j, str, k + 1, flag) ||
			isHasPath(matrix, rows, cols, i - 1, j, str, k + 1, flag) )			
		{
			return true;
		}
		flag[index] = false;
		return false;
	}
	bool hasPath(char* matrix, int rows, int cols, char* str)
	{
		if (strlen(matrix)<rows*cols || strlen(str)>strlen(matrix)) return false;

		bool* flag = new bool[rows*cols];//标记该位置是否有效		
		for (int i = 0; i < rows*cols; i++)flag[i] = false;		
		for (int i = 0; i < rows;i++)
		{ 
			for (int j = 0; j < cols;j++)
			{
				if (isHasPath(matrix, rows, cols, i, j, str,0, flag))
					return true;
			}			
		}

		delete[] flag;
		return false;
	}
	/*输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。
	假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
	例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。*/
	TreeNode* ConstructTree(vector<int>&pre, vector<int>&vin,int preLeft,int preRight,int vinLeft,int vinRight)
	{
		if (preLeft > preRight || vinLeft> vinRight)return NULL;

		TreeNode* root = new TreeNode(0);
		root->val = pre[preLeft];

 		int index = vinLeft;
		while (vin[index] != pre[preLeft])index++;//在中序遍历中找到根节点位置
		int length = index - vinLeft;//左子树节点个数
		//int length2 = vinRight - index;//右子树节点个数

		TreeNode* leftTree = ConstructTree(pre, vin, preLeft + 1, preLeft+length,index-length,index -1);//注意下标
		TreeNode* rightTree = ConstructTree(pre, vin, preLeft+length + 1,preRight,index+1,vinRight );

		root->left = leftTree;
		root->right = rightTree;
		return root;
	}
	TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin)
	{
		if (pre.size() == 0||pre.size()!=vin.size()) return NULL;

		TreeNode* root = new TreeNode(0);		
		root->val = pre[0];		
		root = ConstructTree(pre, vin, 0, pre.size() - 1, 0, vin.size() - 1);
		return root;
	}
	/*输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
	如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。*/
	bool isOK(vector<int>&a,int left,int right)
	{//抄的 马克（Mark）
		if (left >= right) return true;
		int  i = right;
		while (i > left && a[i - 1] > a[right])i--;//a[right]为根 找到中间左右子树界限
		for (int j = i - 1; j >= left;j--)
		{
			if (a[j] > a[right])return false;//如果左子树有大于根的 返回FALSE
		}
		return isOK(a, left, i - 1) && isOK(a, i, right - 1);
	}
	bool VerifySquenceOfBST(vector<int> sequence)
	{//BST的后序序列的合法序列是，对于一个序列S，最后一个元素是x （也就是根），如果去掉最后一个元素的序列为T，
	//那么T满足：T可以分成两段，前一段（左子树）小于x，后一段（右子树）大于x，且这两段（子树）都是合法的后序序列。完美的递归定义 : ) 。
		if (sequence.size() == 0)return false;
		return isOK(sequence,0,sequence.size()-1);
		
	}
	/*输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。
	要求不能创建任何新的结点，只能调整树中结点指针的指向。*/
	void InOrderNonRecursiveTraverse(TreeNode*pRoot, vector<TreeNode*>& result)//非递归中序遍历
	{
		if (pRoot == NULL)return;
		stack<TreeNode*>st;
		while (pRoot!=NULL||!st.empty())
		{
			while (pRoot != NULL)
			{
				st.push(pRoot);
				pRoot = pRoot->left;//最左端
			}
			if (!st.empty())
			{
				pRoot = st.top();//出栈
				st.pop();
				result.push_back(pRoot);
				pRoot = pRoot->right;//向右边遍历
			}
		}
	}
	TreeNode* Convert(TreeNode* pRootOfTree)
	{//首先中序遍历，存储在一个vector里 然后遍历vector建立链表 别人貌似不是这么做的。。么有用vector存储一遍的
		if (pRootOfTree == NULL)return pRootOfTree;
		vector<TreeNode*> result;
		InOrderTraverse(pRootOfTree, result);
		
		for (int i = 0; i < result.size()-1; i++)
		{
			result[i]->right = result[i + 1];
			result[i + 1]->left = result[i];
		}
		
		return result[0];		
	}

	/*给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。
	注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。*/	
	TreeLinkNode* GetNext(TreeLinkNode* pNode)
	{
		if (pNode == NULL) return NULL;
		if (pNode->right!=NULL)//有右子树
		{
			pNode = pNode->right;
			while (pNode->left!=NULL)
			{
				pNode = pNode->left;
			}
			return pNode;
		}

		TreeLinkNode* parent = pNode->next;
		while (parent!=NULL )//父亲的父亲的。。。父亲为空停止循环 或者找到 作为父亲的左孩子为止&& parent->next->left != parent 
		{
			if (parent->left == pNode)//if (parent->next->left ==parent)//原来是这么写的 不对！！！
			{
				return parent;//return parent->next;
			}
			pNode = parent;
			parent = parent->next;
			
		}			
		
		return NULL;
		
	}
	/*给定一颗二叉搜索树，请找出其中的第k大的结点。
	例如， 5 / \ 3 7 /\ /\ 2 4 6 8 中，按结点数值大小顺序第三个结点的值为4。*/
	void InOrderTraverse(TreeNode*pRoot, vector<TreeNode*>& result)
	{
		if (pRoot!=NULL)
		{
			InOrderTraverse(pRoot->left, result);
			result.push_back(pRoot);
			InOrderTraverse(pRoot->right, result);
		}
	}
	TreeNode* KthNode(TreeNode* pRoot, int k)
	{//首先中序遍历 然后返回kth值。。。效率太低了吧。。但是暂时没有高效率方法
		if (pRoot == NULL || k <= 0) return NULL;
		vector<TreeNode*> result;
		InOrderTraverse(pRoot,result);

		if (k > result.size()) return NULL;
		return result[k - 1];		
	}
	/*输入一棵二叉树，判断该二叉树是否是平衡二叉树。*/
	//网上有复杂度为O（n）方法
	int getTreeDepth(TreeNode* pRoot)
	{
		if (pRoot == NULL) return 0;
		return 1+max(getTreeDepth(pRoot->left),getTreeDepth(pRoot->right));
	}
	bool IsBalanced_Solution(TreeNode* pRoot)
	{
		if (pRoot == NULL) return true;
		if (!IsBalanced_Solution(pRoot->left))return false;
		if (!IsBalanced_Solution(pRoot->right))return false;

		int leftDepth = getTreeDepth(pRoot->left);
		int rightDepth = getTreeDepth(pRoot->right);

		if (abs(leftDepth - rightDepth) > 1) return false;
		return true;
	}
	/*输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针指向任意一个节点），
	返回结果为复制后复杂链表的head。（注意，输出结果中请不要返回参数中的节点引用，否则判题程序会直接返回空）*/
	RandomListNode* Clone(RandomListNode* pHead)
	{
		if (pHead == NULL)
			return NULL;

		//开辟一个新节点
		RandomListNode* pClonedHead = new RandomListNode(pHead->label);
		pClonedHead->next = pHead->next;
		pClonedHead->random = pHead->random;

		//递归其他节点
		pClonedHead->next = Clone(pHead->next);

		return pClonedHead;
		/*if (pHead == NULL)return pHead;
		RandomListNode* tempPre = new RandomListNode(0);
		tempPre->label = pHead->label;
		pHead = pHead->next;
		while (pHead != NULL)
		{
			RandomListNode* tempCur = new RandomListNode(0);
			RandomListNode* tempRandom = new RandomListNode(0);
			tempPre->next = tempCur;
			tempPre->random = tempRandom;

			tempCur->label = pHead->label;			

			temp->label = pHead->label;
			temp->next = pHead->next;
			temp->random = pHead->random;
			pHead = pHead->next;
		}*/
	}
	/*如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。
	如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。
	*/
	///别人貌似都不是这么做的。。不知道为啥他们都用堆结构等等。。。不是舍近求远么 
	vector<int> data;
	void Insert(int num)
	{
		data.push_back(num);
	}
	double GetMedian()
	{
		sort(data.begin(),data.end());
		if (data.size() % 2 == 1)
		{
			return data[data.size() / 2];
		}
		else
			return (data[data.size() / 2] + data[data.size() / 2 - 1]) / 2.0;
	}
	/*一个链表中包含环，请找出该链表的环的入口结点。*/
	ListNode* EntryNodeOfLoop(ListNode* pHead)
	{
		if (pHead == NULL)return NULL;
		map<ListNode*, int> table;//用来记录访问次数
		ListNode* entry= NULL;
		while (pHead!=NULL)
		{
			table[pHead]++;
			if (table[pHead]==2)
			{
				return pHead;
			}
			pHead = pHead->next;
		}
		return entry;
	}
	/*输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构）*/
	/*class Solution {//别人 de
		bool isSubtree(TreeNode* pRootA, TreeNode* pRootB) {
			if (pRootB == NULL) return true;
			if (pRootA == NULL) return false;
			if (pRootB->val == pRootA->val) {
				return isSubtree(pRootA->left, pRootB->left)
					&& isSubtree(pRootA->right, pRootB->right);
			}
			else return false;
		}
	public:
		bool HasSubtree(TreeNode* pRootA, TreeNode* pRootB)
		{
			if (pRootA == NULL || pRootB == NULL) return false;
			return isSubtree(pRootA, pRootB) ||
				HasSubtree(pRootA->left, pRootB) ||
				HasSubtree(pRootA->right, pRootB);
		}
	};*/
	void PreOrder(TreeNode* pRoot, vector<TreeNode*>& result)
	{
		if (pRoot != NULL)
		{
			result.push_back(pRoot);
			PreOrder(pRoot->left, result);			
			PreOrder(pRoot->right, result);
		}
	}
	bool isContain2(vector<TreeNode*>order1, vector<TreeNode*>order2)
	{//子串是否包含函数
		int N = order1.size();
		int M = order2.size();			
		for (int i = 0; i <= N - M; i++)//判断连续子串 只需到N-M
		{
			int j;
			for (j = 0; j < M; j++)
			{
				if (order1[i + j]->val != order2[j]->val)//是order1[i + j]->val相等 不是order1[i + j]相等
					break;
			}
			if (j == M)
			{
				return true;
			}
		}
		return false;
	}
	/*测试用例:{8,8,7,9,2,#,#,#,#,4,7},{8,9,2} true*/
	bool isContain(vector<TreeNode*>order1, vector<TreeNode*>order2)
	{
		int N = order1.size();
		int M = order2.size();
		int j = 0;
		for (int i = 0; i < N; i++)//边界条件！此题不需要连续子串
		{
						
			if (j<M && order1[i]->val==order2[j]->val)
			{
				j++;
			}			
			if (j == M)
			{
				return true;
			}
		}
		return false;
	}
	bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
	{//中序遍历和前序遍历 生成字符串 同理判断是否存在包含关系
		if (pRoot1 == NULL || pRoot2 == NULL) return false;
		vector<TreeNode*>inOrder1, inOrder2,preOrder1,preOrder2;
		PreOrder(pRoot1, preOrder1);
		PreOrder(pRoot2, preOrder2);

		InOrderTraverse(pRoot1, inOrder1);
		InOrderTraverse(pRoot2, inOrder2);

		//判断是否是子串关系
		if (isContain(preOrder1, preOrder2) && isContain(inOrder1, inOrder2))
			return true;
		
		return false;

	}
	/*请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，
	第二层按照从右至左的顺序打印，第三行按照从左到右的顺序打印，其他行以此类推。*/	
	vector<vector<int> > Print2(TreeNode* pRoot)
	{
		vector<vector<int> > result;
		if (pRoot==NULL)return result;
		//首先层次遍历 最后将偶数层 翻转。。。。效率貌似不高。。。 高效率就是 访问偶数层的时候  反着插入
		queue<TreeNode*>myqueue;
		myqueue.push(pRoot);
	    int flag = 1;//flag 表示奇数还是偶数层
		while (!myqueue.empty())
		{
			int index = 0, levelSize = myqueue.size();
			vector<int> level;
			TreeNode* temp;
			
			while (index++ < levelSize)
			{
				temp = myqueue.front();
				myqueue.pop();
				vector<int>::iterator it;

				if (flag==1)//第奇数层
				{									
					level.push_back(temp->val);
				}
				else//第偶数层
				{
					it = level.begin();
					level.insert(it, temp->val);							
				}
				if (temp->left)	myqueue.push(temp->left);
				if (temp->right)myqueue.push(temp->right);
			}
			result.push_back(level);
			level.clear();
			if (flag == 1)flag = 0;
			else if (flag == 0)flag = 1;
		}
		return result;

	}
	/*从上到下按层打印二叉树，同一层结点从左至右输出。每一层输出一行。*/
	vector<vector<int> > Print(TreeNode* pRoot)
	{
		/*  vector<vector<int>> ret;
		if (pRoot == NULL) return ret;

		queue<TreeNode*> q;
		q.push(pRoot);

		while (!q.empty())
		{
		int low = 0, high = q.size();
		vector<int> level;
		TreeNode *tmp;

		while (low++ < high)     //按层次来!!!
		{
		tmp = q.front();
		q.pop();
		level.push_back(tmp->val);
		if (tmp->left)
		q.push(tmp->left);
		if (tmp->right)
		q.push(tmp->right);
		}
		ret.push_back(level);
		level.clear();
		}
		return ret;*/

		vector<vector<int>> result;
		if (pRoot == NULL)return result;
		queue<TreeNode*> myqueue;
		myqueue.push(pRoot);
		int i = 0, levelLen = 1,nextLevelLen = 0;//当前索引  当前层的长度  下一层长度 貌似看别人的方法不用求 利用queue.size 统计队内元素个数
		while (!myqueue.empty())
		{
			vector<int> temp;
			while (i < levelLen)
			{
				temp.push_back(myqueue.front()->val);
				if (myqueue.front()->left!=NULL)
				{
					myqueue.push(myqueue.front()->left);
					nextLevelLen++;
				}
				if (myqueue.front()->right != NULL)
				{
					myqueue.push(myqueue.front()->right);
					nextLevelLen++;
				}
				myqueue.pop();
				if (i == levelLen-1)//本层最后一个元素  将本层遍历过的元素保存 
				{
					result.push_back(temp);					
				}				
				i++;
			}
			levelLen = nextLevelLen; //本层遍历结束 进入下一层
			nextLevelLen = 0;
			i = 0;//每层从头开始			
		}
		return result;
	}
	/*从上往下打印出二叉树的每个节点，同层节点从左至右打印。*/
	vector<int> PrintFromTopToBottom(TreeNode* root)
	{ //层序遍历
		vector<int> result;
		queue<TreeNode*> myqueue;
		if (root == NULL)  return result;

		myqueue.push(root);
		while (!myqueue.empty())
		{
			result.push_back(myqueue.front()->val);
			if (myqueue.front()->left != NULL)
			{
				myqueue.push(myqueue.front()->left);
			}
			if (myqueue.front()->right != NULL)
			{
				myqueue.push(myqueue.front()->right);
			}
			myqueue.pop();
		}

		return result;

	}
	/*请实现一个函数，用来判断一颗二叉树是不是对称的。
	注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的*/
	bool Symmetrical(TreeNode* pLeft, TreeNode* pRight)
	{
		if (pLeft == NULL && pRight == NULL)return true;
		if ((pLeft == NULL&&pRight != NULL) || (pLeft != NULL&&pRight == NULL))return false;		
		if (pLeft->val != pRight->val)return false;
		
		return Symmetrical(pLeft->left, pRight->right) && Symmetrical(pLeft->right, pRight->left);		
	}
	bool isSymmetrical(TreeNode* pRoot)
	{
		if (pRoot == NULL)return true;
		return Symmetrical(pRoot, pRoot);
	}
	/*输入一颗二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。
	路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。*/
	vector<vector<int>> result;
	vector<int> temp;
	void Traverse(TreeNode* root, int expectNumber)
	{
		temp.push_back(root->val);
		if (expectNumber == root->val && root->left==NULL && root->right ==NULL)//正好找到为叶结点
		{
			result.push_back(temp);
		}
		else
		{
			if(root->left)Traverse(root->left, expectNumber - root->val);
			if(root->right)Traverse(root->right, expectNumber - root->val);
		}
		temp.pop_back(); //深度遍历 要回退一个结点
	}
	vector<vector<int> > FindPath(TreeNode* root, int expectNumber)
	{		
		if (root == NULL ) return result;

		Traverse(root,expectNumber);
		return result;
	}
	/*操作给定的二叉树，将其变换为源二叉树的镜像。 */
	void Mirror(TreeNode *pRoot)
	{//递归 类似先序遍历
		if (pRoot == NULL)return;
		TreeNode* temp = pRoot->left;
		pRoot->left = pRoot->right;
		pRoot->right = temp;
		Mirror(pRoot->left);
		Mirror(pRoot->right);
		
	}
	/*求出1~13的整数中1出现的次数,并算出100~1300的整数中1出现的次数？为此他特别数了一下1~13中包含1的数字有1、10、11、12、13因此共出现6次,
	但是对于后面问题他就没辙了。ACMer希望你们帮帮他,并把问题更加普遍化,可以很快的求出任意非负整数区间中1出现的次数。*/
	int PowerBase10(unsigned int n)
	{		// 10^n
		int result = 1;
		for (unsigned int i = 0; i < n; ++i)
			result *= 10;
		return result;
	}
	int b10(unsigned int n)
	{
		return PowerBase10(n);
	}
	int NumberBitCount(unsigned int n)
	{
		int N = 0;
		while (n)
		{
			n = n / 10;
			N++;
		}
		return N;
	}
	int NumberOf1Between1AndN_Solution(int n)
	{//看不懂 抄的http://www.cnblogs.com/hellogiser/p/3738812.html
		// T(n) = o(N) = o(lgn)
		if (n<=0)
		{
			return 0;
		}
		int N = NumberBitCount(n);
		int si, sum = 0;
		int A, B, bi, ri;
		for (int i = 1; i <= N; i++)
		{
			A = n / b10(i) * b10(i - 1);
			bi = n / b10(i - 1) % 10;
			ri = n % b10(i - 1);
			if (bi == 0)
			{
				B = 0;
			}
			else if (bi == 1)
			{
				B = ri + 1;
			}
			else if (bi > 1)
			{
				B = b10(i - 1);
			}
			si = A + B;
			sum += si;
		}
		return sum;
	}
	/*输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。
	假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，
	序列4，5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。
	（注意：这两个序列的长度是相等的）*/
	bool IsPopOrder(vector<int> pushV, vector<int> popV)
	{//设置一个辅助栈，将pushV中的数字依次压入栈中，一直检查栈顶元素是否与popV中的第一个数字相等，
	 //如果相等则弹出栈，不相等就接着将pushV中数字push进栈，直到将所有数字都入栈，如果最后栈不空，则不是弹出序列
		/*        if(pushV.size() == 0) return false;//别人的简洁
		vector<int> stack;
		for(int i = 0,j = 0 ;i < pushV.size();){
		stack.push_back(pushV[i++]);
		while(j < popV.size() && stack.back() == popV[j]){
		stack.pop_back();
		j++;
		}
		}
		return stack.empty();*/
		if (pushV.size() != popV.size() || pushV.size()<1 || popV.size()<1)return false;
		
		stack<int>temp;
		int i=1,j = 0;
		temp.push(pushV[0]);
		while (1)
		{
			while (temp.top() != popV[j] && i < pushV.size())
			{
				temp.push(pushV[i++]);
			}
			if (temp.top() == popV[j])
			{
				temp.pop();
				j++;
			}
			else //将pushV里的数字都入栈了也没有找到
			{
				return false;
			}
			if (temp.size() == 0) //栈最后为空 或者popV为空 说明都匹配完毕
			{
				return true;
			}
		}		
		return false;//yong 不上 
	}
	/*把只包含因子2、3和5的数称作丑数（Ugly Number）。
	例如6、8都是丑数，但14不是，因为它包含因子7。
	习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。*/
	int GetUglyNumber_Solution(int index)
	{//参考作者博客http://zhedahht.blog.163.com/blog/static/2541117420094245366965/
		if (index < 1)return index;
		vector<int>ugly;
		ugly.push_back(1);
		int index2 = 0, index3 = 0, index5 = 0;
		int i = 1;
		while (i<index)
		{			
			ugly.push_back(std::min(ugly[index2] * 2, std::min(ugly[index3] * 3, ugly[index5] * 5)));
			while (ugly[index2] * 2 <= ugly[i])
				index2++;
			while (ugly[index3] * 3 <= ugly[i])
				index3++;
			while (ugly[index5] * 5 <= ugly[i])
				index5++;
			i++;
		}
		return ugly[index - 1];
	}
	/*请实现一个函数用来找出字符流中第一个只出现一次的字符。*/
	//Insert one char from stringstream
	//用map来统计出现次数
	map<char, int>table;
	vector<char>charStream;
	void Insert(char ch)
	{
		charStream.push_back(ch);
		table[ch]++;
	}
	//return the first appearence once char in current stringstream
	char FirstAppearingOnce()
	{
		vector<char>::iterator it;
		for (it = charStream.begin(); it != charStream.end();it++)
		{
			if (table[*it]==1)
			{
				return *it;
			}
		}
		return '#';
	}
	/*输入两个链表，找出它们的第一个公共结点。*/
	int getListLength(ListNode* pHead)
	{
		int length = 0;
		if (pHead == NULL)return length;
		while (pHead)
		{
			pHead = pHead->next;
			length++;
		}
		return length;
	}
	ListNode *move(ListNode* list,int length)
	{
		while (length)
		{
			list = list->next;
			length--;
		}
		return list;
	}
	ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2)
	{//首先求两个链表长度，做差  同时向后移动
		int length1 = 0, length2 = 0;
		length1 = getListLength(pHead1);
		length2 = getListLength(pHead2);
		if (length1 == 0)return NULL;
		if (length2 == 0)return NULL;
		ListNode* temp1 = pHead1;
		ListNode* temp2 = pHead2;
		if (length1>length2)
		{
			temp1 = move(pHead1, length1 - length2);
		}
		else if (length1<length2)
		{
			temp2 = move(pHead2, length2 - length1);
		}
		while (temp1&&temp2)
		{
			if (temp1==temp2)
			{
				return temp1;
			}
			else
			{
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
		}

		return NULL;		
	}
	/*扑克牌顺子 大王用0表示   可以表示任何数字*/
	bool IsContinuous(vector<int> numbers)
	{
		if (numbers.size() != 5)return false;
		sort(numbers.begin(),numbers.end());
		int zreos = 0, gap = 0;//记录0的个数 和记录差距 
		for (int i = 0; i < numbers.size();i++)
		{
			if (numbers[i] == 0)zreos++;
			else if (i + 1 < numbers.size())
			{
				if (numbers[i] == numbers[i + 1])return false;
				gap += numbers[i + 1] - numbers[i] - 1;				
			}
		}
		if (gap>zreos)		//差距大于0的个数
			return false;
		return true;
		
	}
	/*输出所有和为S的连续正数序列。序列内按照从小至大的顺序，序列间按照开始数字从小到大的顺序*/
	vector<vector<int> > FindContinuousSequence(int sum) 
	{
		vector<vector<int>> result;
		if (sum <= 2)return result;

		for (int a = 1; a <= sum / 2;a++)
		{
			float b;
			b = (-1 + sqrt(1 + 4 * a*a - 4 * a + 8 * sum)) / 2;
			if ((b-(int)b)==0)//如果b是整数 则存在序列
			{
				vector<int> temp;
				for (int i = a; i <= b;i++)
				{
					temp.push_back(i);
				}
				result.push_back(temp);
			}
		}
		return result;
	}
	/*输入一个递增排序的数组和一个数字S，在数组中查找两个数，
	是的他们的和正好是S，如果有多对数字的和等于S，输出两个数的乘积最小的。 */
	vector<int> FindNumbersWithSum(vector<int> array, int sum)
	{//别人写的o（n）的复杂度
		/* vector<int> result;
		int length = array.size();
		int start = 0;
		int end = length - 1;
		while (start < end)
		{
		if (array[start] + array[end] == sum)
		{
		result.push_back(array[start]);
		result.push_back(array[end]);
		break;
		}
		else if (array[start] + array[end] < sum)
		start++;
		else
		end--;
		}*/
		vector<int>result;
		if (array.size() <= 1)return result;
		for (int i = 0; i < array.size() - 1;i++)
		{
			for (int j = array.size() - 1; j>i;j--)
			{
				if (array[i]+array[j]==sum)
				{
					result.push_back(array[i]);
					result.push_back(array[j]);
					//break; 退出循环
					i = array.size();
				}				
			}
		}
		return result;

	}
	/*定义栈的数据结构，请在该类型中实现一个能够得到栈最小元素的min函数。*/
	stack<int>s1, min1;
	void push1(int value)
	{
		s1.push(value);
		if (min1.empty())min1.push(value);
		if (min1.top()>=value)
		{
			min1.push(value);
		}
	
	}
	void pop1()
	{
		s1.pop();
		if (s1.top() == min1.top())min1.pop();
	}
	int top()
	{
		return s1.top();
	}
	int min()
	{
		return min1.top();
	}

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
	/*大家都知道斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项。*/
	int Fibonacci(int n) 
	{
		if (n <= 0)	return 0;		
		if (n == 1 || n == 2)		
			return 1;
		else			
			return Fibonacci(n - 1) + Fibonacci(n - 2);
	}
	/*一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶总共有多少种跳法。*/
	int jumpFloorII(int number)
	{
	  if (number <= 0)	return -1;
	  if (number == 1)	return 1;
	  else	return 2 * jumpFloorII(number - 1);
	
	 }
	/*一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法。*/
	int jumpFloor(int number)
	{
		if (number == 1)return 1;			
		else if (number == 2)return 2;
		return jumpFloor(number - 1) + jumpFloor(number - 2);
	}
	/*输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，
	例如，如果输入如下矩阵： 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.*/
    vector<int> printMatrix(vector<vector<int> > matrix)
	{
		int row = matrix.size();
		int col = matrix[0].size();
		vector<int> a;
		//参考的别人的代码。。。   上地https://www.nowcoder.com/profile/709885
		if (row == 0 || col == 0)  return a;
		// 定义四个关键变量，表示左上和右下的打印范围
		int left = 0, top = 0, right = col - 1, bottom = row - 1;
		while (left <= right && top <= bottom)
		{
			// left to right
			for (int i = left; i <= right; ++i)  a.push_back(matrix[top][i]);
			// top to bottom
			for (int i = top + 1; i <= bottom; ++i)  a.push_back(matrix[i][right]);
			// right to left
			if (top != bottom)
			for (int i = right - 1; i >= left; --i)  a.push_back(matrix[bottom][i]);
			// bottom to top
			if (left != right)
			for (int i = bottom - 1; i > top; --i)  a.push_back(matrix[i][left]);
			left++, top++, right--, bottom--;
		}
		return a;
	}
	/*输入一个链表，反转链表后，输出链表的所有元素。*/
    ListNode* ReverseList(ListNode* pHead)
	{
		if (pHead == NULL)
			return pHead;
		ListNode *curNode = pHead;
		ListNode *nextNode = curNode->next;
		ListNode *temp;
		if (curNode->next != NULL)
		{
			pHead = curNode->next;
		}
		curNode->next = NULL;
		//保存当前结点指针 下一个结点指针 还有下一个的下一个结点指针
		while (nextNode)
		{
			pHead = nextNode;
			temp = nextNode->next;
			nextNode->next = curNode;

			curNode = nextNode;
			nextNode = temp;
		}
		return pHead;
	}
	/*输入一棵二叉树，求该树的深度。从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。*/
    int TreeDepth(TreeNode* pRoot)
	{
		if (pRoot == NULL)
		{
			return 0;
		}
		int a = TreeDepth(pRoot->left);
		int b = TreeDepth(pRoot->right);
		return 1 + (a > b ? a : b);
	}
	/*输入一个链表，从尾到头打印链表每个节点的值。*/
   vector<int> printListFromTailToHead(ListNode* head)
	{
		vector<int> a;
		if (head != NULL)
		{
			a.insert(a.begin(), head->val);
			while (head->next != NULL)
			{
				head = head->next;
				a.insert(a.begin(), head->val);
			}
		}
		return a;
    }
   /*实现一个函数，将一个字符串中的空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。*/
   void replaceSpace(char *str, int length)
   {
		if (str == NULL || length <= 0)		return;		
		int i = 0;
		int oldLength = 0;
		int space = 0;
		while (str[i] != '\0')
		{
			oldLength++;
			if (str[i] == ' ')	space++;			
			i++;
		}
		int newLength = oldLength + space * 2;//新的字符串长度     
		if (newLength > length)	return;
		while (oldLength >= 0)
		{
			if (str[oldLength] == ' ')
			{
				str[newLength--] = '0';
				str[newLength--] = '2';
				str[newLength--] = '%';
			}
			else
			{
				str[newLength--] = str[oldLength];
			}

			oldLength--;
		}
	}
   /*在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。
   请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。*/
	bool Find(int target, vector<vector<int> > array)
	{
		   int colNum;
		   int rowNum;
		   rowNum = array.size();
		   colNum = array[0].size();
		   bool flag = false;
		   int j = 0;
		   int i = rowNum - 1;
		   while (!flag)
		   {
			   if (0 <= i && j <= colNum - 1)
			   {
				   if (array[i][j] < target)   j++;				  
				   else if (array[i][j] > target)  i--;			 
				   else if (array[i][j] == target) flag = true;
			   }
			   else	   break;			  
		   }
		   return flag;
	 }

private:
	stack<int> stack1;
	stack<int> stack2;
};

int main()
{
	ListNode node1(1), node2(2), node3(3), node4(4), node5(9),node6(5);
	ListNode* resultNode= NULL;
	node1.next = &node3;
	node2.next = &node4;
	node3.next = &node5;
	node4.next = &node6;
	node5.next = &node4;
	vector<int> test,popV;
	
	test.push_back(1);
	test.push_back(2);
	test.push_back(4);
	test.push_back(7);
	test.push_back(3);
	test.push_back(5);
	test.push_back(6);
	test.push_back(8);

	popV.push_back(4);
	popV.push_back(7);
	popV.push_back(2);
	popV.push_back(1);
	popV.push_back(5);
	popV.push_back(3);
	popV.push_back(8);
	popV.push_back(6);	


	Solution sl;
	vector<vector<int>> result;
	vector<TreeNode*> tree;
	
	TreeNode * root;

	root = sl.reConstructBinaryTree(test, popV);

//	cout << sl.Serialize(root);
	for (int i = 0; i < strlen(sl.Serialize(root));i++)
	{
		cout <<(int)sl.Serialize(root)[i] << " ";
	}
	
	cout <<  endl;

	TreeNode * root2;
	root2 = sl.Deserialize(sl.Serialize(root));
	for (int i = 0; i < strlen(sl.Serialize(root2)); i++)
	{
		cout << (int)sl.Serialize(root2)[i] << " ";
	}
	
	for (int i = 0; i < tree.size();i++)
	{		
		cout << tree[i]->val << " ";
	}	

	getchar();
	return 0;
}