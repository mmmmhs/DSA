#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int n, m, k;
string a, b;
int matrix[110][502000] = {0};//dp[i + j][j]存储在matrix[i - inf][j]中

int solve(){
	int inf = -((m - n + k) / 2);//i的下界
	int sup = (n - m + k) / 2;//i的上界
	for(int j = 0; j <= m; j++)
	{
		int i = max(inf, -j);//i + j >= 0
		while((i <= sup) && (i + j <= n))
		{
			if(j == 0)
				matrix[i - inf][j] = i;
			else if(i + j == 0)
				matrix[i - inf][j] = j;
			else if(a[i + j] == b[j])
				matrix[i - inf][j] = matrix[i - inf][j - 1];
			else if(i == inf)
				matrix[i - inf][j] = k + 1;//越界值	
			else if(i == sup)
				matrix[i - inf][j] = matrix[i - 1 - inf][j] + 1;//不考虑matrix[i + 1 - inf][j - 1]	
			else 
				matrix[i - inf][j] = min(matrix[i - 1 - inf][j], matrix[i + 1 - inf][j - 1]) + 1;  
			i++;			
		}
	}
	if(matrix[n - m - inf][m] <= k)
		return matrix[n - m - inf][m];
	else 
		return -1;	
}

int main(){
	cin >> n >> m >> k;
	cin >> a;
	cin >> b;	
	if(abs(n - m) > k)
		cout << -1;//若两字符串长度相差超过k则必然失败
	else
		cout << solve();	
	return 0;		
}