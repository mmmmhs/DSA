#include <iostream>
using namespace std;
typedef long long ll;
typedef unsigned int uint;

const int mPosi = 400000; //最大访问端点数
int m;					  //操作数
uint posi[mPosi];		  //端点坐标
uint Q[mPosi], R[mPosi];  //查询、翻转坐标
int pn = 0;				  //端点个数
int qn = 0;				  //查询端点数
int rn = 0;				  //翻转端点数
bool operType[mPosi / 2]; //记录每次操作的类型;翻转为T,查询为F
ll ans;					  //查询结果

struct Node
{
	uint l, r, len;	   //左右端点(左闭右开),区间内点数
	ll rev = 0;		   //总翻转次数;修改懒惰标记时也应修改
	int lt = 0;		   //懒惰标记,记录每个点翻转次数
	bool leaf = false; //是否为叶子
} segtree[4 * mPosi];

int cmp(const void *a, const void *b)
{
	return *(uint *)a - *(uint *)b;
}

/*初始化节点,将其左右端点坐标分别设置为posi数组中的lr位与rr位
并下传至子节点
等同于先序遍历,O(n)*/
void initval(int nr, int lr, int rr)
{
	segtree[nr].l = posi[lr];
	segtree[nr].r = posi[rr];
	segtree[nr].len = segtree[nr].r - segtree[nr].l;
	if (rr - lr > 1)
	{
		int mr = (lr + rr) >> 1; //中间位置
		initval(2 * nr + 1, lr, mr);
		initval(2 * nr + 2, mr, rr);
	}
	else
		segtree[nr].leaf = true;
}

//下传懒惰标记
void passLT(int nr)
{
	segtree[2 * nr + 1].lt += segtree[nr].lt;
	segtree[2 * nr + 1].rev += (ll)segtree[nr].lt * segtree[2 * nr + 1].len;
	segtree[2 * nr + 2].lt += segtree[nr].lt;
	segtree[2 * nr + 2].rev += (ll)segtree[nr].lt * segtree[2 * nr + 2].len;
	segtree[nr].rev -= (ll)segtree[nr].lt * segtree[nr].len;
	segtree[nr].lt = 0;
}

//节点与区间相交
bool intersected(int nr, uint lp, uint rp)
{
	return !(segtree[nr].l >= rp || lp >= segtree[nr].r);
}

void reverseNode(int nr, uint lp, uint rp)
{
	if (segtree[nr].l >= lp && segtree[nr].r <= rp)
	{
		segtree[nr].lt++;
		segtree[nr].rev += segtree[nr].len;
		return;
	}
	if (segtree[nr].leaf)
		return;
	passLT(nr);
	if (intersected(2 * nr + 1, lp, rp))
		reverseNode(2 * nr + 1, lp, rp);
	if (intersected(2 * nr + 2, lp, rp))
		reverseNode(2 * nr + 2, lp, rp);
	segtree[nr].rev = (segtree[2 * nr + 1].rev + segtree[2 * nr + 2].rev);
}

void queryNode(int nr, uint lp, uint rp)
{
	if (segtree[nr].l >= lp && segtree[nr].r <= rp)
	{
		ans += segtree[nr].rev;
		return;
	}
	if (segtree[nr].leaf)
		return;
	passLT(nr);
	if (intersected(2 * nr + 1, lp, rp))
		queryNode(2 * nr + 1, lp, rp);
	if (intersected(2 * nr + 2, lp, rp))
		queryNode(2 * nr + 2, lp, rp);
	segtree[nr].rev = (segtree[2 * nr + 1].rev + segtree[2 * nr + 2].rev);
}

//参考讲义实现
//去重,返回新长度
int uniquify()
{
	int i = 0, j = 0;
	while (j < pn)
	{
		if (posi[i] != posi[j])
		{
			i++;
			posi[i] = posi[j];
		}
		j++;
	}
	return i + 1;
}

int main()
{
	ios::sync_with_stdio(false);
	int n;
	cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		char c;
		uint lp, rp;
		cin >> c >> lp >> rp;
		posi[pn++] = lp;
		posi[pn++] = rp + 1;
		if (c == 'Q')
		{
			Q[qn++] = lp;
			Q[qn++] = rp + 1;
			operType[i] = false;
		}
		if (c == 'H')
		{
			R[rn++] = lp;
			R[rn++] = rp + 1;
			operType[i] = true;
		}
	} //处理输入
	qsort(posi, pn, sizeof(uint), cmp);
	pn = uniquify();
	initval(0, 0, pn - 1); //建树
	int qtime = 0, rtime = 0;
	for (int i = 0; i < m; i++)
	{
		if (operType[i])
		{
			reverseNode(0, R[rtime], R[rtime + 1]);
			rtime += 2;
		}
		else
		{
			ans = 0;
			queryNode(0, Q[qtime], Q[qtime + 1]);
			cout << ans << "\n";
			qtime += 2;
		}
	} //翻转、查询
	return 0;
}