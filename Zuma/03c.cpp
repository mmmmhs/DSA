#include <iostream>
using namespace std;

const int M = 500000;

int main(){
	freopen("03.in", "w", stdout);
	for(int i = 0; i < M / 2; i++)
		cout << "AB";
	cout << endl << M << endl;
	for(int i = 0; i < M; i++)
		cout << M / 2 << " " << "C" << endl;	
	return 0;	
}