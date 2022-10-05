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

//�ο�����ʵ�� ��ʽ�Ѻϲ�
Node *mergeNode(Node *a, Node *b)
{
	if(!a) return b;
	if(!b) return a;
	if(a->data > b->data) swap(a, b); //С����
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
	int s = 1; //�ڵ���
	int getmin()
	{
		return root->data;
	}
	void pop()
	{
		root = mergeNode(root->lc, root->rc);
		s--;
	}
	//��lh���뱾��ʽ��
	void mergeLH(Leftheap lh)
	{
		root = mergeNode(root, lh.root);
		s += lh.s;
		while (s > k) pop(); //��֤���д洢����k��
	}
} lh[len];

int parent[len], sz[len]; //���鼯�нڵ㸸��, ���ϴ�С
int path[len]; //·��ѹ���� ��¼�ڵ㵽��������·��

//���鼯���� ·��ѹ��
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

//��С���ϲ���󼯺�, ���ش󼯺ϸ�
//�豣֤�������ڵ㲻ͬ
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
		//�Ѻϲ��벢�鼯����һ��, ��֤���±�ʼ���벢�鼯���ڵ���ͬ	
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