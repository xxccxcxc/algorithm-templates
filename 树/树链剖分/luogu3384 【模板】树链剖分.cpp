#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long LL;
const int N = 1e5+50;

struct Mint {
	static LL mod;
	LL x;
	
	Mint(LL _x=0) { x = (_x % mod + mod) % mod; }
	friend Mint operator + (const Mint &a, const Mint &b) { return Mint(a.x + b.x); }
	Mint operator += (const Mint &b) { return *this = *this + b; }
	Mint operator - () const { return Mint(-x); }
	friend Mint operator - (const Mint &a, const Mint &b) { return Mint(a.x - b.x); }
	Mint operator -= (const Mint &b) { return *this = *this - b; }
	friend Mint operator * (const Mint &a, const Mint &b) { return Mint(a.x * b.x % mod); }
	Mint operator *= (const Mint &b) { return *this = *this * b; }
	friend istream& operator >> (istream &in, Mint &a) { in >> a.x; return in; }
	friend ostream& operator << (ostream &out, const Mint &a) { out << a.x; return out; }
};
LL Mint::mod = 5;

struct Graph {
	struct Edge {
		int to, nxt;
		Edge() {}
		Edge(int _to, int _nxt): to(_to), nxt(_nxt) {}
	} e[N<<1];
	int top, head[N];
	
	Graph(): top(0) { memset(head, -1, sizeof(head)); }
	void Add1(int u, int v) { e[top] = Edge(v, head[u]); head[u] = top++; }
	void Add(int u, int v) { Add1(u, v); Add1(v, u); }
};

struct BIT {
	int n;
	Mint b[N], c[N];
	
	int Lowbit(int x) { return x & -x; }
	void InitSize(int _n) { n = _n; }
	
	void Add(Mint *t, int pos, Mint val) {
		for (int i = pos; i <= n; i += Lowbit(i))
			t[i] += val;
	}
	
	void Add(int l, int r, Mint val) {
		Add(b, l, val); Add(b, r+1, -val);
		Add(c, l, val*(l-1)); Add(c, r+1, -val*r);
	}
	
	Mint Query(Mint *t, int pos) {
		Mint ret = 0;
		for (int i = pos; i > 0; i -= Lowbit(i))
			ret += t[i];
		return ret;
	}
	
	Mint Query(int l, int r) {
		Mint s1 = (l-1) * Query(b, l-1) - Query(c, l-1);
		Mint s2 = r * Query(b, r) - Query(c, r);
		return s2 - s1;
	}
};

struct ChainDevide {
	Graph G;
	BIT bit;
	int dfsCnt;
	
	struct Node {
		int fa, dep, siz, son, top, id;
	} tr[N];
	
	void AddEdge(int u, int v) { G.Add(u, v); }
	
	void Devide(int n, int root, const int *val) {
		bit.InitSize(n);
		Dfs1(root, 0); Dfs2(root, root, val);
	}
	
	void Dfs1(int u, int fa) {
		tr[u].fa = fa;
		tr[u].dep = tr[fa].dep + 1;
		tr[u].siz = 1; tr[u].son = 0;
		for (int i = G.head[u]; ~i; i = G.e[i].nxt) {
			int v = G.e[i].to;
			if (v == fa) continue;
			Dfs1(v, u);
			tr[u].siz += tr[v].siz;
			if (tr[v].siz > tr[tr[u].son].siz)
				tr[u].son = v;
		}
	}
	
	void Dfs2(int u, int top, const int *val) {
		tr[u].top = top;
		tr[u].id = ++dfsCnt;
		bit.Add(tr[u].id, tr[u].id, val[u]);
		if (!tr[u].son) return;
		Dfs2(tr[u].son, top, val);
		for (int i = G.head[u]; ~i; i = G.e[i].nxt) {
			int v = G.e[i].to;
			if (v != tr[u].fa && v != tr[u].son)
				Dfs2(v, v, val);
		}
	}
	
	void PathAdd(int u, int v, Mint val) {
		int tu = tr[u].top, tv = tr[v].top;
		while (tu != tv) {
			if (tr[tu].dep > tr[tv].dep)
				swap(u, v), swap(tu, tv);
			bit.Add(tr[tv].id, tr[v].id, val);
			v = tr[tv].fa; tv = tr[v].top;
		}
		if (tr[u].dep > tr[v].dep) swap(u, v);
		bit.Add(tr[u].id, tr[v].id, val);
	}
	
	Mint PathQuery(int u, int v) {
		int tu = tr[u].top, tv = tr[v].top;
		Mint ret = 0;
		while (tu != tv) {
			if (tr[tu].dep > tr[tv].dep)
				swap(u, v), swap(tu, tv);
			ret += bit.Query(tr[tv].id, tr[v].id);
			v = tr[tv].fa; tv = tr[v].top;
		}
		if (tr[u].dep > tr[v].dep) swap(u, v);
		return ret += bit.Query(tr[u].id, tr[v].id);
	}
	
	void TreeAdd(int u, Mint val) {
		bit.Add(tr[u].id, tr[u].id + tr[u].siz - 1, val);
	}
	
	Mint TreeQuery(int u) {
		return bit.Query(tr[u].id, tr[u].id + tr[u].siz - 1);
	}
} tree;

int r[N];

int main() {
	ios::sync_with_stdio(false);
	int n, m, root; cin >> n >> m >> root >> Mint::mod;
	for (int i = 1; i <= n; i++)
		cin >> r[i];
	for (int u, v, i = 1; i < n; i++) {
		cin >> u >> v;
		tree.AddEdge(u, v);
	}
	tree.Devide(n, root, r);
	while (m--) {
		int opt, u, v; Mint val;
		cin >> opt;
		switch (opt) {
			case 1: cin >> u >> v >> val; tree.PathAdd(u, v, val);               break;
			case 2: cin >> u >> v;        cout << tree.PathQuery(u, v) << endl;  break;
			case 3: cin >> u >> val;      tree.TreeAdd(u, val);                  break;
			case 4: cin >> u;             cout << tree.TreeQuery(u) << endl;     break;
		}
	}
    return 0;
}

