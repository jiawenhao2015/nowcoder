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



int topdigit(int x)
{
	while (x>=10)
	{
		x /= 10;
	}
	return x;
}
void fuza(int x, int left, int right, vector<int>&ret)
{
	vector<int>temp(10, 0);
	for (int i = 1; i*i <= x;i++)
	{
		if (x%i==0)
		{
			temp[topdigit(i)]++;
			if (i*i != x)temp[topdigit(x / i)]++;
		}
	}
	for (int i = 1; i <= 9; i++)//x的所有因子最高位结果反馈到最终结果
	{
		ret[i] += temp[i];
	}
}
void getFactor(int x,vector<int>&ret,vector<bool>&flag,int& left,int& right)
{
	if (x ==1)
	{
		ret[x]++;
		return;
	}
	 
	if (flag[x-left] == false)return;	 
	flag[x - left] = false;
	map<int, int>mpx;
	vector<int> facortopdigit(10,0);
	for (int i = 1; i * i <= x;i++)
	{
		if (x%i ==0)
		{
			mpx[i]++;//记录因子
			facortopdigit[topdigit(i)]++;
			if (i != x / i)
			{
				facortopdigit[topdigit(x / i)]++;
				mpx[x / i]++;
			}
		}
	}
	for (int i = 1; i <= 9;i++)//x的所有因子最高位结果反馈到最终结果
	{
		ret[i] += facortopdigit[i];
	}

	for (int i = 2; i*x <= right;i++)
	{
		flag[i*x -left] = false;
		vector<int> factortemp = facortopdigit;

		for (int k = 1; k*k <= i;k++)
		{
			if (i%k==0)
			{		
				//if (k == 1) k = i;
				for (auto it = mpx.begin(); it != mpx.end(); it++)
				{
					if (!mpx.count(k*it->first))factortemp[topdigit(k*it->first)]++;
					if (!mpx.count((i / k)*it->first))factortemp[topdigit((i / k)*it->first)]++;
				}
			}
		}
	
		for (int m = 1; m <= 9; m++)//i*x的所有因子最高位结果反馈到最终结果
		{
			ret[m] += factortemp[m];
		}
	}
}
void getFactor(int left, int right)
{
	vector<int> ret(10,0);
	vector<bool> flag(right-left+1,true);
	for (int x = left; x <= right;x++)
	{
		fuza(x, left,right,ret);
	}
	for (int i = 1; i < ret.size();i++)
	{
		cout << ret[i] << endl;
	}
}


int maxSurvival(vector<int>& score,int n)
{
	int xiaomei = score[0];
	sort(score.begin(), score.end());
	int i = 0;//xiaomei的索引
	/*while (i<n && score[i] != xiaomei)i++;
	while (i<n && score[i] == xiaomei)i++;*/
	//i -= 1;//从0开始不需要-1了 下标0认为是第一个
	
	i = upper_bound(score.begin(), score.end(), xiaomei) - score.begin();

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
	long long diff = INT_MAX;
	long long  sum = 0;
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
	//vector<int> pitch1, pitch2;
	//
	//cin >> n;	
	//for (int i = 0; i < n;i++)
	//{
	//	cin >> temp;
	//	pitch1.push_back(temp);
	//}
	//cin >> m;
	//for (int i = 0; i < m; i++)
	//{
	//	cin >> temp;
	//	pitch2.push_back(temp);
	//}
	//cout << difference(pitch1, n, pitch2, m) << endl;
	//cout << maxSurvival(pitch1,n) << endl;

	cin >> n>>m;
	getFactor(n, m);
	system("PAUSE");
	return 0;
}
