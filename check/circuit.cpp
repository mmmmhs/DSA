#include <iostream>
#include <string>
using namespace std;

struct Listnode
{
	Listnode *pr, *su;
	int data;
	Listnode(int d, Listnode *p, Listnode *s) : data(d), pr(p), su(s){}
	Listnode(){
		pr = nullptr;
		su = nullptr;
	}
};

class Queue{
private:
	Listnode *head, *tail;
public:
	int sz;
	Queue(){
		head = new Listnode();
		tail = new Listnode();
		head->su = tail;
		tail->pr = head;
		sz = 0;
	}
	void enqueue(int e)
	{
		Listnode *x = new Listnode(e, head, head->su);
		head->su->pr = x;
		head->su = x;
		sz++;
	}
	int dequeue(){
		int d = tail->pr->data;
		tail->pr->pr->su = tail;
		tail->pr = tail->pr->pr;
		sz--;
		return d;
	}
	//get the first num that is not equal to e
	int getfneq(int e)
	{
		int d = tail->pr->data;
		if(d == e) return tail->pr->pr->data;
		else return d;
	}
};

struct Treenode
{
	Treenode *lc = nullptr, *rc = nullptr;
	int num = 0;
} trie[31501000]; //63 * 500000

struct Leafnode : public Treenode
{
	Queue q;
} leaves[500100]; //叶子节点

string input[500100]; // n == 500000

int tnnum = 1; //内部节点数 初始:根
int lnnum = 0; //叶子数

void insert(string str, int codenum){
	Treenode *cur = trie;
	for(int i = 0; i < 63; i++)
	{
		cur->num++;
		if(str[i] == '0'){
			if(cur->lc == nullptr){
				cur->lc = &trie[tnnum];
				tnnum++;
			}
			cur = cur->lc;	
		}
		else if(str[i] == '1'){
			if(cur->rc == nullptr){
				cur->rc = &trie[tnnum];
				tnnum++;
			}
			cur = cur->rc;	
		}
	}
	//此时cur为目标叶子节点的父亲
	cur->num++;
	if(str[63] == '0')
	{
		if(cur->lc == nullptr)
		{
			cur->lc = &leaves[lnnum];
			leaves[lnnum].q.enqueue(codenum);
			leaves[lnnum].num++;
			lnnum++;
		}
		else
		//此处已有叶子;编号入队
		{
			Leafnode *l = static_cast<Leafnode*>(cur->lc);
			l->q.enqueue(codenum);
			l->num++;
		}
	}
	else if(str[63] == '1')
	{
		if(cur->rc == nullptr){
			cur->rc = &leaves[lnnum];
			leaves[lnnum].q.enqueue(codenum);
			leaves[lnnum].num++;
			lnnum++;
		}
		else
		//此处已有叶子;编号入队
		{
			Leafnode *l = static_cast<Leafnode*>(cur->rc);
			l->q.enqueue(codenum);
			l->num++;
		}
	}
}

void remove(string str, int codenum)
{
	Treenode *cur = trie;
	for(int i = 0; i < 63; i++)
	{
		cur->num--;
		if(str[i] == '0')
			cur = cur->lc;
		else if(str[i] == '1')
			cur = cur->rc;	
	}
	//此时cur为目标叶子节点的父亲
	//叶子编号出队
	cur->num--;
	if(str[63] == '0')
	{
		Leafnode *l = static_cast<Leafnode*>(cur->lc);
		l->q.dequeue();
		l->num--;
	}
	else if(str[63] == '1')
	{
		Leafnode *l = static_cast<Leafnode*>(cur->rc);
		l->q.dequeue();
		l->num--;
	}
}

//查询 返回编号
int search(string str, int codenum)
{
	Treenode *cur = trie;
	for(int i = 0; i < 64; i++)
	{
		if(str[i] == '0')
		{
			if(cur->rc && cur->rc->num > 0)
				cur = cur->rc;
			else cur = cur->lc;	
		}
		else if(str[i] == '1')
		{
			if(cur->lc && cur->lc->num > 0)
				cur = cur->lc;
			else cur = cur->rc;	
		}	
	}
	//此时cur为目标叶子节点
	Leafnode *l = static_cast<Leafnode*>(cur);
	return l->q.getfneq(codenum);
}

int main(){
	ios::sync_with_stdio(false);
	int n, k;
	cin >> n >> k;
	string s;
	for(int i = 1; i <= n; i++)
	{
		cin >> s;
		input[i] = s;
	}
	int ori = min(k + 2, n); //初始规模
	int ir; //插入位置
	for(ir = 1; ir <= ori; ir++)
		insert(input[ir], ir);
	int sr; //查询位置
	int rr = 1; //删除位置
	for(sr = 1; sr <= n; sr++)
	{
		cout << search(input[sr], sr) - 1 << "\n";
		if(sr - k > 1)
		{
			remove(input[rr], rr);
			rr++;
		}
		if(sr + k + 2 <= n)
		{
			insert(input[ir], ir);
			ir++;
		}
	}
	return 0;
}
