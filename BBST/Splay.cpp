#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;
//using gbk

#define stature(p) ((p) ? (p)->height : -1)					 //BST中节点的高度（nullptr视作空树，对应于-1）
#define BalFac(x) (stature((x).lc) - stature((x).rc))		 //平衡因子
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
	int data;				   //数值
	BinNode *parent, *lc, *rc; //父节点及左、右孩子
	int height;				   //高度
	BinNode(int e, BinNode *p = nullptr, BinNode *lc = nullptr, BinNode *rc = nullptr,
			int h = 0, int l = 1) : data(e), parent(p), lc(lc), rc(rc), height(h) {}
	// BinNode *succ();
};

class BST
{ 
protected:
	int _size = 0;
	BinNode *_root = nullptr;
	BinNode *_hot = nullptr; //“命中”节点的父亲
	BinNode *pred(int e);		   //获取e的直接前驱
	int updateHeight(BinNode *x);
	void updateHeightAbove(BinNode *x);

public:											 //基本接口：以virtual修饰，强制要求所有派生类（BST变种）根据各自的规则对其重写
	virtual BinNode *search(const int &e);	     //查找<=e的最大节点
	virtual BinNode *&searchExact(const int &e); //精确查找
	virtual BinNode *insert(const int &e) = 0;	 //插入
	virtual bool remove(const int &e) = 0;		 //删除
};

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
		if (!v)
		{
			BinNode *tmp = pred(e);
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
void BST::updateHeightAbove(BinNode *x) //更新高度
{
	while (x)
	{
		updateHeight(x);
		x = x->parent;
	}
} //从x出发，覆盖历代祖先

class Splay : public BST
{ //由BST派生的Splay树类
protected:
	BinNode *splay(BinNode *v); //将节点v伸展至根
public:
	BinNode *&searchExact(const int &e) override; //精确查找（重写）
	BinNode *search(const int &e) override;		  //查找（重写）
	BinNode *insert(const int &e) override;		  //插入（重写）
	bool remove(const int &e) override;			  //删除（重写）
};

//在节点*p与*lc（可能为空）之间建立父（左）子关系
inline void attachAsLC(BinNode *lc, BinNode *p)
{
	p->lc = lc;
	if (lc)
		lc->parent = p;
}
//在节点*p与*rc（可能为空）之间建立父（右）子关系
inline void attachAsRC(BinNode *p, BinNode *rc)
{
	p->rc = rc;
	if (rc)
		rc->parent = p;
}

BinNode *Splay::splay(BinNode *v)
{ //v为因最近访问而需伸展的节点位置
	if (!v)
		return NULL;
	BinNode *p;
	BinNode *g; //*v的父亲与祖父
	while ((p = v->parent) && (g = p->parent))
	{							 //自下而上，反复对*v做双层伸展
		BinNode *gg = g->parent; //每轮之后*v都以原曾祖父（great-grand parent）为父
		if (IsLChild(*v))
			if (IsLChild(*p))
			{ //zig-zig
				attachAsLC(p->rc, g);
				attachAsLC(v->rc, p);
				attachAsRC(p, g);
				attachAsRC(v, p);
			}
			else
			{ //zig-zag
				attachAsLC(v->rc, p);
				attachAsRC(g, v->lc);
				attachAsLC(g, v);
				attachAsRC(v, p);
			}
		else if (IsRChild(*p))
		{ //zag-zag
			attachAsRC(g, p->lc);
			attachAsRC(p, v->lc);
			attachAsLC(g, p);
			attachAsLC(p, v);
		}
		else
		{ //zag-zig
			attachAsRC(p, v->lc);
			attachAsLC(v->rc, g);
			attachAsRC(v, g);
			attachAsLC(p, v);
		}
		if (!gg)
			v->parent = NULL; //若*v原先的曾祖父*gg不存在，则*v现在应为树根
		else				  //否则，*gg此后应该以*v作为左或右孩子
			(g == gg->lc) ? attachAsLC(v, gg) : attachAsRC(gg, v);
		updateHeight(g);
		updateHeight(p);
		updateHeight(v);
	} //双层伸展结束时，必有g == NULL，但p可能非空
	if (p = v->parent)
	{ //若p果真非空，则额外再做一次单旋
		if (IsLChild(*v))
		{
			attachAsLC(v->rc, p);
			attachAsRC(v, p);
		}
		else
		{
			attachAsRC(p, v->lc);
			attachAsLC(p, v);
		}
		updateHeight(p);
		updateHeight(v);
	}
	v->parent = NULL;
	return v;
} //调整之后新树根应为被伸展的节点，故返回该节点的位置以便上层函数更新树根

BinNode* Splay::search(const int &e){
	BinNode *p = BST::search(e);
	_root = splay(p ? p : _hot); //将最后一个被访问的节点伸展至根
	return p;
}

BinNode *&Splay::searchExact(const int &e)
{ //在伸展树中查找e
	BinNode *p = BST::searchExact(e);
	_root = splay(p ? p : _hot); //将最后一个被访问的节点伸展至根
	return _root;
} //与其它BST不同，无论查找成功与否，_root都指向最后被访问的节点

BinNode *Splay::insert(const int &e)
{ //将关键码e插入伸展树中
	if (!_root)
	{
		_size++;
		return _root = new BinNode(e);
	} //处理原树为空的退化情况
	if (e == searchExact(e)->data)
		return _root; //确认目标节点不存在
	_size++;
	BinNode *t = _root; //创建新节点。以下调整<=7个指针以完成局部重构
	if (_root->data < e)
	{														//插入新根，以t和t->rc为左、右孩子
		t->parent = _root = new BinNode(e, NULL, t, t->rc); //2 + 3个
		if (HasRChild(*t))
		{
			t->rc->parent = _root;
			t->rc = NULL;
		} //<= 2个
	}
	else
	{														//插入新根，以t->lc和t为左、右孩子
		t->parent = _root = new BinNode(e, NULL, t->lc, t); //2 + 3个
		if (HasLChild(*t))
		{
			t->lc->parent = _root;
			t->lc = NULL;
		} //<= 2个
	}
	updateHeightAbove(t); //更新t及其祖先（实际上只有_root一个）的高度
	return _root;		  //新节点必然置于树根，返回之
} //无论e是否存在于原树中，返回时总有_root->data == e

bool Splay::remove(const int &e)
{ //从伸展树中删除关键码e
	if (!_root || (e != searchExact(e)->data))
		return false;	//若树空或目标不存在，则无法删除
	BinNode *w = _root; //assert: 经查找后节点e已被伸展至树根
	if (!HasLChild(*_root))
	{ //若无左子树，则直接删除
		_root = _root->rc;
		if (_root)
			_root->parent = NULL;
	}
	else if (!HasRChild(*_root))
	{ //若无右子树，也直接删除
		_root = _root->lc;
		if (_root)
			_root->parent = NULL;
	}
	else
	{ //若左右子树同时存在，则
		BinNode *lTree = _root->lc;
		lTree->parent = NULL;
		_root->lc = NULL; //暂时将左子树切除
		_root = _root->rc;
		_root->parent = NULL; //只保留右子树
		searchExact(w->data); //以原树根为目标，做一次（必定失败的）查找
							  //assert: 至此，右子树中最小节点必伸展至根，且（因无雷同节点）其左子树必空，于是
		_root->lc = lTree;
		lTree->parent = _root; //只需将原左子树接回原位即可
	}
	_size--; //释放节点，更新规模
	if (_root)
		updateHeight(_root); //此后，若树非空，则树根的高度需要更新
	return true;			 //返回成功标志
} //若目标节点存在且被删除，返回true；否则返回false

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
	Splay s;
	for(int i = 0; i < n; i++)
		scanf("%c %d", &oper[i].type, &oper[i].num);
	beg = clock();	
	for(int i = 0; i < n; i++)
	{
		if(oper[i].type == 'A')
			s.insert(oper[i].num);
		else if(oper[i].type == 'B')
			s.remove(oper[i].num);
		else if(oper[i].type == 'C'){
			BinNode* ans = s.search(oper[i].num);
			// if(ans) printf("%d\n", ans->data);
			// else printf("-1\n");
		}	
	}			
	fin = clock();
	ofstream fout("time.txt", ios::app);
	fout << "splay " << fin - beg << endl;
	return 0;
}

