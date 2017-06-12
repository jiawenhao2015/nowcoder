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
using namespace std;

//sort 
int maxSurvival(vector<int>& score,int n)
{
	int xiaomei = score[0];
	sort(score.begin(), score.end());
	int i = 0;//xiaomei的索引
	while (i<n && score[i] != xiaomei)i++;
	while (i<n && score[i] == xiaomei)i++;
	//i -= 1;//从0开始不需要-1了 下标0认为是第一个

	int round =0;

	while (i != 1)
	{
		i /= 2;
		round++;
	}
	return round;
}

int difference(vector<int>& pitch1, int n, vector<int>& pitch2, int m)
{
	int diff = INT_MAX;
	int sum = 0;
	for (int t= 0; t <= m - n;t++)//窗口移动次数
	{
		sum = 0;
		for (int i = 0; i < n;i++)
		{			
			sum += (pitch1[i] - pitch2[i + t])*(pitch1[i] - pitch2[i + t]);
		}
		diff = min(diff, sum);
	}
	return diff;
}

int main()
{
	int n, m,temp;
	vector<int> pitch1, pitch2;
	
	cin >> n;	
	for (int i = 0; i < n;i++)
	{
		cin >> temp;
		pitch1.push_back(temp);
	}
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> temp;
		pitch2.push_back(temp);
	}
	cout << difference(pitch1, n, pitch2, m) << endl;
	//system("PAUSE");
	return 0;
}