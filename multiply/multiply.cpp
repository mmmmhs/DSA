#include <string>
#include <iostream>
#include <cstring>
using namespace std;
typedef unsigned long long Ull;

const int len = 630;//输入数组最大长度; 5000 / 8 = 625
const int dblen = 1260;//乘积数组最大长度; 630 * 2 = 1260
const int rad = 100000000;//10 ^ 8进制
const int log = 8;

int la, lb;//a, b长度
int input[2][len];//format()后a, b分别存储在input[0]与input[1]中
Ull mulres[dblen];//存储乘积

//将string a, b转变为10^8进制数组
void format(string s1, string s2){
	int sl1 = s1.size();
	int l1 = sl1 / log;
	int sl2 = s2.size();
	int l2 = sl2 / log;
	for(int i = 0; i < l1; i++){
		input[0][i] = stoi(string(s1, sl1 - log * (i + 1), log));
	}
	//自后向前, 每8位存入int
	int left = sl1 - log * l1;
	if(left > 0)
		input[0][l1] = stoi(string(s1, 0, left));
	else
		input[0][l1] = 0;
	//若有剩余存入,否则存0		
	for(int i = 0; i < l2; i++){
		input[1][i] = stoi(string(s2, sl2 - log * (i + 1), log));
	}
	left = sl2 - log * l2;
	if(left > 0)
		input[1][l2] = stoi(string(s2, 0, left));
	else
		input[1][l2] = 0;	
}

//O(n^2)
Ull* multiply(int* a, int* b){	
	memset(mulres, 0, dblen * sizeof(Ull));	
	for(int i = 0; i <= la; i++){
		for(int j = 0; j <= lb; j++)
			mulres[i + j] += (Ull) a[i] * b[j];
	}//求值
	for(int i = 0; i < la + lb + 1; i++)
	{
		mulres[i + 1] += mulres[i] / rad;
		mulres[i] %= rad;
	}//进位
	return mulres;
}

string tostr(Ull* num){
	string res;
	bool start = false;//判断是否开始
	for(int i = la + lb + 1; i >= 0; i--)
	{
		if(!start){
			if(num[i] != 0){
				start = true;
				res = to_string(num[i]);
			}
			continue;
		}		
		string str = to_string(num[i]);
		int l = str.size();
		if(l < log){
			for(int i = 0; i < log - l; i++)
				str = "0" + str;	
		}
		res += str;
	}
	if(res.size() == 0)
		res = "0";
	return res;
}

int main(){
	int n; 
	cin >> n;
	string a, b;
	for(int i = 0; i < n; i++){
		cin >> a >> b;
		la = a.size() / log;
		lb = b.size() / log;
		format(a, b);
		cout << tostr(multiply(input[0], input[1])) << endl;
	}
	return 0;
}
