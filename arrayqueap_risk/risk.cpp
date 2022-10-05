#include <iostream>
#include <stdlib.h>
using namespace std;

struct Record{int num, cnt = 0;};//记录最大值与出现次数

int n, t;
int num[1000010];//病例数
int beg[1000010];//追溯开始时间
int maxnum[1000010];//最大值
Record queap[1000010];//参考习题解析10-20优化改进
int front = 0;//当前追溯开始处
int head = 0, rear = 0;//queap数组起始与终止下一位

void enqueue(int a){
	int c = 1;
	while ((rear - head != 0) && ((queap[rear - 1].num < a) || (queap[rear - 1].num == a)))
	{
		c += queap[rear - 1].cnt;
		rear--;
	}
	//合并前面较小的值
	rear++;	
	Record rec;
	rec.num = a;
	rec.cnt = c;
	queap[rear - 1] = rec;
}

void dequeue(){
	queap[head].cnt--;
	if(queap[head].cnt == 0)
		head++;
}

int setMax(int i){
	enqueue(num[i]);
	while (front < beg[i]){
		dequeue();
		front++;
	}	
	return maxnum[i] = queap[head].num;
}

//归并排序,参考讲义实现
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

//二分查找,参考讲义实现
//返回小于s的个数
int count(unsigned int s){
	int hi = n, lo = 0;
	while(lo < hi){
		int mi = (lo + hi) >> 1;
		if(s > (unsigned) maxnum[mi])
			lo = mi + 1;
		else
			hi = mi;
	}
	return lo;
}

int main(){
	num[0] = 0;
	maxnum[0] = 0;
	cin >> n;
	for(int i = 1; i <= n; i++)
		scanf("%d", &num[i]);
	for(int i = 0; i < n; i++){
		unsigned int m;
		scanf("%u", &m);
		beg[i] = (unsigned int)i > m ? i - m : 0;
	}
	for(int i = 1; i <= n; i++)
		setMax(i);	
	mergeSort(maxnum, n);		
	cin >> t;
	unsigned int l, h;
	for(int i = 0; i < t; i++){
		scanf("%u %u", &l, &h);
		int a = count(l);
		int b = count(h);
		cout << a << " " << b - a << endl;
	}
	return 0;	
}