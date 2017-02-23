#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;
struct TreeNode{
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {
	}
};
class Solution 
{
public:
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

	
};

int main()
{
	Solution sl;
	vector<int>test;
	test.push_back(2);
	test.push_back(7);
	test.push_back(11);
	test.push_back(15);
	vector<string> str;
	str.push_back("0");
	str.push_back("3");
	str.push_back("/");
	/*str.push_back("3");
	str.push_back("*");	*/

	cout << sl.evalRPN(str) << endl;
	getchar();
	return 0;
}
