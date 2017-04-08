#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <map>

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
		 sort(nums.begin(),nums.end(),greater<int>());
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
	int removeDuplicates(vector<int>& nums)
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

	ListNode* deleteDuplicates(ListNode* head)
	{
		if (head == NULL || head->next == NULL) return head;
		ListNode* p = head->next;
		if (p->val != head->val) {
			head->next = deleteDuplicates(p);
			return head;
		}
		else {
			while (p != NULL && p->val == head->val) p = p->next;
			return deleteDuplicates(p);
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
};

int main()
{
	Solution sl;
	vector<int>test,test1,test2;
	test.push_back(-1);
	test.push_back(0);
	test.push_back(1);
	test.push_back(2);
	test.push_back(-1);
	test.push_back(-4);
	test2.push_back(0);
	test2.push_back(0);
	test2.push_back(0);
	
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
	 
	vector<vector<int>>mat;
	/*mat.push_back(test);
	mat.push_back(test1);
	mat.push_back(test2);*/
	test = sl.getRow(3);
	
	for (int i = 0; i < test.size();i++)
	{
		cout << test[i] << " ";
	}
	for (int i = 0; i < mat.size();i++)
	{
		for (int j = 0; j < mat[i].size(); j++)
		{
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
	while (resultNode != NULL)
	{
		//cout << resultNode->val << " ";
		resultNode = resultNode->next;
	}
		
	getchar();
	return 0;
}
