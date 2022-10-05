#include <iostream>
using namespace std;

const int len = 1001000;
int k;
struct Node
{
	int data;
	int npl = 1;
	Node *lc, *rc;
} nodes[len];

//参考讲义实现 左式堆合并
Node *mergeNode(Node *a, Node *b)
{
	if(!a) return b;
	if(!b) return a;
	if(a->data > b->data) swap(a, b); //小顶堆
	a->rc = mergeNode(a->rc, b);
	if(!a->lc || a->lc->npl < a->rc->npl)
		swap(a->lc, a->rc); 
	if(a->rc)
		a->npl = 1 + a->rc->npl;
	else a->npl = 1;
	return a;		
}

class Leftheap {	
public:	
	Node *root;
	int s = 1; //节点数
	int getmin()
	{
		return root->data;
	}
	void pop()
	{
		root = mergeNode(root->lc, root->rc);
		s--;
	}
	//将lh并入本左式堆
	void mergeLH(Leftheap lh)
	{
		root = mergeNode(root, lh.root);
		s += lh.s;
		while (s > k) pop(); //保证堆中存储最大的k个
	}
} lh[len];

int parent[len], sz[len]; //并查集中节点父亲, 集合大小
int path[len]; //路径压缩用 记录节点到根经历的路径

//并查集查找 路径压缩
int find(int r)
{
	int i = 0;
	while(r != parent[r])
	{
		path[i] = r;
		i++;
		r = parent[r];
	}
	while(i--)
		parent[path[i - 1]] = r;
	return r;
}

//将小集合并入大集合, 返回大集合根
//需保证参数根节点不同
int mergeUF(int xroot, int yroot)
{
	if(sz[xroot] < sz[yroot])
	{
		parent[xroot] = yroot;
		sz[yroot] += sz[xroot];
		return yroot;
	}
	else
	{
		parent[yroot] = xroot;
		sz[xroot] += sz[yroot];
		return xroot;
	}
}

void merge(int u, int v)
{
	int uroot = find(u);
	int vroot = find(v);
	if(uroot != vroot)
	{
		if(uroot == mergeUF(uroot, vroot))
			lh[uroot].mergeLH(lh[vroot]);
		else
			lh[vroot].mergeLH(lh[uroot]);	
		//堆合并与并查集方向一致, 保证堆下标始终与并查集根节点相同	
	}	
}

int main()
{
	ios::sync_with_stdio(false);
	int n, m, q;
	cin >> n >> m >> k >> q;
	for(int i = 1; i <= n; i++)
	{
		cin >> nodes[i].data;
		lh[i].root = &nodes[i];
		parent[i] = i;
		sz[i] = 1;
	}
	while (m--)
	{
		int u, v;
		cin >> u >> v;
		merge(u, v);
	}
	while (q--)
	{
		int op;
		cin >> op;
		if(op == 1)
		{
			int u, v;
			cin >> u >> v;
			merge(u, v);
		}
		else if(op == 2)
		{
			int u;
			cin >> u;
			int uroot = find(u);
			if(lh[uroot].s < k) 
				cout << "-1\n";
			else cout << lh[uroot].getmin() << "\n";
		}
	}
	return 0;
}