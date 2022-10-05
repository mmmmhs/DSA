#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;
//using gbk

#define stature(p) ((p) ? (p)->height : -1)					 //BST�нڵ�ĸ߶ȣ�nullptr������������Ӧ��-1��
#define BalFac(x) (stature((x).lc) - stature((x).rc))		 //ƽ������
#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define tallerChild(x) (                                                                                                                                                                               \
	stature((x)->lc) > stature((x)->rc) ? (x)->lc : (																					 /*���*/                                                    \
													 stature((x)->lc) < stature((x)->rc) ? (x)->rc : (									 /*�Ҹ�*/                                                    \
																									  IsLChild(*(x)) ? (x)->lc : (x)->rc /*�ȸߣ��븸��xͬ���ߣ�zIg-zIg��zAg-zAg������*/ \
																									  )))
// #define FromParentTo(x) /*���Ը��׵�����*/ \
// 	(IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)

struct BinNode
{							   //�������ڵ�
	int data;				   //��ֵ
	BinNode *parent, *lc, *rc; //���ڵ㼰���Һ���
	int height;				   //�߶�
	BinNode(int e, BinNode *p = nullptr, BinNode *lc = nullptr, BinNode *rc = nullptr,
			int h = 0, int l = 1) : data(e), parent(p), lc(lc), rc(rc), height(h) {}
	// BinNode *succ();
};

class BST
{ 
protected:
	int _size = 0;
	BinNode *_root = nullptr;
	BinNode *_hot = nullptr; //�����С��ڵ�ĸ���
	BinNode *pred(int e);		   //��ȡe��ֱ��ǰ��
	int updateHeight(BinNode *x);
	void updateHeightAbove(BinNode *x);

public:											 //�����ӿڣ���virtual���Σ�ǿ��Ҫ�����������ࣨBST���֣����ݸ��ԵĹ��������д
	virtual BinNode *search(const int &e);	     //����<=e�����ڵ�
	virtual BinNode *&searchExact(const int &e); //��ȷ����
	virtual BinNode *insert(const int &e) = 0;	 //����
	virtual bool remove(const int &e) = 0;		 //ɾ��
};

BinNode *BST::pred(int e)
{
	BinNode *s = _hot;
	while (s && s->data > e)
		s = s->parent;
	return s;
}

//�ҵ�<=Ŀ������ڵ�;�����ڷ��ؿ�
BinNode *BST::search(const int &e)
{
	if (!_root || e == _root->data)
	{
		_hot = nullptr;
		return _root;
	}
	for (_hot = _root;;)
	{
		BinNode *&v = (e < _hot->data) ? _hot->lc : _hot->rc; //ȷ����������һ��
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
{ //��BST�в��ҹؼ���e
	if (!_root || e == _root->data)
	{
		_hot = nullptr;
		return _root;
	} //��������ǡ����������
	for (_hot = _root;;)
	{														  //�����Զ�����
		BinNode *&v = (e < _hot->data) ? _hot->lc : _hot->rc; //ȷ����������һ��
		if (!v || e == v->data)
			return v;
		_hot = v; //һ�����л�ִ�Ҷ�ӣ��漴����
	}			  //����Ŀ��ڵ�λ�õ����ã��Ա�������롢ɾ������
} //�������л�ʧ�ܣ�_hot��ָ��v֮���ף�v�Ǹ�ʱ��hotΪNULL��

int BST::updateHeight(BinNode *x) //���½ڵ�x�߶�
{
	return x->height = 1 + max(stature(x->lc), stature(x->rc));
} //���������������
void BST::updateHeightAbove(BinNode *x) //���¸߶�
{
	while (x)
	{
		updateHeight(x);
		x = x->parent;
	}
} //��x������������������

class Splay : public BST
{ //��BST������Splay����
protected:
	BinNode *splay(BinNode *v); //���ڵ�v��չ����
public:
	BinNode *&searchExact(const int &e) override; //��ȷ���ң���д��
	BinNode *search(const int &e) override;		  //���ң���д��
	BinNode *insert(const int &e) override;		  //���루��д��
	bool remove(const int &e) override;			  //ɾ������д��
};

//�ڽڵ�*p��*lc������Ϊ�գ�֮�佨���������ӹ�ϵ
inline void attachAsLC(BinNode *lc, BinNode *p)
{
	p->lc = lc;
	if (lc)
		lc->parent = p;
}
//�ڽڵ�*p��*rc������Ϊ�գ�֮�佨�������ң��ӹ�ϵ
inline void attachAsRC(BinNode *p, BinNode *rc)
{
	p->rc = rc;
	if (rc)
		rc->parent = p;
}

BinNode *Splay::splay(BinNode *v)
{ //vΪ��������ʶ�����չ�Ľڵ�λ��
	if (!v)
		return NULL;
	BinNode *p;
	BinNode *g; //*v�ĸ������游
	while ((p = v->parent) && (g = p->parent))
	{							 //���¶��ϣ�������*v��˫����չ
		BinNode *gg = g->parent; //ÿ��֮��*v����ԭ���游��great-grand parent��Ϊ��
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
			v->parent = NULL; //��*vԭ�ȵ����游*gg�����ڣ���*v����ӦΪ����
		else				  //����*gg�˺�Ӧ����*v��Ϊ����Һ���
			(g == gg->lc) ? attachAsLC(v, gg) : attachAsRC(gg, v);
		updateHeight(g);
		updateHeight(p);
		updateHeight(v);
	} //˫����չ����ʱ������g == NULL����p���ܷǿ�
	if (p = v->parent)
	{ //��p����ǿգ����������һ�ε���
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
} //����֮��������ӦΪ����չ�Ľڵ㣬�ʷ��ظýڵ��λ���Ա��ϲ㺯����������

BinNode* Splay::search(const int &e){
	BinNode *p = BST::search(e);
	_root = splay(p ? p : _hot); //�����һ�������ʵĽڵ���չ����
	return p;
}

BinNode *&Splay::searchExact(const int &e)
{ //����չ���в���e
	BinNode *p = BST::searchExact(e);
	_root = splay(p ? p : _hot); //�����һ�������ʵĽڵ���չ����
	return _root;
} //������BST��ͬ�����۲��ҳɹ����_root��ָ����󱻷��ʵĽڵ�

BinNode *Splay::insert(const int &e)
{ //���ؼ���e������չ����
	if (!_root)
	{
		_size++;
		return _root = new BinNode(e);
	} //����ԭ��Ϊ�յ��˻����
	if (e == searchExact(e)->data)
		return _root; //ȷ��Ŀ��ڵ㲻����
	_size++;
	BinNode *t = _root; //�����½ڵ㡣���µ���<=7��ָ������ɾֲ��ع�
	if (_root->data < e)
	{														//�����¸�����t��t->rcΪ���Һ���
		t->parent = _root = new BinNode(e, NULL, t, t->rc); //2 + 3��
		if (HasRChild(*t))
		{
			t->rc->parent = _root;
			t->rc = NULL;
		} //<= 2��
	}
	else
	{														//�����¸�����t->lc��tΪ���Һ���
		t->parent = _root = new BinNode(e, NULL, t->lc, t); //2 + 3��
		if (HasLChild(*t))
		{
			t->lc->parent = _root;
			t->lc = NULL;
		} //<= 2��
	}
	updateHeightAbove(t); //����t�������ȣ�ʵ����ֻ��_rootһ�����ĸ߶�
	return _root;		  //�½ڵ��Ȼ��������������֮
} //����e�Ƿ������ԭ���У�����ʱ����_root->data == e

bool Splay::remove(const int &e)
{ //����չ����ɾ���ؼ���e
	if (!_root || (e != searchExact(e)->data))
		return false;	//�����ջ�Ŀ�겻���ڣ����޷�ɾ��
	BinNode *w = _root; //assert: �����Һ�ڵ�e�ѱ���չ������
	if (!HasLChild(*_root))
	{ //��������������ֱ��ɾ��
		_root = _root->rc;
		if (_root)
			_root->parent = NULL;
	}
	else if (!HasRChild(*_root))
	{ //������������Ҳֱ��ɾ��
		_root = _root->lc;
		if (_root)
			_root->parent = NULL;
	}
	else
	{ //����������ͬʱ���ڣ���
		BinNode *lTree = _root->lc;
		lTree->parent = NULL;
		_root->lc = NULL; //��ʱ���������г�
		_root = _root->rc;
		_root->parent = NULL; //ֻ����������
		searchExact(w->data); //��ԭ����ΪĿ�꣬��һ�Σ��ض�ʧ�ܵģ�����
							  //assert: ���ˣ�����������С�ڵ����չ�������ң�������ͬ�ڵ㣩���������ؿգ�����
		_root->lc = lTree;
		lTree->parent = _root; //ֻ�轫ԭ�������ӻ�ԭλ����
	}
	_size--; //�ͷŽڵ㣬���¹�ģ
	if (_root)
		updateHeight(_root); //�˺������ǿգ��������ĸ߶���Ҫ����
	return true;			 //���سɹ���־
} //��Ŀ��ڵ�����ұ�ɾ��������true�����򷵻�false

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

