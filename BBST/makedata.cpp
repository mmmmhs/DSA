/* 测例生成器
生成测例的类型取决于输入的命令行参数:
输入0生成适用于avl树的测例,输入1生成适用于伸展树的测例 
输出到input.txt中 */

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <random>
#include <ctime>
using namespace std;

const int access_num = 50; //访问量上界
const int sup = 8500000; //数据大小上界
const long long n = 10000000; //操作数
set<int> data_insert; //记录数据,防止重复插入
vector<int> data_access; //可访问数据

int randint(){
	return (long long) rand() * RAND_MAX + rand();
}

void insertAvl()
{
	int num = randint() % sup;
	while (data_insert.count(num))
		num = randint() % sup;	
	printf("A %d \n", num);						
	data_insert.insert(num);
	data_access.push_back(num);
}

void searchAvl()
{
	int num = randint() % sup;
	printf("C %d \n", num);
}

void remove()
{
	int num = randint() % data_access.size();
	printf("B %d \n", data_access[num]);
	data_insert.erase(data_insert.find(data_access[num]));
	data_access.erase(data_access.begin() + num);
}

//生成适用于avl树的测例:完全随机
void testAvl(){
	freopen("input.txt", "w", stdout);
	printf("%64d\n", n);
	for(long long i = 0; i < n; i++){
		if(data_insert.empty())//为空时不删除
		{
			int type = rand() % 2;
			if(type > 0)
				insertAvl();
			else
				searchAvl();
		}
		else
		{
			int type = rand() % 100;
			if(type > 0){
				if(type % 2)
					insertAvl();
				else
					searchAvl();
			}
			else
				remove();
			//插入:查询:删除 = 99:99:2			
		}
	}	
}

void insertSplay(int i, int beg)
{
	int num = randint() % sup;
	while (data_insert.count(num))
		num = randint() % sup;
	printf("A %d \n", num);						
	data_insert.insert(num);
	if(i - beg < access_num)
		data_access.push_back(num);//访问数据数量限制
}

void searchSplay(long long i)
{
	printf("C %d \n", data_access[i]); //结果在访问范围内
}

//生成针对伸展树的测例:重复访问一部分数据
void testSplay(){
	freopen("input.txt", "w", stdout);
	printf("%64d\n", n);
	int t = n / 10000;
	int accbeg = randint() % t;
	for(int i = 0; i < t; i++)
		insertSplay(i, accbeg);
	for(int i = 0; i < access_num; i++)
	{
		long long j = (n - t) / access_num - 1; //每轮访问次数
		while(j--)
			searchSplay(i); //每轮固定访问一个数
	}
	for(int i = 0; i < access_num; i++)
		remove();
}

int main(int argc, char** argv){
	srand(time(0));
	if(argc > 1){
		if(argv[1][0] == '0')
		{
			freopen("time.txt", "a", stdout);
			cout << "test avl" << endl;
			testAvl();
		}
		else if(argv[1][0] == '1')
		{
			freopen("time.txt", "a", stdout);
			cout << "test splay" << endl;
			testSplay();
		}
	}
	return 0;	
}