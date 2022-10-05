#include <iostream>
#include <string>
using namespace std;

int main(){
	ios::sync_with_stdio(false);
	freopen("hdu.txt", "r", stdin);
	int i = 0, m = 0;
	while(i < 606677)
	{
		string str;
		int a, b;
		cin >> i >> str >> a >> b;
		if(str.size() > m) m = str.size();
	}
	cout << m;
	return 0;
}