#pragma once
#include "list.h"

struct Record
{int num, cnt = 0;};

//存储每一位后继及自己中的最大值,重复者以cnt计数
class Queap : public List<Record>{
public:	
	void enqueue(int n){
		int c = 1;
		while ((size() != 0) && ((last()->data.num < n) || (last()->data.num == n)))
			c += remove(last()).cnt;
		Record rec;
		rec.num = n;
		rec.cnt = c;
		insertL(rec);
	}

	Record dequeue(){
		first()->data.cnt--;
		if(first()->data.cnt == 0)
			return remove(first());
		return first()->data;	
	}

	//区间最大值即首位值
	int max(){return first()->data.num;}
};
