#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;
//using utf-8

#define stature(p) ((p) ? (p)->height : -1)					 //BST中节点的高度（nullptr视作空树，对应于-1）
#define BalFac(x) (stature((x).lc) - stature((x).rc))		 //平衡因子
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2)) //AVL平衡条件
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define tallerChild(x) (                                                                                                                                                                               \
	stature((x)->lc) > stature((x)->rc) ? (x)->lc : (																					 /*左高*/                                                    \
													 stature((x)->lc) < stature((x)->rc) ? (x)->rc : (									 /*右高*/                                                    \
																									  IsLChild(*(x)) ? (x)->lc : (x)->rc /*等高：与父亲x同侧者（zIg-zIg或zAg-zAg）优先*/ \
																									  )))
// #define FromParentTo(x) /*来自父亲的引用*/ \
// 	(IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)

struct BinNode
{							   //二叉树节点
	int data;				   //数据
	BinNode *parent, *lc, *rc; //父节点及左、右孩子
	int height;				   //高度
	BinNode(int e, BinNode *p = nullptr, BinNode *lc = nullptr, BinNode *rc = nullptr,
			int h = 0, int l = 1) : data(e), parent(p), lc(lc), rc(rc), height(h) {}
	BinNode *succ();
};

class BST
{ 
protected:
	int _size = 0;
	BinNode *_root = nullptr;
	BinNode *_hot = nullptr; //“命中”节点的父亲
	BinNode *connect34( //按照“3 + 4”结构，联接3个节点及四棵子树
		BinNode *, BinNode *, BinNode *,
		BinNode *, BinNode *, BinNode *, BinNode *);
	BinNode *rotateAt(BinNode *x); //对x及其父亲、祖父做统一旋转调整
	BinNode *pred(int e);		   //获取e的直接前驱
	int updateHeight(BinNode *x);

public:										//基本接口：以virtual修饰，强制要求所有派生类（BST变种）根据各自的规则对其重写
	BinNode *search(const int &e);    		//查找<=e的最大节点
	BinNode *&searchExact(const int &e);	//精确查找
	virtual BinNode *insert(const int &e) = 0;	//插入
	virtual bool remove(const int &e) = 0;		//删除
};

//根据数据得到直接前驱
BinNode *BST::pred(int e)
{
	BinNode *s = _hot;
	while (s && s->data > e)
		s = s->parent;
	return s;
}

//找到<=目标的最大节点;不存在返回空
BinNode *BST::search(const int &e)
{
	if (!_root || e == _root->data)
	{
		_hot = nullptr;
		return _root;
	}
	for (_hot = _root;;)
	{
		BinNode *&v = (e < _hot->data) ? _hot->lc : _hot->rc; //确定方向，深入一层
		if (!v){
			BinNode* tmp = pred(e);
			return tmp;
		}
		if (e == v->data)
			return v;
		_hot = v;
	}
}

BinNode *&BST::searchExact(const int &e)
{ //在BST中查找关键码e
	if (!_root || e == _root->data)
	{
		_hot = nullptr;
		return _root;
	} //空树，或恰在树根命中
	for (_hot = _root;;)
	{														  //否则，自顶而下
		BinNode *&v = (e < _hot->data) ? _hot->lc : _hot->rc; //确定方向，深入一层
		if (!v || e == v->data)
			return v;
		_hot = v; //一旦命中或抵达叶子，随即返回
	}			  //返回目标节点位置的引用，以便后续插入、删除操作
} //无论命中或失败，_hot均指向v之父亲（v是根时，hot为NULL）

int BST::updateHeight(BinNode *x) //更新节点x高度
{
	return x->height = 1 + max(stature(x->lc), stature(x->rc));
} //具体规则，因树而异

BinNode *BST::connect34(
	BinNode *a, BinNode *b, BinNode *c,
	BinNode *T0, BinNode *T1, BinNode *T2, BinNode *T3)
{
	a->lc = T0;
	if (T0)
		T0->parent = a;
	a->rc = T1;
	if (T1)
		T1->parent = a;
	updateHeight(a);
	c->lc = T2;
	if (T2)
		T2->parent = c;
	c->rc = T3;
	if (T3)
		T3->parent = c;
	updateHeight(c);
	b->lc = a;
	a->parent = b;
	b->rc = c;
	c->parent = b;
	updateHeight(b);
	return b; //该子树新的根节点
}

BinNode *BST::rotateAt(BinNode *v)
{ //v为非空孙辈节点
	BinNode *p = v->parent;
	BinNode *g = p->parent; //视v、p和g相对位置分四种情况
	if (IsLChild(*p))
	{ /* zig */
		if (IsLChild(*v))
		{ /* zig-zig */			   
			p->parent = g->parent; //向上联接
			return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
		}
		else
		{ /* zig-zag */			   
			v->parent = g->parent; //向上联接
			return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
		}
	}
	else
	{ /* zag */
		if (IsRChild(*v))
		{ /* zag-zag */			   
			p->parent = g->parent; //向上联接
			return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
		}
		else
		{ /* zag-zig */			   
			v->parent = g->parent; //向上联接
			return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
		}
	}
}

class AVL : public BST
{
public:
	BinNode *insert(const int &e) override; //插入（重写）
	bool remove(const int &e) override;		//删除（重写）
											//BST::search()等其余接口可直接沿用
};

BinNode *AVL::insert(const int &e)
{ //将关键码e插入AVL树中
	BinNode *&x = searchExact(e);
	if (x)
		return x; //确认目标节点不存在
	BinNode *xx = x = new BinNode(e, _hot);
	_size++; //创建新节点x
	if(_root == nullptr) _root = xx;
	// 此时，x的父亲_hot若增高，则其祖父有可能失衡
	for (BinNode *g = _hot; g; g = g->parent) //从x之父出发向上，逐层检查各代祖先g
		if (!AvlBalanced(*g))
		{	//一旦发现g失衡，则（采用“3 + 4”算法）使之复衡，并将子树
			if(!g->parent)
				_root = rotateAt(tallerChild(tallerChild(g))); 
			else{
				BinNode* gp = g->parent;
				if(g == gp->lc)
					gp->lc = rotateAt(tallerChild(tallerChild(g)));
				if(g == gp->rc)	
					gp->rc = rotateAt(tallerChild(tallerChild(g)));
			} //重新接入原树
			break; //局部子树复衡后，高度必然复原；其祖先亦必如此，故调整结构
		}
		else				 //否则（g仍平衡）
			updateHeight(g); //只需更新其高度（注意：即便g未失衡，高度亦可能增加）
	return xx;				 //返回新节点位置
} //无论e是否存在于原树中，总有AVL::insert(e)->data == e

BinNode *BinNode::succ()
{					   //定位节点v的直接后继
	BinNode *s = this; //记录后继的临时变量
	if (rc)
	{			//若有右孩子，则直接后继必在右子树中，具体地就在
		s = rc; //右子树中
		while (HasLChild(*s))
			s = s->lc; //最靠左（最小）的节点
	}
	else
	{ //否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”，具体地就在
		while (IsRChild(*s))
			s = s->parent; //逆向地沿右向分支，不断朝左上方移动
		s = s->parent;	   //最后再朝右上方移动一步，即抵达直接后继（如果存在）
	}
	return s;
}

BinNode *removeAt(BinNode *&x, BinNode *&hot)
{
	BinNode *w = x;
	BinNode *succ = nullptr;
	if (!HasLChild(*x))
		succ = x = x->rc;
	else if (!HasRChild(*x))
		succ = x = x->lc;
	else
	{
		w = w->succ();
		swap(x->data, w->data);
		BinNode *u = w->parent;
		((u == x) ? u->rc : u->lc) = succ = w->rc;
	}
	hot = w->parent;
	if (succ)
		succ->parent = hot;
	return succ;
}

bool AVL::remove(const int &e)
{ //从AVL树中删除关键码e
	BinNode *&x = searchExact(e);
	if (!x)
		return false; //确认目标存在（留意_hot的设置）
	removeAt(x, _hot);
	_size--; //先按BST规则删除之（此后，原节点之父_hot及其祖先均可能失衡）
	for (BinNode *g = _hot; g; g = g->parent)
	{																	  //从_hot出发向上，逐层检查各代祖先g
		if (!AvlBalanced(*g))	
			if(!g->parent)
				g = _root = rotateAt(tallerChild(tallerChild(g))); 
			else
			{
				BinNode* gp = g->parent;
				if(g == gp->lc)
					g = gp->lc = rotateAt(tallerChild(tallerChild(g)));
				if(g == gp->rc)	
					g = gp->rc = rotateAt(tallerChild(tallerChild(g)));
			} //一旦发现g失衡，则（采用“3 + 4”算法）使之复衡，并将该子树联至原父亲
		updateHeight(g);	//更新高度（注意：即便g未失衡或已恢复平衡，高度均可能降低）
	}						//可能需做Omega(logn)次调整——无论是否做过调整，全树高度均可能降低
	return true;		    //删除成功
}

struct Op{
	char type;
	int num;
} oper[10000001];

int main(){
	clock_t beg, fin;
	
	// ios::sync_with_stdio(false);
	freopen("input.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	AVL avl;
	for(int i = 0; i < n; i++)
		scanf("%c %d", &oper[i].type, &oper[i].num);
	beg = clock();	
	for(int i = 0; i < n; i++)
	{
		if(oper[i].type == 'A')
			avl.insert(oper[i].num);
		else if(oper[i].type == 'B')
			avl.remove(oper[i].num);
		else if(oper[i].type == 'C'){
			BinNode* ans = avl.search(oper[i].num);
			// if(ans) printf("%d\n", ans->data);
			// else printf("-1\n");
		}	
	}			
	fin = clock();
	ofstream fout("time.txt", ios::app);
	fout << "avl " << fin - beg << endl;
	return 0;
}
