#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <stdlib.h>
#include "crc32.h"
using namespace std;
typedef const unsigned char *Text;
typedef unsigned int Key;

class Entry
{
public:
	Text text;			//明文
	Key key;			//密文
	bool dup = false;	//是否有重复
	bool valid = false; //是否有效
	Entry() {}
	Entry(Text t, Key k) : text(t), key(k) {}
};

const int M = 5010013;			//足够大的质数
Entry ht[M];					//哈希表
unsigned char txt[M][9] = {{}}; //管理已插入明文
const unsigned char letter[] = "0123456789tsinghua";
unsigned char salt[5];
unsigned int slen;			//salt长度
unsigned char beg[9] = {0}; //前8条明文首字母
int N = 0, suc = 0;			//词条数、查询成功次数

//参考讲义实现
//线性试探
int probe(Key k)
{
	int r = k % M;
	while (ht[r].valid && ht[r].key != k)
		r = (r + 1) % M;
	return r;
}

//插入词条
bool put(Text t, unsigned int len, Key prefix = 0)
{
	Key k1 = crc32(prefix, t, len);
	Text csalt = salt;
	Key k = crc32(k1, csalt, slen);
	int r = probe(k);
	if (ht[r].valid)
	{
		bool flag = true;
		int len2 = strlen((char*)ht[r].text);
		int minl = min((int)len, len2);
		for (int i = 0; i < minl; i++)
		{
			if (t[i] != ht[r].text[i])
			{
				flag = false;
				break;
			}
		}
		if (len != len2 || !flag)
			ht[r].dup = true;
		return false;
	} //判断明文是否相同,设置重复标记
	for (int i = 0; i < len; i++)
		txt[N][i] = t[i];
	ht[r] = Entry(txt[N], k);
	ht[r].valid = true;
	N++;
	return true;
}

Entry *get(Key k)
{
	int r = probe(k);
	if (ht[r].valid)
		return &ht[r];
	return nullptr; //密码本中不存在
}

//初始化密码本
void init()
{
	unsigned char init[6];
	int sup = pow(18, 5);
	for (int cnt = 0; cnt < sup; cnt++)
	{
		int a = sup, b = sup / 18;
		for (int i = 0; i < 5; i++)
		{
			init[i] = letter[(cnt % a) / b];
			a /= 18;
			b /= 18;
		} //遍历5位明文
		for (int i = 0; i < 5; i++)
		{
			if (cnt % a == 0)
				put(init, 5 - i);
			a *= 18;
		} //记入密码本
	}
}

//查询
void query(Key k)
{
	Entry *ans = get(k);
	if (!ans)
	{
		printf("No\n");
		return;
	}
	if (ans->dup)
	{
		printf("Duplicate\n");
		return;
	}
	printf("%s\n", ans->text);
	suc++;
	memmove(beg, beg + 1, 7);
	beg[7] = ans->text[0];
	int entnum = min(suc - 5, 3); //增加条目个数
	for (int i = 0; i < entnum; i++)
		put(beg + 2 - i, 6 + i); //增加条目
}

int main()
{
	ios::sync_with_stdio(false);
	int num;
	cin >> num;
	cin >> salt;
	slen = strlen((const char *)salt);
	init();
	for (int i = 0; i < num; i++)
	{
		char input[9];
		cin >> input;
		Key k = strtoul(input, 0, 16);
		query(k);
	}
	return 0;
}
