#pragma once

template <typename T> class Node{
public: 
	T data;
	Node<T>* pre;
	Node<T>* suc;
	Node(){}
	Node<T>(T n, Node<T>* p = nullptr, Node<T>* s = nullptr) : data(n), pre(p), suc(s){}
	Node<T>* insertP(T const & n);
	Node<T>* insertS(T const & n);
};

template <typename T> class List{
private: 
	int s;
	Node<T>* head;
	Node<T>* trail;

protected:
public:
	List();
	~List();

	Node<T>* first(){return head->suc;}
	Node<T>* last(){return trail->pre;}
	int size(){return s;}

	//插入前驱
	Node<T>* insert(T const & n, Node<T>* p);
	//插入第一个
	Node<T>* insertF(T const & n);
	//插入末尾
	Node<T>* insertL(T const & n);

	//删除节点
	T remove(Node<T>* p);
	//清空列表
	int clear();
};