#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
const int N = 500050, M = 500050;

struct Edge {
    int to, next;
    Edge(int _to = 0, int _next = -1): to(_to), next(_next) {}
}e[N<<1];

struct Node {
    int fa, son, siz, dep, top;
    Node(int _fa=0, int _son=0, int _siz=0, int _dep=0, int _top=0) {
        fa = _fa; son = _son; siz = _siz; dep = _dep; top = _top;
    }
}tr[N];

int ecnt, head[N];

void add(int u, int v) {
    e[ecnt] = Edge(v, head[u]); head[u] = ecnt++;
    e[ecnt] = Edge(u, head[v]); head[v] = ecnt++;
}

void dfs1(int u, int fa) {
    tr[u] = Node(fa, 0, 1, tr[fa].dep+1);
    for (int i = head[u]; ~i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs1(v, u);
        if (tr[v].siz > tr[tr[u].son].siz)
            tr[u].son = v;
        tr[u].siz += tr[v].siz;
    }
}

void dfs2(int u, int curTop) {
    tr[u].top = curTop;
    if (!tr[u].son) return;
    dfs2(tr[u].son, curTop);
    for (int i = head[u]; ~i; i = e[i].next) {
        int v = e[i].to;
        if (v != tr[u].fa && v != tr[u].son)
            dfs2(v, v);
    }
}

int lca(int u, int v) {
    int tu = tr[u].top, tv = tr[v].top;
    while (tu != tv) {
        if (tr[tu].dep > tr[tv].dep)
            swap(u, v), swap(tu, tv);
        v = tr[tv].fa; tv = tr[v].top;
    }
    return tr[u].dep < tr[v].dep ? u : v;
}

int main() {
    memset(head, -1, sizeof(head));
    int n, m, root;
    scanf("%d%d%d", &n, &m, &root);
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        add(u, v);
    }
    dfs1(root, 0);
    dfs2(root, root);
    for (int u, v; m--; ) {
    	scanf("%d%d", &u, &v);
    	printf("%d\n", lca(u, v));
    }
    return 0;
}

