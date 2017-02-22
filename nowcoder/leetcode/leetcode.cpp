#include <iostream>
#include <algorithm>
#include <vector>
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
	/*1. Two Sum
	Given an array of integers, return indices of the two numbers such that they add up to a specific target.
	You may assume that each input would have exactly one solution, and you may not use the same element twice.
	Example:
	Given nums = [2, 7, 11, 15], target = 9,
	Because nums[0] + nums[1] = 2 + 7 = 9,
	return [0, 1].*/
	vector<int> twoSum(vector<int>& nums, int target)
	{
		if (nums.size() == 0) return nums;
		vector<int>result;
		//sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size(); i++)
		{
			for (int j = i + 1; j < nums.size();j++)
			{
				if (nums[i]+nums[j] == target)
				{
					result.push_back(i);
					result.push_back(j);
					return result;
				}
			}
		}
		return result;
	}
	/*Given a binary tree, find its minimum depth.The minimum depth is the number of nodes
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
	test.push_back(3);
	test.push_back(2);
	test.push_back(4);

	cout << sl.twoSum(test, 6)[0] << " "<<sl.twoSum(test, 6)[1] << endl;
	getchar();
	return 0;
}
