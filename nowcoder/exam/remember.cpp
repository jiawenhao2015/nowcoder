
auto 关键字 用于 iterator等处 方便
getline()读取一行字符串
string str;  包含#inclue<string>即可
getline(cin, str);
getline(cin, str,':');//mao hao fen ge fu



/********	----------------------------------------------------------------------------DFS BFS******
经典题目：
[LeetCode]419 --- Battleships in a Board 平板上的战船   
 

Given an 2D board, count how many different battleships are in it. The battleships are represented with 'X's, 
empty slots are represented with '.'s. You may assume the following rules:

You receive a valid board, made of only battleships or empty slots.
Battleships can only be placed horizontally or vertically. In other words, 
they can only be made of the shape 1xN (1 row, N columns) or Nx1 (N rows, 1 column), where N can be of any size.
At least one horizontal or vertical cell separates between two battleships - there are no adjacent battleships.
Example:

X..X
...X
...X
In the above board there are 2 battleships.

Invalid Example:

...X
XXXX
...X
This is not a valid board - as battleships will always have a cell separating between them.

Your algorithm should not modify the value of the board.

 

这道题好像之前在地里面见过，忘了是哪家公司的面试题了，现在被LeetCode收录了，感觉现在LeetCode更新越来越快了，感觉要成为第一大题库了，
赞一个👍。这道题让我们求战舰的个数，所谓的战舰就是只能是一行或者一列，不能有拐弯
。这道题降低了难度的做法是限定了不会有相邻的两个战舰的存在，有了这一点限制，那么我们只需要遍历一次二维数组就行了
，只要找出战舰的起始点。所谓的战舰起始点，就是为X的点，而且该点的上方和左边的点不能为X，
所以我们只要找出所有满足这个条件的点即可，参见代码如下：

 

解法一：
*/
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return 0;
        int res = 0, m = board.size(), n = board[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == '.' || (i > 0 && board[i - 1][j] == 'X') || (j > 0 && board[i][j - 1] == 'X')) continue;
                ++res;
            }
        }
        return res;
    }
};
 

/*
然而我自己在做的时候并没有注意到题目中限制了两艘战舰不能相邻的情况，
我加上了处理方法，首先我算出来了所有连续X的区域的个数，
方法跟之前那道Number of Islands一样，稍有不同的是，
我分别记录下来每一个连续区域的i和j，把所有的点的横纵坐标分别或了起来，
这样做的好处是如果是在一条直线上的战舰，那么所有点肯定是要么横坐标都相同，
要么纵坐标都相同，所以最后我们检测如果横纵坐标的累积或都跟之前的i和j不同的话，
那么一定不是题目中定义的战舰，那么我们就不累加结果res，参见代码如下：
 

解法二：
*/
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return 0;
        int m = board.size(), n = board[0].size(), res = 0;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'X' && !visited[i][j]) {
                    int vertical = 0, horizontal = 0;
                    dfs(board, visited, vertical, horizontal, i, j);
                    if (vertical == i || horizontal == j) ++res;
                }
            }
        }
        return res;
    }
    void dfs(vector<vector<char>>& board, vector<vector<bool>>& visited, int& vertical, int& horizontal, int i, int j) {
        int m = board.size(), n = board[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || board[i][j] == '.') return;
        vertical |= i; horizontal |= j;
        visited[i][j] = true;
        dfs(board, visited, vertical, horizontal, i - 1, j);
        dfs(board, visited, vertical, horizontal, i + 1, j);
        dfs(board, visited, vertical, horizontal, i, j - 1);
        dfs(board, visited, vertical, horizontal, i, j + 1);
    }
};

/*
既然DFS能实现，那么BFS就应该没啥问题，这里完全按题目的要求，默认两个战舰不会相邻，并没有添加解法二中的过滤条件，参见代码如下：

 

解法三：
*/
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return 0;
        int res = 0, m = board.size(), n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<vector<int>> dirs{{0,-1},{-1,0},{0,1},{1,0}};
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'X' && !visited[i][j]) {
                    ++res;
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    while (!q.empty()) {
                        auto t = q.front(); q.pop();
                        visited[t.first][t.second] = true;
                        for (auto dir : dirs) {
                            int x = t.first + dir[0], y = t.second + dir[1];
                            if (x < 0 || x >= m || y < 0 || y >= n || visited[x][y] || board[x][y] == '.') continue;
                            q.push({x, y});
                        }
                    }
                }
            }
        }
        return res;
    }
};
/*leetcode-200-Number of Islands
Given a 2d grid map of '1's (land) and '0's (water), 
count the number of islands. An island is surrounded by water
 and is formed by connecting adjacent lands horizontally or vertically.
 You may assume all four edges of the grid are all surrounded by water.

Example 1:

11110
11010
11000
00000
Answer: 1

Example 2:

11000
11000
00100
00011
Answer: 3
*/ 

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
/*-------------------------------------------------------------------------------------HASH  桶排序

Given a non-empty array of integers, return the k most frequent elements.

For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].

Note: 

You may assume k is always valid, 1 ? k ? number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
思路：

首先用map统计数字出现的次数，然后再将出现的次数作为关键词，使用桶排序，然后从后遍历，返回关键字即可。
后来又看到有人用优先队列存储，感觉更方便了。*/
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
	 
	 vector<int> topKFrequent(vector<int>& nums, int k)
	 {
        unordered_map<int,int> map;
        for(int num : nums){
            map[num]++;
        }
        
        vector<int> res;
        // pair<first, second>: first is frequency,  second is number
        priority_queue<pair<int,int>> pq; 
        for(auto it = map.begin(); it != map.end(); it++){
            pq.push(make_pair(it->second, it->first));
            if(pq.size() > (int)map.size() - k){
                res.push_back(pq.top().second);
                pq.pop();
            }
        }
        return res;
    }
	
	
	/*  字符串  stringstream 的应用 以及查找字符的find函数
	
A group of duplicate files consists of at least two files that have exactly the same content.

A single directory info string in the input list has the following format:

"root/d1/d2/.../dm f1.txt(f1_content) f2.txt(f2_content) ... fn.txt(fn_content)"

It means there are n files (f1.txt, f2.txt ... fn.txt with content f1_content, f2_content ... fn_content, respectively) in directory root/d1/d2/.../dm. Note that n >= 1 and m >= 0. If m = 0, it means the directory is just the root directory.

The output is a list of group of duplicate file paths. For each group, it contains all the file paths of the files that have the same content. A file path is a string that has the following format:

"directory_path/file_name.txt"

Example 1:
Input:
["root/a 1.txt(abcd) 2.txt(efgh)", "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)", "root 4.txt(efgh)"]
Output:  
[["root/a/2.txt","root/c/d/4.txt","root/4.txt"],["root/a/1.txt","root/c/3.txt"]]*/
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
	vector<vector<string>> findDuplicate(vector<string>& paths)
	{
    unordered_map<string, vector<string>> files;
    vector<vector<string>> result;

    for (auto path : paths) {
	    stringstream ss(path);
	    string root;
	    string s;
	    getline(ss, root, ' ');
	    while (getline(ss, s, ' ')) {
		    string fileName = root + '/' + s.substr(0, s.find('('));
		    string fileContent = s.substr(s.find('(') + 1, s.find(')') - s.find('(') - 1);
		    files[fileContent].push_back(fileName);
	    }
    }

    for (auto file : files) {
	    if (file.second.size() > 1)
		    result.push_back(file.second);
    }

    return result;
}

/*
leetcode-644-Maximum Average Subarray II
Given an array consisting of n integers, find the contiguous subarray whose length is greater than or equal to k that has the maximum average value. And you need to output the maximum average value.

Example 1:
Input: [1,12,-5,-6,50,3], k = 4
Output: 12.75
Explanation:
when length is 5, maximum average value is 10.8,
when length is 6, maximum average value is 9.16667.
Thus return 12.75.
Note:
1 <= k <= n <= 10,000.
Elements of the given array will be in range [-10,000, 10,000].
The answer with the calculation error less than 10-5 will be accepted.

用一个sum去记录从开始到当前元素之前的所有元素的和，即sum[i]记录下标从0到i-1的所有元素的和。

这样区间[i,j]的和就可以表示为sum[j+1] - sum[i].
*/

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

/*[leetcode-646-Maximum Length of Pair Chain]

You are given n pairs of numbers. In every pair, the first number is always smaller than the second number.

Now, we define a pair (c, d) can follow another pair (a, b) if and only if b < c. Chain of pairs can be formed in this fashion.

Given a set of pairs, find the length longest chain which can be formed. You needn't use up all the given pairs. You can select pairs in any order.

Example 1:

Input: [[1,2], [2,3], [3,4]]
Output: 2
Explanation: The longest chain is [1,2] -> [3,4]
 

Note:

The number of given pairs will be in the range [1, 1000].
思路：
动态规划。递推公式是 dp[i] = max(dp[i],dp[j]+1);其中0=<j<i;
*/
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
/*
[leetcode-650-2 Keys Keyboard]

Initially on a notepad only one character 'A' is present. You can perform two operations on this notepad for each step:

Copy All: You can copy all the characters present on the notepad (partial copy is not allowed).
Paste: You can paste the characters which are copied last time.
 

Given a number n. You have to get exactly n 'A' on the notepad by performing the minimum number of steps permitted. Output the minimum number of steps to get n 'A'.

Example 1:

Input: 3
Output: 3
Explanation:
Intitally, we have one character 'A'.
In step 1, we use Copy All operation.
In step 2, we use Paste operation to get 'AA'.
In step 3, we use Paste operation to get 'AAA'.
 

Note:

The n will be in the range [1, 1000].
思路：

如果知道了i的结果，那么2×i的步骤只需在i的结果上加上2即可，一次复制，一次粘贴。同理3×i的结果为一次复制，两次粘贴，i的结果加上3。

*/
int minSteps(int n)
{
  int step[1010];
  for(int i=0;i<1010;++i)step[i]= 1010;
  step[1] = 0;
  for(int i=1;i<=1000;i++)
  {
    int k =2;
    for(int j=i*2;j<=1000;j+=i)
    {
      step[j] = min(step[j],step[i]+k);
      k++;
    }
  }
  return step[n];  
 }

/*
[leetcode-651-4 Keys Keyboard]

Imagine you have a special keyboard with the following keys:

Key 1: (A): Prints one 'A' on screen.

Key 2: (Ctrl-A): Select the whole screen.

Key 3: (Ctrl-C): Copy selection to buffer.

Key 4: (Ctrl-V): Print buffer on screen appending it after what has already been printed.

Now, you can only press the keyboard for N times (with the above four keys), find out the maximum numbers of 'A' you can print on screen.

Example 1:
Input: N = 3
Output: 3
Explanation: 
We can at most get 3 A's on screen by pressing following key sequence:
A, A, A 

Example 2:

Input: N = 7
Output: 9
Explanation: 
We can at most get 9 A's on screen by pressing following key sequence:
A, A, A, Ctrl A, Ctrl C, Ctrl V, Ctrl V 

Note:

1 <= N <= 50
Answers will be in the range of 32-bit signed integer.
思路：

要想N步生成最多个A，可在N-2步的时候，Ctrl A，N-1步的时候，Ctrl C，第N步的时候Ctrl V，这样就能将N-3步生成的A的个数，翻倍。

如何确定在第几步Ctrl A，然后再Ctrl C、Ctrl V呢，需要依次判断第i-3步之前的步骤。

得到递推公式 dp[i] = max(dp[i],dp[i-j-1]);dp[i]表示第i步生成的最多的A的个数。
*/

int maxA(int N)
 {
   vector<int>dp(N+1);
   for(int i=0;i<=N;i++)
   {
     dp[i] = i;
     for(int j=0;j<=i-3;j++)
     {
       dp[i] = max(dp[i],dp[j]*(i-j-2+1));
    }
  }
  return dp[N];
} 