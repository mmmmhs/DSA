#include<iostream>
#include <string>
using namespace std;

class a{
	int n;
};
class b{
	int n;
	virtual void m(){
		cout << "b";
	}
	virtual void k(){
		cout << "k";
	} 
};
class c : public b{
	void m() override{
		cout << "c";
	}
	void k() override{
		cout << "cc";
	}
};

int main(){
	string s;
	for(int i = 0; i < 64; i++)
		s.append("0");
	cout << sizeof(s);	
	return 0;
}