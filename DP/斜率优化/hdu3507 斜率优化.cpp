#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 500050;
int n, m, s[N], f[N];
int q[N], h, t;

int getx(int j, int k) { return 2 * (s[j] - s[k]); }
int gety(int j, int k) { return f[j] + s[j] * s[j] - (f[k] + s[k] * s[k]); }
int getf(int i, int j) { return f[j] + m + (s[i] - s[j]) * (s[i] - s[j]); }

int main() {
	/*
	题意：将n个数分成若干段，每段花费为这段数的和的平方加常数m，求最小花费
	f[i]=f[j]+m+(s[i]-s[j])*(s[i]-s[j])
	设k<j，若j比k优，则： 
	f[i]-2*s[i]*s[j]+s[j]*s[j]-(f[k]-2*s[i]*s[k]+s[k]*s[k])<=0
	化简得((f[j]+s[j]*s[j])-(f[k]+s[k]*s[k]))/(2*(s[j]-s[k]))<=s[i]
	设y[i]=f[i]+s[i]*s[i], x[i]=2*s[i]，
	则原式变为(y[j]-y[k])/(x[j]-x[k])<=s[i]
	左边可以看成斜率式，设i<j, i,j斜率为g[i][j]
	则若k<j且g[k][j]<=s[i]，则j比k优
	设k<j<i，若g[k][j]>g[j][i]，则j点无用
	因为若g[j][i]<=s，则i比j优，j无用
	若g[j][i]>s，则j比i优，而g[k][j]>g[j][i]>s，则k比j优，j无用
	所以维护一个斜率单调递增的下凸壳，又因为s是前缀和，单调递增，
	所以每次从队首开始，把g<s的都删掉，剩下的队首就是最优决策点
	然后从队尾插入新元素，维护单调性 
	*/
	while (scanf("%d%d", &n, &m) == 2) {
		h = 0; q[t = 0] = 0;
		for (int i = 1, tmp; i <= n; i++) {
			s[i] = s[i-1] + (scanf("%d", &tmp), tmp);
			while (h < t && gety(q[h+1], q[h]) <= s[i] * getx(q[h+1], q[h])) ++h;
			f[i] = getf(i, q[h]);
			while (h < t && gety(q[t], q[t-1]) * getx(i, q[t]) >= gety(i, q[t]) * getx(q[t], q[t-1])) --t;
			q[++t] = i;
		}
		printf("%d\n", f[n]);
	}
	return 0;
}

