#include <iostream>
using namespace std;

int main(){
	freopen("10.in", "w", stdout);
	int s = 2048;
	for(int i = 0; i < s; i++)
		cout << "AB";
	cout << "BCC" << endl << 1 << endl;	
	cout << 2 * s << " B";
	return 0;	
}