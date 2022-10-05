#include <iostream>
using namespace std;

const int M = 500000;

int main(){
	freopen("06.in", "w", stdout);
	for(int i = 0; i < M / 2; i++)
		cout << "AB";
	cout << endl << 6000 << endl;
	for(int i = 0; i < 3000; i++){
		cout << 0 << " " << "C" << endl;
		cout << 0 << " " << "D" << endl;
	}
	return 0;	
}