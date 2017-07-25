#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <map>
#include<string>
#include<sstream>
#include <set>
#include <numeric>
using namespace std;
struct Interval{
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
	};
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
	/*516. Longest Palindromic Subsequence
	Given a string s, find the longest palindromic subsequence's length in s. 
	You may assume that the maximum length of s is 1000.
	Example 1:
	Input:"bbbab"
	Output:4	One possible longest palindromic subsequence is "bbbb".
	Example 2:
	Input:	"cbbd"
	Output:	2	One possible longest palindromic subsequence is "bb".*/
	int longestPalindromeSubseq(string s)
	{
		if (s.size() <= 1)return s.size();
		unordered_map<char,int>table;
		for (int i = 0; i < s.size();i++)
		{
			table[s[i]]++;
		}
		int result = 0;
		unordered_map<char, int>::iterator it;
	
		for (it = table.begin(); it != table.end();it++)
		{
			cout << it->first << "==>" << it->second << endl;
			result = max(result,it->second);
		}
		return result;
	}

	/*leetcode[115] Distinct Subsequences*/

	/*leetcode-77-Combinations
	Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
	For example,
	If n = 4 and k = 2, a solution is:
	[
	[2,4],
	[3,4],
	[2,3],
	[1,2],
	[1,3],
	[1,4],
	]*/
	//回溯法
	void combine(vector<vector<int>>& result,vector<int>& temp,int n,int k,int start)
	{
		if (temp.size() == k)
		{
			result.push_back(temp);
			return;
		}
		for (int i = start; i <= n;i++)
		{
			temp.push_back(i);//插入
			combine(result, temp,n,k,i+1);//是i+1 不是start+1
			temp.pop_back();//弹出
		}	
	}
	vector<vector<int>> combine(int n, int k)
	{
		vector<vector<int>>result;
		if (n < k) return result;
		vector<int> temp;
		combine(result, temp, n, k, 1);
		return result;
	}

	/*leetcode-101-Symmetric Tree
	Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
	For example, this binary tree [1,2,2,3,4,4,3] is symmetric:
	    1
	   / \
	  2   2
	 / \ / \
	3  4 4  3
	But the following [1,2,2,null,3,null,3] is not:
	 1
	/ \
	2   2
	 \   \
	 3    3
	Note:
	Bonus points if you could solve it both recursively and iteratively.*/
	bool isSymmetric2(TreeNode *root)
	{//非递归 层次遍历二叉树
		TreeNode *left, *right;
		if (!root)
			return true;
		queue<TreeNode*> q1, q2;
		q1.push(root->left);
		q2.push(root->right);
		while (!q1.empty() && !q2.empty()){
			left = q1.front();
			q1.pop();
			right = q2.front();
			q2.pop();
			if (NULL == left && NULL == right)
				continue;
			if (NULL == left || NULL == right)
				return false;
			if (left->val != right->val)
				return false;
			q1.push(left->left);
			q1.push(left->right);
			q2.push(right->right);
			q2.push(right->left);
		}
		return true;
	}
	bool isSymmetricCore(TreeNode* left, TreeNode* right)
	{
		if (left == NULL && right == NULL) return true;
		if (left == NULL && right != NULL || left != NULL && right == NULL || left->val != right->val)return false;
		return isSymmetricCore(left->left, right->right) && isSymmetricCore(left->right, right->left);//递归判断
	}
	bool isSymmetric(TreeNode* root)
	{
		if (root == NULL) return true;
		return isSymmetricCore(root->left, root->right);
	}
	/*leetcode-21-Merge Two Sorted Lists
	Merge two sorted linked lists and return it as a new list.
	The new list should be made by splicing together the nodes of the first two lists.*/
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
	{
		ListNode* dummy = new ListNode(0);
		ListNode* p = dummy ;
		while (l1 != NULL && l2 != NULL)
		{
			if (l1->val < l2->val)
			{
				p->next = l1;
				l1 = l1->next;
			}
			else
			{
				p->next = l2;
				l2 = l2->next;
			}
			p = p->next;			 
		}
		if (l1 != NULL)p->next = l1;		
		if (l2 != NULL)p->next = l2;		
		return dummy->next;
	}
	/*leetcode-109-Convert Sorted List to Binary Search Tree
	Given a singly linked list where elements are sorted in
	ascending order, convert it to a height balanced BST.*/
	TreeNode* sortedListToBST(ListNode* head)
	{
		//利用fast 和 slow 指针 找到链表中点
		return build(head,NULL);
	}
	TreeNode* build(ListNode* start, ListNode* end)
	{
		if (start == end)
		{
			return NULL;
		}
		ListNode* fast = start;
		ListNode* slow = start;
		while (fast != end && fast->next != end)//注意第一次执行的时候end为NULL 没毛病。。
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		TreeNode* node = new TreeNode(slow->val);
		node->left = build(start, slow);
		node->right = build(slow->next, end);
		return node;	
	}
	/*leetcode-108-Convert Sorted Array to Binary Search Tree
	Given an array where elements are sorted in ascending order,
	convert it to a height balanced BST.*/
	TreeNode* ArrayToBST(vector<int>& nums, int i, int j)
	{	
		if (i > j) return NULL;
		int middle = (i + j) / 2;
		TreeNode *root = new TreeNode(nums[middle]);
		root->left = ArrayToBST(nums, i, middle - 1);
		root->right = ArrayToBST(nums,middle + 1,j);
		return root;
	}
	TreeNode* sortedArrayToBST(vector<int>& nums)
	{
		int size = nums.size();
		if (size == 0) return NULL;

		TreeNode *root = ArrayToBST(nums,0,size-1);
		
		return root;
	}
	/*leetcode-124-Binary Tree Maximum Path Sum
	Given a binary tree, find the maximum path sum.
	For this problem, a path is defined as any sequence of nodes from some starting node to
	any node in the tree along the parent-child connections.
	The path must contain at least one node and does not need to go through the root.
	For example:
	Given the below binary tree,
	 1
	/ \
   2   3
	Return 6.*/
	int maxToRoot(TreeNode* root,int &result)
	{
		if (root == NULL)return 0;
		int left = maxToRoot(root->left,result);
		int right = maxToRoot(root->right, result);
		if (left  < 0)left = 0;
		if (right < 0)right = 0;
		if (left + right + root->val > result) result = left + right + root->val;
		return root->val += max(left,right);
	}
	int maxPathSum(TreeNode* root)
	{
		//int max = -2147483648;//编译器报错
		int max = -2147;
		maxToRoot(root, max);
		return max;
	}
	/*leetcode-28-Implement strStr
	Implement strStr().
	Returns the index of the first occurrence of needle in haystack,
	or -1 if needle is not part of haystack.*/
	int strStr(string haystack, string needle)
	{
		int size1 = haystack.size();
		int size2 = needle.size();
		if (size2 == 0) return 0;
		if ((size1 == 0 && size2 != 0)||(size1 < size2)) return -1;
		
		int j = 0;
		for (int i = 0; i <=size1 -size2;i++)
		{	
			if (haystack[i] == needle[j] && j<size2)
			{
				for (int m = i; m < size1;m++)
				{
					if (haystack[m] == needle[j] && j < size2)j++;
					else
					{
						m = size1;//跳出循环
						j = 0;
					}
						
					if (j == size2)	return m - size2 + 1;//succeed
				}
			}
			else j = 0;			
		}
		return -1;
	}
	char *strStr(char *haystack, char *needle)
	{
		int size1 = strlen(haystack);
		int size2 = strlen(needle);
		if (size2 == 0) return &haystack[0];
		if ((size1 == 0 && size2 != 0) || (size1 < size2)) return NULL;
		char* p = haystack;
		int j = 0;
		for (int i = 0; i <= size1 - size2; i++)
		{
			if (haystack[i] == needle[j] && j < size2)
			{
				for (int m = i; m < size1; m++)
				{
					if (haystack[m] == needle[j] && j < size2)j++;
					else
					{
						m = size1;//跳出循环
						j = 0;
					}
					if (j == size2)	return &haystack[m - size2 + 1];//succeed
				}
			}
			else j = 0;
		}
		return NULL;
	}

	/*leetcode-3-Longest Substring Without Repeating Characters
	Given a string, find the length of the longest substring without repeating characters.
	Examples:
	Given "abcabcbb", the answer is "abc", which the length is 3.
	Given "bbbbb", the answer is "b", with the length of 1.
	Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring,
	"pwke" is a subsequence and not a substring.*/
	int lengthOfLongestSubstring(string s)
	{
		int size = s.size();
		if (size <= 1)return size;
		unordered_map<char,int> table;//用来记录字母与对应的下标值
		int length = 0;
		int result = 0;
		int tempIndex = 0;
		int temp = 0;
		for (int i = 0; i < size; i++)
		{
			if (table.count(s[i])>0)//说明map里面有
			{
				result = max(result, length);
				length = i - table[s[i]]-1;
				temp = table[s[i]];
				for (int j = tempIndex; j <= temp; j++)
				{
					table.erase(s[j]);//将这个重复元素之前所有去掉		
				}
				tempIndex = temp + 1;//保存新的起点下标				
			}
			table[s[i]] = i;//记录下标索引值
			length++;			
		}
		result = max(result, length);
		return result;
	}
	/*leetcode-50-Pow(x, n)
	Implement pow(x, n).*/
	double myPow2(double x, int n)
	{
		if (x == 0.0) return 0;
		if (n == 1) return x;

		double result = 1.0;
		unsigned long long p = n;
		if (n < 0) { p = -n; x = 1 / x; }
		while (p)
		{
			if (p & 1) result *= x;
			x *= x;
			p >>= 1;
		}
	 
		return result;	
	}
	double myPow(double x, int n)
	{
		if (x == 0.0) return 0;
		if (n == 1) return x;

		double result = 1.0;
		for (int i = 0; i < abs(n);i++)
		{
			result *= x;
		}
		if (n>0)return result;
		return 1.0/result;
	}
	/*leetcode-91-Decode Ways
	A message containing letters from A-Z is being encoded to numbers using the following mapping:
	'A' -> 1
	'B' -> 2
	...
	'Z' -> 26
	Given an encoded message containing digits, determine the total number of ways to decode it.
	For example,
	Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).
	The number of ways decoding "12" is 2.*/
	int numDecodings(string s)
	{ 
		int size = s.size();
		if (size == 0 || s[0] == '0')return 0;
		vector<int> dp(size+1,0);
		dp[0] = dp[1] = 1;

		for (int i = 1; i < size;i++)
		{
			if (s[i]=='0')
			{
				dp[i] = 0;
			}
			if (s[i - 1] == '1' || s[i - 1] == '2'&&s[i] <= '6')
			{
				dp[i + 1] = dp[i - 1] + dp[i];
			}
			else
				dp[i + 1] = dp[i];
			
		}

		return dp[size];
	}
	/*leetcode-72-Edit Distance
	Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)
	You have the following 3 operations permitted on a word:
	a) Insert a character
	b) Delete a character
	c) Replace a character*/
	int minDistance(string word1, string word2)
	{
		int a = word1.length(), b = word2.length();
		vector<vector<int>> result(a + 1, vector<int>(b + 1, 0));
		for (int i = 1; i <= a; i++)
			result[i][0] = i;
		for (int j = 1; j <= b; j++)
			result[0][j] = j;
		for (int i = 1; i <= a;i++)
		{
			for (int j = 1; j <= b; j++)
			{
				if (word1[i-1] == word2[j-1])
				{
					result[i][j] = result[i-1][j-1];
				}
				else
				{
					result[i][j] = min(result[i - 1][j - 1] + 1, min(result[i][j - 1]+1, result[i - 1][j]+1));
				}
			}
		}
		return result[a][b];
	}
	/*leetcode-67-Add Binary
	Given two binary strings, return their sum (also a binary string).
	For example,
	a = "11"
	b = "1"
	Return "100".*/
	string addBinary(string a, string b)
	{
		int aIndex = a.size() - 1, bIndex = b.size() - 1;
		int numa = 0, numb = 0, carry = 0, temp = 0;
		string c;
		char tempChar[10];
		while (aIndex >= 0 || bIndex >= 0 || carry == 1)//简洁一些了
		{
			numa = 0, numb = 0;
			if(aIndex >= 0)numa = a[aIndex--] - '0';
			if(bIndex >= 0)numb = b[bIndex--] - '0';
			temp = numa + numb + carry;
			if (temp > 1)
			{
				carry = 1;
				temp = temp - 2;
			}
			else carry = 0;			
			sprintf(tempChar, "%d", temp);		
			c.insert(0, tempChar);			
		}
		return c;
	}
	string addBinary2(string a, string b)
	{
		int aIndex = a.size()-1, bIndex = b.size()-1;
		int numa = 0, numb = 0, carry = 0,temp = 0;		
		string c;
		char tempChar[10];
		while (aIndex>=0 && bIndex>=0)
		{
			numa = a[aIndex] - '0';
			numb = b[bIndex] - '0';
			temp = numa + numb + carry;
			if (temp > 1)
			{
				carry = 1;
				temp = temp - 2;
			}
			else
			{
				carry = 0;
			}			
			sprintf(tempChar, "%d", temp);
			//_itoa(temp, tempChar, 10);
			c.insert(0,tempChar);
			aIndex--;
			bIndex--;
		}
		while (aIndex >= 0)
		{
			numa = a[aIndex] - '0';			 
			temp = numa  + carry;
			if (temp > 1)
			{
				carry = 1;
				temp = temp - 2;
			}
			else
			{
				carry = 0;
			}
			sprintf(tempChar,"%d",temp);
			//_itoa(temp, tempChar, 10);
			c.insert(0, tempChar);
			aIndex--;			
		}  
		while (bIndex >= 0)
		{			
			numb = b[bIndex] - '0';
			temp = numb + carry;
			if (temp > 1)
			{
				carry = 1;
				temp = temp - 2;
			}
			else
			{
				carry = 0;
			}
			sprintf(tempChar, "%d", temp);
			//_itoa(temp, tempChar, 10);
			c.insert(0, tempChar);			
			bIndex--;
		}
		if (carry)
		{
			c.insert(0, "1");
		}
		return c;	
	}
	/*leetcode-137-Single Number II
	Given an array of integers, every element appears three times except for one, which appears exactly once. Find that single one.
	Note:
	Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?*/
	int singleNumber2(vector<int>& nums)
	{
		int result = 0;
		for (int i = 0; i < 32;i++)
		{
			int count = 0, bit = 1 << i;
			for (int j = 0; j < nums.size();j++)
			{
				if (nums[j] & bit) count++;			
			}
			if (count % 3 !=0)
				result |= bit;			
		}
		return result;
	}
	/*leetcode-7-Reverse Integer
	Reverse digits of an integer.
	Example1: x = 123, return 321
	Example2: x = -123, return -321*/
	int reverse1(int x)
	{
		long long result = 0;//用long long类型避免32位溢出
		int temp = 0;
		while (x)
		{
			temp = x % 10;
			x /= 10;
			result = result * 10 + temp;
		}
		return (result<INT_MIN || result>INT_MAX) ? 0 : result;
	}
	/*leetcode-60-Permutation Sequence
	The set [1,2,3,…,n] contains a total of n! unique permutations.
	By listing and labeling all of the permutations in order,
	We get the following sequence (ie, for n = 3):
	"123"
	"132"
	"213"
	"231"
	"312"
	"321"////还没看懂。。。。。。http://www.cnblogs.com/yrbbest/p/4436392.html
	Given n and k, return the kth permutation sequence.*/
	string getPermutation(int n, int k)
	{
		vector<int>factorial(n + 1, 1);//保留阶乘
		for (int i = 1; i <= n;i++)		
		 factorial[i] = i * factorial[i - 1];

		vector<char> digits = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
		string result;
		int num = n - 1;

		while (num)
		{
			int t = (k-1) / factorial[num];   //是k/(n-1)! 计算第一位数字
			k = k - t * factorial[num];
			result.push_back(digits[t]);
			digits.erase(digits.begin() + t);
			num--;
		}
		result.push_back(digits[k - 1]);
		return result;
		
	}
	/*leetcode-18-4Sum
	Given an array S of n integers, are there elements a, b, c,
	and d in S such that a + b + c + d = target? Find all unique
	quadruplets in the array which gives the sum of target.
	For example, given array S = [1, 0, -1, 0, -2, 2], and target = 0.
	A solution set is:
	[
	 [-1,  0, 0, 1],
	 [-2, -1, 1, 2],
	 [-2,  0, 0, 2]
	]*/
	vector<vector<int>> fourSum(vector<int>& nums, int target)
	{
		vector<vector<int>>result;
		const int size = nums.size();
		if (size < 4) return result;
		sort(nums.begin(), nums.end());
		vector<int>temp;
		for (int i = 0; i < size - 3; i++)
		{
			if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target) break;//及时跳出循环
			if (nums[i] + nums[size - 3] + nums[size - 2] + nums[size - 1] < target)continue;
			
			for (int j = i + 1; j < size-2; j++)
			{
				if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target) break;//及时跳出循环
				if (nums[i] + nums[j] + nums[size - 2] + nums[size - 1] < target)continue;
				 
				int left = j + 1;
				int right = size - 1;
				while (left < right)
				{
					int sum = nums[i] + nums[j] + nums[left] + nums[right];
					if (sum < target)left++;
					else if (sum > target) right--;
					else
					{
						temp = {nums[i],nums[j],nums[left],nums[right]};//新学一招，类似数组赋值
						result.push_back(temp);
						while (left < right && nums[left] == temp[2])left++;
						while (left < right && nums[right] == temp[3])right--;
					}		 
				}
				while (j + 1 < size && nums[j + 1] == nums[j])j++;
			}
			while (i + 1 < size && nums[i + 1] == nums[i])i++;
		}
		return result;
	}
	/*leetcode-15-3Sum
	Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0?
	Find all unique triplets in the array which gives the sum of zero.
	Note: The solution set must not contain duplicate triplets.
	For example, given array S = [-1, 0, 1, 2, -1, -4],
	A solution set is:
	[
	[-1, 0, 1],
	[-1, -1, 2]
	]*///内存超过限制
	void getTwoSum(vector<vector<int>>& result, vector<int>& nums, int begin, int end, int target)
	{
		int i = begin, j = end;
		while (i < j)
		{
			if (nums[i] + nums[j] + target == 0)
			{	
				vector<int>temp;
				temp.push_back(target);
				temp.push_back(nums[i]);
				temp.push_back(nums[j]);
				result.push_back(temp);
				 
				while (i < j && nums[i] == nums[i + 1])
					++i;
				while (i < j && nums[j] == nums[j - 1])
					--j;
				++i;
				--j;
			}
			else if (nums[i] + nums[j] + target < 0)
				++i;
			else
				--j;
		}
	}
	vector<vector<int>> threeSum(vector<int>& nums)
	{
		vector<vector<int>>result;
		vector<int> temp;
		if (nums.size() < 3)
			return result;
		sort(nums.begin(),nums.end());
		for (int i = 0; i < nums.size()-2;i++)
		{
			if (i>0 && nums[i] == nums[i-1])
				continue;
			getTwoSum(result,nums,i+1,nums.size()-1,nums[i]);
		}	
		return result;
	}
	/*leetcode-47-Permutations II
	Given a collection of numbers that might contain duplicates, return all possible unique permutations.
	For example,
	[1,1,2] have the following unique permutations:
	[
		[1,1,2],
		[1,2,1],
		[2,1,1]
	]*/	
	void permuteUniqueCore(vector<vector<int>>& result, vector<int>  nums, int index)
	{
		if (index == nums.size())
		{
			result.push_back(nums);
		}
		for (int i = index; i < nums.size(); i++)
		{
			if (i!=index && nums[i]==nums[index])continue;//
			swap(nums[i], nums[index]);
			permuteUniqueCore(result, nums, index + 1);
			//swap(nums[i], nums[index]);	//不要交换。。。了。。 参数nums 也是变成了传值 不是传引用
		} 
	}
	vector<vector<int>> permuteUnique(vector<int>& nums)
	{
		vector<vector<int>>result;		
		sort(nums.begin(), nums.end());		 
		permuteUniqueCore(result, nums, 0);
		return result;
	}
	/*leetcode-46-Permutations
	Given a collection of distinct numbers, return all possible permutations.
	For example,
	[1,2,3] have the following permutations:
	[
	[1,2,3],
	[1,3,2],
	[2,1,3],
	[2,3,1],
	[3,1,2],
	[3,2,1]
	]*/
	void permuteCore2(vector<vector<int>>& result, vector<int>& nums , int index)
	{
		if (index == nums.size())
		{
			result.push_back(nums);
		}
		for (int i = index; i < nums.size(); i++)
		{
			swap(nums[i], nums[index]);
			permuteCore2(result, nums,index + 1);
			swap(nums[i], nums[index]);
		}
	}
	void permuteCore(vector<vector<int>>& result,vector<int>& nums, vector<int>& temp,int index)
	{
		if (index == nums.size())
		{
			result.push_back(temp);
		}
		for (int i = index; i < nums.size();i++)
		{
			
			temp.push_back(nums[i]);
			swap(nums[i], nums[index]);
			permuteCore(result, nums, temp, index + 1);
			swap(nums[i], nums[index]);
			temp.pop_back();
			
		}
	}
	vector<vector<int>> permute(vector<int>& nums)
	{
		vector<vector<int>>result;
		vector<int> temp;
		sort(nums.begin(),nums.end());
		//permuteCore(result, nums, temp, 0);
		permuteCore2(result, nums,0);
		return result;
	}
	/*leetcode-78-Subsets
	Given a set of distinct integers, nums, return all possible subsets.
	Note: The solution set must not contain duplicate subsets.
	For example,
	If nums = [1,2,3], a solution is:
	[
	[3],
	[1],
	[2],
	[1,2,3],
	[1,3],
	[2,3],
	[1,2],
	[]
	]*/
	//回溯法
	void dfs(vector<vector<int>>& result, vector<int>& temp, vector<int>& nums, int index)
	{
		result.push_back(temp);
		for (int i = index; i < nums.size();i++)
		{
			temp.push_back(nums[i]);//
			dfs(result,temp,nums,i+1);
			temp.erase(temp.end()-1);//temp.pop_back();
		}
	}
	vector<vector<int>> subsets(vector<int>& nums)
	{
		vector<vector<int>>result;
		vector<int>temp;
		sort(nums.begin(), nums.end());//为什么要加上排序？？
		dfs(result,temp,nums,0);
		return result;
	}
	/*leetcode-63-Unique Paths II
	Follow up for "Unique Paths":
	Now consider if some obstacles are added to the grids. How many unique paths would there be?
	An obstacle and empty space is marked as 1 and 0 respectively in the grid.
	For example,
	There is one obstacle in the middle of a 3x3 grid as illustrated below.
	[
		[0,0,0],
		[0,1,0],
		[0,0,0]
	][[0,0,0],[0,1,0],[0,0,0]]
	The total number of unique paths is 2.*/
	int uniquePathsWithObstacles(vector<vector<int>>& grid)
	{
		//类似没有障碍的方法：将有障碍的地方置为0；
		if (grid.empty())return 0;
		int row = grid.size();
		int col = grid[0].size();
		if (grid[0][0] == 1)return 0;
		
		for (int i = 0; i < col;i++)//处理第一行
		{
			if (grid[0][i] == 0)grid[0][i] = 1;			
			else if (grid[0][i] == 1)
			{
				for (int j = i; j < col; j++)
					grid[0][j] = 0;//i之后都置为0;
				i = col;
			}				
		}
		for (int i = 1; i < row; i++)//处理第一列
		{
			if (grid[i][0] == 0)grid[i][0] = 1;
			else if (grid[i][0] == 1)
			{
				for (int j = i; j < row; j++)
					grid[j][0] = 0;//i之后都置为0;
				i = row;
			}
		}
		for (int i = 1; i < row; i++)
		{
			for (int j = 1; j < col; j++)
			{
				if (grid[i][j] == 0)//不是障碍
				{								
					grid[i][j] = grid[i - 1][j] + grid[i][j - 1];					
				}
				else if(grid[i][j] == 1)grid[i][j] = 0;
			}
		}
		return grid[row - 1][col - 1];
	}
	/*leetcode-62-Unique Paths
	A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
	The robot can only move either down or right at any point in time.
	The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
	How many possible unique paths are there?*/
	int uniquePaths(int m, int n)
	{
		if (m <= 0 || n <= 0)return 0;
		vector<vector<int>>grid(m,vector<int>(n));
		grid[0][0] = 1;
		for (int i = 0; i < m;i++)
		{
			for (int j = 0; j < n;j++)
			{
				if (i ==0 && j != 0)
				{
					grid[i][j] = 1;
				}
				if (i != 0 && j == 0)
				{
					grid[i][j] = 1;
				}
				if (i != 0 && j != 0)
				{
					grid[i][j] = grid[i - 1][j] + grid[i][j-1];
				}
			}
		}
		return grid[m-1][n-1];
	}
	/*leetcode-64-Minimum Path Sum
	Given a m x n grid filled with non-negative numbers, find a path from top left 
	to bottom right which minimizes the sum of all numbers along its path.
	Note: You can only move either down or right at any point in time.*/
	int minPathSum2(vector<vector<int>>& grid)
	{
		if (grid.empty())return 0;
		int row = grid.size();
		int col = grid[0].size();
		//其实可以不必申请空间 直接使用grid就行		
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (i==0 && j!=0)
				{
					grid[i][j] += grid[i][j - 1];
				}
				if (i != 0 && j == 0)
				{
					grid[i][j] += grid[i - 1][j];
				}
				if (i!=0&&j!=0)
				{
					grid[i][j] = grid[i][j] + min(grid[i - 1][j], grid[i][j - 1]);
				}				
			}
		}
		return grid[row - 1][col - 1];
	}
	int minPathSum(vector<vector<int>>& grid)
	{
		if (grid.empty())return 0;
		int row = grid.size();
		int col = grid[0].size();
		vector<vector<int>>pathSum(row,vector<int>(col));//其实可以不必申请空间 直接使用grid就行
		pathSum[0][0] = grid[0][0];
		for (int i = 1; i < row;i++)
		{
			pathSum[i][0] = pathSum[i - 1][0] + grid[i][0];
		}
		for (int i = 1; i < col; i++)
		{
			pathSum[0][i] = pathSum[0][i - 1] + grid[0][i];
		}
		for (int i = 1; i < row;i++)
		{
			for (int j = 1; j < col;j++)
			{
				pathSum[i][j] = grid[i][j] + min(pathSum[i-1][j], pathSum[i][j-1]);
			}
		}
		return pathSum[row-1][col-1];
	}
	/*leetcode-70-Climbing Stairs
	You are climbing a stair case. It takes n steps to reach to the top.
	Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
	Note: Given n will be a positive integer.*/
	int climbStairs2(int n)
	{
		if (n == 1 || n == 2)return n;
		int temp1 = 1;
		int temp2 = 2;
		int temp = 0;
		for (int i = 3; i < n + 1; i++)
		{ 
			temp = temp1 + temp2;
			temp1 = temp2;
			temp2 = temp;
		}
		return temp;
	}
	int climbStairs(int n)
	{
		if (n == 1 || n == 2)return n;
		vector<int>step(n+1);
		step[0] = 0;
		step[1] = 1;
		step[2] = 2;
		for (int i = 3; i < n+1;i++)
		{//每一步有两种方案 走一个台阶 或者走两个台阶
			step[i] = step[i - 1] + step[i - 2];
		}
		return step[n];
	}
	/*leetcode-198-House Robber
	You are a professional robber planning to rob houses along a street. 
	Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of 
	them is that adjacent houses have security system connected and it will automatically contact the police
	if two adjacent houses were broken into on the same night.
	Given a list of non-negative integers representing the amount of money of each house, 
	determine the maximum amount of money you can rob tonight without alerting the police.*/
	int rob(vector<int>& nums) 
	{//money[i] = max{money[i-2]+nums[i],money[i-1]}第i个房间有两种可能
		//要么偷，要不不偷，偷的话就是money[i-2]+nums[i] 不偷就是,money[i-1]
		if (nums.empty())return 0;
		if (nums.size() == 1) return nums[0];
		if (nums.size() == 2) return max(nums[0],nums[1]);
		vector<int>money(nums.size());
		money[0] = nums[0];
		money[1] = max(nums[0], nums[1]);
		for (int i = 2; i < nums.size();i++)
		{
			money[i] = max(money[i-2]+nums[i],money[i-1]);
		}
		return money.back();
		
	}
	/*leetcode-120-Triangle
	Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.
	For example, given the following triangle
	[
	[2],
	[3,4],
	[6,5,7],
	[4,1,8,3]
	]
	The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).*/
	int minimumTotal(vector<vector<int>>& triangle)
	{		
		vector<vector<int>>triangleSum = triangle;
		int size = triangleSum.size();
		for (int i = 1; i < size;i++)
		{
			for (int j = 0; j < triangle[i].size();j++)
			{
				if (j ==0)//第一列
				{
					triangleSum[i][j] = triangleSum[i][j] + triangleSum[i - 1][j];
				}
				else if (j == triangle[i].size() - 1)//最后一列
				{
					triangleSum[i][j] = triangleSum[i][j] + triangleSum[i - 1][j-1];
				}
				else
				{
					triangleSum[i][j] = triangleSum[i][j] + min(triangleSum[i - 1][j], triangleSum[i - 1][j - 1]);
				}				
			}
		}
		
		int result = triangleSum[size -1][0];
		for (int i = 0; i < triangleSum[size - 1].size();i++)
		{
			result = min(result, triangleSum[size - 1][i]);
		}
		return result;
	}
	/*leetcode-53-Maximum Subarray
	Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
	For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
	the contiguous subarray [4,-1,2,1] has the largest sum = 6.*/
	int maxSubArray(vector<int>& nums)
	{
		if (nums.empty())return 0;
		int temp = 0,result = nums[0];
		for (int i = 0; i < nums.size();i++)
		{
			temp += nums[i];
			result = max(result,temp);
			temp = max(temp,0);			
		}
		return result;
	}
	/*leetcode-303-Range Sum Query - Immutable
	Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.
	Example:
	Given nums = [-2, 0, 3, -5, 2, -1]
	sumRange(0, 2) -> 1
	sumRange(2, 5) -> -1
	sumRange(0, 5) -> -3
	You may assume that the array does not change.
	There are many calls to sumRange function.*/
	vector<int> nums;
	void Solution1(vector<int> num)
	{	
		for (int i = 1; i < num.size();i++)
		{
			num[i] = num[i] + num[i - 1];//存储和
		}
		this->nums = num;
	}
	int sumRange(int i, int j)
	{
		if (nums.size() == 0) return NULL;
		if (i ==0)return nums[j];
		return nums[j] - nums[i - 1];
	}
	/*leetcode-123-Best Time to Buy and Sell Stock III
	Say you have an array for which the ith element is the price of a given stock on day i.
	Design an algorithm to find the maximum profit. You may complete at most two transactions.
	Note:
	You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).*/
	int maxProfitnew(vector<int>& prices)
	{
		int size = prices.size();
		if (size == 0 || size == 1) return 0;
		vector<int>profit(size,0);
		vector<int>profit1(size);		
		int local_min = prices[0];
		int local_max = prices[size - 1];
		int j = size - 2;
		int result = 0;
		profit[0] = 0;
		profit1[size - 1] = 0;
		for (int i = 1; i < size + 1 && j >= 0; i++, j--)//扫描一遍，分别计算左边和右边最大的profit
		{
			//记录i左边最大profit 利用i-1的信息 只需比较i-1时候的profit 与现在price-local_min即可
			//如果prices[i] - local_min >profit[i - 1]的话，说明需要更新最大的profit 同理 求右边最大profit也是一个道理
			profit[i] = max(profit[i - 1], prices[i] - local_min);
			local_min = min(local_min, prices[i]);
			profit1[j] = max(profit1[j + 1], local_max - prices[j]);//记录j右边最大profit
			local_max = max(local_max, prices[j]);
		}
		for (int i = 1; i < size; i++)//统计左右两边最大profit之和 取最大
		{
			result = max(result, profit[i] + profit1[i]);
		}
		return result;
	}
	int maxProfitcore(vector<int>& prices,int start,int end)
	{//从start 到 end期间 最大profit
		if (start == end|| prices.size()==0) return 0;
		int tempProfit = 0, maxProfit = 0;
		for (int i = start+1; i <=end; i++)
		{
			tempProfit += prices[i] - prices[i - 1];
			tempProfit = max(0, tempProfit);
			maxProfit = max(maxProfit, tempProfit);
		}
		return maxProfit;
	}//超时
	int maxProfit3(vector<int>& prices)
	{
		int profit = 0;
		for (int i = 1; i < prices.size();i++)
		{
			int pro1 = maxProfitcore(prices, 0, i);
			int pro2 = maxProfitcore(prices, i, prices.size()-1);
			profit = max(profit,pro1+pro2);
		}
		return profit;
	}
	/*leetcode-122-Best Time to Buy and Sell Stock II
	Say you have an array for which the ith element is the price of a given stock on day i.
	Design an algorithm to find the maximum profit. You may complete as many transactions as you like
	(ie, buy one and sell one share of the stock multiple times).
	However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).*/
	int maxProfit2(vector<int>& prices)
	{
		if (prices.size() == 0)return 0;
		int tempProfit = 0;
		for (int i = 1; i < prices.size();i++)
		{
			if (prices[i] - prices[i-1]>0)//有profit
			{
				tempProfit += prices[i] - prices[i - 1];
			}
		}
		return tempProfit;
	}
	/*leetcode-121-Best Time to Buy and Sell Stock
	Say you have an array for which the ith element is the price of a given stock on day i.
	If you were only permitted to complete at most one transaction 
	(ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
	Example 1:
	Input: [7, 1, 5, 3, 6, 4]
	Output: 5
	max. difference = 6-1 = 5 (not 7-1 = 6, as selling price needs to be larger than buying price)
	Example 2:
	Input: [7, 6, 4, 3, 1]
	Output: 0
	In this case, no transaction is done, i.e. max profit = 0.*/
	int maxProfit1(vector<int>& prices)
	{
		if (prices.size() == 0)return 0;
		int tempProfit = 0, maxProfit = 0;
		for (int i = 1; i < prices.size(); i++)
		{
			tempProfit += prices[i] - prices[i - 1];
			tempProfit = max(0, tempProfit);
			maxProfit = max(maxProfit, tempProfit);
		}
		return maxProfit;
	}
	int maxProfit(vector<int>& prices)
	{//复杂度O(n2)
		if (prices.size() == 0)return 0;
		int localMax = 0;
		int globalMax = 0;
		for (int i = 0; i < prices.size();i++)//i买入
		{
			localMax = 0;
			for (int j = i + 1; j < prices.size();j++)//j卖出
			{
				localMax = max(localMax, prices[j] - prices[i]);
			}
			globalMax = max(globalMax, localMax);
		}
		return globalMax;
	}
	/*leetcode-110-Balanced Binary Tree
	Given a binary tree, determine if it is height-balanced.
	For this problem, a height-balanced binary tree is defined as a binary tree 
	in which the depth of the two subtrees of every node never differ by more than 1.*/
	int depthOfTree(TreeNode* root)
	{
		if (root == NULL) return 0;
		int left = depthOfTree(root->left);
		int right = depthOfTree(root->right);
		return 1 + max(left, right);
	}
	bool isBalanced(TreeNode* root)
	{
		if (root == NULL) return true;
		
		int left = depthOfTree(root->left);
		int right= depthOfTree(root->right);
		if (abs(left - right) > 1) return false;
		return isBalanced(root->left) && isBalanced(root->right);
	}
	/*leetcode-113-Path Sum II
	Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
	For example:
	Given the below binary tree and sum = 22,
		5
		/ \
		4   8
		/   / \
		11  13  4
		/  \    / \
		7    2  5   1
	return
	[
	[5,4,11,2],
	[5,8,4,5]
	]
	Subscribe to see which companies asked this question.*/
	void pathSum(TreeNode* root, int sum, vector<vector<int>>& result,vector<int>&path)
	{//值得好好学习一下
		if (root == NULL) return;
		path.push_back(root->val);//暂时放入当前路径中保存
		if (root->left == NULL && root->right == NULL && root->val == sum)//找到路径
		{
			result.push_back(path);
		}
		pathSum(root->left, sum - root->val, result, path);
		pathSum(root->right,sum - root->val, result, path);

		path.pop_back();//弹出 回溯
	}
	vector<vector<int>> pathSum(TreeNode* root, int sum)
	{
		vector<vector<int>> result;
		vector<int> path; 
		
		pathSum(root, sum, result, path);
		return result;
	}
	/*leetcode-112-Path Sum
	Given a binary tree and a sum, determine if the tree has a root-to-leaf path 
	such that adding up all the values along the path equals the given sum.
	For example:
	Given the below binary tree and sum = 22,
		 5
		/ \
	   4   8
		/   / \
		11  13  4
		/  \      \
		7    2      1
	return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.*/
	bool hasPathSum(TreeNode* root, int sum)
	{
		if (root == NULL) return false;
		if (root->val == sum && root->left == NULL && root->right == NULL)return true;
		return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
	}
	/*leetcode-128-Longest Consecutive Sequence
	Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
	For example,
	Given [100, 4, 200, 1, 3, 2],
	The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.
	Your algorithm should run in O(n) complexity.*/
	int longestConsecutive(vector<int>& nums)
	{
		if (nums.size() == 0)return 0;
		unordered_set<int>record(nums.begin(),nums.end());//hash表格
		int result = 1;
		for (int i = 0; i < nums.size();i++)
		{
			if (record.find(nums[i]) == record.end()) continue;//没有找到i
			record.erase(nums[i]);//如果在的话就删除i，减少set的规模
			
			int pre = nums[i] - 1, next = nums[i] + 1;//向前和向后查找
			while (record.find(pre) != record.end())
			{
				record.erase(pre);
				pre--;
			}
			while (record.find(next) != record.end())
			{
				record.erase(next);
				next++;
			}

			result = max(result,next-pre-1);
		}
		return result;
	}
	/*leetcode-58-Length of Last Word
	Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.
	If the last word does not exist, return 0.
	Note: A word is defined as a character sequence consists of non-space characters only.
	For example,
	Given s = "Hello World",
	return 5.*/
	int lengthOfLastWord(string s)
	{
		if (s.size() == 0)return 0;
		int i = s.size()-1;
		while (i >= 0 &&s[i] == ' ')//去除最后最后的空格
		{
			i--;
		}
		if (i == -1) return 0;//全是空格
		int j = i;//记住此时下标
		while (i >= 0 && s[i] != ' ')
		{
			i--;
		}
		return (j - i);
	}
	/*leetcode-134-Gas Station
	There are N gas stations along a circular route, where the amount of gas at station i is gas[i].
	You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). 
	You begin the journey with an empty tank at one of the gas stations.
	Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.
	Note:
	The solution is guaranteed to be unique.*/
	int canCompleteCircuit2(vector<int> &gas, vector<int> &cost) {
		int i, j, n = gas.size();

		/*
		* If start from i, stop before station x -> no station k from i + 1 to x - 1 can reach x.
		* Bcoz if so, i can reach k and k can reach x, then i reaches x. Contradiction.
		* Thus i can jump directly to x instead of i + 1, bringing complexity from O(n^2) to O(n).
		*/
		// start from station i
		for (i = 0; i < n; i += j) {
			int gas_left = 0;
			// forward j stations
			for (j = 1; j <= n; j++) {
				int k = (i + j - 1) % n;
				gas_left += gas[k] - cost[k];
				if (gas_left < 0)
					break;
			}
			if (j > n)
				return i;
		}

		return -1;
	}
	int canCompleteCircuit(vector<int>& gas, vector<int>& cost)
	{
		if (gas.size() != cost.size() || gas.size() == 0)return -1;

		int tank = 0;
		int num = gas.size();
		for (int i = 0; i < num;i++)
		{
			tank = 0;
			for (int j = i; j < num + i;j++)
			{
				tank += gas[j%num];
				tank -= cost[j%num];
				if (tank < 0)//不能到下一个station 重新开始
				{			
					j = num+i;	//退出内层循环
				}
			}
			if (tank>=0)
			{
				return i;
			}
		}
		return -1;
	}
	/*	leetcode-135-Candy
	There are N children standing in a line. Each child is assigned a rating value.
	You are giving candies to these children subjected to the following requirements:
	Each child must have at least one candy.
	Children with a higher rating get more candies than their neighbors.
	What is the minimum candies you must give?*/
	int candy(vector<int>& ratings)
	{
		if (ratings.size() == 0) return 0;
	//	sort(ratings.begin(), ratings.end());
		int sum = 0;//第一个为1
		vector<int>candyvec(ratings.size(),1);
		for (int i = 1; i < ratings.size();i++)
		{
			if (ratings[i] > ratings[i-1])//如果相等
			{
				candyvec[i] = candyvec[i - 1]+1;
			}
			else
			{
				candyvec[i] = 1;//最少1个
			}
		}
		sum = candyvec[ratings.size() - 1];
		for (int i = ratings.size() - 2; i >=0 ;i--)//反向遍历一遍 
		{
			if ((ratings[i] > ratings[i + 1]) && candyvec[i] < (candyvec[i + 1] + 1))candyvec[i] = candyvec[i + 1] + 1;
			sum += candyvec[i];
		}
		 
		return sum;
	}
	/*leetcode-151-Reverse Words in a String
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
			if (s[i] != ' ')temp.append(s.substr(i, 1));			
			else//空格
			{
				if (temp != "")
				{
					temp2.insert(0, " ");
					temp2.insert(0, temp);
					temp.clear();
				}							 
			}
			i++;
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
 		  s.erase(i, 1); 			
 		
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
	/*leetcode-136-Single Number
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
	/*leetcode-2-Add Two Numbers
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
	/*leetcode-150-Evaluate Reverse Polish Notation
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
	/*leetcode-1-Two Sum
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
	/*leetcode-111-Minimum Depth of Binary Tree
	Given a binary tree, find its minimum depth.The minimum depth is the number of nodes
	along the shortest path from the root node down to the nearest leaf node.*/
	int minDepth(TreeNode *root)
	{
		if(root == NULL) return 0;		
		if (root->left==NULL) return 1 + minDepth(root->right);
		if (root->right == NULL) return 1 + minDepth(root->left);
		return 1 + min(minDepth(root->left), minDepth(root->right));		
	}
	/*leetcode-104-Maximum Depth of Binary Tree
	Given a binary tree, find its maximum depth.
	The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.*/
	int maxDepth(TreeNode* root)
	{
		if (root == NULL)return 0;
		int left = maxDepth(root->left);
		int right = maxDepth(root->right);

		return 1+max(left,right);		
	}	
	/*leetcode-102-Binary Tree Level Order Traversal
	Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).
	For example:
	Given binary tree [3,9,20,null,null,15,7],
	3
	/ \
	9  20
	/  \
	15   7
	return its level order traversal as:
	[
	[3],
	[9,20],
	[15,7]
	]*/
	vector<vector<int>> levelOrder(TreeNode* root)
	{
		queue<TreeNode*>que;
		vector<vector<int>>result;
		if (root == NULL)return result;
		que.push(root);
		
		while (!que.empty())
		{
			int size = que.size();//保证que里始终是同一层的数据
			vector<int> temp;
			for (int i = 0; i < size;i++)
			{
				TreeNode* node = que.front();
				que.pop();				
				temp.push_back(node->val);
				if (node->left != NULL)que.push(node->left);
				if (node->right != NULL)que.push(node->right);
			}
			result.push_back(temp);
		}
		return result;
	}
	/*leetcode-107-Binary Tree Level Order Traversal II
	Given a binary tree, return the bottom-up level order traversal of its nodes' values.
	(ie, from left to right, level by level from leaf to root).
	For example:
	Given binary tree [3,9,20,null,null,15,7],
	    3
	   / \
	  9  20
	 /  \
	15   7
	return its bottom-up level order traversal as:
	[
	[15,7],
	[9,20],
	[3]
	]*/
	vector<vector<int>> levelOrderBottom(TreeNode* root)
	{
		queue<TreeNode*>que;
		vector<vector<int>>result;
		if (root == NULL)return result;
		que.push(root);

		while (!que.empty())
		{
			int size = que.size();
			vector<int> temp;
			for (int i = 0; i < size; i++)
			{
				TreeNode* node = que.front();
				que.pop();
				temp.push_back(node->val);
				if (node->left != NULL)que.push(node->left);
				if (node->right != NULL)que.push(node->right);
			}			
			result.insert(result.begin(), temp);//从头部插入即可实现倒序
		}
		return result;
	}
	/*leetcode-125-Valid Palindrome
	Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
	For example,
	"A man, a plan, a canal: Panama" is a palindrome.
	"race a car" is not a palindrome.*/
	bool isSameCharacter(char a, char b)
	{
		if (abs(a - b) == 0 || abs(a - b) == 32)return true;
		else return false;
	}
	bool isNumOrAlpha(char a)
	{
		if ((a >= 48 && a <= 57) || (a >= 65 && a <= 90) || (a >= 97 && a <= 122)) return true;
		else return false;
	}
	char toLower(char a)
	{
		if ((a >= 48 && a <= 57) || (a >= 97 && a <= 122))return a;//数字和小写字母不变
		else return (a + 32);
	}
	bool isPalindrome(string s)
	{
		if (s.size() == 0) return true;
		vector<char>newstr;//处理一下原字符串 去除没有必要的
		for (int i = 0; i < s.size();i++)
		{
			if (isNumOrAlpha(s[i]))newstr.push_back(toLower(s[i]));
		}
		for (int i = 0, j = newstr.size() - 1; i <= j; i++, j--)
		{
			if (!isSameCharacter(newstr[i], newstr[j]))return false;
		}
		return true;
	}
	/*bool isPalindrome(string s) {//#include <ctype.h>即可
		int i,j;
		for(i=0,j=s.length()-1;i<j;++i,--j){
		while(i<j && !isalnum(s[i])) ++i;
		while(i<j && !isalnum(s[j])) --j;
		if (i<j && tolower(s[i])!=tolower(s[j])) return false;
		}
		return true;
		}*/
	/*leetcode-88-Merge Sorted Array
	Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.
	Note:
	You may assume that nums1 has enough space 
	(size that is greater or equal to m + n) to hold additional elements from nums2.
	The number of elements initialized in nums1 and nums2 are m and n respectively.*/
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
	{
		vector<int>newvec;
		int i = 0, j = 0;
		while (i<m && j<n)
		{
			if (nums1[i] <= nums2[j])newvec.push_back(nums1[i++]);
			else newvec.push_back(nums2[j++]);
		}
		while (i<m)
		{
			newvec.push_back(nums1[i++]);
		}
		while (j < n)
		{
			newvec.push_back(nums2[j++]);
		}
		nums1 = newvec;
	}
	/*leetcode-103-Binary Tree Zigzag Level Order Traversal
	Given a binary tree, return the zigzag level order traversal of its nodes' values. 
	(ie, from left to right, then right to left for the next level and alternate between).
	For example:
	Given binary tree [3,9,20,null,null,15,7],
	   3
	  / \
	 9  20
	 /  \
	15   7
	return its zigzag level order traversal as:
	[
	[3],
	[20,9],
	[15,7]
	]*/
	vector<vector<int>> zigzagLevelOrder(TreeNode* root)
	{
		vector<vector<int>> result;
		if (root == NULL)return result;
		queue<TreeNode*>que;
		que.push(root);
		bool flag = false;//判断是否需要翻转
		while (!que.empty())
		{
			int size = que.size();			
			vector<int>level;
			for (int i = 0; i < size;i++)
			{
				TreeNode* temp = que.front();
				que.pop();
				if (temp->left != NULL)que.push(temp->left);
				if (temp->right != NULL)que.push(temp->right);
				level.push_back(temp->val);				
			}
			if (flag)
			{
				reverse(level.begin(), level.end());
				flag = !flag;
			}
			else flag = !flag;
			
			result.push_back(level);		
		}
		return result;
	}
	/*leetcode-9-Palindrome Number
	Determine whether an integer is a palindrome. Do this without extra space.*/
	bool isPalindrome(int x)
	{
		int newNum = 0;
		int a = 0;
		int temp = x;
		while (x>0)
		{
			a = x % 10;
			newNum = newNum * 10 + a;
			x = x / 10;
		}
		if (newNum == temp) return true;
		else return false;		
	}
	/*leetcode-506-Relative Ranks
	Given scores of N athletes, find their relative ranks and the people with the top three highest scores, who will be awarded medals:
	"Gold Medal", "Silver Medal" and "Bronze Medal".
	Example 1:
	Input: [5, 4, 3, 2, 1]
	Output: ["Gold Medal", "Silver Medal", "Bronze Medal", "4", "5"]
	Explanation: The first three athletes got the top three highest scores, so they got "Gold Medal", "Silver Medal" and "Bronze Medal".
	For the left two athletes, you just need to output their relative ranks according to their scores.
	Note:
	N is a positive integer and won't exceed 10,000.
	All the scores of athletes are guaranteed to be unique.*/
	//思路：首先排序，然后用map存储对应名词
	 vector<string> findRelativeRanks(vector<int>& nums)
	 {
		 vector<int>backup = nums;
		 vector<string>result;
		 if(nums.size()==0)return result;
		// sort(nums.begin(),nums.end(),greater<int>());vs下编译报错 先注释
		 map<int,string>table;
		 char rank[10];
		 for(int i = 0;i < nums.size();i++)
		 {
			 sprintf(rank,"%d",i+1);
			 if(i == 0)table[nums[i]]="Gold Medal";
			 else if(i == 1)table[nums[i]]="Silver Medal";
			 else if(i == 2)table[nums[i]]="Bronze Medal";
			 else  table[nums[i]] = rank;
		 }
		
		 for(int i =0;i<nums.size();i++)
		 {
			 result.push_back(table[backup[i]]);
		 }
		 return result;
	}
	/*leetcode-94-Binary Tree Inorder Traversal
	Given a binary tree, return the inorder traversal of its nodes' values.
	For example:
	Given binary tree [1,null,2,3],
	   1
		\
		 2
		/
	   3
	return [1,3,2].
	Note: Recursive solution is trivial, could you do it iteratively?
	*/
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int>result;
		stack<TreeNode*>st;
		while(root != NULL || !st.empty())
		{
			if(root!= NULL)
			{
				st.push(root);
				root = root->left;
			}
			else
			{
				root = st.top();
				result.push_back(root->val);
				st.pop();
				root = root->right;
			}
		}
		return result;
	}
	/*leetcode-26-Remove Duplicates from Sorted Array
	Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length
	Do not allocate extra space for another array, you must do this in place with constant memory.
	For example,
	Given input array nums = [1,1,2],
	Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively.
	It doesn't matter what you leave beyond the new length.*/
	int removeDuplicates(vector<int>& nums)
	{
		if(nums.size()<=1)return nums.size();
		int first =0;
		int second =1;//保存前后两个元素下标位置
		while(second<nums.size())
		{
			while(nums[first] == nums[second])second++;
			if(second<nums.size() && nums[first+1] != nums[second])nums[first+1] = nums[second];

		if(second<nums.size()) first++;
			second++;
		}
		return first+1;
	}
	int removeDuplicates(int A[], int n)
	{
		if(n <= 1)   return n;
		int cnt = 0;
		A[cnt++] = A[0];
		for(int i=1; i<n; i++)
		{
			if(A[i] == A[i-1])      continue;
			else         A[cnt++] = A[i];
		}
		return cnt;
		}
	/*leetcode-118-Pascal's Triangle
	Given numRows, generate the first numRows of Pascal's triangle.
	For example, given numRows = 5,
	Return
	[
		 [1],
		[1,1],
	   [1,2,1],
	  [1,3,3,1],
	 [1,4,6,4,1]
	]
	*/
	vector<vector<int> > generate(int numRows)
	{
		vector<vector<int>> result;
		if(numRows<1)return result;
		vector<int>level;
		level.push_back(1);
		result.push_back(level);
		for(int i = 1;i<numRows;i++)
		{
			level.clear();
			level.push_back(1);
			for(int j=1;j<i;j++)
			{
				level.push_back(result[i-1][j-1] + result[i-1][j]);
			}
			level.push_back(1);
			result.push_back(level);
		}
		return result;
	}
	/*leetcode-119-Pascal's Triangle II
	Given an index k, return the kth row of the Pascal's triangle.
	For example, given k = 3,
	Return [1,3,3,1].
	Note:
	Could you optimize your algorithm to use only O(k) extra space?*/
	vector<int> getRow(int rowIndex)
	{
		vector<int>result;
		vector<int>temp;
		if (rowIndex < 0)return result;
		temp.push_back(1);
		if (rowIndex == 0)return temp;
		
		for (int i = 0; i <= rowIndex;i++)
		{
			result.clear();
			result.push_back(1);
			for (int j = 1; j < i; j++)
			{
				result.push_back(temp[j - 1] + temp[j]);
			}
			result.push_back(1);
			temp = result;
		}
		return result;
	}
	/*leetcode-27-Remove Element
	Given an array and a value, remove all instances of that value in place and return the new length.
	Do not allocate extra space for another array, you must do this in place with constant memory.
	The order of elements can be changed. It doesn't matter what you leave beyond the new length.
	Example:
	Given input array nums = [3,2,2,3], val = 3
	Your function should return length = 2, with the first two elements of nums being 2.*/
	int removeElement(vector<int>& nums, int val)
	{
		if (nums.size() < 1)return nums.size();
		//sort(nums.begin(), nums.end());
		int count = 0;
		for (int i = 0; i < nums.size() ;i++)
		{
			if (nums[i] == val)continue;
			else nums[count++] = nums[i];
		}
		return count;
	}
	/*leetcode-189-Rotate Array
	Rotate an array of n elements to the right by k steps.
	For example, with n = 7 and k = 3, the array [1,2,3,4,5,6,7] is rotated to [5,6,7,1,2,3,4].
	Note:
	Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.*/
	void rotate(vector<int>& nums, int k)
	{
		if (k <= 0 || k%nums.size() == 0)return;
		vector<int>temp = nums;	
		int size = nums.size();
		k %=size;
		int i = 0;
		for (int j = size - k; i < k;j++)
		{
			nums[i++] = temp[j];
		}
		for (int j = 0; j < size - k;j++)
		{
			nums[i++] = temp[j];
		}
	}
	/*leetcode-61-Rotate List
	Given a list, rotate the list to the right by k places, where k is non-negative.
	For example:
	Given 1->2->3->4->5->NULL and k = 2,
	return 4->5->1->2->3->NULL.*/
	ListNode* rotateRight(ListNode* head, int k)
	{
		ListNode* result;
		if (k == 0 || head == NULL) return head;
		int length = 1;
		ListNode* temp = head;
		while (head != NULL && head->next != NULL)
		{
			head = head->next;
			length++;
		}
		k %= length;
		head->next = temp;//head 目前为最后一个结点的指针 指向初始时候的头部结点
		for (int i = 0; i < length - k-1;i++)
		{
			temp = temp->next;
		}
		 result = temp->next;
		temp->next = NULL;
		return result;
	}
	/*leetcode-48-Rotate Image
	You are given an n x n 2D matrix representing an image.
	Rotate the image by 90 degrees(clockwise).
	Follow up :
	Could you do this in - place ?
		思路：先翻转再对换
		1 2 3 　　 7 8 9　　 7 4 1
		4 5 6 = >  4 5 6 = > 8 5 2
		7 8 9 　　 1 2 3 　　9 6 3*/
	void rotate(vector<vector<int>>& matrix)
	{
		reverse(matrix.begin(), matrix.end());
		for (int i = 0; i < matrix.size(); ++i)
		for (int j = 0; j < i; ++j)
			swap(matrix[i][j], matrix[j][i]);
	}
	/*leetcode-83-Remove Duplicates from Sorted List
	Given a sorted linked list, delete all duplicates such that each element appear only once.
	For example,
	Given 1->1->2, return 1->2.
	Given 1->1->2->3->3, return 1->2->3.*/
	ListNode* deleteDuplicates(ListNode* head)
	{
		if (head == NULL || head->next == NULL) return head;		
		ListNode* p = head, *q = head->next;
		while (q != NULL)
		{
			if (p->val == q->val){}
			else
			{
				p->next = q;
				p = q;
			}
			q = q->next;
		}
		p->next = q;
		return head;
	}
	/*leetcode-80-Remove Duplicates from Sorted Array II
	Follow up for "Remove Duplicates":
	What if duplicates are allowed at most twice?
	For example,
	Given sorted array nums = [1,1,1,2,2,3],
	Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3. 
	It doesn't matter what you leave beyond the new length.
	https://discuss.leetcode.com/topic/7673/share-my-o-n-time-and-o-1-solution-when-duplicates-are-allowed-at-most-k-times
	*/
	int removeDuplicates3(vector<int>& nums)
	{
		if (nums.size() <= 2)return nums.size();
		int first = 1;
		int second = 1;
		int count = 1;
		while (second<nums.size())
		{
			if (nums[second-1] == nums[second] )
			{
				if (count<2)
				{
					nums[first++] = nums[second];
					count++;
				}
			}
			else
			{
				count = 1;
				nums[first++] = nums[second];
			}
			second++;
		}
	}
	/*leetcode-82-Remove Duplicates from Sorted List II
	Given a sorted linked list, delete all nodes that have duplicate numbers, 
	leaving only distinct numbers from the original list.
	For example,
	Given 1->2->3->3->4->4->5, return 1->2->5.
	Given 1->1->1->2->3, return 2->3.
	http://www.liuchuo.net/archives/3255
	题目大意：给一个已经排序的链表，删除所有元素值出现过2次或者以上的结点，只保留元素值仅仅出现过一次的结点
	分析：p为head的next，如果p的值和head的值不同，则将head->next置为deleteDuplicates(p)，返回head，
	否则直到找到第一个p不等于head的地方，返回deleteDuplicates(p)*/

	ListNode* deleteDuplicates2(ListNode* head)
	{
		if (head == NULL || head->next == NULL) return head;
		ListNode* p = head->next;
		if (p->val != head->val) {
			head->next = deleteDuplicates(p);
			return head;
		}
		else {
			while (p != NULL && p->val == head->val) p = p->next;
			return deleteDuplicates2(p);
		}
	}
	/*leetcode-92-Reverse Linked List II
	Reverse a linked list from position m to n. Do it in-place and in one-pass.
	For example:
	Given 1->2->3->4->5->NULL, m = 2 and n = 4,
	return 1->4->3->2->5->NULL.
	Note:
	Given m, n satisfy the following condition:
	1 ≤ m ≤ n ≤ length of list.
	思路：
	*/
	ListNode* reverseBetween(ListNode* head, int m, int n)
	 {
		 ListNode dumb(0);
		 dumb.next = head;
		 if(m == n) return head;
		 ListNode* preM = &dumb;//保存m之前结点
		 ListNode* pM = head,*pN = head ,*temp = head;
		 int index=1;
		 while(pN != NULL)
		 {
			 if(index < m)
			 {
				 index++;
				 preM = pM;
				 pM = pM->next;
				 pN = pN->next;
			 }
			 else if(index >= m && index <= n)
			 {
				 temp = pN->next;
				 pN->next = preM->next;
				 preM->next =pN;
				 pN = temp;
				 index++;
			 }
			 else if(index > n)        break;
		 }
			pM->next = pN;
	   return dumb.next;
	}
	ListNode *reverseBetween2(ListNode *head, int m, int n) {
		if(m==n)return head;
		n-=m;
		ListNode prehead(0);
		prehead.next=head;
		ListNode* pre=&prehead;
		while(--m)pre=pre->next;
		ListNode* pstart=pre->next;
		while(n--)
		{
			ListNode *p=pstart->next;
			pstart->next=p->next;
			p->next=pre->next;
			pre->next=p;
		}
		return prehead.next;
	}
	/*leetcode-206-Reverse Linked List
	Reverse a singly linked list*/
	ListNode* reverseList(ListNode* head)
	{
		if(head == NULL) return head;
		ListNode* dumb = new ListNode(0);
		dumb->next = head;
		ListNode * p = head->next;
		head->next = NULL;
		while(p != NULL)
		{
			head = p;
			p = p->next;
			head->next = dumb->next;
			dumb->next = head;
		}
		return dumb->next;
	}
	//递归方法
	ListNode* reverseList2(ListNode* head)
	{
		if(head == NULL || head->next == NULL) return head;

		ListNode * p = head->next;
		head->next = NULL;
		ListNode* newhead = reverseList2(p);
		p->next = head;

		return newhead;
	}
	/*leetcode-25-Reverse Nodes in k-Group
		Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.
		k is a positive integer and is less than or equal to the length of the linked list.
		If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.
		You may not alter the values in the nodes, only nodes itself may be changed.
		Only constant memory is allowed.
		For example,
		Given this linked list: 1->2->3->4->5
		For k = 2, you should return: 2->1->4->3->5
		For k = 3, you should return: 3->2->1->4->5*/
	 ListNode* reverseKGroup(ListNode* head, int k)
	 {
		 if(k == 1 || head == NULL) return head;
		 int length = 0;
		 ListNode* p = head;
		 while(p!=NULL)
		 {
			 length++;
			 p = p->next;
		 }
		 int groupNum = length/k;//组数，比如length=13，k=5，则一共2组
		 ListNode* dumb = new ListNode(0);
		 dumb->next = head;
		 p = head;//p代表当前结点
		 ListNode* q = p->next;//保存下一个结点
		 ListNode* pre = dumb;//当前结点前驱
		ListNode*tempHead = pre; //tempHead为每一组的 头结点前驱 别的结点插入到它后面t empHead->1 2 3 4 5
		 for(int i =1;i <= groupNum;i++)
		 {
			 tempHead = pre;
			 for(int j =0;j < k ;j++)// 组内 头插法翻转
			 {
				 p->next = tempHead->next;
				 tempHead->next = p;
				 pre = p;
				 p = q;
				if(q!=NULL) q = q->next;
			 }
			  head->next  = p;
			  pre = head;
			  head = p;//head 现在为下一组的第一个 相当于刚开始时候的head 也就是每一组的head
		 }
		 pre->next = head;

		 return dumb->next;
	}
	/*leetcode-19-Remove Nth Node From End of List
	Given a linked list, remove the nth node from the end of list and return its head.
	For example,
	   Given linked list: 1->2->3->4->5, and n = 2.
	   After removing the second node from the end, the linked list becomes 1->2->3->5.
	Note:
	Given n will always be valid.
	Try to do this in one pass.
	*/
	ListNode* removeNthFromEnd(ListNode* head, int n)
	{
		if(head == NULL || n<=0)return head;
		ListNode* dumb = new ListNode(0);
		dumb->next = head;
		ListNode* p = dumb;
		head = dumb;
		while(p !=NULL && n--)
		{
			p = p->next;
		}
		while(p !=NULL && p->next != NULL)
		{
			p = p->next;
			head = head->next;
		}
		if(head->next != NULL) head->next = head->next->next;

		return dumb->next;
	}
	/*leetcode-66-Plus One
	Given a non-negative integer represented as a non-empty array of digits, plus one to the integer.
	You may assume the integer do not contain any leading zero, except the number 0 itself.
	The digits are stored such that the most significant digit is at the head of the list.*/
	vector<int> plusOne(vector<int>& digits)
	{
		int carry = 0;
		int temp = 0;
		for(int i = digits.size()-1;i >= 0;i--)
		{
			 if(i == digits.size()-1 )      temp = digits[i] + 1 + carry;
			 else  temp = digits[i] + carry;
			 digits[i] = temp%10;
			 if( temp>=10)      carry = 1;
			else  carry = 0;
		}
		if(carry == 1)
			digits.insert(digits.begin(),1);
		return digits;
	}
	/*leetcode-532-K-diff Pairs in an Array
	Given an array of integers and an integer k, you need to find the number of unique k-diff pairs in the array.
	Here a k-diff pair is defined as an integer pair (i, j), where i and j are both numbers in the array and their absolute difference is k.
	Example 1:
	Input: [3, 1, 4, 1, 5], k = 2
	Output: 2
	Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
	Although we have two 1s in the input, we should only return the number of unique pairs.
	Example 2:
	Input:[1, 2, 3, 4, 5], k = 1
	Output: 4
	Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).
	Example 3:
	Input: [1, 3, 1, 5, 4], k = 0
	Output: 1
	Explanation: There is one 0-diff pair in the array, (1, 1).
	Note:
	The pairs (i, j) and (j, i) count as the same pair.
	The length of the array won't exceed 10,000.
	All the integers in the given input belong to the range: [-1e7, 1e7].
	思路：
	用一个map记录所有关键字，同时去掉了重复元素，然后遍历map，统计个数
	注意 absolute difference 绝对值>=0*/
	int findPairs(vector<int>& nums, int k)
	{
		if (k < 0)return 0;
		int result = 0;
		//sort(nums.begin(),nums.end());//不需要排序
		map<int, int>table;
		map<int, int>::iterator it;
		for (int i = 0; i < nums.size();i++)
		{
			table[nums[i]]++;
		}
		for (it = table.begin(); it != table.end();it++)
		{
			if (k!=0 &&table.count(k + it->first))//比如此时first为1 而k=2 判断是否存在3
			{
				result++;
			}
			else if (k == 0 && it->second >= 2)//说明存在至少两个元素值相等
			{
				result++;
			}
		}
		return result;
	}

	/*Given a linked list, swap every two adjacent nodes and return its head.
	For example,
	Given 1->2->3->4, you should return the list as 2->1->4->3.
	Your algorithm should use only constant space. You may not modify
	the values in the list, only nodes itself can be changed.*/ 
    ListNode *swapPairs(ListNode *head)
	{
	 int k = 2;
     if(k == 1 || head == NULL) return head;
     int length = 0;
     ListNode* p = head;
     while(p!=NULL)
     {
         length++;
         p = p->next;
     }
     int groupNum = length/k;//组数，比如length=13，k=5，则一共2组
     ListNode* dumb = new ListNode(0);
     dumb->next = head;
     p = head;//p代表当前结点
     ListNode* q = p->next;//保存下一个结点
     ListNode* pre = dumb;//当前结点前驱
     ListNode*tempHead = pre; //tempHead为每一组的 头结点前驱 别的结点插入到它后面t empHead->1 2 3 4 5
     for(int i =1;i <= groupNum;i++)
     {
         tempHead = pre;
         for(int j =0;j < k ;j++)// 组内 头插法翻转
         {
             p->next = tempHead->next;
             tempHead->next = p;
             pre = p;
             p = q;
            if(q!=NULL) q = q->next;
         }
          head->next  = p;
          pre = head;
          head = p;//head 现在为下一组的第一个 相当于刚开始时候的head 也就是每一组的head
     }
     pre->next = head;
     return dumb->next; 
    }
	/*leetcode-557-Reverse Words in a String III
	Given a string, you need to reverse the order of characters in each word within a sentence while
	still preserving whitespace and initial word order.
	Example 1:
	Input: "Let's take LeetCode contest"
	Output: "s'teL ekat edoCteeL tsetnoc"
	Note: In the string, each word is separated by single space and there will not be any extra space in the string.
	思路：
	用一个vector<vector<char> >shuzu
	string rev(string x)
    {
        reverse(x.begin(), x.end());
        return x;
    }
    string reverseWords(string s) {
        string t, ans;
        for(char c: s)
        {
            if(c == ' ')
            {
                ans += rev(t) + ' ';
                t = "";
            }
            else
                t += c;
        }
        ans += rev(t);
        return ans;
    }*/
	string reverseWords(string s)
	{
		if(s == "")return s;
		vector<vector<char> >sentence;
		vector<char>word;
		int i=0;
		while(s[i] != '\0')
		{
			if(s[i]!=' ')
			{
				word.insert(word.begin(),s[i]);
			}
			else
			{
				sentence.push_back(word);
				word.clear();
			}
			i++;
		}
		sentence.push_back(word);
		char res[10000];//太小 要用100000
		int ind =0;
		for(int i=0;i<sentence.size();i++)
		{
			for(int j=0;j<sentence[i].size();j++)
			{
				res[ind] = sentence[i][j];
				ind++;
			}
			 res[ind] = ' ';
			 ind++;
		}
		 res[ind-1] = '\0';
		return res;
	}
	/*leetcode-554-Brick Wall My SubmissionsBack To Contest
	User Accepted: 308
	User Tried: 394
	Total Accepted: 310
	Total Submissions: 654
	Difficulty: Medium
	There is a brick wall in front of you. The wall is rectangular and has several rows of bricks.
	The bricks have the same height but different width. You want to draw a vertical line from the top to the bottom and cross the least bricks.
	The brick wall is represented by a list of rows. Each row is a list of integers representing the width of each brick in this row from left to right.
	If your line go through the edge of a brick, then the brick is not considered as crossed.
	You need to find out how to draw the line to cross the least bricks and return the number of crossed bricks.
	You cannot draw a line just along one of the two vertical edges of the wall, in which case the line will obviously cross no bricks.
	Example:
	Input:
	[[1,2,2,1],
	 [3,1,2],
	 [1,3,2],
	 [2,4],
	 [3,1,2],
	 [1,3,1,1]]
	Output: 2
	Explanation:
	思路：
	统计每一层相同的和最多的即为画线的位置
	Note:
	The width sum of bricks in different rows are the same and won't exceed INT_MAX.
	The number of bricks in each row is in range [1,10,000].
	 The height of wall is in range [1,10,000]. Total number of bricks of the wall won't exceed 20,000.
	  map<int, int> ess;
			int s;
			for(auto row: wall)
			{
				s = 0;
				for(auto c: row)
					++ess[s += c];
			}
			int ans = 0;
			for(auto pair: ess)
				if(pair.first != s)
					ans = max(ans, pair.second);
			return (int) wall.size() - ans;*/
	 int leastBricks(vector<vector<int> >& wall)
	 {
		 map<int,int>sumTable;//统计相同和的个数
		 map<int ,int>::iterator it;
		 for(int i =0;i<wall.size();i++)
		 {
			 int sum =0;
			for(int j =0;j<wall[i].size()-1;j++)//从0开始 倒数第一个结束
			{
				sum+=wall[i][j];
				sumTable[sum]++;
			}
		 }
		 int res =0;
		 for(it = sumTable.begin();it!=sumTable.end();it++)
		 {
			 res = max(res,it->second);
		}
		return wall.size()-res;
	}
	/*leetcode-556-Next Greater Element III
	Given a positive 32-bit integer n, you need to find the smallest 32-bit integer which has exactly the same digits existing in
	the integer n and is greater in value than n. If no such positive 32-bit integer exists, you need to return -1.
	Example 1:
	Input: 12
	Output: 21
	Example 2:
	Input: 21
	Output: -1
	思路：
	将n分解为个位数字，放入vector中，然后排序	
	*/
	//大牛写的
	 int nextGreaterElement2(int n) {
        char buf[80];
        sprintf(buf, "%d", n);
        string s = buf;
        puts(s.data());
        sort(s.begin(), s.end());
        long long ans = INT_MAX + 1LL;
        do {
            long long tmp = atoll(s.c_str());
            if (tmp > n) {
                ans = min(ans, tmp);
            }
        } while (next_permutation(s.begin(), s.end()));
        return ans <= INT_MAX ? ans : -1;
    }
	 /*leetcode-461-Hamming Distance
	 The Hamming distance between two integers is the number of positions at
	 which the corresponding bits are different.
	 Given two integers x and y, calculate the Hamming distance.
	 Note:
	 0 ≤ x, y < 231.
	 Example:
	 Input: x = 1, y = 4
	 Output: 2
	 Explanation:
	 1   (0 0 0 1)
	 4   (0 1 0 0)
            ↑  ↑
	 The above arrows point to positions where the corresponding bits are different.*/
	 int hammingDistance(int x, int y)
	 {
		 int res = 0;
		 while (x && y)
		 {
			 int tempx = x & 1;
			 int tempy = y & 1;
			 if (tempx != tempy)res++;
			 x >>= 1;
			 y >>= 1;
		 }
		 while (x)
		 {
			 int tempx = x & 1;
			 x >>= 1;
			 if (tempx) res++;
		 }
		 while (y)
		 {
			 int tempy = y & 1;
			 y >>= 1;
			 if (tempy) res++;
		 }
		 return res;
	 }
	 /*leetcode-500-Keyboard Row
	 Given a List of words, return the words that can be typed using letters 
	 of alphabet on only one row's of American keyboard like the image below.Example 1:
	 Input: ["Hello", "Alaska", "Dad", "Peace"]
	 Output: ["Alaska", "Dad"]
	 Note:
	 You may use one character in the keyboard more than once.
	 You may assume the input string will only contain letters of alphabet.*/
	 bool can(string str, vector<unordered_set<char>>& rows)
	 {		 
		 int row = 0;
		 for (int k = 0; k<3; ++k)
		 {
			 if (rows[k].count((char)tolower(str[0])) > 0) row = k;
		 }
		 for (int i = 1;i<str.size();i++)
		 {	
			 if (rows[row].count((char)tolower(str[i])) == 0) return false;
		 }
		 return true;
	 }
	 vector<string> findWords(vector<string>& words)
	 {
		 vector<string> ret;
		 unordered_set<char> row1{ 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p' };
		 unordered_set<char> row2{ 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l' };
		 unordered_set<char> row3{ 'z', 'x', 'c', 'v', 'b', 'n', 'm' };

		 vector<unordered_set<char>> rows{ row1, row2, row3 };
		 for(int i = 0; i < words.size();i++)
		 {
			 if (can(words[i], rows))
			 {
				 ret.push_back(words[i]);
			 }
		 }
		 return ret;
	 }
	 /*leetcode-496-Next Greater Element I
	 You are given two arrays (without duplicates) nums1 and nums2 where nums1’s elements are subset of nums2. 
	 Find all the next greater numbers for nums1's elements in the corresponding places of nums2.
	 The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2.
	 If it does not exist, output -1 for this number.
	 Example 1:
	 Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
	 Output: [-1,3,-1]
	 Explanation:
	 For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
	 For number 1 in the first array, the next greater number for it in the second array is 3.
	 For number 2 in the first array, there is no next greater number for it in the second array, so output -1.
	 Example 2:
	 Input: nums1 = [2,4], nums2 = [1,2,3,4].
	 Output: [3,-1]
	 Explanation:
	 For number 2 in the first array, the next greater number for it in the second array is 3.
	 For number 4 in the first array, there is no next greater number for it in the second array, so output -1.
	 Note:
	 All elements in nums1 and nums2 are unique.
	 The length of both nums1 and nums2 would not exceed 1000.
	 */
	 vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums)
	 {
		 stack<int> st;
		 map<int, int>M;
		 for (int n : nums)
		 {
			 while (!st.empty() && st.top() < n)
			 {
				 M[st.top()] = n;
				 st.pop();
			 }
			 st.push(n);
		 }
		 vector<int>ret;
		 for (int n : findNums) ret.push_back(M.count(n) ? M[n] : -1);
		 return ret;
	 }
	 /*leetcode-553-Optimal Division
	 Given a list of positive integers, the adjacent integers will perform the float division. For example, [2,3,4] -> 2 / 3 / 4.
	 However, you can add any number of parenthesis at any position to change the priority of operations.
	 You should find out how to add parenthesis to get the maximum result, 
	 and return the corresponding expression in string format. Your expression should NOT contain redundant parenthesis.
	 Example:
	 Input: [1000,100,10,2]
	 Output: "1000/(100/10/2)"
	 Explanation:
	 1000/(100/10/2) = 1000/((100/10)/2) = 200
	 However, the bold parenthesis in "1000/((100/10)/2)" are redundant,
	 since they don't influence the operation priority. So you should return "1000/(100/10/2)".
	 Other cases:
	 1000/(100/10)/2 = 50
	 1000/(100/(10/2)) = 50
	 1000/100/10/2 = 0.5
	 1000/100/(10/2) = 2
	 Note:
	 The length of the input array is [1, 10].
	 Elements in the given array will be in range [2, 1000].
	 There is only one optimal division for each test case.*/
	 string optimalDivision(vector<int>& nums)
	 {
		 string ret;
		 ret = to_string(nums[0]);
		 if (nums.size() == 1)return ret;
		 if (nums.size() == 2) return ret + "/" + to_string(nums[1]);
		 ret += "/(" + to_string(nums[1]);
		 for (int i = 2; i < nums.size();i++)
		 {
			 ret += "/" + to_string(nums[i]);
		 }
		 ret += ")";		
		 return ret;
	 }
	 /*leetcode-504-Base 7
	 Given an integer, return its base 7 string representation.
	 Example 1:
	 Input: 100
	 Output: "202"
	 Example 2:
	 Input: -7
	 Output: "-10"
	 Note: The input will be in range of [-1e7, 1e7].*/
	 string convertToBase7(int num)
	 {
		 if (num == 0) return "0";
		 string ret = "";
		 int temp = num;
		 if (num < 0) num = -num;		 
		 while (num)
		 {
			 //ret.insert(ret.begin(), num % 7 + '0');
			 ret = to_string(num % 7) + ret;//to_string用法
			 num /= 7;
		 }
		 if (temp < 0)ret.insert(ret.begin(), '-');	 
		 return ret;
	 }
	 /*leetcode-521-Longest Uncommon Subsequence I
	 Given a group of two strings, you need to find the longest uncommon subsequence of this group of two strings.
	 The longest uncommon subsequence is defined as the longest subsequence of one of these strings
	 and this subsequence should not be any subsequence of the other strings.
	 A subsequence is a sequence that can be derived from one sequence by 
	 deleting some characters without changing the order of the remaining elements. 
	 Trivially, any string is a subsequence of itself and an empty string is a subsequence of any string.
	 The input will be two strings, and the output needs to be the length of the longest uncommon subsequence.
	 If the longest uncommon subsequence doesn't exist, return -1.
	 Example 1:
	 Input: "aba", "cdc"
	 Output: 3
	 Explanation: The longest uncommon subsequence is "aba" (or "cdc"),
	 because "aba" is a subsequence of "aba",
	 but not a subsequence of any other strings in the group of two strings.
	 Note:
	 Both strings' lengths will not exceed 100.
	 Only letters from a ~ z will appear in input strings.*/
	 int findLUSlength(string a, string b)
	 {
		 if (a == b) return -1;
		 if (a.length() == b.length()) return a.length();
		 return max(a.length(), b.length());
	 }
	 /*leetcode-530-Minimum Absolute Difference in BST
	 Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.
	 Example:
	 Input:
	 1
	 \
	 3
	 /
	 2
	 Output:
	 1
	 Explanation:
	 The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).	 
	 */
	 void zhongxubianli(TreeNode* root, int& ret,int& temp)
	 {
		 if (root!=NULL)
		 {
			 zhongxubianli(root->left, ret,temp);
			 if(temp>=0)ret = min(ret, root->val - temp);
			 temp = root->val;
			 zhongxubianli(root->right, ret,temp);
		 }
	 }
	 int getMinimumDifference(TreeNode* root)
	 {
		 int ret = 100000,temp = -1;
		 zhongxubianli(root, ret,temp);		 
		 return ret;
	 }
	 /*leetcode-541-Reverse String II
	 Given a string and an integer k, you need to reverse the first k characters for every 2k characters
	 counting from the start of the string. If there are less than k characters left, reverse all of them. 
	 If there are less than 2k but greater than or equal to k characters, then reverse the first k characters and left the other as original.
	 Example:
	 Input: s = "abcdefg", k = 2
	 Output: "bacdfeg"
	 Restrictions:
	 The string consists of lower English letters only.
	 Length of the given string and k will in the range [1, 10000]*/
	 string reverseStr(string s, int k)
	 {
		 int group = s.size()/(2*k);
		 int i = 0;
		 for (; i < group;i++)
		 {
			 for (int j = 0; j < k/2;j++)
			 {
				 swap(s[i * 2 * k + j], s[i * 2 * k + k-j-1]);
			 }
		 }
		 int remain = s.size() % (2 * k);
		 int end = (remain >= k) ? k : remain ;
		 for (int j = 0; j < end/2;j++)
		 {
			 swap(s[i * 2 * k + j], s[i * 2 * k + end - j - 1]);
		 }
		 return s;
	 }
	 /*leetcode-543-Diameter of Binary Tree
	 Given a binary tree, you need to compute the length of the diameter of the tree.
	 The diameter of a binary tree is the length of the longest path between any two nodes in a tree. 
	 This path may or may not pass through the root.
	 Example:
	 Given a binary tree
	    1
	   / \
	  2   3
	 / \
	4   5
	 Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].*/
	 int height(TreeNode* root, int& diameter)
	 {
		 if (root == NULL) return 0;
		 int left = height(root->left, diameter);
		 int right = height(root->right, diameter);
		 diameter = max(diameter, left + right);
		 return 1 + max(left, right);
	 }
	 int diameterOfBinaryTree(TreeNode* root)
	 {
		 int diameter = 0;
		 height(root, diameter);
		 return diameter;
	 }
	 /*leetcode-551-Student Attendance Record I
	 You are given a string representing an attendance record for a student.
	 The record only contains the following three characters:
	 'A' : Absent.
	 'L' : Late.
	 'P' : Present.
	 A student could be rewarded if his attendance record doesn't contain more than one 'A' (absent) or more than two continuous 'L' (late).
	 You need to return whether the student could be rewarded according to his attendance record.
	 Example 1:
	 Input: "PPALLP"
	 Output: True
	 Example 2:
	 Input: "PPALLL"
	 Output: False*/
	 bool checkRecord(string s)
	 {
		 map<char, int>record;
		 for (int i = 0; i < s.size();i++)
		 {
			 record[s[i]]++;
		 }
		 if (record['A'] <= 1 && record['L'] <= 2)return true;
		 else if (record['A'] <= 1 && record['L']>2)
		 {
			 for (int i = 2; i < s.size();i++)
			 {
				 if (s[i] == s[i - 1] && s[i] == s[i - 2] && s[i] == 'L') return false;				 
			 }
			 return true;
		 }
		 else return false;
		 /* int a=0, l=0;
	for(int i=0;i<s.size();i++) {
	if(s[i]=='A') a++;
	if(s[i]=='L') l++;
	else l=0;
	if(a>=2||l>2) return false;
	}
	return true;*/
	 }
	 /*leetcode-69-Sqrt(x)
	 Implement int sqrt(int x).
	 Compute and return the square root of x.*/
	 int mySqrt(int x)
	 {
		 if (x == 0) return 0;
		 int left = 1, right = INT_MAX;
		 while (1)
		 {
			 int mid = left + (right - left) / 2;
			 if (mid * mid > x)
			 {
				 right = mid - 1;
			 }
			 else
			 {
				 if((mid + 1)*(mid+1) > x) return mid;				 
				 left = mid + 1;
			 }
		 }
	 }
	 int newton(int x)
	 {
		 if (x == 0) return 0;		 
		 double ans = x;
		 while (abs(pow(ans, 2) - x) > 0.001)
		 {
			 ans = (ans + x / ans) / 2;
		 }
		 return ans;
	 }
	 /*leetcode-14-Longest Common Prefix
	 Write a function to find the longest common prefix string amongst an array of strings.*/
	 string longestCommonPrefix(vector<string>& strs)
	 {
		 if (strs.size() == 0) return "";
		 int strLength = strs[0].size();
		 for (int i = 1; i < strs.size();i++)
		 {
			 strLength = min(strLength, (int)strs[i].size());
		 }
		 int common = strLength;
		 for (int i = 0; i < strLength; i++)
		 {
			 char temp = strs[0][i];
			 for (int j = 1; j < strs.size();j++)
			 {
				 if (strs[j][i] != temp)
				 {
					 common = i;
					 i = strLength;//结束循环
					 break;
				 }
			 }
		 }
		 return strs[0].substr(0, common);
	 }
	 /*leetcode-344-Reverse String
	 Write a function that takes a string as input and returns the string reversed.
	 Example:
	 Given s = "hello", return "olleh".*/
	 string reverseString(string s)
	 {
		 for (int i = 0; i < s.size()/2;i++)
		{
			 swap(s[i], s[s.size() - i - 1]);
		}
		 return s;
	 }
	 /*leetcode-412-Fizz Buzz
	 Write a program that outputs the string representation of numbers from 1 to n.
	 But for multiples of three it should output “Fizz” instead of the number and for the
	 multiples of five output “Buzz”. 
	 For numbers which are multiples of both three and five output “FizzBuzz”.
	 Example:
	 n = 15,
	 Return:
	 [
	 "1",
	 "2",
	 "Fizz",
	 "4",
	 "Buzz",
	 "Fizz",
	 "7",
	 "8",
	 "Fizz",
	 "Buzz",
	 "11",
	 "Fizz",
	 "13",
	 "14",
	 "FizzBuzz"
	 ]*/
	 vector<string> fizzBuzz(int n)
	 {
		 vector<string>ret;
		 stringstream ss;
		 if (n < 1) return ret;
		 for (int i = 1; i <= n;i++)
		 {
			 ss << i;
			 if (i%3 ==0 && i%5!=0) ret.push_back("Fizz");			
			 else if (i%5 ==0 && i%3!=0) ret.push_back("Buzz");			 
			 else if (i%15==0) ret.push_back("FizzBuzz");
			 else ret.push_back(ss.str());
			 ss.str("");			 
		 }
		 return ret;
	 }
	 /*leetcode-463-Island Perimeter
	 You are given a map in form of a two-dimensional integer grid 
	 where 1 represents land and 0 represents water. Grid cells are connected horizontally/vertically (not diagonally). 
	 The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).
	 The island doesn't have "lakes" (water inside that isn't connected to the water around the island). 
	 One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. 
	 Determine the perimeter of the island.*/
	 int islandPerimeter(vector<vector<int>>& grid)
	 {
		 int count = 0, repeat = 0;
		 for (int i = 0; i < grid.size(); i++)
		 {
			 for (int j = 0; j < grid[i].size(); j++)
			 {
				 if (grid[i][j] == 1)
				 {
					 count++;
					 if (i != 0 && grid[i - 1][j] == 1) repeat++;
					 if (j != 0 && grid[i][j - 1] == 1) repeat++;
				 }
			 }
		 }
		 return 4 * count - repeat * 2;
	 }
	 /*leetcode-292-Nim Game
	 suppose there are x stones left for first player (A),
	 he can take 1,2,3 stones away, so second player B will have 
	 three cases to deal with (x -1), (x-2), (x-3). after he pick the stones, 
	 there will be 9 cases left for A.

	 B (x-1) -> A: (x-2), (x-3), (x-4)
	 B (x-2) -> A: (x-3), (x-4), (x-5)
	 B (x-3) -> A: (x-4), (x-5), (x-6)
	 Now, if A can guarantee he win at either of three groups, then he can force B to into that one of the three states 
	 and A can end up in that particular group after B's move.
	 f(x) = (f(x-2)&&f(x-3)&&f(x-4)) || (f(x-3)&&f(x-4)&&f(x-5)) || (f(x-4)&&f(x-5)&&f(x-6))
	 if we examine the equation a little closer, we can find f(x - 4) is a critical point, if f(x-4) is false, then f(x) will be always false.
	 we can also find out the initial conditions, f(1), f(2), f(3) will be true (A always win), and f(4) will be false. so
	 based on previous equation and initial conditions f(5) = f(6) = f(7) = true, f(8) = false;
	 obviously, f(1), f(2), f(3) can make all f(4n + 1), f(4n + 2), f(4n + 3) to be true, only f(4n) will be false then.
	 so here we go our one line solution:
	 return (n % 4 != 0);*/
	 /*leetcode-485-Max Consecutive Ones
	 Given a binary array, find the maximum number of consecutive 1s in this array.
	 Example 1:
	 Input: [1,1,0,1,1,1]
	 Output: 3
	 Explanation: The first two digits or the last three digits are consecutive 1s.
	 The maximum number of consecutive 1s is 3.
	 Note:
	 The input array will only contain 0 and 1.
	 The length of input array is a positive integer and will not exceed 10,000*/
	 int findMaxConsecutiveOnes(vector<int>& nums)
	 {
		 if (nums.size() == 0)return 0;
		 int one = 0;
		 int ret = 0;
		 for (int i = 0; i < nums.size();i++)
		 {
			 if (nums[i] == 1) one++;			
			 else if (nums[i] == 0)
			 {
				 ret = max(ret, one);
				 one = 0;
			 }
		 }
		 ret = max(ret, one);
		 return ret;
	 }
	 /*leetcode-448-Find All Numbers Disappeared in an Array
	 Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.
	 Find all the elements of [1, n] inclusive that do not appear in this array.
	 Could you do it without extra space and in O(n) runtime? 
	 You may assume the returned list does not count as extra space.
	 Example:
	 Input:
	 [4,3,2,7,8,2,3,1]
	 Output:
	 [5,6]*/
	 vector<int> findDisappearedNumbers(vector<int>& nums)
	 {
		 int len = nums.size();
		 for (int i = 0; i<len; i++) {
			 int m = abs(nums[i]) - 1; // index start from 0
			 nums[m] = nums[m]>0 ? -nums[m] : nums[m];
		 }
		 vector<int> res;
		 for (int i = 0; i<len; i++) {
			 if (nums[i] > 0) res.push_back(i + 1);
		 }
		 return res;
	 }
	 /*leetcode-442-Find All Duplicates in an Array
	 Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.
	 Find all the elements that appear twice in this array.
	 Could you do it without extra space and in O(n) runtime?
	 Example:
	 Input:
	 [4,3,2,7,8,2,3,1]
	 Output:
	 [2,3]*/
	 vector<int> findDuplicates(vector<int>& nums)
	 {
		 vector<int>ret;
		 for (int i = 0; i < nums.size();i++)
		 {
			 int index = abs(nums[i]) - 1;
			 if (nums[index] > 0)
			 {
				 nums[index] = - nums[index];
			 }
			 else
			 {
				 ret.push_back(abs(nums[i]));
			 }
		 }
		 return ret;
	 }
	 /*leetcode-389-Find the Difference
	 Given two strings s and t which consist of only lowercase letters.
	 String t is generated by random shuffling string s and then add one more letter at a random position.
	 Find the letter that was added in t.
	 Example:
	 Input:
	 s = "abcd"
	 t = "abcde"
	 Output:
	 e
	 Explanation:
	 'e' is the letter that was added.*/
	 char findTheDifference(string s, string t)
	 {
		 map<char, int>str;
		 for (int i = 0; i < s.size();i++)
		 {
			 str[s[i]]++;
		 }
		 for (int i = 0; i < t.size();i++)
		 {
			 if (str.count(t[i])) str[t[i]]--;			 
			 else return t[i];
		 }
		 map<char, int>::iterator it;
		 for (it = str.begin(); it != str.end();it++)
		 {
			 if (it->second < 0) return it->first;
		 }
	 }
	 /*leetcode-581-Shortest Unsorted Continuous Subarray
	 Given an integer array, you need to find one continuous subarray that
	 if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order, too.
	 You need to find the shortest such subarray and output its length.
	 Example 1:
	 Input: [2, 6, 4, 8, 10, 9, 15]
	 Output: 5
	 Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
	 Note:
	 Then length of the input array is in range [1, 10,000].
	 The input array may contain duplicates, so ascending order here means <=.*/
	 int findUnsortedSubarray(vector<int>& nums)
	 {		 
		 map<int, int>record;
		 for (int i = 0; i < nums.size();i++)  record[i] = nums[i];
		 
		 sort(nums.begin(), nums.end());
		 int start = 0, end = nums.size()-1;
		 while (start< nums.size() && nums[start] == record[start]) start++;
		 while (end >start && nums[end] == record[end]) end--;
		 return end - start + 1;
	 }
	 /*leetcode-582-Kill Process
	 Given n processes, each process has a unique PID (process id) and its PPID (parent process id).
	 Each process only has one parent process, but may have one or more children processes. 
	 This is just like a tree structure. Only one process has PPID that is 0,
	 which means this process has no parent process. All the PIDs will be distinct positive integers.
	 We use two list of integers to represent a list of processes,
	 where the first list contains PID for each process and the second list contains the corresponding PPID.
	 Now given the two lists, and a PID representing a process you want to kill,
	 return a list of PIDs of processes that will be killed in the end. 
	 You should assume that when a process is killed, all its children processes will be killed. No order is required for the final answer.
	 Example 1:
	 Input:
	 pid =  [1, 3, 10, 5]
	 ppid = [3, 0, 5, 3]
	 kill = 5
	 Output: [5,10]
	 Explanation:
	     3
	    /   \
	   1     5
	  /
	 10
	 Kill 5 will also kill 10.
	 Note:
	 The given kill id is guaranteed to be one of the given PIDs.
	 n >= 1.*/
	 void killCore(map<int, set<int>>& nodes, vector<int>& ret, int kill)
	 {
		 ret.push_back(kill);
		 //set<int>::iterator it;
		 //for (it = nodes[kill].begin(); it != nodes[kill].end();it++)
		 //{
			// killCore(nodes, ret, *it);
		 //}
		 for (int child : nodes[kill])
		 {
			 killCore(nodes, ret, child);
		 }
	 }
	 vector<int> killProcess(vector<int>& pid, vector<int>& ppid, int kill)
	 {
		 vector<int> ret;
		 map<int,set<int>> nodes;//每一个父结点对应的子结点
		 for (int i = 0; i < pid.size();i++)
		 {
			 nodes[ppid[i]].insert(pid[i]);
		 }
		 killCore(nodes, ret, kill);

		 return ret;
	 }
	 /*leetcode-583-Delete Operation for Two Strings
	 Given two words word1 and word2, find the minimum number of steps required to make word1 and word2 the same, 
	 where in each step you can delete one character in either string.
	 Example 1:
	 Input: "sea", "eat"
	 Output: 2
	 Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
	 Note:
	 The length of given words won't exceed 500.
	 Characters in given words can only be lower-case letters.*/
	 int minDistance2(string word1, string word2)
	 {
		 vector<vector<int>> dp(word1.size()+1,vector<int>(word2.size()+1,0));
		 for (int i = 0; i <= word1.size();i++)
		 {
			 for (int j = 0; j <= word2.size();j++)
			 {
				 if (i == 0 || j == 0) dp[i][j] = 0;
				 else if (word1[i-1] == word2[j-1])
				 {
					 dp[i][j] = dp[i - 1][j - 1] + 1;
				 }
				 else
				 {
					 dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				 }
				 
			 }
		 }
		 int lcs = dp[word1.size()][word2.size()];
		 return word1.size() - lcs + word2.size() - lcs;
	 }
	 /*leetcode-226-Invert Binary Tree
	 Invert a binary tree.
	      4
	    /   \
	   2     7
	  / \   / \
	 1   3 6   9
	 to
	      4
	    /   \
	   7     2
	  / \   / \
	 9   6 3   1
	 Trivia:
	 This problem was inspired by this original tweet by Max Howell:
	 Google: 90% of our engineers use the software you wrote (Homebrew), but you can’t invert a binary tree on a whiteboard so fuck off.*/
	 void invertCore(TreeNode* root)
	 {
		 if (root == NULL) return;
		 swap(root->left, root->right);
		 invertCore(root->left);
		 invertCore(root->right);
	 }
	 TreeNode* invertTree(TreeNode* root)
	 {
		 invertCore(root);
		 return root;
	 }
	 /*leetcode-283-Move Zeroes
	 Given an array nums, write a function to move all 0's to the end of it while
	 maintaining the relative order of the non-zero elements.
	 For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].
	 Note:
	 You must do this in-place without making a copy of the array.
	 Minimize the total number of operations.*/
	 void moveZeroes(vector<int>& nums)
	 {
		 int zeros = 0;
		 for (int i = 0; i < nums.size();i++)
		 {
			 if (nums[i] == 0) zeros++;
		 }
		 int first = 0;
		 for (int i = 0; i < nums.size();i++)
		 {
			 if (nums[i] != 0)
			 {
				 nums[first++] = nums[i];
			 }
		 }
		 for (int i =first; i < nums.size();i++)
		 {
			 nums[i] = 0;
		 }
	 }
	 /*leetcode-535-Encode and Decode TinyURL
	 TinyURL is a URL shortening service where you enter a URL such as
	 https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk.
	 Design the encode and decode methods for the TinyURL service. 
	 There is no restriction on how your encode/decode algorithm should work. 
	 You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.*/
	 
	 string dict = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	 int id = 0;
	 unordered_map<string, string>m;
	 unordered_map<int, string>idm;
	 // Encodes a URL to a shortened URL.
	 string encode(string longUrl)
	 {
		 if (m.find(longUrl) != m.end())return m[longUrl];
		 string res = "";
		 id++;
		 int count = id;
		 while (count > 0)
		 {
			 res = dict[count % 62] + res;
			 count /= 62;
		 }
		 while (res.size() < 6) res = "0" + res;
		 m[longUrl] = res;
		 idm[id] = longUrl;
		 return res;
	 }
	 // Decodes a shortened URL to its original URL.
	 string decode(string shortUrl)
	 {
		 int id = 0;
		 for (int i = 0; i < shortUrl.size();i++)
		 {
			 id = 62 * id + (int)(dict.find(shortUrl[i]));
		 }
		 if (idm.find(id) != idm.end())return idm[id];
		 return "";
	 }
	 /*leetcode-338-Counting Bits
	 Given a non negative integer number num. For every numbers i in the range 0 ≤ i ≤ num 
	 calculate the number of 1's in their binary representation 
	 and return them as an array.
	 Example:
	 For num = 5 you should return [0,1,1,2,1,2].
	 Follow up:
	 It is very easy to come up with a solution with run time O(n*sizeof(integer)). 
	 But can you do it in linear time O(n) /possibly in a single pass?
	 Space complexity should be O(n).
	 Can you do it like a boss? Do it without using any builtin function like 
	 __builtin_popcount in c++ or in any other language.*/
	 vector<int> countBits(int num)
	 {
		 vector<int> ret(num + 1, 0);
		 ret[0] = 0;
		 int offset = 1;
		 for (int i = 1; i <= num;i++)
		 {
			 if (i == offset*2)
			 {
				 offset *= 2;
			 }
			 ret[i] = ret[i - offset] + 1;
		 }
		 return ret;
	 }
	 /*leetcode-513-Find Bottom Left Tree Value
	 Given a binary tree, find the leftmost value in the last row of the tree.
	 Example 1:
	 Input:
	 2
	 / \
	 1   3

	 Output:
	 1
	 Example 2:
	 Input:
	 1
	 / \
	 2   3
	 /   / \
	 4   5   6
	 /
	 7
	 Output:
	 7*/
	 int findBottomLeftValue(TreeNode* root)
	 {
		 queue<TreeNode*>que;
		 if (root!=NULL)que.push(root);		
		 int ret = -1;
		 while (!que.empty())
		 {
			 int size = que.size();			 
			 for (int i = 0; i < size;i++)//一层
			 {
				 TreeNode* temp = que.front();
				 que.pop();
				 if (i ==0)ret = temp->val;
				 if (temp->left != NULL)que.push(temp->left);
				 if (temp->right != NULL)que.push(temp->right);
			 }
		 }
		 return ret;
	 }
	 /*leetcode-13-Roman to Integer
	 Given a roman numeral, convert it to an integer.
	 Input is guaranteed to be within the range from 1 to 3999.*/
	 int romanToInt(string s)
	 {
		 map<char, int>T = { { 'I', 1 },
							{ 'V', 5 },
							{ 'X', 10 },
							{ 'L', 50 },
							{ 'C', 100 },
							{ 'D', 500 },
							{ 'M', 1000 }		 
							};
		 int sum = T[s.back()];
		 for (int i = s.length() - 2; i >= 0;i--)
		 {
			 if (T[s[i]]<T[s[i+1]])
			 {
				 sum -= T[s[i]];
			 }
			 else
			 {
				 sum += T[s[i]];
			 }
		 }
		 return sum;
	 }

	 /*leetcode-526-Beautiful Arrangement
	 Suppose you have N integers from 1 to N. We define a beautiful arrangement as an array that is constructed by these N numbers successfully
	 if one of the following is true for the ith position (1 ≤ i ≤ N) in this array:
	 The number at the ith position is divisible by i.
	 i is divisible by the number at the ith position.
	 Now given N, how many beautiful arrangements can you construct?
	 Example 1:
	 Input: 2
	 Output: 2
	 Explanation:
	 The first beautiful arrangement is [1, 2]:
	 Number at the 1st position (i=1) is 1, and 1 is divisible by i (i=1).
	 Number at the 2nd position (i=2) is 2, and 2 is divisible by i (i=2).
	 The second beautiful arrangement is [2, 1]:
	 Number at the 1st position (i=1) is 2, and 2 is divisible by i (i=1).
	 Number at the 2nd position (i=2) is 1, and i (i=2) is divisible by 1.
	 Note:
	 N is a positive integer and will not exceed 15.*/
	 int counts(int n,vector<int>& intvec)
	 {
		 if (n <= 0) return 1;
		 int res = 0;
		 for (int i = 0; i < n;i++)
		 {
			 if (intvec[i]%n ==0 || n %intvec[i] ==0)
			 {
				 swap(intvec[i], intvec[n - 1]);
				 res += counts(n - 1, intvec);
				 swap(intvec[i], intvec[n - 1]);
			 }
		 }
		 return res;
	 }
	 int countArrangement(int N)
	 {
		 vector<int> intvec;
		 for (int i = 0; i < N; i++)intvec.push_back(i + 1);
		 return counts(N, intvec);		 
	 }
	 /*leetcode-413-Arithmetic Slices
	 A sequence of number is called arithmetic if it consists of at least three elements
	 and if the difference between any two consecutive elements is the same.
	 For example, these are arithmetic sequence:
	 1, 3, 5, 7, 9
	 7, 7, 7, 7
	 3, -1, -5, -9
	 The following sequence is not arithmetic.
	 1, 1, 2, 5, 7
	 A zero-indexed array A consisting of N numbers is given.
	 A slice of that array is any pair of integers (P, Q) such that 0 <= P < Q < N.
	 A slice (P, Q) of array A is called arithmetic if the sequence:
	 A[P], A[p + 1], ..., A[Q - 1], A[Q] is arithmetic. In particular, this means that P + 1 < Q.
	 The function should return the number of arithmetic slices in the array A.
	 Example:
	 A = [1, 2, 3, 4]
	 return: 3, for 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4] itself.*/
	 int numberOfArithmeticSlices(vector<int>& A)
	 {
		 int n = A.size();
		 if (n < 3 ) return 0;
		 vector<int>dp(n, 0);
		 if (A[2] - A[1] == A[1] - A[0]) dp[2] = 1;
		 int result = dp[2];
		 for (int i = 3; i < n;i++)
		 {
			 if (A[i] - A[i-1] == A[i-1]-A[i-2]) dp[i] = dp[i - 1] + 1;
			 result += dp[i];
		 }
		 return result;
	 }
	 /*leetcode-515-Find Largest Value in Each Tree Row
	 You need to find the largest value in each row of a binary tree.
	 Example:
	 Input:
	     1
	    / \
	   3   2
	  / \   \
	 5   3   9
     Output: [1, 3, 9]*/
	 vector<int> largestValues(TreeNode* root)
	 {
		 vector<int>result;
		 if (root == NULL)return result;
		 queue<TreeNode*>que;
		 que.push(root);
		 int tempmax = INT_MIN;
		 while (!que.empty())
		 {
			 int levelsize = que.size();
			 TreeNode* temp;
			 for (int i = 0; i < levelsize;i++)
			 {
				 temp = que.front();
				 que.pop();
				 if (temp->left != NULL)que.push(temp->left);
				 if (temp->right != NULL)que.push(temp->right);
				 tempmax = max(tempmax, temp->val);
			 }
			 result.push_back(tempmax);
			 tempmax = INT_MIN;
		 }
		 return result;		 
	 }
	 /*leetcode-495-Teemo Attacking
	 In LLP world, there is a hero called Teemo and his attacking can make his enemy Ashe be in poisoned condition.
	 Now, given the Teemo's attacking ascending time series towards Ashe and the poisoning time duration per Teemo's attacking,
	 you need to output the total time that Ashe is in poisoned condition.
	 You may assume that Teemo attacks at the very beginning of a specific time point,
	 and makes Ashe be in poisoned condition immediately.
	 Example 1:
	 Input: [1,4], 2
	 Output: 4
	 Explanation: At time point 1, Teemo starts attacking Ashe and makes Ashe be poisoned immediately.
	 This poisoned status will last 2 seconds until the end of time point 2.
	 And at time point 4, Teemo attacks Ashe again, and causes Ashe to be in poisoned status for another 2 seconds.
	 So you finally need to output 4.
	 Example 2:
	 Input: [1,2], 2
	 Output: 3
	 Explanation: At time point 1, Teemo starts attacking Ashe and makes Ashe be poisoned.
	 This poisoned status will last 2 seconds until the end of time point 2.
	 However, at the beginning of time point 2, Teemo attacks Ashe again who is already in poisoned status.
	 Since the poisoned status won't add up together, though the second poisoning attack will still work at time point 2,
	 it will stop at the end of time point 3.So you finally need to output 3.*/
	 int findPoisonedDuration(vector<int>& timeSeries, int duration)
	 {
		 int ret = 0;
		 int n = timeSeries.size();
		 if (n == 0)return 0;
		 if (n == 1)return duration;

		 for (int i = 0; i < n - 1; i++)
		 {
			 if (timeSeries[i] + duration > timeSeries[i + 1])//超过了
			 {
				 ret = ret + timeSeries[i + 1] - timeSeries[i];
			 }
			 else
			 {
				 ret += duration;
			 }
		 }
		 ret += duration;
		 return ret;
	 }
	 /*leetcode-56-Merge Intervals
	 Given a collection of intervals, merge all overlapping intervals.
	 For example,
	 Given [1,3],[2,6],[8,10],[15,18],
	 return [1,6],[8,10],[15,18].*/
	 vector<Interval> merge(vector<Interval>& intervals)
	 {
		 int n = intervals.size();
		 vector<Interval> ret;
		 if (n <= 1)return intervals;
		 sort(intervals.begin(), intervals.end(), [](Interval a, Interval b){return a.start < b.start;});
		 ret.push_back(intervals[0]);
		 for (int i = 1; i < n; i++)
		 {
			 if (ret.back().end < intervals[i].start)ret.push_back(intervals[i]);
			 else ret.back().end = max(ret.back().end , intervals[i].end);			 
		 }
		 return ret;
	 }
	 /*leetcode-508-Most Frequent Subtree Sum
	 Given the root of a tree, you are asked to find the most frequent subtree sum.
	 The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at
	 that node (including the node itself). So what is the most frequent subtree sum value? If there is a tie,
	 return all the values with the highest frequency in any order.
	 Examples 1
	 Input:
	 5
	 /  \
	 2   -3
	 return [2, -3, 4], since all the values happen only once, return all of them in any order.
	 Examples 2
	 Input:
	 5
	 /  \
	 2   -5
	 return [2], since 2 happens twice, however -5 only occur once.*/
	 int sumofTree(TreeNode* root, map<int, int>&counts, int & maxcount)
	 {
		 if (root == NULL)return 0;
		 int sum = root->val;
		 sum += sumofTree(root->left, counts, maxcount);
		 sum += sumofTree(root->right, counts, maxcount);
		 counts[sum]++;
		 maxcount = max(maxcount, counts[sum]);
		 return sum;
	 }
	 vector<int> findFrequentTreeSum(TreeNode* root)
	 {
		 vector<int>ret;
		 map<int, int>counts;
		 int maxcount = 0;
		 sumofTree(root, counts, maxcount);

		 for (auto it = counts.begin(); it != counts.end();it++)
		 {
			 if (it->second == maxcount)ret.push_back(it->first);			  
		 }
		 return ret;
	 }
	 /*leetcode-190-Reverse Bits
	 Reverse bits of a given 32 bits unsigned integer.
	 For example, given input 43261596 (represented in binary as 00000010100101000001111010011100),
	 return 964176192 (represented in binary as 00111001011110000010100101000000).
	 Follow up:
	 If this function is called many times, how would you optimize it?
	 Related problem: Reverse Integer*/
	 int reverseBits(int n)
	 {
		 int m = 0;
		 
		 for (int i = 0; i < 32;i++)
		 {
			 m <<= 1;
			 m += n & 1;
			 n >>= 1;
		 }
		 return m;
	 }
	 /*leetcode-20-Valid Parentheses
	 Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
	 The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.*/
	 bool isValid(string s)
	 {
		 stack<char>st;		
		 for (int i = 0; i < s.size();i++)
		 {
			 switch (s[i])
			 {
			 case '(':
			 case '[':
			 case '{':st.push(s[i]); break;
			 case ')':if (st.empty() || st.top() != '(')return false; else st.pop(); break;
			 case '}': if (st.empty() || st.top() != '{') return false; else st.pop(); break;
			 case ']': if (st.empty() || st.top() != '[') return false; else st.pop(); break;
			 default:;
			 }			  
		 }
		 return st.empty();		
	 }
	 /*leetcode-12-Integer to Roman
	 Given an integer, convert it to a roman numeral.
	 */
	 string intToRoman(int num)
	 {
		 string M[] = { "", "M", "MM", "MMM" };
		 string C[] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
		 string X[] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
		 string I[] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
		 return M[num / 1000] + C[(num % 1000) / 100] + X[(num % 100) / 10] + I[num % 10];
	 }
	 /*leetcode-22-Generate Parentheses
	 Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
	 For example, given n = 3, a solution set is:
	 [
	 "((()))",
	 "(()())",
	 "(())()",
	 "()(())",
	 "()()()"
	 ]*/
	 void addParenthesis(vector<string>& res, string str, int open, int close,int n)
	 {
		 if (str.length() == n*2)
		 {
			 res.push_back(str);
			 return;
		 }
		 if (open<n)addParenthesis(res, str + "(", open + 1, close, n);
		 if (close < open)addParenthesis(res, str + ")", open, close + 1, n);		 
	 }
	 vector<string> generateParenthesis(int n)
	 {
		 vector<string>res;
		 addParenthesis(res, "", 0, 0, n);
		 return res;
	 }
	 /*486. Predict the Winner
	 Given an array of scores that are non-negative integers. Player 1 picks one of the numbers from either end of the array
	 followed by the player 2 and then player 1 and so on. Each time a player picks a number, that number will
	 not be available for the next player. This continues until all the scores have been chosen. The player with the maximum score wins.
	 Given an array of scores, predict whether player 1 is the winner. You can assume each player plays to maximize his score.
	 Example 1:
	 Input: [1, 5, 2]
	 Output: False
	 Explanation: Initially, player 1 can choose between 1 and 2.
	 If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5. If player 2 chooses 5, then player 1 will be left with 1 (or 2).
	 So, final score of player 1 is 1 + 2 = 3, and player 2 is 5.
	 Hence, player 1 will never be the winner and you need to return False.
	 Example 2:
	 Input: [1, 5, 233, 7]
	 Output: True
	 Explanation: Player 1 first chooses 1. Then player 2 have to choose between 5 and 7. No matter which number player 2 choose, player 1 can choose 233.
	 Finally, player 1 has more score (234) than player 2 (12), so you need to return True representing player1 can win.
	 Note:
	 1 <= length of the array <= 20.
	 Any scores in the given array are non-negative integers and will not exceed 10,000,000.
	 If the scores of both players are equal, then player 1 is still the winner.*/
	 
	 /*leetcode-374-Guess Number Higher or Lower
	 We are playing the Guess Game. The game is as follows:
	 I pick a number from 1 to n. You have to guess which number I picked.
	 Every time you guess wrong, I'll tell you whether the number is higher or lower.
	 You call a pre-defined API guess(int num) which returns 3 possible results (-1, 1, or 0):
	 -1 : My number is lower
	 1 : My number is higher
	 0 : Congrats! You got it!
	 Example:
	 n = 10, I pick 6.
	 Return 6.*/
	 int guess(int num);
	 int guessNumber(int n)
	 {
		 int maxnum = n, minnum = 1;
		 while (1)
		 {
			 int mid = minnum + (maxnum - minnum) / 2;
			 int gus = guess(mid);
			 if (gus == 0)return mid;
			 if (gus == 1)
			 {
				 minnum = mid + 1;
			 }
			 else maxnum = mid - 1;
		 }		 
		  
	 }
	 /*leetcode-54-Spiral Matrix]
	 Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.
	 For example,Given the following matrix:
	 [
	 [ 1, 2, 3 ],
	 [ 4, 5, 6 ],
	 [ 7, 8, 9 ]
	 ]
	 You should return [1,2,3,6,9,8,7,4,5].*/
	 vector<int> spiralOrder(vector<vector<int>>& matrix)
	 {
		 if (matrix.empty())return{};
		 int m = matrix.size(), n = matrix[0].size();
		 vector<int> spiral(m*n);
		 int up = 0, down = m - 1, left = 0, right = n - 1, k = 0;
		 while (1)
		 {
			 for (int col = left; col <= right; col++)spiral[k++] = matrix[up][col];
			 if (++up > down)break;
			 for (int row = up; row <= down; row++)spiral[k++] = matrix[row][right];
			 if (--right < left)break;
			 for (int col = right; col >= left; col--)spiral[k++] = matrix[down][col];
			 if (--down < up)break;
			 for (int row = down; row >= up; row--)spiral[k++] = matrix[row][left];
			 if (++left > right)break;
		 }
		 return spiral;
	 }
	 /*leetcode-59-Spiral Matrix II
	 Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.
	 For example,
	 Given n = 3,
	 You should return the following matrix:
	 [
	 [ 1, 2, 3 ],
	 [ 8, 9, 4 ],
	 [ 7, 6, 5 ]
	 ]*/
	 vector<vector<int>> generateMatrix(int n)
	 {
		 if (n <= 0)return{};		 
		 vector<vector<int>>matrix(n,vector<int>(n,0));
		 int up = 0, down = n - 1, left = 0, right = n - 1 ,k =1;
		 while (1)
		 {
			 for (int col = left; col <= right; col++)matrix[up][col] = k++;
			 if (++up>down)break;
			 for (int row = up; row <= down; row++)matrix[row][right] = k++;
			 if (--right < left)break;
			 for (int col = right; col >= left; col--)matrix[down][col] = k++;
			 if (--down < up)break;
			 for (int row = down; row >= up; row--)matrix[row][left] = k++;
			 if (++left>right)break;
		 }
		 return matrix;
	 }
	 /*leetcode-74-Search a 2D Matrix
	 Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
	 Integers in each row are sorted from left to right.
	 The first integer of each row is greater than the last integer of the previous row.
	 For example,
	 Consider the following matrix:
	 [
	 [1,   3,  5,  7],
	 [10, 11, 16, 20],
	 [23, 30, 34, 50]
	 ]
	 Given target = 3, return true.*/
	 bool searchMatrix(vector<vector<int>>& matrix, int target)
	 {
		 if (matrix.size() == 0) return false;
		
		 int row = matrix.size(), col = matrix[0].size();
		 int left = 0, right = row*col - 1, middle = left + (right - left) / 2;
		 
		 while (left <= right)
		 {
			 middle = left + (right - left) / 2;
			 if (target == matrix[middle / col][middle%col])return true;
			 else if (target < matrix[middle / col][middle%col])right = middle - 1;
			 else left = middle + 1;
		 }
		 return false;		 
	 }
	 /*leetcode-75-Sort Colors
	 Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, 
	 with the colors in the order red, white and blue.
	 Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
	 Note:
	 You are not suppose to use the library's sort function for this problem. */
	 void sortColors(vector<int>& nums)
	 {
		 int n = nums.size();
		 if (n <= 1)return;
		 int *temp = new int[n];
		 //vector<int>temp = nums;
		 int zero = 0, one = 0, two = 0, index0 = 0, index1 = 0, index2 = 0;
		 for (int i = 0; i < n;i++)
		 {
			 if (nums[i] == 0)zero++;
			 if (nums[i] == 1)one++;
			 if (nums[i] == 2)two++;
			 temp[i] = nums[i];
		 }
		 index1 = zero, index2 = zero + one;
		 for (int i = 0; i < n; i++)
		 {
			 if (temp[i] == 0)nums[index0++] = 0;
			 if (temp[i] == 1)nums[index1++] = 1;
			 if (temp[i] == 2)nums[index2++] = 2;
		 }
		 delete[]temp;
	 }
	 /*leetcode-76-Minimum Window Substring
	 Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).
	 For example,
	 S = "ADOBECODEBANC"
	 T = "ABC"
	 Minimum window is "BANC".
	 Note:
	 If there is no such window in S that covers all characters in T, return the empty string "".
	 If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.*/
	 string minWindow(string s, string t)
	 {

	 }
	 /*leetcode-35-Search Insert Position
	 You may assume no duplicates in the array.
	 Here are few examples.
	 [1,3,5,6], 5 → 2
	 [1,3,5,6], 2 → 1
	 [1,3,5,6], 7 → 4
	 [1,3,5,6], 0 → 0
	 */
	 int searchInsert(vector<int>& nums, int target)
	 {
		 int len = nums.size();
		 if (len == 0 || nums[0]>=target)return 0;
		 for (int i = 1; i < len;i++)
		 {
			 if (nums[i]==target) return i;
			 if (nums[i]>target && target>nums[i - 1])return i;
		 }
		 return len;
	 }
	 /*leetcode-33-Search in Rotated Sorted Array
	 Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
	 (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
	 You are given a target value to search. If found in the array return its index, otherwise return -1.
	 You may assume no duplicate exists in the array.*/
	 int search(vector<int>& nums, int target)
	 {
		 int len = nums.size();
		 if (len == 0)return -1;
		 for (int i = 0; i < len; i++)
		 {
			 if (nums[i] == target)return i;
		 }
		 return -1;
	 }
	 /*leetcode-34-Search for a Range
	 Given an array of integers sorted in ascending order, find the starting and ending position of a given target value.
	 Your algorithm's runtime complexity must be in the order of O(log n).
	 If the target is not found in the array, return [-1, -1].
	 For example,
	 Given [5, 7, 7, 8, 8, 10] and target value 8,
	 return [3, 4].*/
	 vector<int> searchRange(vector<int>& nums, int target)
	 {
		 int len = nums.size(),low=0,high = len-1,mid = low +(high-low)/2;
		 vector<int>ret;
		 while (low <= high)
		 {
			 mid = low + (high - low) / 2;
			 if (nums[mid] == target)
			 {
				 while (mid>=0 && nums[mid] == target)
				 {
					 mid--;
				 }
				 ret.push_back(mid + 1);
				 mid++;
				 while (mid<len && nums[mid] == target)
				 {
					 mid++;
				 }
				 ret.push_back(mid - 1);
				 break;
			 }
			 else if (nums[mid]<target)
			 {
				 low = mid + 1;
			 }
			 else high = mid - 1;
		 }
		 if (ret.size()==0)
		 {
			 ret.push_back(-1), ret.push_back(-1);
		 }
		 return ret;
	 }
	 /*leetcode-51-N-Queens
	 */
	 bool isValid(vector<string>& nQueens, int row, int col, int &n)
	 {
		 for (int i = 0; i < row;i++)
		 {
			 if (nQueens[i][col] == 'Q')return false;
		 }
		 for (int i = row - 1, j = col - 1; i >= 0&&j >= 0;i--,j--)
		 {
			 if (nQueens[i][j] == 'Q')return false;
		 }
		 for (int i = row - 1, j = col + 1; i >= 0&&j < n;i--,j++)
		 {
			 if (nQueens[i][j] == 'Q')return false;
		 }
		 return true;
	 }
	 void solveNQueens(vector<vector<string>>& ret, vector<string>& nQueens, int row, int & n)
	 {
		 if (row == n)
		 {
			 ret.push_back(nQueens);
			 return;
		 }
		 for (int col = 0; col < n;col++)
		 {
			 if (isValid(nQueens,row,col,n))
			 {
				 nQueens[row][col] = 'Q';
				 solveNQueens(ret, nQueens, row + 1, n);
				 nQueens[row][col] = '.';
			 }
		 }
	 }
	 vector<vector<string>> solveNQueens(int n)
	 {
		 vector<vector<string>> ret;
		 vector<string> nQueens(n, string(n, '.'));
		 solveNQueens(ret, nQueens, 0, n);
		 return ret;
	 }
	 /*leetcode-52-N-Queens II
	 Follow up for N-Queens problem.
	 Now, instead outputting board configurations, return the total number of distinct solutions.*/
	 void totalNQueens(int& n, int row, vector<string>& nQueens, int& total)
	 {
		 if (row == n)
		 {
			 total += 1;
			 return;
		 }
		 for (int col = 0; col < n;col++)
		 {
			 if (isValid(nQueens, row, col, n))
			 {
				 nQueens[row][col] = 'Q';
				 totalNQueens(n, row + 1, nQueens, total);
				 nQueens[row][col] = '.';
			 }
		 }
	 }
	 int totalNQueens(int n)
	 {
		 vector<string> nQueens(n, string(n, '.'));
		 int total = 0;
		 totalNQueens(n, 0, nQueens, total);
		 return total;
	 }
	 /*leetcode-5-Longest Palindromic Substring
	 Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
	 Example:
	 Input: "babad"
	 Output: "bab"
	 Note: "aba" is also a valid answer.
	 Example:
	 Input: "cbbd"
	 Output: "bb"*/
	 string longestPalindrome(string s)
	 {
		
	 }
	 /*leetcode-17-Letter Combinations of a Phone Number*/
	 vector<string> letterCombinations(string digits)
	 {
		 vector<string>res;
		 if (digits.size() == 0)return res;
		 string charmap[10] = { "0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
		 res.push_back("");
		 for (int i = 0; i < digits.size();i++)
		 {
			 vector<string>tempres;
			 string chars = charmap[digits[i]-'0'];
			 for (int c = 0; c < chars.size();c++)
			 {
				 for (int j = 0; j < res.size();j++)
				 {
					 tempres.push_back(res[j] + chars[c]);
				 }
			 }
			 res = tempres;
		 }
		 return res;
	 }
	 /*leetcode-39-Combination Sum
	 Given a set of candidate numbers (C) (without duplicates) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
	 The same repeated number may be chosen from C unlimited number of times.
	 Note:
	 All numbers (including target) will be positive integers.
	 The solution set must not contain duplicate combinations.
	 For example, given candidate set [2, 3, 6, 7] and target 7,
	 A solution set is:
	 [
	 [7],
	 [2, 2, 3]
	 ]*/
	 void combinationSum(vector<vector<int>>&ret, vector<int>& temp, vector<int>& candidates, int target,int begin)
	 {
		 if (target==0)
		 {
			 ret.push_back(temp);
			 return;
		 }
		 for (int i = begin; i < candidates.size() && candidates[i]<=target;i++)
		 {
			 temp.push_back(candidates[i]);
			 combinationSum(ret, temp, candidates, target - candidates[i],i);
			 temp.pop_back();
		 }
	 }
	 vector<vector<int>> combinationSum(vector<int>& candidates, int target)
	 {
		 vector<vector<int>>ret;
		 vector<int>temp;
		 sort(candidates.begin(), candidates.end());
		 combinationSum(ret, temp, candidates, target,0);
		 return ret;
	 }
	 /*leetcode-167-Two Sum II - Input array is sorted
	 Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.
	 The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2.
	 Please note that your returned answers (both index1 and index2) are not zero-based.
	 You may assume that each input would have exactly one solution and you may not use the same element twice.
	 Input: numbers={2, 7, 11, 15}, target=9
	 Output: index1=1, index2=2*/
	 vector<int> twoSum2(vector<int>& numbers, int target)
	 {
		 vector<int>ret;
		// unordered_map<int,int>mp;//map hash方法不行 不能处理重复数据情况
		 int low = 0, high = numbers.size() - 1;
		 while (low < high)
		 {
			 if (numbers[low]+numbers[high] == target)
			 {
				 ret.push_back(low+1);
				 ret.push_back(high+1);
				 break;
			 }
			 else if (numbers[low] + numbers[high] < target)
			 {
				 low++;
			 }
			 else high--;
		 }
		 return ret;
	 }
	 /*leetcode-260-Single Number III
	 Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice.
	 Find the two elements that appear only once.
	 For example:
	 Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].
	 Note:
	 The order of the result is not important. So in the above example, [5, 3] is also correct.
	 Your algorithm should run in linear runtime complexity.
	 Could you implement it using only constant space complexity?*/
	 vector<int> singleNumber1(vector<int>& nums)
	 {
		 int r = 0, n = nums.size(), i = 0, last = 0;
		 vector<int> ret(2, 0);

		 for (i = 0; i < n; ++i)
			 r ^= nums[i];

		 last = r & (~(r - 1));
		 for (i = 0; i < n; ++i)
		 {
			 if ((last & nums[i]) != 0)
				 ret[0] ^= nums[i];
			 else
				 ret[1] ^= nums[i];
		 }

		 return ret;
	 }
	 /*leetcode-547-Friend Circles
	 There are N students in a class. Some of them are friends, while some are not.
	 Their friendship is transitive in nature.
	 For example, if A is a direct friend of B, and B is a direct friend of C, then A is an indirect friend of C.
	 And we defined a friend circle is a group of students who are direct or indirect friends.
	 Given a N*N matrix M representing the friend relationship between students in the class. If M[i][j] = 1,
	 then the ith and jth students are direct friends with each other, otherwise not.
	 And you have to output the total number of friend circles among all the students.
	 Example 1:
	 Input:
	 [[1,1,0],
	 [1,1,0],
	 [0,0,1]]
	 Output: 2
	 Explanation:The 0th and 1st students are direct friends, so they are in a friend circle.
	 The 2nd student himself is in a friend circle. So return 2.
	 Example 2:
	 Input:
	 [[1,1,0],
	 [1,1,1],
	 [0,1,1]]
	 Output: 1
	 Explanation:The 0th and 1st students are direct friends, the 1st and 2nd students are direct friends,
	 so the 0th and 2nd students are indirect friends. All of them are in the same friend circle, so return 1.
	 Note:
	 N is in range [1,200].
	 M[i][i] = 1 for all students.
	 If M[i][j] = 1, then M[j][i] = 1.*/
	 void mark(vector<vector<int>>& M,vector<bool>&flag,int k)
	 {
		 flag[k] = true;
		 for (int i = 0; i < M.size();i++)
		 {
			 if (flag[i]==false && M[k][i]==1)
			 {
				 mark(M, flag, i);
			 }
		 }

	 }
	 int findCircleNum(vector<vector<int>>& M)
	 {
		 int m = M.size();
		 if (m == 0)return 0;		 
		 vector<bool>flag(m,false);
		 int circle = 0;
		 for (int i = 0; i < m;i++)
		 {
			 if (flag[i]==false)
			 {
				 mark(M, flag, i);
				 circle++;
			 }
		 }
		 return circle;
	 }
	 /*leetcode-447-Number of Boomerangs*/
	 int numberOfBoomerangs(vector<pair<int, int>>& points)
	 {
		 int ret = 0;
		 for (int i = 0; i < points.size();i++)
		 {
			 map<int, int>mp;
			 for (int j = 0; j < points.size();j++)
			 {
				 if (i == j)continue;
				 int dx = points[i].first - points[j].first;
				 int dy = points[i].second - points[j].second;
				 mp[dx*dx + dy*dy]++;
			 }
			 for (auto it = mp.begin(); it != mp.end();it++)
			 {
				 ret += it->second *(it->second - 1);
			 }
		 }
		 return ret;
	 }
	 /*leetcode-434-Number of Segments in a String
	 */
	 int countSegments(string s)
	 {
		 int seg = 0;
		 int len = s.length();
		 for (int i = 0; i < len;)
		 {
			 while (i < len && s[i] == ' ')i++;//去掉空格
			 if (i>=len) break;			  
			 while (i < len && s[i] != ' ')i++;
			 seg++;			
		 }
		 return seg;
	 }
	 /*leetcode-452-Minimum Number of Arrows to Burst Balloons*/
	 int findMinArrowShots(vector<pair<int, int>>& points)
	 {
		 if (points.empty()) return 0;
		 sort(points.begin(), points.end());
		 int res = 1, end = points[0].second;
		 for (int i = 1; i < points.size(); ++i) {
			 if (points[i].first <= end) {
				 end = min(end, points[i].second);
			 }
			 else {
				 ++res;
				 end = points[i].second;
			 }
		 }
		 return res;
	 }
	 
	 /*leetcode-40-Combination Sum II*/
	 void combine(vector<vector<int>>& res, vector<int>& candidates, vector<int>& cantemp,int begin, int target)
	 {
		 if (target < 0) return;
		 
		 if ( target == 0)
		 {
			 res.push_back(cantemp);
			 return;
		 }
		 for (int i = begin; i < candidates.size();i++)
		 {
			 //if (candidates[i]>target)return;
			 if (i && candidates[i]==candidates[i-1]&& i>begin) continue;//避免重复元素
			 cantemp.push_back(candidates[i]);
			 combine(res, candidates, cantemp, i + 1, target - candidates[i]);
			 cantemp.pop_back();			 
		 }
	 }
	 vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
	 {		
		 vector<vector<int>> res;
		 if (candidates.size() == 0)return res;
		 sort(candidates.begin(), candidates.end());
		 vector<int> cantemp;
		 combine(res, candidates, cantemp, 0, target);
		 return res;
	 }
	 /*leetcode-131-Palindrome Partitioning*/
	 bool isPali(string s)
	 {
		 int len = s.length();		
		 for (int i = 0; i <= s.length()/2;i++)
		 {
			 if (s[i] != s[len - i - 1])return false;
		 }
		 return true;
	 }
	 void parti(vector<vector<string>>& res, vector<string>& pal,string s,int begin)
	 {
		 if (begin>=s.length())
		 {
			 res.push_back(pal);
			 return;
		 }
		 for (int i = begin; i < s.length();i++)
		 {
			 if (isPali(s.substr(begin,i-begin+1)))
			 {
				 pal.push_back(s.substr(begin, i - begin + 1));// pal.push_back(s.substr(i, i - begin + 1));这样不对
				 parti(res, pal, s, i + 1);
				 pal.pop_back();
			 }
		 }
	 }
	 vector<vector<string>> partition(string s)
	 {
		 vector<vector<string>> res;
		 if (s.empty())return res;
		 vector<string> pal;
		 parti(res, pal, s, 0);
		 return res;
	 }
	 /*132. Palindrome Partitioning II*/
	 int minCut(string s)
	 {
		 vector<vector<string>> res;
		 if (s.empty())return 0;
		 vector<string> pal;
		 parti(res, pal, s, 0);
		 int ret = INT_MAX;
		 for (int i = 0;i<res.size();i++)
		 {
			 ret = min(ret, (int)res[i].size());
		 }
		 return ret-1;
	 }
	 /*212. Word Search II	 */
	 vector<string> findWords(vector<vector<char>>& board, vector<string>& words)
	 {
		 vector<string> ret;

		 return ret;
	 }
	 /*leetcode-523-Continuous Subarray Sum*/
	 bool checkSubarraySum(vector<int>& nums, int k)
	 {
		 int len = nums.size();
		// vector<vector<int>> dp(len, vector<int>(len, 0));
		 long long cur = 0, pre = 0;
		 for (int i = 0; i < len;i++)
		 {
			 for (int j = i; j < len;j++)
			 {
				 if (j == i)cur = nums[i];
				 else
				 {
					 cur = pre + nums[j];
					 if (k != 0 && cur % k == 0)return true;
					 else if (k == 0 && cur == 0) return true;					  
				 }
				 pre = cur;
			 }
		 }
		 return false;
	 }
	 /*leetcode-494-Target Sum*/
	 int result;
	 int findTargetSumWays(vector<int>& nums, int S) {
		 dfs(0, 0, nums, S);
		 return result;
	 }
	 void dfs(int sum, int cnt, vector<int>& nums, int S) {
		 if (cnt == nums.size()) {
			 if (sum == S)
				 result++;
			 return;
		 }
		 dfs(sum + nums[cnt], cnt + 1, nums, S);
		 dfs(sum - nums[cnt], cnt + 1, nums, S);
	 }
	 /*leetcode-486-Predict the Winner*/
	 bool PredictTheWinner(vector<int>& nums)
	 {
		 int n = nums.size();
		 vector<vector<int>>dp(n, vector<int>(n));
		 vector<int>sum(n);
		 sum[0] = nums[0];
		 dp[0][0] = nums[0];
		 for (int i = 1; i < n;i++)
		 {
			 sum[i] += sum[i - 1] + nums[i];
			 dp[i][i] = nums[i];
		 }
		 for (int i = 1; i < n;i++)
		 {
			 for (int j = 0; i + j < n;j++)
			 {
				 dp[j][i + j] = max(sum[i+j]-sum[j]+nums[j] -dp[j+1][i+j],sum[i+j]-sum[j]+nums[j]-dp[j][i+j-1]);
			 }
		 }
		 return 2 * dp[0][n - 1] >= sum[n - 1];
	 }
	 /*leetcode-416-Partition Equal Subset Sum*/
	 void Par(bool& flag, vector<int>&nums, int target,int& temp,int begin)
	 {
		 if (temp == target)
		 {
			 flag = true;
			 return;
		 }
		 for (int i = begin; i < nums.size(); i++)
		 {
			 if (!flag)
			 {
				 temp += nums[i];
				 if(temp<=target)Par(flag, nums, target, temp, i + 1);
				 temp -= nums[i];
			 }			 
		 }
	 }
	 bool canPartition(vector<int>& nums)
	 {		 
		 int sum = 0;
		 if (nums.size() == 1)return false;
		 for (int n : nums)sum += n;
		 if (sum & 1)return false;
		 sum = sum >> 1;//除以2
		 vector<int> dp(sum + 1,0);//dp[i]代表和为i的可能输
		 dp[0] = 1;
		 for (int i = 0; i < nums.size();i++)
		 {
			 for (int j = sum; j >= i;j--)
			 {
				 dp[j] = dp[j] || dp[j - nums[i]];
			 }
		 }
		 return dp[sum];
	 }
	 /*leetcode-474-Ones and Zeroes*/
	 int findMaxForm(vector<string>& strs, int m, int n)
	 {
		 vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
		 int ones , zeros ;

		 for (string str : strs)
		 {
			 ones = 0, zeros = 0;
			 for (char ch : str)
			 {
				 if (ch == '0')zeros++;
				 else if (ch == '1')ones++;
			 }

			 for (int i = m; i >= zeros;i--)
			 {
				 for (int j = n; j >= ones;j--)
				 {
					 dp[i][j] = max(dp[i][j],dp[i-zeros][j-ones]+1);
				 }
			 }
		 }
		 return dp[m][n];
	 }
	 /*leetcode-357-Count Numbers with Unique Digits*/
	 int countNumbersWithUniqueDigits(int n)
	 {   
		 if (n == 0)return 1;
		 if (n == 1)return 10;
		 vector<int>dp(n+1,9);
		 n = min(n,10);
		 int cnt = 10;
		 for (int i = 2; i <= n;i++)
		 {
			 int j = 11 - i;
			 dp[i] = dp[i - 1] * j;
			 cnt += dp[i];
		 }
		 return cnt;
	 }
	 /*leetcode-343-Integer Break*/
	 int integerBreak(int n)
	 {
		 if (n == 2)return 1;
		 if (n == 3)return 2;
		 if (n == 4)return 4;
		 if (n == 5)return 6;
		 if (n == 6)return 9;
		 return 3 * integerBreak(n - 3);
		 
	 }
	 /*leetcode-392-Is Subsequence*/
	 bool isSubsequence(string s, string t)
	 {
		 int  lens = s.length(), lent = t.length(), indexS = 0, indexT = 0;
		 if (lens == 0)return true;
		 while (indexT < lent)
		 {
			 if (t[indexT]==s[indexS])
			 {
				 indexS++;
				 if (indexS == lens)return true;
			 }
			 indexT++;
		 }
		 return false;
	 }
	 /*5个数分成2个一组3个一组*/
	 void divide(vector<vector<int>>&ret2, vector<vector<int>>&ret3,vector<bool>&index, vector<int>&temp, vector<int>&nums, int begin)
	 {
		 if (temp.size() == 2)
		 {
			 ret2.push_back(temp);
			 vector<int> temp3;
			 for (int i = 0; i < index.size();i++)
			 {
				 if (index[i] == false)temp3.push_back(nums[i]);
			 }
			 ret3.push_back(temp3);
			 return;
		 }
		 for (int i = begin; i < nums.size();i++)
		 {
			 temp.push_back(nums[i]);
			 index[i]=true;
			 divide(ret2,ret3,index,temp, nums, i + 1);
			 temp.pop_back();
			 index[i] = false;
		 }
	 }

	 /*leetcode-216-Combination Sum III*/
	 void combinationSum3(vector<vector<int>>&ret, vector<int>&comb, int k, int n,int &sum, int begin)
	 {
		 if (sum > n)return;
		 if (comb.size() == k && sum != n)return;		 
		 else if (comb.size() == k && sum == n) 
		 {
			 ret.push_back(comb);
			 return;
		 }
		 for (int i = begin; i <= 9;i++)
		 {
			 comb.push_back(i);
			 sum += i;
			 combinationSum3(ret, comb, k, n, sum, i + 1);
			 sum -= i;
			 comb.pop_back();
		 }
	 }
	 vector<vector<int>> combinationSum3(int k, int n)
	 {
		 vector<vector<int>> ret;
		 vector<int> comb;
		 int sum = 0;
		 combinationSum3(ret, comb, k, n, sum, 1);
		 return ret;
	 }
	 /*leetcode-377-Combination Sum IV*/
	 int combinationSum4(vector<int>& nums, int target)
	 {
		 sort(nums.begin(), nums.end());
		 vector<int>dp(target+1,0);
		 dp[0] = 1;
		 for (int i = 1; i <= target;i++)
		 {
			 for (int a : nums)
			 {
				 if (i<a)break;//a排序后只能越来越大 i>=a才有意义 否则提前结束内部循环
				 dp[i] += dp[i - a];
			 }
		 }
		 return dp[target];
	 }
	 /*leetcode-322-Coin Change*/
	 int coinChange(vector<int>& coins, int amount)
	 {

	 }
	 /*leetcode-312-Burst Balloons*/
	 int maxCoins(vector<int>& nums)
	 {
		 int n = nums.size();
		 nums.insert(nums.end(), 1);
		 nums.insert(nums.begin(), 1);

		 vector<vector<int>>dp(n+2,vector<int>(n+2,0));
		 for (int len = 1; len <= n;len++)
		 {
			 for (int left = 1; left <= n - len + 1;left++)
			 {
				 int right = left + len - 1;
				 for (int k = left; k <= right;k++)
				 {
					 dp[left][right] = max(dp[left][right], dp[left][k-1]+dp[k+1][right]+ nums[left-1]*nums[k]*nums[right+1]);
				 }
			 }
		 }
		 return dp[1][n];
	 }
	 /*leetcode-300-Longest Increasing Subsequence*/
	 int lengthOfLIS(vector<int>& nums)
	 {
		 int n = nums.size(),ret = 0;
		 if (n == 0) return 0;
		 vector<int>dp(n, 1);
		 for (int i = 0; i < n;i++)
		 {
			 for (int j = 0; j < i; j++)
			 {
				 if(nums[i]>nums[j])dp[i] = max(dp[i], dp[j] + 1);				 
			 }
			 ret = max(ret, dp[i]);
		 }
		 return ret;		 
	 }

	 /*leetcode-279-Perfect Squares*/
	 int numSquares(int n)
	 {
		 vector<int>dp(n + 1);
		 for (int i = 0; i <= n;i++)
		 {
			 dp[i] = i;
			 for (int j = 1; j*j <= i;j++)
			 {
				 dp[i] = min(dp[i], dp[i - j*j] + 1);
			 }
		 }
		 return dp[n];
	 }

	 /*leetcode-376-Wiggle Subsequence*/
	 int wiggleMaxLength(vector<int>& nums)
	 {
		 int n = nums.size(),maxup=0,maxdown =0;
		 vector<int>up(n + 1,0);
		 vector<int>down(n + 1, 0);
		 for (int i = 0; i <n;i++)
		 {
			 up[i] = 1;
			 down[i] = 1;
			 for (int j = 0; j < i;j++)
			 {
				 if (nums[i]>nums[j])
				 {
					 up[i] = max(up[i], down[j] + 1);
				 }
				 if (nums[i]<nums[j])
				 {
					 down[i] = max(down[i], up[j] + 1);
				 }
			 }
			// maxup = max(maxup, up[i]);
			// maxdown = max(maxdown, down[i]);
		 }
		 return max(up.back(), down.back());
	 }
	 /*leetcode-406-Queue Reconstruction by Height*/
	 vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people)
	 {
		 sort(people.begin(), people.end(), [](const pair<int, int>& a, const pair<int, int>& b){
			 return a.first > b.first || (a.first == b.first && a.second < b.second);
		 });
		 vector<pair<int, int>> ret;
		 for (auto a : people)
		 {
			 ret.insert(ret.begin() + a.second, a);
		 }
		 return ret;
	 }
	 
	 /*leetcode-455-Assign Cookies*/
	 int findContentChildren(vector<int>& g, vector<int>& s)
	 {
		 int people = g.size(),cookie = s.size();
		 sort(g.begin(), g.end());
		 sort(s.begin(), s.end());
		 int content = 0;
		 int curindex = 0;//代表饼干的索引
		 for (int i = 0; i < people;i++)
		 {
			 for (int j = curindex; j < cookie; j++)
			 {
				 if (s[j]>=g[i])
				 {
					 content++;
					 curindex = j + 1;//j已经被分出去了 得从下一个开始
					 break;
				 }
			 }
		 }
		 return content;
	 }
	 /*leetcode-349-Intersection of Two Arrays*/
	 vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
	 {
		 set<int>s(nums1.begin(), nums1.end()), ret;
		 for (auto a:nums2)
		 {
			 if (s.count(a))ret.insert(a);
		 }
		 return vector<int>(ret.begin(), ret.end());
	 }
	 
	 /*leetcode-635-Design Log Storage System*/
	 map<string, vector<int>>mp;
	 map<string, int>idmap;
	 map<string, int>mapping;
	 Solution()
	 {
		 mapping["Year"] = 0;
		 mapping["Month"] = 1;
		 mapping["Day"] = 2;
		 mapping["Hour"] = 3;
		 mapping["Minute"] = 4;
		 mapping["Second"] = 5;
	 }
	 vector<int> convert(string s)
	 {
		 for (int i = 0; i < s.size();i++)if (s[i] == ':')s[i] = ' ';
		 stringstream ss(s);
		 int x;
		 vector<int>a;
		 while (ss >> x)a.push_back(x);
		 return a;		 
	 }
	
	 void put(int id, string timestamp) 
	 {
		 idmap[timestamp] = id;
		 mp[timestamp] = convert(timestamp);
	 }
	 vector<int> retrieve(string s, string e, string gra)
	 {
		 vector<int>result;
		 vector<int>from = convert(s), to = convert(e);
		 for (int i = mapping[gra] + 1; i < 6;i++)
		 {
			 from[i] = 0;
			 to[i] = 99;
		 }
		 for (auto &it : mp)
		 {
			 if (it.second >= from && it.second <= to)
			 {
				 result.push_back(idmap[it.first]);
			 }
		 }
		 return result;
	 }
	 /*leetcode-453-Minimum Moves to Equal Array Elements*/
	 int minMoves(vector<int>& nums)
	 {
		 int ret = 0;
		 int smallest = *min_element(nums.begin(), nums.end());
		 for (auto a:nums)
		 {
			 ret += (a - smallest);
		 }
		 return ret;
	 }
	 /*leetcode-383-Ransom Note*/
	 bool canConstruct(string ransomNote, string magazine)
	 {
		 map<char, int>mpmag;
		 for (auto ch : magazine)mpmag[ch]++;
		 for (auto ch : ransomNote)
		 {
			 mpmag[ch]--;
			 if (mpmag[ch] < 0)return false;			 
		 }
		 return true;		 
	 }
	 /*leetcode-404-Sum of Left Leaves*/
	 void tr(TreeNode* root, int& sum)
	 {
		 if (root == NULL)return;
		 if (root->left != NULL && root->left->left == NULL && root->left->right == NULL)sum += root->left->val;
		 tr(root->left, sum);
		 tr(root->right, sum);
	 }
	 int sumOfLeftLeaves(TreeNode* root)
	 {
		 if (root == NULL)return 0;
		 int sum = 0;
		 tr(root, sum);
		 return sum;
	 }

	 /*leetcode-171-Excel Sheet Column Number*/
	 int titleToNumber(string s)
	 {
		 int n = s.length();
		 int num = 0;
		 int cur = 0;
		 for (int i = n-1; i >=0;i--)
		 {
			 cur = (s[i] - 'A' + 1)*pow(26, n-1-i);
			 num+=cur;
			 cur = 0;
		 }

		 return num;
	 }
	 /*leetcode-168-Excel Sheet Column Title*/
	 string convertToTitle(int n)
	 {
		 string s;
		 bool flag = false;
		 while (n > 0)
		 {
			 if (n % 26 == 0)
			 {
				 s += 'Z';				
				 flag = true;
			 }
			 else  s += ('A' - 1 + n % 26);
			 n /= 26;
			 if (flag) n -= 1;
			 
		 }
		 reverse(s.begin(),s.end());
		 return s;
		 //return n == 0 ? "" : convertToTitle(n / 26) + (char) (--n % 26 + 'A');
	 }
	 /*leetcode-268-Missing Number*/
	 int missingNumber(vector<int>& nums)
	 {
		 int ret = nums.size();
		 for (int i = 0; i < nums.size();i++)
		 {
			 ret = ret ^ i ^ nums[i];
		 }
		 return ret;
	 }
	 
	 /*leetcode-415-Add Strings*/
	 string addStrings(string num1, string num2)
	 {
		 int n1 = num1.length()-1, n2 = num2.length()-1;
		 string ret="";
		 int digit = 0;
		 int carry = 0;
		 int sum = 0;
		 while (n1 >= 0 && n2 >= 0)
		 {
			 sum = carry + num1[n1--] + num2[n2--] - '0' - '0';
			 digit = sum %10;
			 carry = (sum >= 10) ? 1 : 0;
			 ret += (digit+'0');
		 }
		
		 while (n1 >= 0)
		 {
			 sum = carry + num1[n1--] - '0';
			 digit = sum % 10;
			 carry = (sum >= 10) ? 1 : 0;
			 ret += (digit + '0');
		 }		
		 
		 while (n2 >= 0)
		 {
			 sum = carry + num2[n2--] - '0';
			 digit = sum % 10;
			 carry = (sum >= 10) ? 1 : 0;
			 ret += (digit + '0');
		 }		
		 
		if (carry) ret += '1';
		 reverse(ret.begin(), ret.end());
		 return ret;		 
	 }
	 /*leetcode-451-Sort Characters By Frequency*/
	 string frequencySort(string str)
	 {
		 vector<int>mp(256,0);
		 for (auto c:str)
		 {
			 mp[c]++;
		 }
		 string s="";
		 int most = 0;
		 int index = 0;
		 for (int i = 0; i < 256;i++)
		 {
			 if (mp[i] == 0)continue;

			 for (int j = 0; j < 256;j++)
			 {
				 if (mp[j] == 0)continue;
				 if (most < mp[j])
				 {
					 most = mp[j];
					 index = j;
				 }
			 }
			 s.append(most, char(index));
			 /* for (int i = 0; i < most;i++)
			  {
			  s.push_back(char(index));
			  }*/
			 mp[index] = 0;
			 most = 0;
		 }
		 return s;
	 }
	 
	 /*leetcode-368-Largest Divisible Subset*/
	
	 vector<int> largestDivisibleSubset(vector<int>& nums)
	 {

	 }
	 /*leetcode-264-Ugly Number II*/
	 int nthUglyNumber(int n)
	 {
		 vector<int>ret(n, 1);
		 int index2 = 0, index3 = 0, index5 = 0;
		 for (int i = 1; i < n; i++)
		 {
			 ret[i] = min(ret[index2]*2,min(ret[index3]*3,ret[index5]*5));
			 if (ret[i] == ret[index2] * 2)index2++;
			 if (ret[i] == ret[index3] * 3)index3++;
			 if (ret[i] == ret[index5] * 5)index5++;
		 }
		 return ret[n - 1];
	 }

	 int findSubstringInWraproundString(string p)
	 {
		 int n = p.length();
		 vector<vector<int>> dp(n+1,vector<int>(n+1,0));

		

		 return dp[1][n];
	 }
	 /*leetcode-350-Intersection of Two Arrays II*/
	 vector<int> intersect(vector<int>& nums1, vector<int>& nums2)
	 {
		 vector<int>ret;
		 map<int, int>mp;
		 for (auto a : nums1)mp[a]++;
		 for (auto a:nums2)
		 {
			 if (mp[a] > 0)
			 {
				 mp[a]--;
				 ret.push_back(a);
			 }
		 }
		 return ret;
	 }
	 /*leetcode-405-Convert a Number to Hexadecimal*/
	 string toHex(int num)
	 {
		 string s;
		 int digital;
		 char c[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
		 if (num == 0)return "0";
		 int count = 0;
		 while (num > 0 && count++<8)
		 {
			 digital = num & 0xf;
			 s  = c[digital] + s;
			 num >>4;
		 }
		 return s;
	 }

	 /*leetcode-89-Gray Code*/
	 vector<int> grayCode(int n)
	 {
		 vector<int>ret;
		 ret.push_back(0);
		 for (int i = 0; i < n;i++)
		 {
			 int size = ret.size();
			 for (int j = size-1; j >=0;j--)
			 {
				ret.push_back(ret[j] | 1 << i);
			 }
		 }
		 return ret;
	 }

	 /*leetcode-419-Battleships in a Board*/
	 void dfsbattle(vector<vector<char>>& board,vector<vector<bool>>& visited,int i,int j)
	 {
		 int m = board.size(), n = board[0].size();
		 if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || board[i][j] == '.')return;
		 visited[i][j] = true;
		 dfsbattle(board, visited, i + 1, j);
		 dfsbattle(board, visited, i - 1, j);
		 dfsbattle(board, visited, i , j+1);
		 dfsbattle(board, visited, i , j-1);
	 }
	 int countBattleships(vector<vector<char>>& board)
	 {
		 if (board.empty())return 0;
		 int m = board.size(), n = board[0].size();
		 vector<vector<bool>>visited(m, vector<bool>(n, false));
		 int ret = 0;
		 for (int i = 0; i < m;i++)
		 {
			 for (int j = 0; j < n;j++)
			 {
				 if (board[i][j]=='X'&& !visited[i][j])
				 {
					 dfsbattle(board, visited, i,j);
					 ret++;
				 }
			 }
		 }
		 return ret;
	 }
	 /*leetcode-200-Number of Islands*/
	 void dfsisland(vector<vector<char>>& grid, vector<vector<bool>>& visited,int i,int j)
	 {
		 int m = grid.size(), n = grid[0].size();
		 if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || grid[i][j] == '0')return;
		 visited[i][j] = true;
		 dfsisland(grid, visited, i + 1, j);
		 dfsisland(grid, visited, i - 1, j);
		 dfsisland(grid, visited, i, j + 1);
		 dfsisland(grid, visited, i, j - 1);
	 }
	 int numIslands(vector<vector<char>>& grid)
	 {
		 if (grid.empty())return 0;
		 int m = grid.size(), n = grid[0].size();
		 vector<vector<bool>>visited(m, vector<bool>(n, false));
		 int ret = 0;
		 for (int i = 0; i < m;i++)
		 {
			 for (int j = 0; j < n;j++)
			 {
				 if (grid[i][j] == '1' && !visited[i][j])
				 {
					 dfsisland(grid, visited,i,j);
					 ret++;
				 }
			 }
		 }
		 return ret;
	 }
	 /*leetcode-347-Top K Frequent Elements*/
	 vector<int> topKFrequent(vector<int>& nums, int k)
	 {
		 if (nums.empty())return{};
		 map<int, int>mp;
		 vector<vector<int>>bucket(nums.size() + 1);
		 for (auto a:nums)mp[a]++;
		 for (auto it : mp)bucket[it.second].push_back(it.first);
		 vector<int>ret;
		 for (int i = nums.size(); i >= 0 && k>0;i--)
		 {
			 if (!bucket[i].empty())
			 {
				 for (int j = 0; j < bucket[i].size() && k>0; j++)
				 {
					 ret.push_back(bucket[i][j]);
					 k--;
				 }
			 }
		 }
		  
		 return ret;
	 }

	 /*leetcode-609-Find Duplicate File in System*/
	 
	 void parse(string orign,string& fileName,string& content)
	 {
		 int index = orign.find_first_of('(');
		 fileName = orign.substr(0, index);
		 content = orign.substr(index + 1,orign.length()-index-2);
	 }
	void getFullPath(string p,vector<string>&path,vector<string>&conVec)
	 {
		 stringstream ss(p);
		 string pathPrefix;
		 ss >> pathPrefix;
		 string file;
		 while (ss >> file)
		 {
			 string fileName, content;
			 parse(file,fileName, content);
			 path.push_back(pathPrefix + "/"+fileName);
			 conVec.push_back(content);
		 }
	 }
	vector<vector<string>> findDuplicate(vector<string>& paths)
	 {		
		 vector<string>pathVec, conVec;
		 for (auto p:paths)
		 {
			 getFullPath(p,pathVec,conVec);			 
		 }
		 map<string, set<string>>mp2;
		 for (int i = 0; i < pathVec.size();i++)
		 {
			 mp2[conVec[i]].insert(pathVec[i]);
			// cout << pathVec[i] << " " << conVec[i] << endl;
		 }
		 vector<vector<string>>ret;
		 for (auto it :mp2)
		 {
			 if (it.second.size() == 1)continue;
			 vector<string> temp(it.second.begin(),it.second.end());
			 ret.push_back(temp);
		 }
		 return ret;
	 }
	
	/*leetcode-525-Contiguous Array*/
	int findMaxLength(vector<int>& nums)
	{
		for (auto& a:nums) if (a == 0)a = -1;
		map<int, int>mp;
		mp[0] = -1;
		int sum = 0,ret =0;
		for (int i = 0; i < nums.size();i++)
		{
			sum += nums[i];
			if (mp.count(sum))ret = max(ret, i - mp[sum]);
			else mp[sum] = i;
		}
		return ret;		 
	}
	/*leetcode-643-Maximum Average Subarray I*/
	double findMaxAverage(vector<int>& nums, int k)
	{
		int s = accumulate(nums.begin(), nums.begin() + k, 0), mx = s;
		for (int i = k; i < nums.size(); i++) {
			s += nums[i] - nums[i - k];
			mx = max(mx, s);
		}
		return double(mx) / k;
	}

	/*leetcode-644-Maximum Average Subarray II*/
	double findMaxAverage1(vector<int>& nums, int k)
	{
		int n = nums.size();
		vector<double>sum(n + 1,0);
		for (int i = 0; i < n; i++)sum[i + 1] = sum[i] + nums[i];
		double ret = -1e4;
		for (int i = 0; i <= n - k;i++)
		{
			for (int window = k; window + i <= n;window++)
			{
				//ret = max(ret,(sum[i+window]-sum[i])/window);//超时。。。
				if (ret*window < (sum[i + window] - sum[i]))ret = (sum[i + window] - sum[i])/window;
			}
		}
		return ret;
	}
	
	/*leetcode-636-Exclusive Time of Functions*/
	vector<int> exclusiveTime(int n, vector<string>& logs) 
	{
		vector<int>ret(n), sta;
		int id, time, last;
		for (auto log:logs)
		{
			for (auto& c : log) if (c == ':')c = ' ';
			stringstream ss(log);
			
			char s[9];
			ss >> id >> s >> time;

			//sscanf(log.c_str(), "%d:%[^:]:%d", &id, s, &time);
			//cout << id << " " << s << " " << time<<endl;
			if (s[0]=='s')
			{
				if (sta.size() > 0)ret[sta.back()] += time - last;
				sta.push_back(id);				
			}
			else
			{
				ret[sta.back()] += ++time - last;
				sta.pop_back();
			}
			last = time;
		}
		return ret;
	}
	/*leetcode-645-Set Mismatch*/
	vector<int> findErrorNums(vector<int>& nums)
	{
		vector<int> ret;
		vector<bool>flag(nums.size()+1,false);

		for (int i = 0; i < nums.size();i++)
		{
			 if (flag[nums[i]] == true)ret.push_back(nums[i]);			 
			 flag[nums[i]] = true;			 	 
		}
		for (int i = 1; i < flag.size(); i++)
		{
			if (flag[i] == false)ret.push_back(i);			 
		}
		return ret;
	}
	/*leetcode-646-Maximum Length of Pair Chain*/	 
	int findLongestChain(vector<vector<int>>& pairs)
	{
		sort(pairs.begin(), pairs.end(), [](const vector<int>&a, const vector<int>&b){return a[0] < b[0]; });
		 
		vector<int> dp(pairs.size(), 1);
		for (int i = 1; i < pairs.size(); i++)
		{
			for (int j = 0; j<i;j++)
			{
				if (pairs[i][0]>pairs[j][1])
				{
					dp[i] = max(dp[i],dp[j]+1);					
				}
			}
			
		}
		return *max_element(dp.begin(), dp.end());
	}
	/*leetcode-647-Palindromic Substrings*/
	void ifsub(string& s,int l,int r,int& cnt)
	{
		while (l >= 0 && r < s.length() && s[l] == s[r])
		{
			cnt++;
			l--;
			r++;
		}
	}
	int countSubstrings(string s)
	{
		if (s.length() == 0)return 0;
		int cnt = 0;
		for (int i = 0; i < s.length();i++)
		{
			ifsub(s, i, i, cnt);
			ifsub(s, i, i+1, cnt);
		}
		return cnt;
	}
	/*leetcode-648-Replace Words*/
	string replaceWords(vector<string>& dict, string sentence)
	{
		map<string, string>mpdic;
		for (auto s : dict)mpdic[s] = s;
		vector<string>word;
		stringstream ss(sentence);
		string tmp;
		while (ss >> tmp)word.push_back(tmp);
		for (auto &str : word)
		{
			for (int i = 1; i < str.length();i++)
			{
				if (mpdic.count(str.substr(0,i)))
				{
					str = str.substr(0, i);
					break;
				}
			}
		}
		string ret = word[0];
		for (int i = 1; i < word.size();i++)ret += " " + word[i];
		return ret;		
	}
	/*leetcode-213-House Robber II*/
	int rob2(vector<int>& nums,int start,int end)
	{
		int n = nums.size();
		vector<int>dp(n);
		if (start == end)return nums[start];
		if (start + 1 == end)return max(nums[start], nums[end]);		 

		dp[start] = nums[start];
		dp[start + 1] = max(nums[start], nums[start+1]);

		for (int i = start+2; i <= end;i++)
		{
			dp[i] = max(dp[i-2]+nums[i],dp[i-1]);
		}

		return dp[end];
	}
	int rob2(vector<int>& nums)
	{
		int n = nums.size();
		if (nums.empty())return 0;
		if (n == 1)return nums[0];
		if (n == 2)return max(nums[0],nums[1]);
		if (n == 3)return max(nums[0], max(nums[1],nums[2]));

		//int r1 = nums[0] + rob2(nums,2,n-2);
		//int r2 = nums[1] + rob2(nums, 3, n - 1);//不对
		
		int r1 = rob2(nums, 1, n - 1);
		int r2 = rob2(nums, 0, n - 2); 
		return max(r1, r2);
	}
};

int main()
{
	Solution sl;

	vector<int>test, test1;

	test.push_back(0);
	test.push_back(4);
	test.push_back(0);
	test.push_back(3);
	test.push_back(2);

	vector<vector<int>>mat2;
	vector<vector<int>>mat3;
	vector<string> logs = {"0:start:0", "1:start:2", "1:end:5", "0:end:6"};
	
  test1 = sl.exclusiveTime(2,logs);	 
	 
	
		
	getchar();
	return 0;
}
