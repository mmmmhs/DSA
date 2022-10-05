/* ����������
���ɲ���������ȡ��������������в���:
����0����������avl���Ĳ���,����1������������չ���Ĳ��� 
�����input.txt�� */

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <random>
#include <ctime>
using namespace std;

const int access_num = 50; //�������Ͻ�
const int sup = 8500000; //���ݴ�С�Ͻ�
const long long n = 10000000; //������
set<int> data_insert; //��¼����,��ֹ�ظ�����
vector<int> data_access; //�ɷ�������

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

//����������avl���Ĳ���:��ȫ���
void testAvl(){
	freopen("input.txt", "w", stdout);
	printf("%64d\n", n);
	for(long long i = 0; i < n; i++){
		if(data_insert.empty())//Ϊ��ʱ��ɾ��
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
			//����:��ѯ:ɾ�� = 99:99:2			
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
		data_access.push_back(num);//����������������
}

void searchSplay(long long i)
{
	printf("C %d \n", data_access[i]); //����ڷ��ʷ�Χ��
}

//���������չ���Ĳ���:�ظ�����һ��������
void testSplay(){
	freopen("input.txt", "w", stdout);
	printf("%64d\n", n);
	int t = n / 10000;
	int accbeg = randint() % t;
	for(int i = 0; i < t; i++)
		insertSplay(i, accbeg);
	for(int i = 0; i < access_num; i++)
	{
		long long j = (n - t) / access_num - 1; //ÿ�ַ��ʴ���
		while(j--)
			searchSplay(i); //ÿ�̶ֹ�����һ����
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