#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long LL;
const int N = 200050;

struct Seg {
	int l, r;
	LL sum, lazy;
	int size() { return r - l + 1; }
	void mod(LL mo) { sum %= mo; lazy %= mo; }
}seg[N<<2];

LL mo;

int son(int u, int p) { return u << 1 | p; }

void pushup(int u) { seg[u].sum = (seg[son(u, 0)].sum + seg[son(u, 1)].sum) % mo; }

void build(int u, int l, int r, LL *a) {
	seg[u].l = l; seg[u].r = r;
	if (l == r) { seg[u].sum = a[l] % mo; return; }
	int mid = (l + r) >> 1;
	build(son(u, 0), l, mid, a);
	build(son(u, 1), mid+1, r, a);
	pushup(u);
}

void addVal(int u, LL val) {
	seg[u].sum += seg[u].size() * val;
	seg[u].lazy += val;
	seg[u].mod(mo);
}

void pushdown(int u) {
	for (int i = 0; i <= 1; i++)
		addVal(son(u, i), seg[u].lazy);
	seg[u].lazy = 0;
}

void update(int u, int l, int r, LL val) {
	if (seg[u].l == l && seg[u].r == r) { addVal(u, val); return; }
	if (seg[u].lazy) pushdown(u);
	int mid = (seg[u].l + seg[u].r) >> 1;
	if (l <= mid) update(son(u, 0), l, min(r, mid), val);
	if (r > mid) update(son(u, 1), max(l, mid+1), r, val);
	pushup(u);  // pushup别忘记写 
}

LL query(int u, int l, int r) {
	if (seg[u].l == l && seg[u].r == r) return seg[u].sum;
	if (seg[u].lazy) pushdown(u);
	LL ret = 0; int mid = (seg[u].l + seg[u].r) >> 1;
	if (l <= mid) ret += query(son(u, 0), l, min(r, mid));
	if (r > mid) ret += query(son(u, 1), max(l, mid+1), r);
	return ret %= mo;  // 记得mod 
}

struct Edge {
	int to, nxt;
	Edge(int _to=0, int _nxt=0): to(_to), nxt(_nxt) {}
}e[N<<1];

int ecnt, head[N];

void add(int u, int v) {
	e[ecnt] = Edge(v, head[u]); head[u] = ecnt++;
	e[ecnt] = Edge(u, head[v]); head[v] = ecnt++;
}

struct SpNode {
	int fa, son, siz, dep, id, top;
	SpNode(int _fa=0, int _son=0, int _siz=0, int _dep=0, int _id=0, int _top=0) {
		fa = _fa; son = _son; siz = _siz; dep = _dep; id = _id; top = _top;
	}
}sp[N];

void dfs1(int u, int fa) {
	sp[u] = SpNode(fa, 0, 1, sp[fa].dep+1);
	for (int i = head[u]; ~i; i = e[i].nxt) {
		int v = e[i].to;
		if (v == fa) continue;
		dfs1(v, u);
		if (sp[v].siz > sp[sp[u].son].siz)
			sp[u].son = v;
		sp[u].siz += sp[v].siz;
	}
}

int dfscnt = 0;
LL a[N], segInit[N];

void dfs2(int u, int curTop) {
	sp[u].id = ++dfscnt;
	segInit[sp[u].id] = a[u];
	sp[u].top = curTop;
	if (!sp[u].son) return;
	dfs2(sp[u].son, curTop);
	for (int i = head[u]; ~i; i = e[i].nxt) {
		int v = e[i].to;
		if (v != sp[u].fa && v != sp[u].son)
			dfs2(v, v);
	}
}

void pathModify(int u, int v, LL val) {  // 路径修改 
	int tu = sp[u].top, tv = sp[v].top;
	while (tu != tv) {
		if (sp[tu].dep > sp[tv].dep)
			swap(u, v), swap(tu, tv);
		update(1, sp[tv].id, sp[v].id, val);
		v = sp[tv].fa; tv = sp[v].top;
	}
	if (sp[u].dep > sp[v].dep) swap(u, v);
	update(1, sp[u].id, sp[v].id, val);
}

LL pathQuery(int u, int v) {  // 路径查询 
	int tu = sp[u].top, tv = sp[v].top;
	LL ret = 0;
	while (tu != tv) {
		if (sp[tu].dep > sp[tv].dep)
			swap(u, v), swap(tu, tv);
		ret = (ret + query(1, sp[tv].id, sp[v].id)) % mo;
		v = sp[tv].fa; tv = sp[v].top;
	}
	if (sp[u].dep > sp[v].dep) swap(u, v);
	return ret = (ret + query(1, sp[u].id, sp[v].id)) % mo;
}

// 子树修改（利用子树的dfn是连续的） 
void treeModify(int u, LL val) { update(1, sp[u].id, sp[u].id + sp[u].siz - 1, val); }

// 子树查询 
LL treeQuery(int u) { return query(1, sp[u].id, sp[u].id + sp[u].siz - 1); }

int main() {
	memset(head, -1, sizeof(head));
	int n, m, root;
	scanf("%d%d%d%lld", &n, &m, &root, &mo);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	for (int i = 1, u, v; i < n; add(u, v), i++)
		scanf("%d%d", &u, &v);
	dfs1(root, 0); dfs2(root, root); build(1, 1, n, segInit);
	while (m--) {
		int opt, u, v; LL val;
		scanf("%d", &opt);
		switch (opt) {
			case 1: scanf("%d%d%lld", &u, &v, &val); pathModify(u, v, val);             break; 
			case 2: scanf("%d%d", &u, &v);           printf("%lld\n", pathQuery(u, v)); break;
			case 3: scanf("%d%lld", &u, &val);       treeModify(u, val);                break;
			case 4: scanf("%d", &u);                 printf("%lld\n", treeQuery(u));    break;
		}
	}
    return 0;
}

