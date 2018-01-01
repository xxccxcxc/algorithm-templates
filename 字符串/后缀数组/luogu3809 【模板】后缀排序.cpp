#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 2e6+50;
char s[N];
int n, t[N], x[N], y[N], sa[N], rk[N], height[N];

void GetSA() {  // 求sa,rk,height数组 

	int m = 'z' + 5;  // m是桶排的上界，可变 
	
	// 先桶排，相当于把字符离散化一下 
	for (int i = 1; i <= n; i++) t[x[i] = s[i]]++;
	for (int i = 1; i <= m; i++) t[i] += t[i-1];
	for (int i = n; i >= 1; i--) sa[t[x[i]]--] = i;  // 倒序循环，保证排序稳定 
	
	for (int k = 1; ; k <<= 1) {  // k表示当前要排序的串长度/2 
		int cnt = 0;
		
		// y中存储待排序二元组的第一关键字的位置 
		// 后k个串没有第二关键字，优先级最高，先放进来 
		for (int i = n - k + 1; i <= n; i++) y[++cnt] = i;  
		
		// 有第二关键字的二元组，按第二关键字从小到大放进来，保证双关键字排序 
		for (int i = 1; i <= n; i++) if (sa[i] > k) y[++cnt] = sa[i] - k;
		
		// 对第一关键字进行桶排序（x中保存的是上一次排序的结果） 
		memset(t, 0, sizeof(int) * (m + 5));
		for (int i = 1; i <= n; i++) t[x[y[i]]]++;
		for (int i = 1; i <= m; i++) t[i] += t[i-1];
		for (int i = n; i >= 1; i--) sa[t[x[y[i]]]--] = y[i];
		
		// 把上次排序结果暂时放在y里（跟y的意义没关系），更新这次排序结果x 
		// 这个swap只是交换指针，既省空间又省时间 
		swap(x, y); x[sa[1]] = cnt = 1;
		for (int i = 2; i <= n; i++)
			// 如果串相同则结果相同 
			x[sa[i]] = y[sa[i]] == y[sa[i-1]] && y[sa[i]+k] == y[sa[i-1]+k] ? cnt : ++cnt;
		
		// 更新桶排上界（即不同的元素个数），若上界为n则已经排好序，没必要继续做 
		if ((m = cnt) >= n) break;
	}
	
	// 顺便求一下rk和height（虽然这题没用到） 
	for (int i = 1; i <= n; i++) rk[sa[i]] = i;
	
	// height[i]>=height[i的前一名]-1，利用这个性质O(n)计算 
	for (int i = 1, k = 0, j; i <= n; height[rk[i++]] = k)
		for (k = k ? k - 1 : k, j = sa[rk[i]-1]; s[i+k] == s[j+k]; k++);
}

/*
题意：把字符串的所有非空后缀按字典序从小到大排序，然后按顺序输出后缀的第一个字符在原串中的位置
（即求sa数组） 
*/
int main() { 
	scanf("%s", s + 1); n = strlen(s + 1);
	GetSA();
	for (int i = 1; i <= n; i++)
		printf("%d ", sa[i]);
	putchar('\n');
    return 0;
}

