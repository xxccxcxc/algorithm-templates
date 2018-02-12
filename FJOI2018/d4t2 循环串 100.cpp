/*
luoguU19961 day4T2 循环串(string) 100pts

题意：定义长度为n，最小循环节长度为m的字符串的价值为n^2/m，
给定一个只包含abc的字符串，求字符串的子序列的最大价值 

解法：根据抽屉原理，至少有一个字母出现超过n/3次
把这个字母单独拉出来，价值为n^2/9，所以我们只要处理长度<=8的循环节
如果循环节中存在字母出现>=3次，设循环节出现次数为k
那把这个字母拉出来，价值为9k^2，而原来价值至多为8k^2
所以我们只要枚举每个字母出现<=2次的循环节 
该结论可以推广，8改成m*m-1，2改成m-1 
*/ 
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+50, M = 4;
long long ans;
int n, m = 3, cnt[M];
char s[N], t[M*M];

void Calc(int top) {
	int k = 0;
	for (int i = 1, j = 1; i <= n; i++)
		if (s[i] == t[j])
			if (j == top) j = 1, k++;
			else j++;
	ans = max(ans, 1LL * k * k * top);
}

void Dfs(int u) {
	for (int i = 0; i < m; i++) {
		if (cnt[i] + 1 >= m) continue;  // cnt要加上当前字母 
		cnt[i]++;
		t[u] = 'a' + i;
		Calc(u);
		Dfs(u + 1);
		cnt[i]--;
	}
}

int main() {
	ios::sync_with_stdio(false);
	int T; cin >> T;
	while (T--) {
		cin >> n >> (s+1);
		ans = (n-1)/m+1;  // 抽屉原理要上取整 
		ans *= ans;
		Dfs(1);
		cout << ans << endl;
	}
    return 0;
}

