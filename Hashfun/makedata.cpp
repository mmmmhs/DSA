//utf-8
/*数据生成器
命令行参数: 
argv[1] == "1"或"2"(1表示使用poj.txt数据,2表示使用hdu.txt数据)
argv[2]为插入次数 argv[3]为查询次数*/

/*生成实验数据命令：
.\makedata 1 4000 20000 > 1_1.in
.\makedata 1 12000 12000 > 1_2.in 
.\makedata 1 20000 4000 > 1_3.in  
.\makedata 2 4000 20000 > 2_1.in
.\makedata 2 12000 12000 > 2_2.in 
.\makedata 2 20000 4000 > 2_3.in
*/

#include <vector>
#include <set>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
using namespace std;

struct Entry
{
	char str[40];
	int num;
} hashdata[610000];

int total;
set<int> set_inserted;
vector<int> vec_inserted;

int randint()
{
	return (long long) rand() * RAND_MAX + rand();
}

void insert(){
	ios::sync_with_stdio(false);
	int rank = randint() % total;
	while(set_inserted.count(rank))
		rank = randint() % total;
	cout << "0 " << hashdata[rank].str << " " << hashdata[rank].num << "\n";
	set_inserted.insert(rank);
	vec_inserted.push_back(rank);
}

void query(){
	ios::sync_with_stdio(false);
	int rank = randint() % vec_inserted.size();
	cout << "1 " << hashdata[vec_inserted[rank]].str << "\n";
}

int main(int argc, char** argv){
	ios::sync_with_stdio(false);
	srand(time(0));
	if(argc > 3)
	{
		if(argv[1][0] == '1'){
			freopen("poj.txt", "r", stdin);
			total = 500000;
			for(int i = 0; i < total; i++)
			{
				int a, b;
				cin >> a >> hashdata[i].str >> hashdata[i].num >> b;
			}
		}
		else if(argv[1][0] == '2'){
			freopen("hdu.txt", "r", stdin);
			total = 606677;
			for(int i = 0; i < total; i++)
			{
				int a, b;
				cin >> a >> hashdata[i].str >> hashdata[i].num >> b;
			}
		}
		int it = atoi(argv[2]); //插入次数
		int qt = atoi(argv[3]); //查询次数
		while (it > 0 && qt > 0)
		{
			if(set_inserted.empty()){
				insert();
				it--;
				continue;
			}
			int type = rand() % 2;
			if(type == 0) 
			{
				insert();
				it--;
			}	
			else 
			{
				query();
				qt--;
			}	
		}
		while(it > 0)
		{
			insert();
			it--;
		}
		while (qt > 0)
		{
			query();
			qt--;
		}
		cout << "2\n";
	}
	return 0;
}