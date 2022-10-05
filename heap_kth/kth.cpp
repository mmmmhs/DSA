#include <iostream>
#include <stdlib.h>
#include "kth.h"
using namespace std;

int array1[500010];
int array2[500010];
int array3[500010];

struct Node
{
	int x, y, z; //存储array下标
	Node(int a, int b, int c) : x(a), y(b), z(c){}
	Node(){}
};

int num = 0; //堆大小 
Node heap[4000010];

inline bool lt(Node a, Node b)
{
	return compare(array1[a.x], array2[a.y], array3[a.z], array1[b.x], array2[b.y], array3[b.z]);
}

//入堆 参考讲义实现
void push(Node n)
{
	heap[num] = n;
	int i = num;
	while (i > 0)
	{
		int p = (i - 1) >> 1;
		if (lt(heap[p], heap[i]))
			break;
		swap(heap[i], heap[p]);
		i = p;
	}
	num++;
}

int newparent(int i)
{
	int ans = i;
	int lc = 1 + (i << 1);
	int rc = (1 + i) << 1;
	if (lc < num)
	{
		if (lt(heap[lc], heap[ans]))
			ans = lc;
	}
	if (rc < num)
	{
		if (lt(heap[rc], heap[ans]))
			ans = rc;
	}
	return ans;
}

//出堆 参考讲义实现
Node pop()
{
	Node m = heap[0];
	heap[0] = heap[num - 1];
	num--;
	int i = 0;
	int p = newparent(i);
	while (i != p)
	{
		swap(heap[i], heap[p]);
		i = p;
		p = newparent(i);
	}
	return m;
}

int cmpx(const void *a, const void *b)
{
	if(compare(*((int*) a), 1, 1, *((int*) b), 1, 1) > 0)
		return -1;
	return 1;	
}
int cmpy(const void *a, const void *b)
{
	if(compare(1, *((int*) a), 1, 1, *((int*) b), 1) > 0)
		return -1;
	return 1;	
}
int cmpz(const void *a, const void *b)
{
	if(compare(1, 1, *((int*) a), 1, 1, *((int*) b)) > 0)
		return -1;
	return 1;	
}

void get_kth(int n, int k, int *x, int *y, int *z)
{
	for(int i = 0; i < n; i++)
	{
		array1[i] = i + 1;
		array2[i] = i + 1;
		array3[i] = i + 1;
	}
	qsort(array1, n, sizeof(int), cmpx);
	qsort(array2, n, sizeof(int), cmpy);
	qsort(array3, n, sizeof(int), cmpz);
	// a[array1[i]] < a[array1[j]] iff i < j; b[]c[]同理
	Node ans;
	push(Node(0, 0, 0));
	while (k--)
	{
		ans = pop();
		if(ans.z == 0)
		{
			if(ans.y == 0 && ans.x < n - 1)
				push(Node(ans.x + 1, ans.y, ans.z));	
			if(ans.y < n - 1)					
				push(Node(ans.x, ans.y + 1, ans.z));
		}
		if(ans.z < n - 1)
			push(Node(ans.x, ans.y, ans.z + 1));
	} //规定插入顺序 防止重复插入
	*x = array1[ans.x];
	*y = array2[ans.y];
	*z = array3[ans.z];
}