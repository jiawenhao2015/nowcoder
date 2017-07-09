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


void abstr(string& ret, vector<int>&a, vector<int>&b,int begin,int n,bool &flag,stack<int>& index)
{
	if ( begin == n-1)
	{ 
		flag = true;
		return;
	}
	if ( begin > n-1 || begin < 0) return;
	
	
	for (int i = begin; !flag && i < n ;)
	{	
		cout << ret << " " << begin << endl;		
		
		if (a[i]!=0 &&i+a[i]<n && i+a[i]>=0)
		{
			ret.push_back('a');
			index.push(i);
			abstr(ret, a, b, i + a[i], n, flag, index);
			ret.pop_back();
			i = index.top();
			index.pop();
		}						
		else
		{
			
		}

		if (b[i] != 0 && i + b[i] < n && i + b[i] >= 0)
		{
			ret.push_back('b');
			index.push(i);
			abstr(ret, a, b, i + b[i], n, flag, index);
			ret.pop_back();
			i = index.top();
			index.pop();
		}
		else
		{
			
		}
		
	}
}
string abstr(vector<int>&a, vector<int>&b,int n)
{
	string str = "";
	bool flag = false;
	stack<int> index;
	abstr(str, a, b, 0, n, flag,index);
	return str;
}

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
/*给定一个正整数，编写程序计算有多少对质数的和等于输入的这个正整数，并输出结果。
输入值小于1000。
如，输入为10, 程序应该输出结果为2。（共有两对质数的和为10,分别为(5,5),(3,7)） */
bool isPrime(int n)
{
	if (n == 2 || n == 3)return true;
	if (n % 2 == 0)return false;
	for (int i = 3; i <= sqrt(n);i+=2)
	{
		if (n%i == 0)return false;
	}
	return true;
}
void primepair()
{
	int n;
	cin >> n;
	int res = 0;
	for (int i = 2; i <= n / 2;i++)
	{
		if (isPrime(i) && isPrime(n - i))res++;
	}
	cout << res << endl;
}
/*geohash编码：geohash常用于将二维的经纬度转换为字符串，分为两步：第一步是经纬度的二进制编码，第二步是base32转码。
此题考察纬度的二进制编码：算法对纬度[-90, 90]通过二分法进行无限逼近（取决于所需精度，本题精度为6）。
注意，本题进行二分法逼近过程中只采用向下取整来进行二分，针对二分中间值属于右区间。算法举例如下： 针对纬度为80进行二进制编码过程：
1) 区间[-90, 90]进行二分为[-90, 0),[0, 90]，成为左右区间，可以确定80为右区间，标记为1；
2) 针对上一步的右区间[0, 90]进行二分为[0, 45),[45, 90]，可以确定80是右区间，标记为1；
3) 针对[45, 90]进行二分为[45, 67),[67,90],可以确定80为右区间，标记为1；
4) 针对[67,90]进行二分为[67, 78),[78,90]，可以确定80为右区间，标记为1；
5) 针对[78, 90]进行二分为[78, 84),[84, 90]，可以确定80为左区间，标记为0；
6) 针对[78, 84)进行二分为[78, 81), [81, 84)，可以确定80为左区间，标记为0；
*/
void geohash()
{
	int n;
	cin >> n;
	int step = 0;
	int left = -90, right = 90;
	string code = "";
	while (step < 6)
	{
		step++;
		int  mid = (left + right)/2;
		if (mid <= n)
		{
			left = mid;
			code += '1';

		}
		else if (mid>n)
		{
			right = mid;
			code += '0';
		}
	}
	cout << code << endl;
}
/*游戏里面有很多各式各样的任务，其中有一种任务玩家只能做一次，这类任务一共有1024个，任务ID范围[1,1024]。
请用32个unsigned int类型来记录着1024个任务是否已经完成。初始状态都是未完成。 输入两个参数，都是任务ID，
需要设置第一个ID的任务为已经完成；并检查第二个ID的任务是否已经完成。 
输出一个参数，如果第二个ID的任务已经完成输出1，如果未完成输出0。
如果第一或第二个ID不在[1,1024]范围，则输出-1。*/
vector<unsigned int>flags(32, 0);
void setmark(int id)
{
	int index = (id - 1) / 32;
	int offset = (id - 1) % 32;
	unsigned int mask = 1 << offset;//标记
	flags[index] |= mask;
}
bool getmark(int id)
{
	int index = (id - 1) / 32;
	int offset = (id - 1) % 32;
	unsigned int mask = 1 << offset;
	bool ret = (flags[index] & mask) >> offset;
	return ret;
}
void markgame()
{
	int id1, id2;
	cin >> id1 >> id2;
	if (id1 > 1024 || id2 > 1024 || id1 < 1 || id2 < 1)
	{
		cout << -1 << endl;
		return;
	}
	setmark(id1);
	cout << getmark(id2) << endl;
}

/*假定一种编码的编码范围是a ~ y的25个字母，从1位到4位的编码，如果我们把该编码按字典序排序，
形成一个数组如下：a, aa, aaa, aaaa, aaab, aaac, … …, b, ba, baa, baaa, baab, baac … …,
yyyw, yyyx, yyyy 其中a的Index为0，aa的Index为1，aaa的Index为2，以此类推。 
编写一个函数，输入是任意一个编码，输出这个编码对应的Index.*/
void code()
{
	string s;
	cin >> s;
	int index=0;

	for (int i = 0; i < s.length();i++)
	{
		if (i == 0) index = (s[i] - 'a')*(1+25+25*25+25*25*25);
		if (i == 1) index += (s[i] - 'a')*(1 + 25 + 25 * 25)+1;
		if (i == 2) index += (s[i] - 'a')*(1 + 25)+1;
		if (i == 3) index += (s[i] - 'a')+1;
	}
	cout << index;
	
}
/*
给你六种面额 1、5、10、20、50、100 元的纸币，假设每种币值的数量都足够多，编写程序求组成N元（N为0~10000的非负整数）的不同组合的个数。
#include<iostream>
using namespace std;
  
int main(){
    int N = 0;
    cin >> N;
    long long * F = new long long[N + 1]();
    int c[6] = { 1, 5, 10, 20, 50, 100 };
  
    F[0] = 1;
    for (int i = 0; i < 6; i++)
        for (int v = c[i]; v <= N; v++){
            F[v] = F[v] + F[v - c[i]];
        }
    cout << F[N]<<endl;
    return 0;
}


*/


/*动态规划 填表dp[h][n+1],h代表有h种硬币coins[]={1,5,10,20,50,100} ，
           n+1代表要拼目标为0-n
  递推公式 :dp[i][j]=dp[i][j]+dp[i-1][j-k*coins[i]],其中k[0,n/coins[i]].
        解释：使用前i种钱币拼凑面值为j的方法数dp[i][j]= 
        使用前i-1种钱币，使用k个第i种钱币，拼凑面值为j的方法数，
        即使用前i-1种钱币拼凑面值为j的方法数dp[i-1][j-k*coins[i]]
初始化：
上表的第一行dp[0]均为1，表示任意目标，只由面值为1的硬币拼凑，拼凑方法为1；

import java.util.Scanner;
import java.util.Arrays;
public class Main{
    public static long count(int n){
    int coins[]={1,5,10,20,50,100};
    int h=coins.length;
    long dp[][]=new long[h][n+1];
    Arrays.fill(dp[0], 1);//基础 该数字都由1组成 方法数是1
    for(int i=1;i<h;i++){
        for(int j=1;j<=n;j++){
            int m=j/coins[i];
        for(int k=0;k<=m;k++){
            dp[i][j]=dp[i][j]+dp[i-1][j-k*coins[i]];
            }
        }
        }
    return dp[h-1][n];
    }
    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        while(sc.hasNext()){
          int n=sc.nextInt();
          long res=count(n);
          System.out.println(res);
        }
    }
}
*/


/*
给定一组非负整数组成的数组h，代表一组柱状图的高度，其中每个柱子的宽度都为1。
在这组柱状图中找到能组成的最大矩形的面积（如图所示）。 入参h为一个整型数组，代表每个柱子的高度，返回面积的值。
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
 
std::vector<int> getFirstSmallValue(std::vector<int> height) {
    std::vector<int> ans;
    std::stack<int> stack_;
    int len = height.size();
    for (int i = 0; i < len; i++) {
        while (!stack_.empty()) {
            if (height[i] > height[stack_.top()]) {
                ans.push_back(i - stack_.top() - 1);
                stack_.push(i);
                break;
            }
            else {
                stack_.pop();
            }
        }
        if (stack_.empty()) {
            stack_.push(i);
            ans.push_back(i);
        }
    }
    return ans;
}
int main() {
    using namespace std;
    int n;
    while (cin >> n) {
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        vector<int> left(getFirstSmallValue(arr));//右侧第一个比i点高度低的位置
        reverse(arr.begin(), arr.end());
        vector<int> right(getFirstSmallValue(arr));//左侧第一个比i点高度低的位置
        reverse(right.begin(), right.end());
        reverse(arr.begin(), arr.end());
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            long long temp = (left[i] + right[i] + 1) * arr[i];
            if (ans < temp) {
                ans = temp;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
*/

/*给出两个字符串（可能包含空格）,找出其中最长的公共连续子串,输出其长度。
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
    string s1, s2;
    while (getline(cin, s1), getline(cin, s2)){
        int l1 = s1.size();
        int l2 = s2.size();
        vector<vector<int>> dp(l1 + 1, vector<int>(l2 + 1, 0));
        int result = 0;
        for (int i = 1; i <= l1; i++){
            for (int j = 1; j <= l2; j++){
                if (s1[i - 1] == s2[j - 1]){
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    result = max(dp[i][j], result);
                }
                else{
                    dp[i][j] = 0;
                }
            }
        }
        cout << result << endl;
    }
    return 0;
}*/
int main()
{
	int n, m,temp;
	vector<int> a = { 5, -3, 6, 5, -5, -1, 6 }, b = { -6, 1 ,4 ,- 2, 0, - 2, 0};

	code();	
	
	system("PAUSE");
	return 0;
}
