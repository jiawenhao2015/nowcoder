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
/*����һ������������д��������ж��ٶ������ĺ͵�����������������������������
����ֵС��1000��
�磬����Ϊ10, ����Ӧ��������Ϊ2�����������������ĺ�Ϊ10,�ֱ�Ϊ(5,5),(3,7)�� */
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
/*geohash���룺geohash�����ڽ���ά�ľ�γ��ת��Ϊ�ַ�������Ϊ��������һ���Ǿ�γ�ȵĶ����Ʊ��룬�ڶ�����base32ת�롣
���⿼��γ�ȵĶ����Ʊ��룺�㷨��γ��[-90, 90]ͨ�����ַ��������ޱƽ���ȡ�������辫�ȣ����⾫��Ϊ6����
ע�⣬������ж��ַ��ƽ�������ֻ��������ȡ�������ж��֣���Զ����м�ֵ���������䡣�㷨�������£� ���γ��Ϊ80���ж����Ʊ�����̣�
1) ����[-90, 90]���ж���Ϊ[-90, 0),[0, 90]����Ϊ�������䣬����ȷ��80Ϊ�����䣬���Ϊ1��
2) �����һ����������[0, 90]���ж���Ϊ[0, 45),[45, 90]������ȷ��80�������䣬���Ϊ1��
3) ���[45, 90]���ж���Ϊ[45, 67),[67,90],����ȷ��80Ϊ�����䣬���Ϊ1��
4) ���[67,90]���ж���Ϊ[67, 78),[78,90]������ȷ��80Ϊ�����䣬���Ϊ1��
5) ���[78, 90]���ж���Ϊ[78, 84),[84, 90]������ȷ��80Ϊ�����䣬���Ϊ0��
6) ���[78, 84)���ж���Ϊ[78, 81), [81, 84)������ȷ��80Ϊ�����䣬���Ϊ0��
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
/*��Ϸ�����кܶ��ʽ����������������һ���������ֻ����һ�Σ���������һ����1024��������ID��Χ[1,1024]��
����32��unsigned int��������¼��1024�������Ƿ��Ѿ���ɡ���ʼ״̬����δ��ɡ� ����������������������ID��
��Ҫ���õ�һ��ID������Ϊ�Ѿ���ɣ������ڶ���ID�������Ƿ��Ѿ���ɡ�
���һ������������ڶ���ID�������Ѿ�������1�����δ������0��
�����һ��ڶ���ID����[1,1024]��Χ�������-1��*/
vector<unsigned int>flags(32, 0);
void setmark(int id)
{
	int index = (id - 1) / 32;
	int offset = (id - 1) % 32;
	unsigned int mask = 1 << offset;//���
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

/*�ٶ�һ�ֱ���ı��뷶Χ��a ~ y��25����ĸ����1λ��4λ�ı��룬������ǰѸñ��밴�ֵ�������
�γ�һ���������£�a, aa, aaa, aaaa, aaab, aaac, �� ��, b, ba, baa, baaa, baab, baac �� ��,
yyyw, yyyx, yyyy ����a��IndexΪ0��aa��IndexΪ1��aaa��IndexΪ2���Դ����ơ�
��дһ������������������һ�����룬�����������Ӧ��Index.*/
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