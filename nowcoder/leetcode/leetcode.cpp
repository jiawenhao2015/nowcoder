#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};
struct TreeNode{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {}
};
struct Point {
	int x;
	int y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
};
class Solution 
{
public:
	/*151. Reverse Words in a String
	Given an input string, reverse the string word by word.

	For example,
	Given s = "the sky is blue",
	return "blue is sky the".

	Update (2015-02-12):
	For C programmers: Try to solve it in-place in O(1) space.
	*/
	void reverseWords(string &s)
	{
		if (s == "")return;
		int i = 0;
		string temp="";
		string temp2 = "";
		 
		while (s[i]!='\0')
		{
			if (s[i] != ' ')
			{
				temp.append(s.substr(i, 1));
				i++;
			}
			else//空格
			{
				if (temp != "")
				{
					temp2.insert(0, " ");
					temp2.insert(0, temp);
					temp.clear();
				}				
				i++;			 
			}
		}
		temp2.insert(0, " ");
		temp2.insert(0, temp);
		
		cout << temp2.c_str() << endl;
		temp2.erase(temp2.size()-1, 1);//擦去最后一个空格
		cout << temp2.c_str() << endl;
		
		s.clear();
		s = temp2;
		i = s.size() - 1;
		while (s[i] == ' ')//擦除结尾空格
		{
			s.erase(i, 1);
			i = s.size() - 1;
		}
		i = 0;
 		while (s[i] == ' ')//擦除前面空格
 		{
 			s.erase(i, 1); 			
 		}
	}
	/*leetcode-139-Word Break
	Given a non-empty string s and a dictionary wordDict containing a list of non-empty words,
	determine if s can be segmented into a space-separated sequence of one or more dictionary words.
	You may assume the dictionary does not contain duplicate words.

	For example, given
	s = "leetcode",
	dict = ["leet", "code"].

	Return true because "leetcode" can be segmented as "leet code".
	*/
	bool wordInDict(string s,vector<string>& wordDict)
	{
		if (s == "")return true;
		vector<string>::iterator it;
		for (it = wordDict.begin(); it != wordDict.end();it++)
			if (*it == s)	return true;		
	 return false;
	}
	bool wordBreak(string s, vector<string>& wordDict)
	{
		vector<bool> flag(s.size(),false);//从某位置开始，是否能分词
		return wordBreak(s, wordDict, 0, flag);
	}
	bool wordBreak(string s, vector<string>& wordDict,int index,vector<bool>& flag)
	{
		if (flag[index]) return false;
		
		int len = s.size() - index;
		for (int i = len; i > 0;i--)
		{
			string word = s.substr(index, i);
			if (wordInDict(word,wordDict))
			{
				if (i == len) return true;
				else
				{
					if (wordBreak(s, wordDict, index+i, flag)) return true;
				}
			}
		}
		flag[index] = true;
		return false;
	}
	
	/*leetcode-129-Sum Root to Leaf Numbers
	Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

	An example is the root-to-leaf path 1->2->3 which represents the number 123.

	Find the total sum of all root-to-leaf numbers.

	For example,

	1
	/ \
	2   3
	The root-to-leaf path 1->2 represents the number 12.
	The root-to-leaf path 1->3 represents the number 13.

	Return the sum = 12 + 13 = 25.*/
	int sumNumbersCore(TreeNode* node,int sum)
	{
		if (node == NULL)return 0;
		sum = sum * 10 + node->val;
		if (node->left == NULL && node->right == NULL) return sum;//叶结点

		return sumNumbersCore(node->left, sum) + sumNumbersCore(node->right, sum);		 
	}
	int sumNumbers(TreeNode* root)
	{		 
		return sumNumbersCore(root,0);
	}
	/*leetcode-143-Reorder List
	Given a singly linked list L: L0→L1→…→Ln-1→Ln,
	reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

	You must do this in-place without altering the nodes' values.
	For example,
	Given {1,2,3,4}, reorder it to {1,4,2,3}.	*/
	/*思路：用快慢指针将链表分为前后两部分，
	将后部分链表用头插法翻转
	将翻转后的链表跟前半部分连起来*/
	ListNode* reversal(ListNode* head)
	{//将链表用头插法 翻转
		if (head == NULL || head->next == NULL) return head;
		ListNode dump(0);		
		ListNode* next = head->next;
		while (next != NULL)
		{			
			head->next = dump.next;
			dump.next = head;
			head = next;
			next = next->next;
		}
		head->next = dump.next;
		dump.next = head;
		return dump.next;
	}
	ListNode* mergeList(ListNode* head, ListNode* head2)
	{//将list2 每一个元素插入到对应位置的list1元素的后面
		ListNode* temp = head;
		ListNode* p1 = head->next;
		ListNode* p2 = head2->next;
		while (head!=NULL && p1 != NULL && p2!= NULL)
		{
			head->next = head2;
			head2->next = p1;
			head = p1;
			p1 = p1->next;
			head2 = p2;
			p2 = p2->next;
		}
		head->next = head2;
		head2->next = p1;//处理最后一个结点		

		return temp;
	}
	void reorderList(ListNode* head)
	{
		if (head == NULL || head->next == NULL || head->next->next == NULL) return;
		ListNode* slow = head, *fast = head;

		while (fast->next!=NULL && fast->next->next!=NULL)//当fast结点后只有一个或者没有结点时停止循环
		{
			slow = slow->next;
			fast = fast->next->next;
		}	
		ListNode*lastPart = reversal(slow->next); //后半部分链表 翻转		
		slow->next = NULL;//将链表分为前后两个部分	前一个链表长度大于或者等于后边链表长度

		head = mergeList(head, lastPart);
	}
	/*leetcode-141-Linked List Cycle
	Given a linked list, determine if it has a cycle in it.
	Follow up:	Can you solve it without using extra space?*/
	bool hasCycle(ListNode *head)
	{
		/*判断链表是否带环，我们可以采用在头结点设两个指针，一个叫fast，一个叫slow，fast一下走两步，而slow一下走一步。
		如果链表中存在环的话，那么fast和slow必定会在环中相遇。若链表中没有环的话，那么fast必定现于slow指针先到达链表的尾节点（->next = Null）。
		为什么链表中存在环，则slow和fast会在环中相遇？
		可以联想在体育场里面跑步时候的场景，速度快和速度慢的在同一起点的话，必定在某个时间点，速度快的会追上速度慢的 */
		ListNode* slow = head, *fast = head;
		while (fast != NULL && fast->next != NULL)
		{
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast) return true;
		}
		if (fast==NULL || fast->next ==NULL)//没有环
		{
			return false;
		}
		return true;
	}
	/*leetcode-100-Same Tree
	Given two binary trees, write a function to check if they are equal or not.
	Two binary trees are considered equal if they are structurally identical and the nodes have the same value.*/
	bool isSameTree2(TreeNode* p, TreeNode* q)
	{//先序非递归
		stack<TreeNode*>st1, st2;
		if (p != NULL)st1.push(p);
		if (q!= NULL)st2.push(q);
		TreeNode* ptemp;
		TreeNode* qtemp;
		while (!st1.empty() && !st2.empty())
		{
			ptemp = st1.top();
			qtemp = st2.top();
			if (ptemp->val != qtemp->val) return false;
			st1.pop();
			st2.pop();
			if (ptemp->right != NULL) st1.push(ptemp->right);
			if (qtemp->right != NULL) st2.push(qtemp->right);
			if (st1.size() != st2.size()) return false;//比较两个栈的大小 

			if (ptemp->left != NULL) st1.push(ptemp->left);
			if (qtemp->left != NULL) st2.push(qtemp->left);
			if (st1.size() != st2.size()) return false;//比较两个栈的大小 
		}
		return (st1.size() == st2.size());
	}
	bool isSameTree(TreeNode* p, TreeNode* q)
	{//递归
		if (p == NULL && q == NULL) return true;
		if (p == NULL && q != NULL || p != NULL && q == NULL || q->val != p->val) return false;

		return isSameTree(p->left, q->left) && isSameTree(p->right,q->right);
	}
	/*leetcode-145-Binary Tree Postorder Traversal
	Given a binary tree, return the postorder traversal of its nodes' values.
	For example:
	Given binary tree {1,#,2,3},
	1
	\
	2
	/
	3
	return [3,2,1].
	Note: Recursive solution is trivial, could you do it iteratively?*/
	vector<int> postorderTraversal(TreeNode* root)
	{
		vector<int>result;
		if (root == NULL)return result;
		stack<TreeNode*>st;
		bool flag;
		TreeNode* temp;
		do
		{
			while (root != NULL)//左结点入栈
			{
				st.push(root);
				root = root->left;
			}
			flag = true;//设置root 为已经访问过
			temp = NULL;//temp 指向栈顶结点的前一个已访问的结点

			while (!st.empty() && flag)
			{
				root = st.top();
				if (root ->right == temp)//右孩子不存在或者右孩子已经访问过 则访问 root结点
				{
					result.push_back(root->val);//访问
					st.pop();
					temp = root;//指向被访问的结点
				}
				else
				{
					root = root->right;
					flag = false;//设置为未被访问过
				}
			}
		} while (!st.empty());
		return result;
	}
	/*leetcode-144-Binary Tree Preorder Traversal
	Given a binary tree, return the preorder traversal of its nodes' values.
	Given binary tree {1,#,2,3},
	1
	\
	2
	/
	3
	return [1,2,3].
	Note: Recursive solution is trivial, could you do it iteratively?*/
	void preorderNonRecursiveTraversal(TreeNode*pRoot, vector<int>& result)
	{
		if (pRoot == NULL) return;
		stack<TreeNode*> st;
		TreeNode* temp;
		st.push(pRoot);
		while (!st.empty())
		{
			temp = st.top();
			result.push_back(temp->val);
			st.pop();
			if (temp->right != NULL)st.push(temp->right);//先右 后左
			if (temp->left != NULL)st.push(temp->left);
		}

	}
	vector<int> preorderTraversal(TreeNode* root)
	{
		vector<int> result;
		if (root == NULL) return result;
		preorderNonRecursiveTraversal(root, result);
		return result;
	}
	/*leetcode-147-Insertion Sort List
		Sort a linked list using insertion sort.*/
	ListNode* insert(ListNode* head, ListNode* node)
	{//将node插入到有序链表中的合适位置 保持从小到大有序
		ListNode dump(0);
		dump.next = head;		
		ListNode* pre = &dump;
		while (head != NULL && head->val < node->val )
		{
			pre = head;
			head = head->next;			
		}
		pre->next = node;
		node->next = head;

		return dump.next;

	}
	ListNode* insertionSortList(ListNode* head)
	{
		if (head == NULL || head->next == NULL) return head;
		
		ListNode* temp = head;
		ListNode  newList(0) ;
		
		while (head != NULL)
		{
			temp = head->next;//保存当前的下一个结点位置
			newList.next =insert(newList.next, head);
			head = temp;		
		}
		return newList.next;
	}
	/*leetcode-148-Sort List
    Sort a linked list in O(n log n) time using constant space complexity.*/	
	ListNode* merge(ListNode* l1, ListNode* l2)
	{//合并两个有序链表
		ListNode dumb(0);
		ListNode* cur = &dumb;
		while (l1 != NULL && l2 != NULL)
		{
			if (l1->val < l2->val)
			{
				cur->next = l1;
				l1 = l1->next;
			}
			else
			{
				cur->next = l2;
				l2 = l2->next;
			}
			cur = cur->next;
		}
		if (l1 != NULL)	cur->next = l1;			
		if (l2 != NULL)	cur->next = l2;	
		return dumb.next;
	}
	ListNode* sortList(ListNode* head)
	{//归并
		if (head == NULL || head->next == NULL) return head;
		
		ListNode* first = head;
		ListNode* second = head->next;
		while (second != NULL && second->next != NULL)
		{
			first = first->next;
			second = second->next->next;//每次移动两个结点
		}
		second = first->next;
		first->next = NULL;//将链表分成两个部分

		return merge(sortList(head), sortList(second));
	}
	/*leetcode-149-Max Points on a Line
	Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.*/	
	void getLine(double& a, double& b, double & c, Point pt1, Point pt2)
	{//ax+by+c = 0;
		a = pt2.y - pt1.y;
		b = pt1.x - pt2.x;
		c = pt2.x * pt1.y - pt1.x *pt2.y;
	}
	bool isOnLine(double a,double b,double c,Point pt)
	{
		if (a*a + b*b == 0) return true;
		double distance = abs(a*pt.x + b*pt.y + c) / sqrt(a*a + b*b);
		if (distance < 0.000001)
			return true;
		else return false;
	}
	int maxPoints(vector<Point>& points)
	{
		if (points.size() <= 2) return points.size();	
		int max = 0;
		for (int i = 0; i < points.size();i++)
		{		
			int same = 1;
			for (int j = i+1; j < points.size();j++)
			{
				if (points[i].x == points[j].x && points[i].y == points[j].y)	//两个点相同
				{				
					same++;
					continue;
				}
				double a=0, b=0, c=0;
				int num = 0;
				getLine(a, b, c, points[i], points[j]);				
				for (int k = 0;  k < points.size(); k++)
				{
					if (isOnLine(a, b, c, points[k]))
					{
						num++;
					}
				}
				if (max < num)max = num;				
			}
			if (same == points.size())
			{
				max = same;
			}
		}		
		return max;
	}
	/*136. Single Number
	Given an array of integers, every element appears twice except for one. Find that single one.
	Note:
	Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?*/
	int singleNumber(vector<int>& nums)
	{
		for (int i = 1; i < nums.size();i++)
		{
			nums[0] ^= nums[i];
		}
		return nums[0];
	}
	/*2. Add Two Numbers
	You are given two non - empty linked lists representing two non - negative integers.
	The digits are stored in reverse order and each of their nodes contain a single digit.
	Add the two numbers and return it as a linked list.
	You may assume the two numbers do not contain any leading zero, except the number 0 itself.
	Input : (2 -> 4 -> 3) + (5 -> 6 -> 4)
	Output : 7 -> 0 -> 8
	*/
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
	{
		/*ListNode preHead(0), *p = &preHead;
	int extra = 0;
	while (l1 || l2 || extra) {
	int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + extra;
	extra = sum / 10;
	p->next = new ListNode(sum % 10);
	p = p->next;
	l1 = l1 ? l1->next : l1;
	l2 = l2 ? l2->next : l2;
	}
	return preHead.next;*/
		int carry = 0;//进位
		ListNode* result = l1;
		while (l1->next != NULL && l2->next != NULL)
		{
			l1->val = l1->val + l2->val + carry;							
			if (l1->val >= 10)
			{
				l1->val -= 10;
				carry = 1;
			}
			else carry = 0;
			l1 = l1->next;
			l2 = l2->next;
		}
		l1->val = l1->val + l2->val + carry;
		if (l1->val >= 10)
		{
			l1->val -= 10;
			carry = 1;
		}
		else carry = 0;
		if (l1->next == NULL && l2->next == NULL)
		{
			if (carry == 1)
			{
				ListNode* newNode = new ListNode(1);
				l1->next = newNode;
			}
		}
		else
		{			
			if (l1->next == NULL &&  l2->next != NULL)//l2非空
			{			
				l1->next = l2->next;
				l1 = l1->next;
				while (carry && l1->next!=NULL)
				{
					l1->val += carry;
					if (l1->val >= 10)
					{
						l1->val -= 10;
						carry = 1;
					}
					else carry = 0;
					l1 = l1->next;
				}
				if (carry ==1)//最后一位
				{
					l1->val += carry;
					if (l1->val >= 10)
					{
						l1->val -= 10;
						ListNode* newNode = new ListNode(1);//新建结点
						l1->next = newNode;
						carry = 1;
					}
					else carry = 0;
				}
				
			}
			else if (l1->next != NULL && l2->next == NULL)
			{				
				l1 = l1->next;
				while (carry && l1->next != NULL)
				{
					l1->val += carry;
					if (l1->val >= 10)
					{
						l1->val -= 10;
						carry = 1;
					}
					else carry = 0;
					l1 = l1->next;
				}
				if (carry == 1)//最后一位
				{
					l1->val += carry;
					if (l1->val >= 10)
					{
						l1->val -= 10;
						ListNode* newNode = new ListNode(1);//新建结点
						l1->next = newNode;
						carry = 1;
					}
					else carry = 0;
				}
			}
		}	
		
		return result;
	}
	/*150. Evaluate Reverse Polish Notation
	Evaluate the value of an arithmetic expression in Reverse Polish Notation.
	Valid operators are +, -, *, /. Each operand may be an integer or another expression.
	Some examples:
	["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
	["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
	*/
	int evalRPN(vector<string>& tokens)
	{//字符串可以直接比较。。不用strcmp 直接tokens[i]=="*"
		stack<int> st;
		for (int i = 0; i < tokens.size();i++)
		{
			if (atoi(tokens[i].c_str())!=0)st.push(atoi(tokens[i].c_str()));//返回非0代表为数字 
			else if (strcmp(tokens[i].c_str(), "0") == 0)
			{
				 st.push(atoi(tokens[i].c_str()));				
			}
			else
			{				
				int b = st.top();
				st.pop();
				int a = st.top();
				st.pop();
				if (strcmp(tokens[i].c_str(), "+")==0)	st.push(a + b);				
				else if (strcmp(tokens[i].c_str(), "-") == 0)st.push(a - b);
				else if (strcmp(tokens[i].c_str(), "*") == 0)st.push(a * b);
				else if (tokens[i] == "/")st.push(a / b);
				else
				{
					//说明有别的字符 错误					
				}
			}
		}
		return st.top();
	}
	/*1. Two Sum
	Given an array of integers, return indices of the two numbers such that they add up to a specific target.
	You may assume that each input would have exactly one solution, and you may not use the same element twice.
	Example:
	Given nums = [2, 7, 11, 15], target = 9,
	Because nums[0] + nums[1] = 2 + 7 = 9,
	return [0, 1].*/
	vector<int> twoSum(vector<int>& nums, int target)
	{
		//用hash表能够实现O(n)时间复杂度
		unordered_map<int, int>hashtable;
		vector<int>result;
		for (int i = 0; i < nums.size();i++)
		{
			int numberToFind = target - nums[i];//另外一个需要找的数字

			if (hashtable.find(numberToFind) != hashtable.end())
			{
				result.push_back(hashtable[numberToFind]+1);
				result.push_back(i+1);
			}

			hashtable[nums[i]] = i;//没有找到 就插入map里面
		}
		return result;
		//if (nums.size() == 0) return nums;
		//vector<int>result;
		////sort(nums.begin(), nums.end());
		//for (int i = 0; i < nums.size(); i++)
		//{
		//	for (int j = i + 1; j < nums.size();j++)
		//	{
		//		if (nums[i]+nums[j] == target)
		//		{
		//			result.push_back(i);
		//			result.push_back(j);
		//			return result;
		//		}
		//	}
		//}
		//return result;
	}
	/*111. Minimum Depth of Binary TreeGiven a binary tree, find its minimum depth.The minimum depth is the number of nodes
	along the shortest path from the root node down to the nearest leaf node.*/
	int minDepth(TreeNode *root)
	{
		if(root == NULL) return 0;		
		if (root->left==NULL) return 1 + minDepth(root->right);
		if (root->right == NULL) return 1 + minDepth(root->left);
		return 1 + min(minDepth(root->left), minDepth(root->right));		
	}
	/*104. Maximum Depth of Binary Tree
	Given a binary tree, find its maximum depth.
	The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.*/
	int maxDepth(TreeNode* root)
	{
		if (root == NULL)return 0;
		int left = maxDepth(root->left);
		int right = maxDepth(root->right);

		return 1+max(left,right);
		
	}
		
};

int main()
{
	Solution sl;
	vector<int>test;	
	test.push_back(3);
	test.push_back(4);
	test.push_back(2);
	test.push_back(3);
	test.push_back(5);
	test.push_back(4);
	test.push_back(2);
	vector<string> str;
	str.push_back("0");
	str.push_back("3");
	str.push_back("/");
	/*str.push_back("3");
	str.push_back("*");	*/

	ListNode node1(1), node2(2), node3(3), node4(4), node5(5), node6(6);
	
	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = &node5;
	node5.next = &node6;
	
	TreeNode treenode(1);
	TreeNode treenode2(2);
	treenode.left = &treenode2;
	ListNode* resultNode = &node1;
	
	vector<string>strvec;
	strvec.push_back("a");
	strvec.push_back("abc");
	strvec.push_back("b");
	strvec.push_back("cd3");
	string str1 = "  a b  ";
	sl.reverseWords(str1);
	cout <<":"<< str1.c_str();
	 
	while (resultNode != NULL)
	{
		//cout << resultNode->val << " ";
		resultNode = resultNode->next;
	}
		
	getchar();
	return 0;
}
