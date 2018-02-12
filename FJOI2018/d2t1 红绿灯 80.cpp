/*
luoguU19764 day2T1 红绿灯(light) 80pts

题意：n个路口，绿灯g秒红灯r秒，q个询问，询问从时间t出发到达终点的最短时间 

解法：f[i]表示从i点绿灯刚开始时走到终点的最短用时
f[i]用逆序dp求：从i点开始走，直到在j点遇到红灯
f[i]=dis(i,j)+等红灯时间+f[j]
求ans也是类似，走到第一个红灯i，ans=dis(0,i)+wait+f[i]
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 5e4+50;
int n;
LL g, r, d[N], f[N];

void Init() {
	for (int i = n; i; i--) {
		for (int j = i+1; j <= n+1; j++) {
			f[i] += d[j];
			if (j <= n && f[i] % (g+r) >= g) {
				//绿灯时刻为g+r，所以要等的时间为g+r-到达时间 
				f[i] += g+r-f[i]%(g+r) + f[j];
				break;
			}
		}
	}
}

LL Solve(LL st) {
	LL ans = st;
	for (int i = 1; i <= n+1; i++) {
		ans += d[i];
		if (i <= n && ans%(g+r) >= g) {
			// 同上 
			ans += g+r-ans%(g+r) + f[i];
			break;
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> g >> r;
	for (int i = 1; i <= n+1; i++)
		cin >> d[i];
	Init();
	int q; cin >> q;
	for (LL r; q--; ) {
		cin >> r;
		cout << Solve(r) << endl;
	}
    return 0;
}

