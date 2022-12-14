# PA 1-3 filename 解题报告

## 1.数据结构 ##

二维数组

## 2.算法原理 ##

使用动态规划算法。设`dp[x][y]`表示A字符串前x位的子串与B字符串前y位子串之间的修改代价，则所求即为`dp[n][m]`。二维数组`dp`满足以下状态转移方程：
$$
dp[x][y]=\begin{cases}
x, \quad y=0\\
y, \quad x=0\\
dp[x-1][y-1], \quad xy \ne 0且A[x]=B[y]\\
min(dp[x-1][y], \ dp[x][y-1])+1, \quad xy \ne 0且A[x] \ne B[y]\\
\end{cases}
$$
然而，如果通过动态规划求`dp[n][m]`的值则时间复杂度为`O(mn)`，不满足题目要求。因此，为减小复杂度，需要考虑修改代价不超过k的限制。由上式可知如果`x * y != 0 && A[x] != B[y] `的情况在由`dp[0][0]`到达`dp[n][m]`的过程中出现k次以上则答案必不满足要求，可以舍去。观察可知这种情况必然伴随着二维数组下标之差`x - y`的变化，因此若`dp[x][y]`在求解范围之内，考虑从(0, 0)到(n, m)经由(x, y)的轨迹，应当有
$$
|x-y-0|+|(x-y)-(n-m)|\leq k
$$
解得
$$
-(m-n+k)/2\ \leq\ x-y\ \leq\ (n-m+k)/2
$$
(前提是`|n - m| <= k`；若此不等式不成立，则答案必超过k，可直接舍去。)

注意到`x - y`的范围宽度恰好为k，因此如果进行换元，以`i`表示`x - y`，`j`表示`y`，则可在一一对应的基础上将矩阵规模与时间复杂度缩小为`O(km)`。由于`x - y`可能为负数，因此将其减去下界`inf = -(m-n+k)/2`实现平移以保证数组下标范围正确，即：
$$
matrix[i - inf][j] := dp[i + j][j]
$$
此时，状态转移方程变为
$$
matrix[i - inf][j]=\begin{cases}
i, \quad j=0\\
j, \quad i+j=0\\
matrix[i - inf][j - 1], \quad j(i + j) \ne 0且A[i + j]=B[j] \quad (1)\\
min(matrix[i - 1 - inf][j], matrix[i + 1 - inf][j - 1]) + 1,
\quad j(i + j) \ne 0且A[i + j] \ne B[j]\quad (2)\\
\end{cases}
$$
为实现操作、访问顺序正确，外循环应为`j`的遍历，而内循环为`i`的遍历；在`i`为下界时，只能通过上式中(1)得到，否则应置为越界值；在`i`为上界时，上式(2)中`matrix[i + 1 - inf][j - 1]`应被视为越界值而不予考虑。

## 3.实现要点 ##

(1)动态规划状态转移方程的构造
(2)复杂度的减小
(3)越界访问的规避

(均在**2.**中)

## 4.解题过程中的问题与技巧

最初未考虑到越界访问问题，在使用对拍程序调试后发现并修改。

## 5.复杂度分析 ##

由**2.**可知，得到答案的过程等同于构造`k*m`矩阵的过程，因此时间、空间复杂度均为`O(km)`。



