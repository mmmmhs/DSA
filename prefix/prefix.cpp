#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int nl[20000010] = {0}; //next链长度
int n[20000010] = {0}; //next表

//生成next表并返回next链长度之和
//参考讲义实现
long long calc(string s){
	int len = s.size();
	int t = n[0] = -1;
	int i = 0;
	long long sum = 0;
	while(i < len)
	{
		if(t < 0 || s[i] == s[t])
		{
			i++;
			t++;
			n[i] = t;
			if(t > 0) {
				nl[i] = nl[t] + 1;
				sum += nl[i];
			}	
		}
		else
			t = n[t];
	}
	return sum;
}

int main() {
	string str;
	ios::sync_with_stdio(false);
	cin >> str;
	cout << calc(str) + str.size();
	return 0;
}