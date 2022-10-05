#include <iostream>
using namespace std;

struct Record
{int num, cnt = 0;};

int n, t;
int num[1000010];
int beg[1000010];
//int maxnum[1000010];
int count[2000010];
int sum[2000010];
int maxi = 0;//最大值中最大者
Record queap[1000010];
int front = 0;//指示追溯开始处
int head = 0, rear = 0;//queap数组起始与终止下一位

void enqueue(int a){
	int c = 1;
	while ((rear - head != 0) && ((queap[rear - 1].num < a) || (queap[rear - 1].num == a)))
	{
		c += queap[rear - 1].cnt;
		rear--;
	}
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
	int ans = queap[head].num;
	count[ans]++;
	if(ans > maxi) maxi = ans;
	return ans;
}

int main(){
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	num[0] = 0;
	count[0] = 1;
	sum[0] = 1;
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
	for(int i = 1; i <= maxi; i++)
		sum[i] = sum[i - 1] + count[i];	
	cin >> t;
	int l, h;
	for(int i = 0; i < t; i++){
		cin >> l >> h;
		long long a = sum[l - 1];
		long long b = sum[h - 1];
		cout << a << " " << b - a << endl;
	}
	return 0;	
}