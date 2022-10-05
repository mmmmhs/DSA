#include <iostream>
using namespace std;

const int M = 2048;

int main(){
	freopen("07.in", "w", stdout);
	for(int i = 0; i < M / 2 - 1; i++)
		cout << "AB";
	cout << "DDBA";
	for(int i = 0; i < M / 4 - 1; i++)
		cout << "BBAA";
	cout << "BBC" << endl; 
	cout << 2 << endl;
	cout << 3072 << " B" << endl;
	cout << M << " D";
	return 0;	
}