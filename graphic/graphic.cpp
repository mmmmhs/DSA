#include <iostream>
using namespace std;

typedef long long ll;
struct Dot{
	int x, y;
};

int *xdot, *ydot;
int n;

//d是否在(x,0)与(0,y)线段的左边
//toLeft测试(通过网上搜索了解)
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

//归并排序(参考讲义实现)
void mergeSort(int *a, int num){
	if(num < 2) return;
	int mid = num >> 1;
	mergeSort(a, mid);
	mergeSort(a + mid, num - mid);
	merge(a, num);
}

//返回在d左边线段的数量
//二分查找(参考讲义实现)
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
	cin >> n;
	xdot = new int[n];
	ydot = new int[n];
	for(int i = 0; i < n; i++)
		cin >> xdot[i];
	for(int i = 0; i < n; i++)
		cin >> ydot[i];
	int m;
	cin >> m;
	Dot test;
	mergeSort(xdot, n);
	mergeSort(ydot, n);	
	for(int i = 0; i < m; i++){
		cin >> test.x >> test.y;
		cout << count(test) << endl;
	}
	delete[] xdot;
	delete[] ydot;	
	return 0;
}