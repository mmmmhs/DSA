#include <iostream>
#include <fstream>
using namespace std;
typedef long long ll;

struct Dot{
	int x, y;
};

int xdot[200000], ydot[200000];
int n;
Dot test[200000];

bool toLeft(Dot d, int x, int y){
	return ((ll)x * y - (ll)y * d.x - (ll)x * d.y > 0);
}

void merge(int *a, int num){
	int mid = num >> 1;
	int *fm = new int[mid];
	for(int i = 0; i < mid; i++)
		fm[i] = a[i];
	int *lt = a + mid;
	int i = 0, j = 0, k = 0;
	while((j < mid) && (k < num - mid))
		a[i++] = (fm[j] <= lt[k]) ? fm[j++] : lt[k++];
	while (j < mid)
		a[i++] = fm[j++];
	delete[] fm;
}

void mergeSort(int *a, int num){
	if(num < 2) return;
	int mid = num >> 1;
	mergeSort(a, mid);
	mergeSort(a + mid, num - mid);
	merge(a, num);
}

int count(Dot d){
	int hi = n, lo = 0;
	while(lo < hi){
		int mi = (lo + hi) >> 1;
		if(toLeft(d, xdot[mi], ydot[mi]))
			hi = mi;
		else
			lo = mi + 1;
	}
	return lo;
}

int main(){
	ifstream fin("input.txt");
	fin >> n;
	for(int i = 0; i < n; i++)
		fin >> xdot[i];
	for(int i = 0; i < n; i++)
		fin >> ydot[i];
	int m;
	fin >> m;
	for(int i = 0; i < m; i++)
		fin >> test[i].x >> test[i].y;
	mergeSort(xdot, n);
	mergeSort(ydot, n);	
	for(int i = 0; i < m; i++)
		cout << count(test[i]) << endl;
	return 0;
}