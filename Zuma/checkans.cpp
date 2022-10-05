#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int rep = 1;

int main(){
	fstream f1("output1.txt"), f2("output2.txt");
	int a = 0;
	string s1, s2;
	while(a < rep){
		f1 >> s1;
		f2 >> s2;
		int x1 = s1.size();
		int x2 = s2.size();
		int x = min(x1, x2);
		for(int i = 0; i < x1; i++){
			if(s1[x1 - i] != s2[x2 - i])
			{
				cout << a << endl;
				cout << i <<" "<< x1 <<" "<< x2;
				return 0;
			}
		}
		a++;
	}
	cout << "ok";
	return 0;
}