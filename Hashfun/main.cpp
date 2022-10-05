#include <cstdio>
#include <ctime>
#include <fstream>
#include "hashtable.h"
using namespace std;

int main(int argc, char** argv)
{
	if(argc > 2){
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
	}
	int type;
	char buffer[1000];
	int data;
	hashing_strategy* hs = new naive_hashing();
	collision_strategy* cs = new linear_probe();
	if(argc > 4){
		if (argv[3][0] == '2')
			hs = new ascii_hashing();
		else if	(argv[3][0] == '3')
			hs = new utf8_hashing();
		if (argv[4][0] == '2')
			cs = new dblsqr_probe();
		else if (argv[4][0] == '3')
			cs = new ofarea_probe();		
	}
	hashtable table(41843, hs, cs);
	time_t beg, fin;
	beg = clock();
	while (true)
	{
		scanf("%d", &type);
		if (type == 0)
		{
			scanf("%s", buffer);
			scanf("%d", &data);
			table.insert(hash_entry(buffer, data));
		}
		else if (type == 1)
		{
			scanf("%s", buffer);
			printf("%d\n", table.query(buffer));
		}
		else break;
	}
	fin = clock();
	if(argc > 4){
		ofstream fout("time.txt", ios::app);
		fout << argv[1] << " hs = " << argv[3] << " cs = " << argv[4] << " time = " << fin - beg << "\n";
	}
	return 0;
}