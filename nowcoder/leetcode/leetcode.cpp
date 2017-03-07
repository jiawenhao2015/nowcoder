#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
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

	void dfs(vector<vector<int>>& result, vector<int>& temp, vector<int>& nums, int index)
	{
		result.push_back(temp);
		for (int i = index; i < nums.size();i++)
		{
			temp.push_back(nums[i]);//
			dfs(result,temp,nums,i+1);
			temp.erase(temp.end()-1);
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
};

int main()
{
	Solution sl;
	vector<int>test,test1,test2;
	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test1.push_back(0);
	test1.push_back(1);
	test1.push_back(0);
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
	mat.push_back(test);
	mat.push_back(test1);
	mat.push_back(test2);
	 sl.subsets(test);
	  
	while (resultNode != NULL)
	{
		//cout << resultNode->val << " ";
		resultNode = resultNode->next;
	}
		
	getchar();
	return 0;
}
