#include <stdlib.h>
#include <climits>
#include <iostream>
#include "temperature.h"
using namespace std;

const int maxl = 200000;
int ans; //当前查询结果

struct Posi
{
	int x, y, temp;
} position[maxl];

struct Node
{
	int x1, x2, y1, y2; //表示[x1, x2] * [y1, y2]的区域
	int max, min;		//最高、最低温度
	bool leaf = false;	//是否是叶子
} kdTree[4 * maxl];

int cmpV(const void *a, const void *b)
{
	return ((Posi *)a)->x - ((Posi *)b)->x;
}
int cmpH(const void *a, const void *b)
{
	return ((Posi *)a)->y - ((Posi *)b)->y;
}

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

void buildNode(Posi *a, int len, int rank, int dep)
{
	if (len == 1)
	{
		kdTree[rank].max = a[0].temp;
		kdTree[rank].min = a[0].temp;
		kdTree[rank].x1 = a[0].x;
		kdTree[rank].x2 = a[0].x;
		kdTree[rank].y1 = a[0].y;
		kdTree[rank].y2 = a[0].y;
		kdTree[rank].leaf = true;
		return;
	} //递归基：叶子
	if (dep % 2 == 0)
		qsort(a, len, sizeof(Posi), cmpV);
	else
		qsort(a, len, sizeof(Posi), cmpH); //不断重复先后竖切、横切
	buildNode(a, len >> 1, 2 * rank + 1, dep + 1);
	buildNode(a + (len >> 1), len - (len >> 1), 2 * rank + 2, dep + 1);
	kdTree[rank].max = max(kdTree[2 * rank + 1].max, kdTree[2 * rank + 2].max);
	kdTree[rank].min = min(kdTree[2 * rank + 1].min, kdTree[2 * rank + 2].min);
	kdTree[rank].x1 = min(kdTree[2 * rank + 1].x1, kdTree[2 * rank + 2].x1);
	kdTree[rank].x2 = max(kdTree[2 * rank + 1].x2, kdTree[2 * rank + 2].x2);
	kdTree[rank].y1 = min(kdTree[2 * rank + 1].y1, kdTree[2 * rank + 2].y1);
	kdTree[rank].y2 = max(kdTree[2 * rank + 1].y2, kdTree[2 * rank + 2].y2);
	//根据子节点情况初始化
}

//节点范围包含于查询范围
bool contained(int x1, int x2, int y1, int y2, int rank)
{
	return kdTree[rank].x1 >= x1 && kdTree[rank].x2 <= x2 && kdTree[rank].y1 >= y1 && kdTree[rank].y2 <= y2;
}
//节点范围与查询范围不相交
bool separated(int x1, int x2, int y1, int y2, int rank)
{
	return kdTree[rank].x2 < x1 || kdTree[rank].x1 > x2 || kdTree[rank].y2 < y1 || kdTree[rank].y1 > y2;
}

int searchmin(int x1, int x2, int y1, int y2, int rank)
{
	if (kdTree[rank].leaf)
	{
		if (contained(x1, x2, y1, y2, rank))
			return kdTree[rank].min;
		else
			return -1;
	}
	int ans1 = 0, ans2 = 0;
	if (separated(x1, x2, y1, y2, 2 * rank + 1))
		ans1 = -1;
	if (separated(x1, x2, y1, y2, 2 * rank + 2))
		ans2 = -1;
	if (contained(x1, x2, y1, y2, 2 * rank + 1))
		ans = min(ans, kdTree[2 * rank + 1].min);
	else if (!separated(x1, x2, y1, y2, 2 * rank + 1) && kdTree[2 * rank + 1].min < ans)
	{
		ans1 = searchmin(x1, x2, y1, y2, 2 * rank + 1);
		if (ans1 != -1)
			ans = min(ans, ans1);
	}
	if (contained(x1, x2, y1, y2, 2 * rank + 2))
		ans = min(ans, kdTree[2 * rank + 2].min);
	else if (!separated(x1, x2, y1, y2, 2 * rank + 2) && kdTree[2 * rank + 2].min < ans)
	{
		ans2 = searchmin(x1, x2, y1, y2, 2 * rank + 2);
		if (ans2 != -1)
			ans = min(ans, ans2);
	} //根据子树情况与当前结果剪枝
	if (ans1 == -1 && ans2 == -1)
		return -1; //若子节点均未找到返回-1
	return ans;
}

int searchmax(int x1, int x2, int y1, int y2, int rank)
{
	if (kdTree[rank].leaf)
	{
		if (contained(x1, x2, y1, y2, rank))
			return kdTree[rank].max;
		else
			return -1;
	}
	int ans1 = 0, ans2 = 0;
	if (separated(x1, x2, y1, y2, 2 * rank + 1))
		ans1 = -1;
	if (separated(x1, x2, y1, y2, 2 * rank + 2))
		ans2 = -1;
	if (contained(x1, x2, y1, y2, 2 * rank + 1))
		ans = max(ans, kdTree[2 * rank + 1].max);
	else if (!separated(x1, x2, y1, y2, 2 * rank + 1) && kdTree[2 * rank + 1].max > ans)
	{
		ans1 = searchmax(x1, x2, y1, y2, 2 * rank + 1);
		if (ans1 != -1)
			ans = max(ans, ans1);
	}
	if (contained(x1, x2, y1, y2, 2 * rank + 2))
		ans = max(ans, kdTree[2 * rank + 2].max);
	else if (!separated(x1, x2, y1, y2, 2 * rank + 2) && kdTree[2 * rank + 2].max > ans)
	{
		ans2 = searchmax(x1, x2, y1, y2, 2 * rank + 2);
		if (ans2 != -1)
			ans = max(ans, ans2);
	} //根据子树情况与当前结果剪枝
	if (ans1 == -1 && ans2 == -1)
		return -1; //若子节点均未找到返回-1
	return ans;
}

void init(int n, const int *x, const int *y, const int *t)
{
	for (int i = 0; i < n; i++)
	{
		position[i].x = x[i];
		position[i].y = y[i];
		position[i].temp = t[i];
	}
	buildNode(position, n, 0, 0);
}

void query(int x1, int x2, int y1, int y2, int *tmin, int *tmax)
{
	ans = INT_MAX;
	*tmin = searchmin(x1, x2, y1, y2, 0);
	ans = INT_MIN;
	*tmax = searchmax(x1, x2, y1, y2, 0);
}
