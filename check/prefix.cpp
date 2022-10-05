#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int nl[20000010] = {0}; //next¡¥≥§∂»
int n[20000010] = {0}; //next±Ì

int calc(string s){
	int len = s.size();
	int t = n[0] = -1;
	int i = 0, sum = 0;
	while(i < len){
		if(t < 0 || s[i] == s[t])
		{
			i++;
			t++;
			n[i] = t;
			if(t > 0){
				nl[i] = nl[t] + 1;
				sum += nl[i];
			}	
		}
		else
			t = n[t];
	}
	return sum;
}

int main(){
	string str;
	ios::sync_with_stdio(false);
	cin >> str;
	cout << calc(str) + str.size();
	return 0;
}