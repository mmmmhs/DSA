#include <iostream>
#include "list.h"
#include "queap.h"
using namespace std;

int n, t;
int num[1000010];
int beg[1000010];
int maxnum[1000010];
//int count[2000010];
Queap q = Queap();
int front = 0;

int setMax(int i){
	q.enqueue(num[i]);
	while (front < beg[i]){
		q.dequeue();
		front++;
	}	
	return maxnum[i] = q.max();
}

void merge(int *a, int nn){
	int mid = nn >> 1;
	int *fm = new int[mid];
	for(int i = 0; i < mid; i++)
		fm[i] = a[i];
	int *lt = a + mid;
	int i = 0, j = 0, k = 0;
	while((j < mid) && (k < nn - mid))
		a[i++] = (fm[j] < lt[k]) ? fm[j++] : lt[k++];
	while (j < mid)
		a[i++] = fm[j++];
	delete[] fm;
}

void mergeSort(int *a, int nn){
	if(nn < 2) return;
	int mid = nn >> 1;
	mergeSort(a, mid);
	mergeSort(a + mid, nn - mid);
	merge(a, nn);
}

//返回小于s的个数
int count(int s){
	int hi = n, lo = 0;
	while(lo < hi){
		int mi = (lo + hi) >> 1;
		if(s > maxnum[mi])
			lo = mi + 1;
		else
			hi = mi;
	}
	return lo;
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	num[0] = 0;
	maxnum[0] = 0;
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> num[i];
	for(int i = 0; i < n; i++){
		long long m;
		cin >> m;
		beg[i] = (long long)i - m > 0 ? i - m : 0;
	}
	for(int i = 1; i <= n; i++)
		setMax(i);
	for(int i = 0; i < n; i++)
		cout << maxnum[i] << " ";
	cout << endl;		
	mergeSort(maxnum, n);
	for(int i = 0; i < n; i++)
		cout << maxnum[i] << " ";
	cout << endl;		
	cin >> t;
	int l, h;
	for(int i = 0; i < t; i++){
		cin >> l >> h;
		long long a = count(l);
		long long b = count(h);
		cout << a << " " << b - a << endl;
	}
	return 0;	
}