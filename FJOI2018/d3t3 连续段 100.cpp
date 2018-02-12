/*
luoguU19869 day3T3 连续段(interval) 100pts

题意：定义连续区间为将区间排序后得到的是一段连续的数
每次询问给出区间[x,y]，求包含[x,y]的最小连续区间[l,r]

解法：复杂度玄学的分块
扩展操作为查询[l,r]的值域[mi,mx]，再查询[mi,mx]的位置极值[newl,newr]（通过预处理RMQ完成） 
合并操作为对l和r分别取min和max
先预处理出每两块之间的答案
具体是先确定左端的块l，然后向右逐块先合并再扩展
查询时，若[l,r]包含的整块的答案[tl,tr]包含[l,r]，则[tl,tr]即为最终答案
合法性：[tl,tr]包含[l,r]且为连续区间
最优性：[tl,tr]是比[l,r]小的一段区间的最优解，[l,r]的最优解不可能比这更优
如果[tl,tr]不包含[l,r]，则对这两个区间进行合并与拓展，更新[l,r]，重复以上操作
询问的复杂度不会证，听说是n*sqrt(n)，反正跑的很快 
*/ 
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+50, LOGN = 22, B = 350;

struct Range {
	int l, r;
	Range(int _l=N-1, int _r=0): l(_l), r(_r) {}  // 初值[N,0]，方便合并时取min和max 
	Range operator + (const Range &t) const { return Range(min(l, t.l), max(r, t.r)); }  // 合并 
	Range operator += (const Range &t) { return *this = *this + t; }
	bool operator == (const Range &t) const { return l == t.l && r == t.r; }
	bool operator != (const Range &t) const { return !(*this == t); }
};

int bin[LOGN], lo[N];
int n, siz, m, num[N], bl[N];
Range body[B], ans[B][B];
int lb[N], rb[N];

struct Rmq {
	int a[N];
	Range f[N][LOGN];
	
	void Init() {
		for (int i = 1; i <= n; i++)
			f[i][0] = Range(a[i], a[i]);
		for (int j = 1; bin[j] <= n; j++)
			for (int i = 1; i <= n-bin[j-1]+1; i++)
				f[i][j] = f[i][j-1] + f[i+bin[j-1]][j-1];
				// 合并区间，相当于同时处理min和max 
	}
	
	Range Query(Range q) {
		int k = lo[q.r-q.l+1];
		return f[q.l][k] + f[q.r-bin[k]+1][k];
	}
} q1, q2;  // q1查询位置区间的值域，q2查询值区间的位置域 

Range Extend(const Range &x) {  // 扩展 
	return q2.Query(q1.Query(x));
}

int main() {
	ios::sync_with_stdio(false);
	bin[0] = 1; for (int i = 1; i < LOGN; i++) bin[i] = bin[i-1] << 1;
	lo[0] = -1; for (int i = 1; i < N; i++) lo[i] = lo[i>>1] + 1;
	cin >> n; siz = sqrt(n);
	for (int i = 1; i <= n; i++) {
		cin >> num[i];
		q1.a[i] = num[i];
		q2.a[num[i]] = i;
	}
	q1.Init(); q2.Init();
	for (int i = 1; i <= n; i++)
		bl[i] = (i-1)/siz+1;
	m = bl[n];
	for (int i = 1; i <= m; i++)
		body[i] = Range((i-1)*siz+1, min(i*siz, n));
	for (int l = 1; l <= m; l++) {
		Range x = body[l], y;
		while ((y = Extend(x)) != x) x = y; 
		ans[l][l] = x;
		for (int r = l+1; r <= m; r++) {
			y = x + body[r];  // 合并新块 
			while (y != x) x = y, y = Extend(x);  // 并进行扩展 
			ans[l][r] = x;  // 得到新的答案 
		}
	}
	for (int i = 1; i <= n; i++) {
		lb[i] = bl[i]; if (i != body[bl[i]].l) lb[i]++;
		rb[i] = bl[i]; if (i != body[bl[i]].r) rb[i]--;
		// 处理[l,r]包含的整块区间的左端点和右端点 
	}
	int m; cin >> m;
	for (int l, r; m--; ) {
		cin >> l >> r;
		Range x(l, r), y;
		while (true) {
			y = ans[lb[x.l]][rb[x.r]];
			if (y.l <= x.l && x.r <= y.r) {
				// 若[tl,tr]包含[l,r]，则答案为[tl,tr] 
				x = y;
				break;
			}
			x += y;
			if ((y = Extend(x)) == x) break;
			x = y;
			// 合并、扩展与更新区间 
		}
		printf("%d %d\n", x.l, x.r);
	}
    return 0;
}

