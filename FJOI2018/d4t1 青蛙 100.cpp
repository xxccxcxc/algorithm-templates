/*
luoguU19958 day4T1 青蛙(frog) 100pts

题意：k个石头排成一排，m只青蛙从1跳到n，每个石头必须恰好被跳一次
每当第i只青蛙跳的距离大于d，就要支付一次c[i]的费用。最小化总费用

解法：首先处理出最多有多少只青蛙可以免费到达，记为p
若p>0则最优方法是免费的把石头都覆盖了，剩余m-p只直接从1跳到n
若p=0则最优方法是c[i]最小的青蛙把1~n全跳一遍，剩下直接从1跳到n
求p方法是贪心，每只青蛙跳到能跳的最右边的点 
具体地，对于每个i，求出dis(i,j)<=d的最大的j，那么想跳到j+1必须通过[i+1,j]这j-i块石头
于是对每个i求min(j-i)即为p，而随着i递增j也递增，复杂度O(n) 
*/ 
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+50;
int cost[N], pos[N];
int main() {
	ios::sync_with_stdio(false);
	int T; cin >> T;
	for (int n, m, k, d; T--; ) {
		cin >> n >> m >> k >> d;
		for (int i = 1; i <= m; i++)
			cin >> cost[i];
		for (int i = 1; i <= k; i++)
			cin >> pos[i];
		sort(cost + 1, cost + m + 1);
		sort(pos + 1, pos + k + 1); 
		pos[0] = 1; pos[k+1] = n;
		int far = 0;
		for (int i = 0; i <= k; i++)
			if (pos[i+1] - pos[i] > d) far++;
		long long ans = 0;
		if (far) {  // 没有能免费到达的青蛙 
			ans = 1LL * far * cost[1];  // 费用最小的青蛙全跳一遍 
			for (int i = 2; i <= m; i++)
				ans += cost[i];  // 其余从1飞到n 
		} else {
			int free = m;
			for (int l = 0, r = 0; l <= k; l++) {
				while (r <= k && pos[r+1] - pos[l] <= d) r++;
				if (r == k + 1) break;
				free = min(free, r - l);  // p=min{r-l} 
			}
			for (int i = 1; i <= m - free; i++)
				ans += cost[i];  // 剩下m-p只青蛙从1飞到n 
		}
		cout << ans << endl;
	}
    return 0;
}

