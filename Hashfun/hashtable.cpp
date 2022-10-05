#include <cstring>
#include "hashtable.h"
typedef unsigned char uc;
typedef unsigned long long ull;
typedef unsigned int uint;

int naive_hashing::operator()(char *str, int N)
{
	if (str == NULL)
		return 0;
	else
		return (str[0] + N) % N;
}

int ascii_hashing::operator()(char *str, int N)
{
	if (str == nullptr)
		return 0;
	int len = strlen(str);
	uint ans = 0;
	for (int i = 0; i < len; i++)
		ans += (uint)((uc)str[i] << (len - i - 1)); //采用2进制多项式哈希
	return ans % N;
}

int utf8_hashing::operator()(char *str, int N){
	if (str == nullptr)
		return 0;
	int len = strlen(str);
	ull ans = 0;
	int i = 0, j = 0;//字节数、字符数
	while (i < len)
	{
		if((uc)str[i] >> 7 == 0){
			ans += (ull)(((uc)str[i] % (1 << 7)) << j);
			i++;
		}
		else if((uc)str[i] >> 5 == 6){
			ans += (ull)(((uc)str[i] % (1 << 5) + (uc)str[i + 1] % (1 << 6)) << j);
			i += 2;
		}
		else if((uc)str[i] >> 4 == 14){
			ans += (ull)(((uc)str[i] % (1 << 4) + (uc)str[i + 1] % (1 << 6) + (uc)str[i + 2] % (1 << 6)) << j);
			i += 3;
		}
		j++;	
	}
	return ans % N;
}

int linear_probe::operator()(hash_entry *Table, int table_size, int last_choice)
{
	return (last_choice + 1) % table_size;
}
void linear_probe::init()
{
	return; // do nothing
}

int dblsqr_probe::operator()(hash_entry *Table, int table_size, int last_choice)
{
	if(dir)
	{
		int ans = (last_choice + t * t + (t + 1) * (t + 1)) % table_size;
		t++;
		dir = false;
		return ans;
	}	
	else
	{
		dir = true;
		int tmp = last_choice - 2 * t * t;
		while (tmp < 0)
			tmp += table_size;
		return tmp % table_size;
	}
}
void dblsqr_probe::init()
{
	t = 0;
	dir = true;
}

int ofarea_probe::operator()(hash_entry *Table, int table_size, int last_choice)
{
	if(last_choice < table_size / 2) return table_size / 2;
	return (last_choice + 1) % (table_size / 2) + table_size / 2;
}
void ofarea_probe::init()
{
	return; // do nothing
}
