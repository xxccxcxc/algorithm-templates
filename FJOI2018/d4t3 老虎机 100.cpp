/*
luoguU19964 day4T3 老虎机(slot) 100pts

题意：n个老虎机里面有Li个球，每个球有颜色
求最坏情况下要用多少个硬币才能拿到两个颜色相同的球

解法：先讨论两个球来自同一个机器的情况，方案数为
min{颜色有重复的机器的颜色数+1}
接下来讨论两个球来自不同机器，就可以先去个重
设f(i,j)表示机器i上第j个球在其他机器被拿出来的最小步数
那么机器一定会按f递减的顺序吐球
把每个机器上的f降序排序，则ans=min{j+f(i,j)} 
f(i,j)可以通过处理取出每个颜色的球步数的最小值和次小值得到 
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+50, INF = 0x3f3f3f3f;
int min1[N], min2[N], siz[N], f[N];
vector<int> a[N];
int main() {
	ios::sync_with_stdio(false);
	int T; cin >> T;
	while (T--) {
		int ans = INF;
		memset(min1, 0x3f, sizeof(min1));
		memset(min2, 0x3f, sizeof(min2));
		int n; cin >> n;
		for (int i = 1; i <= n; i++) {
			a[i].clear();
			cin >> siz[i];
			for (int j = 0, r; j < siz[i]; j++)
				cin >> r, a[i].push_back(r);
			sort(a[i].begin(), a[i].end());
			int k = unique(a[i].begin(), a[i].end()) - a[i].begin();
			if (k < siz[i]) {  // 两个球可能来自同一个机器 
				ans = min(ans, k + 1);
				siz[i] = k;
			}
			for (int j = 0; j < siz[i]; j++) {
				// 处理颜色步数最小值和次小值 
				if (siz[i] < min1[a[i][j]])
					min2[a[i][j]] = min1[a[i][j]], min1[a[i][j]] = siz[i];
				else min2[a[i][j]] = min(min2[a[i][j]], siz[i]);
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < siz[i]; j++) {
				if (siz[i] == min1[a[i][j]])
					f[j] = min2[a[i][j]];
				else f[j] = min1[a[i][j]];
			}
			// 算出f并排序 
			sort(f, f + siz[i], greater<int>());
			for (int j = 0; j < siz[i]; j++)
				ans = min(ans, j+1+f[j]);  // 因为下标从0开始，要记得+1 
		}
		cout << ans << endl;
	}
    return 0;
}

