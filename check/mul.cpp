#include <string>
#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>
using namespace std;
typedef unsigned long long Ull;

const int len = 560;
const int dblen = 1120;
const int rad = 1000000000;
const int log = 9;

int la, lb;
int input[len];
Ull mulres[dblen];
int ans[len][len][2];

void format(string s){
	int sl = s.size();
	int l = sl / log;
	memset(input, 0, len * sizeof(int));
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
void add(){
	Ull carry = 0;
	int k = 0;
	while((k < len) && (k <= la + lb + 1)){
		int i = max(k - 1 - lb, 0);
		while((i <= la + 1) && (i < k))
		{
			mulres[k] += ans[i][k - i][0];
			mulres[k] += ans[i][k - 1 - i][1];
			i++;
		}
		mulres[k] += ans[k][0][0];
		mulres[k] += carry;
		carry = mulres[k] / rad;
		mulres[k] %= rad; 
		k++;
	}
	for(k = len; k <= la + lb + 1; k++){
		int i = max(k - 1 - lb, 0);
		while(i <= la + 1)
		{
			mulres[k] += ans[i][k - i][0];
			mulres[k] += ans[i][k - 1 - i][1];
			i++;
		}
		mulres[k] += ans[k - len][len - 1][1];
		mulres[k] += carry;
		carry = mulres[k] / rad;
		mulres[k] %= rad; 
	}
}

Ull* multiply(int* a, int* b){
	int carry = 0;
	for(int i = 0; i < len; i++){
		for(int j = 0; j < len; j++)
			memset(ans[i][j], 0, 2 * sizeof(int));
	}	
	memset(mulres, 0, dblen * sizeof(Ull));
	//O(n^2)	
	for(int i = 0; i <= la; i++){
		for(int j = 0; j <= lb; j++)
		{
			Ull product = (Ull) a[i] * b[j] + carry;
			ans[i][j][1] = product / rad;
			ans[i][j][0] = product % rad;
		}
	}
	add();
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
	// clock_t start,finish;
 	// start = clock();
	int n; 
	// ifstream fin("input.txt");
	cin >> n;
	string a, b;
	for(int i = 0; i < n; i++){
		cin >> a >> b;
		la = a.size() / log;
		lb = b.size() / log;
		int numa[len], numb[len];
		format(a);
		for(int i = 0; i < len; i++)
			numa[i] = input[i];
		format(b);
		cout << tostr(multiply(numa, input)) << endl;
	}
	// finish = clock();
 	// cout << finish-start << endl;
	return 0;
}
