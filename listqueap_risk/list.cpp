#include "list.h"
#include "queap.h"
using namespace std;

template <typename T>
Node<T>* Node<T>::insertP(T const & n){
	Node<T>* x = new Node<T>(n, pre, this);
	pre->suc = x;
	pre = x;
	return x;
}
template <typename T>
Node<T>* Node<T>::insertS(T const & n){
	Node<T>* x = new Node<T>(n, this, suc);
	suc->pre = x;
	suc = x;
	return x;
}

template <typename T>
List<T>::List(){
	head = new Node<T>();
	trail = new Node<T>();
	head->suc = trail;
	head->pre = nullptr;
	trail->pre = head;
	trail->suc = nullptr;
}
template <typename T>
List<T>::~List(){
	clear();
	delete head;
	delete trail;
}

template <typename T>
Node<T>* List<T>::insert(T const & n, Node<T>* p){
	s++;
	return p->insertP(n);
}
template <typename T>
Node<T>* List<T>::insertF(T const & n){
	return insert(n, head->suc);
}
template <typename T>
Node<T>* List<T>::insertL(T const & n){
	return insert(n, trail);
}

template <typename T>
T List<T>::remove(Node<T>* p){
	T n = p->data;
	p->pre->suc = p->suc;
	p->suc->pre = p->pre;
	delete p;
	s--;
	return n;
} 

template <typename T>
int List<T>::clear(){
	int n = s;
	while (s > 0)
		remove(head->suc);
	return n;
}

template class Node<Record>;
template class List<Record>;