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

//2017
/*给定一个正整数，编写程序计算有多少对质数的和等于输入的这个正整数，并输出结果。
输入值小于1000。
如，输入为10, 程序应该输出结果为2。（共有两对质数的和为10,分别为(5,5),(3,7)） */
bool isPrime(int n)
{
	if (n == 2 || n == 3)return true;
	if (n % 2 == 0)return false;
	for (int i = 3; i <= sqrt(n); i += 2)
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
	for (int i = 2; i <= n / 2; i++)
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
		int  mid = (left + right) / 2;
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
	int index = 0;

	for (int i = 0; i < s.length(); i++)
	{
		if (i == 0) index = (s[i] - 'a')*(1 + 25 + 25 * 25 + 25 * 25 * 25);
		if (i == 1) index += (s[i] - 'a')*(1 + 25 + 25 * 25) + 1;
		if (i == 2) index += (s[i] - 'a')*(1 + 25) + 1;
		if (i == 3) index += (s[i] - 'a') + 1;
	}
	cout << index;

}