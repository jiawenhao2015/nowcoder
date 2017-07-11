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
	for (int i = 1; i <= 9; i++)//x�������������λ������������ս��
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
			mpx[i]++;//��¼����
			facortopdigit[topdigit(i)]++;
			if (i != x / i)
			{
				facortopdigit[topdigit(x / i)]++;
				mpx[x / i]++;
			}
		}
	}
	for (int i = 1; i <= 9;i++)//x�������������λ������������ս��
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
	
		for (int m = 1; m <= 9; m++)//i*x�������������λ������������ս��
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
	int i = 0;//xiaomei������
	/*while (i<n && score[i] != xiaomei)i++;
	while (i<n && score[i] == xiaomei)i++;*/
	//i -= 1;//��0��ʼ����Ҫ-1�� �±�0��Ϊ�ǵ�һ��
	
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
	for (int t= 0; t <= m - n;t++)//�����ƶ�����
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

/*
����������� 1��5��10��20��50��100 Ԫ��ֽ�ң�����ÿ�ֱ�ֵ���������㹻�࣬��д���������NԪ��NΪ0~10000�ķǸ��������Ĳ�ͬ��ϵĸ�����
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


/*��̬�滮 ���dp[h][n+1],h������h��Ӳ��coins[]={1,5,10,20,50,100} ��
           n+1����ҪƴĿ��Ϊ0-n
  ���ƹ�ʽ :dp[i][j]=dp[i][j]+dp[i-1][j-k*coins[i]],����k[0,n/coins[i]].
        ���ͣ�ʹ��ǰi��Ǯ��ƴ����ֵΪj�ķ�����dp[i][j]= 
        ʹ��ǰi-1��Ǯ�ң�ʹ��k����i��Ǯ�ң�ƴ����ֵΪj�ķ�������
        ��ʹ��ǰi-1��Ǯ��ƴ����ֵΪj�ķ�����dp[i-1][j-k*coins[i]]
��ʼ����
�ϱ�ĵ�һ��dp[0]��Ϊ1����ʾ����Ŀ�ֻ꣬����ֵΪ1��Ӳ��ƴ�գ�ƴ�շ���Ϊ1��

import java.util.Scanner;
import java.util.Arrays;
public class Main{
    public static long count(int n){
    int coins[]={1,5,10,20,50,100};
    int h=coins.length;
    long dp[][]=new long[h][n+1];
    Arrays.fill(dp[0], 1);//���� �����ֶ���1��� ��������1
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
����һ��Ǹ�������ɵ�����h������һ����״ͼ�ĸ߶ȣ�����ÿ�����ӵĿ�ȶ�Ϊ1��
��������״ͼ���ҵ�����ɵ������ε��������ͼ��ʾ���� ���hΪһ���������飬����ÿ�����ӵĸ߶ȣ����������ֵ��
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
        vector<int> left(getFirstSmallValue(arr));//�Ҳ��һ����i��߶ȵ͵�λ��
        reverse(arr.begin(), arr.end());
        vector<int> right(getFirstSmallValue(arr));//����һ����i��߶ȵ͵�λ��
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

/*���������ַ��������ܰ����ո�,�ҳ�������Ĺ��������Ӵ�,����䳤�ȡ�
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



int mainmei()
{
	int n, m,temp;
	vector<int> a = { 5, -3, 6, 5, -5, -1, 6 }, b = { -6, 1 ,4 ,- 2, 0, - 2, 0};

	//code();	
	
	system("PAUSE");
	return 0;
}
