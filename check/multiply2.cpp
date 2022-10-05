#include <string>
#include <iostream>
#include <cstring>
using namespace std;
typedef unsigned long long Ull;

const int len = 560;
const int dblen = 1120;
const int rad = 1000000000;
const int log = 9;

int la, lb;
int input[len];
Ull mulres[dblen];

void format(string s){
	int sl = s.size();
	int l = sl / log;
	for(int i = 0; i < l; i++){
		input[i] = stoi(string(s, sl - log * (i + 1), log));
	}
	int left = sl - log * l;
	if(left > 0)
		input[l] = stoi(string(s, 0, left));
	else
		input[l] = 0;	
}

//O(n^2)
Ull* multiply(int* a, int* b){	
	memset(mulres, 0, dblen * sizeof(Ull));
	//O(n^2)	
	for(int i = 0; i <= la; i++){
		for(int j = 0; j <= lb; j++)
		{
			Ull product = (Ull) a[i] * b[j];
			mulres[i + j] += product;
			mulres[i + j + 1] += mulres[i + j] / rad;
			mulres[i + j] %= rad;
		}
	}
	return mulres;
}

string tostr(Ull* num){
	string res;
	bool start = false;
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
		int numa[len];
		format(a);
		for(int i = 0; i < len; i++)
			numa[i] = input[i];
		format(b);
		cout << tostr(multiply(numa, input)) << endl;
	}
	return 0;
}
