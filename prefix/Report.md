# PA 3-5 Prefix 解题报告

## 1.数据结构 ##

+ 数组

## 2.算法原理 ##

1. 欲求字符串所有前缀出现的次数总和，由于每一位前缀本身会出现一次，所以前缀出现次数总和 = 字符串长度(即前缀个数) + 前缀重复次数。问题转化为求各前缀重复次数。
2. 考虑KMP算法中的next表，next[i] == j表示字符串中[0, i - 1]这一子串中最长的"真前缀 = 真后缀"长度为j，即[0, j - 1]这一前缀在[i - j, i - 1]重复出现。但由于j为这样的前缀长度最大值，这里并未考虑到多个前缀重复的情况：如`aabaab`这一字符串中，`aa`的重复出现包含着`a`的重复出现。
3. 由于j为长度最大值，重复出现的前缀必然包括在j长前缀中。因此可以递归地考虑next[j]，next[next[j]] ... 所有因前缀相包含而一同重复出现的前缀长度均应在此序列中。将这一从j出发一直到0为止(不包括0)的序列称为next链，则由于j长前缀的重复出现，重复的前缀个数即等于next链的长度。因此前缀重复次数即为每一位next链长度之和。

## 3.实现要点 ##

使用动态规划避免递归。具体地，以nl[]数组记录每一位next链长度。

在建立next表的过程中，如果出现next[i] = j，则表明i位next链在j位的基础上增加一位，即nl[i] = nl[j] + 1.

求得nl[]值时将其加入累加变量即可，最终将累加值加上字符串长度即为答案。

## 4.解题过程中的问题与技巧

+ 最初累加变量使用int，出现超限。改为long long后正确。

## 5.复杂度分析 ##

(1)时间复杂度

与KMP算法建立next[]表的时间复杂度一致，为O(n).

(2)空间复杂度

产生空间复杂度的因素为next表与用于记录next链长度的数组，共计O(n).

## 6.参考资料

参考讲义建立next表算法实现。