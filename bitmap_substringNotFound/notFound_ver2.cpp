#include <iostream>
#include <string.h>
using namespace std;

//参考讲义实现
//位图
class Bitmap
{
private:
	int N;
	char *M;

public:
	Bitmap() { M = nullptr; }
	Bitmap(int n)
	{
		N = (n + 7) / 8;
		M = new char[N];
		memset(M, 0, N);
	}
	void set(int k) { M[k >> 3] |= (0x80 >> (k & 0x07)); }
	bool test(int k) { return M[k >> 3] & (0x80 >> (k & 0x07)); }
	void clear(int k) { M[k >> 3] &= ~(0x80 >> (k & 0x07)); }
};

char str[24];  //输入的前24位
int toSet = 0; //01串对应整数
int len = 24;  //输入长度与24之间的较小者
Bitmap bm[24]; //bm[i]记录i+1长度子串出现情况

//输出num对应的l位01串
void output(int l, int num)
{
	char res[(const int)l + 1];
	for (int i = 0; i < l; i++)
	{
		if (num & (1 << (l - i - 1)))
			res[i] = '1';
		else
			res[i] = '0';
	}
	res[l] = '\0';
	cout << res << endl;
}

//从n + 1位子串出现情况获得n位子串出现情况
void setNextBM(int n)
{
	for (int i = 0; i < (1 << (n + 1)); i++)
	{
		if (bm[n].test(i))
		{
			bm[n - 1].set(i >> 1);
			bm[n - 1].set(i % (1 << n));
		}
	}
}

int main()
{
	for (int i = 0; i < 24; i++)
		bm[i] = Bitmap(1 << (i + 1));
	for (int i = 0; i < 24; i++)
	{
		char c = getchar();
		if (c != '\n')
			str[i] = c;
		else
		{
			len = i;
			break;
		}
	}
	for (int i = 0; i < len; i++)
	{
		if (str[i] == '1')
			toSet += (1 << (len - i - 1));
	}
	bm[len - 1].set(toSet); //处理初始字符串,防止长度小于24
	if (len == 24)
	{
		char c;
		while ((c = getchar()) != '\n')
		{
			toSet = (toSet % (1 << 23)) << 1;
			if (c == '1')
				toSet++;
			bm[23].set(toSet);
		}
	} //若字符串超过24位,遍历所有24位子串, O(n)
	for (int i = len - 1; i > 0; i--)
		setNextBM(i);
	bool stop = false;
	for (int i = 0; i < 24; i++)
	{
		if (stop)
			break;
		for (int j = 0; j < (1 << (i + 1)); j++)
		{
			if (!bm[i].test(j))
			{
				output(i + 1, j);
				stop = true;
				break;
			}
		}
	}
	return 0;
}
