#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 1e5+50, MX = 2e5+50;

struct BIT {
	int n, a[MX];
	
	void Init(int _n) { n = _n; }
	int Lowbit(int x) { return x & -x; }
	
	void Add(int pos, int val) {
		for (int u = pos; u <= n; u += Lowbit(u))
			a[u] += val;
	}
	
	int Query(int pos) {
		int ret = 0;
		for (int u = pos; u; u -= Lowbit(u))
			ret += a[u];
		return ret;
	}
	
	int Query(int l, int r) {
		return Query(r) - Query(l - 1);
	}
} bit;

struct Data {
	int a, b, c, cnt, ans;
	void Input() { scanf("%d%d%d", &a, &b, &c); }
	bool operator < (const Data &t) const {
		return a != t.a ? a < t.a : b != t.b ? b < t.b : c < t.c;
	}
	bool operator != (const Data &t) const {
		return a != t.a || b != t.b || c != t.c;
	}
} data[N], tmp[N];

void CDQ(int l, int r) {
	if (l == r) { data[l].ans += data[l].cnt - 1; return; }
	int mid = l + r >> 1;
	CDQ(l, mid); CDQ(mid + 1, r);  // 统计左右区间内自己的影响
	// 类似归并排序，统计左区间的修改对右区间的询问的影响。 
	int pl = l, pr = mid + 1, top = 0;
	while (pl <= mid && pr <= r)
		if (data[pl].b <= data[pr].b) {
			bit.Add(data[pl].c, data[pl].cnt);
			tmp[top++] = data[pl++];
		} else {
			data[pr].ans += bit.Query(data[pr].c);
			tmp[top++] = data[pr++];
		}
	while (pr <= r) {
		data[pr].ans += bit.Query(data[pr].c);
		tmp[top++] = data[pr++];
	}
	for (int i = l; i < pl; i++) bit.Add(data[i].c, -data[i].cnt);
	while (pl <= mid) tmp[top++] = data[pl++];
	for (int i = 0; i < top; i++) data[l+i] = tmp[i];
}

int f[N];

int main() {
	int n, mx; scanf("%d%d", &n, &mx); bit.Init(mx);
	for (int i = 1; i <= n; i++) data[i].Input();
	sort(data + 1, data + n + 1);  // 按时间轴排序 
	int top = 0;
	for (int i = 1; i <= n; i++) {
		if (i == 1 || data[i] != data[i-1])
			data[++top] = data[i];
		data[top].cnt++;
	}
	CDQ(1, top);
	for (int i = 1; i <= n; i++) f[data[i].ans] += data[i].cnt;
	for (int i = 0; i < n; i++) printf("%d\n", f[i]);
	return 0;
}

