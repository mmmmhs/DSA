#include <cstring>
#include <cstdio>
const int TABLE_SIZE = 499883; // = 124970 * 4 + 3
struct hash_entry
{
	char *my_string;
	int my_data;
	hash_entry()
	{
		my_string = NULL;
		my_data = 0;
	}
	hash_entry(char *str, int data) : my_data(data)
	{
		my_string = new char[strlen(str) + 1];
		strcpy(my_string, str);
	}
};

struct hashing_strategy
{
	virtual int operator()(char *str, int N) = 0;
};
struct naive_hashing : public hashing_strategy
{
	int operator()(char *str, int N) override;
};
struct ascii_hashing : public hashing_strategy
{
	int operator()(char *str, int N) override;
};
struct utf8_hashing : public hashing_strategy
{
	int operator()(char *str, int N) override;
};

struct collision_strategy
{
	virtual void init() = 0; // pure virtual function
	virtual int operator()(hash_entry *Table, int table_size, int last_choice) = 0;
};
struct linear_probe : public collision_strategy
{
	void init();
	int operator()(hash_entry *Table, int table_size, int last_choice) override;
};
//double direction square
struct dblsqr_probe : public collision_strategy
{
	int t = 0; //双向试探次数 偏移量为t^2
	bool dir = true; //偏移方向(true为+,false为-)
	void init();
	int operator()(hash_entry *Table, int table_size, int last_choice) override;
};
//overflow area
struct ofarea_probe : public collision_strategy
{
	void init();
	int operator()(hash_entry *Table, int table_size, int last_choice) override;
};

struct hashtable
{
	hash_entry *Table;
	int table_size;
	hashing_strategy *my_hashing; // 如果改为hashing_strategy my_hashing, 即不是用指针作为hashtable的成员, 而是让hashing_strategy结构体直接作为hashtable的成员. 会发生什么bug?
	collision_strategy *my_collision;
	hashtable(int size, hashing_strategy *hashing, collision_strategy *collision)
		: table_size(size), my_hashing(hashing), my_collision(collision)
	{
		Table = new hash_entry[table_size];
	}

	bool insert(hash_entry entry)
	{
		ofarea_probe* ofa = dynamic_cast<ofarea_probe*>(my_collision);
		int last_choice;
		if(ofa != nullptr)
			last_choice = (*my_hashing)(entry.my_string, table_size / 2);
		else	
			last_choice = (*my_hashing)(entry.my_string, table_size);
		my_collision->init();
		while (Table[last_choice].my_string != NULL)
		{ // loop infinitely? return false when no more space?
			last_choice = (*my_collision)(Table, table_size, last_choice);
		}
		Table[last_choice] = entry;
		return true;
	}
	
	int query(char *query_string)
	{
		ofarea_probe* ofa = dynamic_cast<ofarea_probe*>(my_collision);
		int last_choice;
		if(ofa != nullptr)
			last_choice = (*my_hashing)(query_string, table_size / 2);
		else	
			last_choice = (*my_hashing)(query_string, table_size);
		my_collision->init();
		while (Table[last_choice].my_string != NULL &&
			   strcmp(Table[last_choice].my_string, query_string) != 0)
		{ // 未处理的情况: 哈希表已满
			last_choice = (*my_collision)(Table, table_size, last_choice);
			// 处理冲突，直至找不到/找到string相同条目
		}
		if (Table[last_choice].my_string == NULL)
		{
			return -1;
		}
		else
		{
			return Table[last_choice].my_data;
		}
	}
};
