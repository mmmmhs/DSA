#include <iostream>
#include <string.h>
using namespace std;

class Bitmap{
private: 
	int N;
	char* M;
public:
	Bitmap(){ M = nullptr; }
	Bitmap(int n){
		N = (n + 7) / 8;
		M = new char[N];
		memset(M, 0, N);
	}	
	~Bitmap(){
	    // delete [] M;
		// M = nullptr;
	}
	void set(int k){ M[k >> 3] |= (0x80 >> (k & 0x07)); }
	bool test(int k){ return M[k >> 3] & (0x80 >> (k & 0x07)); }
	void clear(int k){ M[k >> 3] &= ~(0x80 >> (k & 0x07));}
};

char str[24];
int setnum[24];
Bitmap bm[24];//bm[i]记录i+1长度子串出现情况

//得到长r的01串的二进制值, O(r)
int str2int(char* s, int r){
	int ans = 0;
	for(int i = 0; i < r; i++){
		if(s[i] == '1')
			ans += (1 << (r - i - 1));
	}
	return ans;	
}

//处理新读入的字符
void input(char c){
	memmove(str, str + 1, 23);
	str[23] = c;
	int total = str2int(str, 24);
	for(int i = 0; i < 24; i++)
		bm[i].set(total % (1 << (i + 1)));
}

//输出num对应的l位01串
void output(int l, int num){
	char res[l + 1];
	for(int i = 0; i < l; i++){
		if(num & (1 << (l - i - 1)))
			res[i] = '1';
		else res[i] = '0';	
	}
	res[l] = '\0';
	cout << res << endl;
}

int main(){
	for(int i = 0; i < 24; i++)
		bm[i] = Bitmap(1 << (i + 1));
	int len = 24;//输入长度与24之间的较小者	
	for(int i = 0; i < 24; i++){
		char c = getchar();
		if(c != '\n') str[i] = c;
		else 
		{
			len = i;
			break;
		}	
	}	
	for(int i = 1; i <= len; i++)//子串长
	{
		for(int j = 0; j <= len - i; j++)//开始位置
			bm[i - 1].set(str2int(str + j, i));
	}//遍历初始子串
	if(len == 24){
		char c;
		while((c = getchar()) != '\n'){
			input(c);
		}
	}
	bool stop = false;
	for(int i = 0; i < 24; i++){
		if(stop) break;
		for(int j = 0; j < (1 << (i + 1)); j++){
			if(!bm[i].test(j)){
				output(i + 1, j);
				stop = true; 
				break;
			}
		}
	}		
	return 0;
}
