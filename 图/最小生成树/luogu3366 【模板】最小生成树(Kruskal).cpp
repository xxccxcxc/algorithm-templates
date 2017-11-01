#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 5050, M = 200050;
struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int _u, int _v, int _w): u(_u), v(_v), w(_w) {}
    bool operator<(const Edge &t) const { return w < t.w; }
}e[M];

struct MFS {  // 并查集 merging and finding set
    int fa[N];
    MFS() {}
    MFS(int n) {
        for (int i = 1; i <= n; i++)
            fa[i] = i;
    }
    int find(int x) {
        if (fa[x] != x) fa[x] = find(fa[x]);
        return fa[x];
    }
    bool unionn(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return false;
        fa[fx] = fy;
        return true;
    }
};

int main() {  // Kruskal 
    int n, m;
    scanf("%d%d", &n, &m);
    MFS mfs(n);
    for (int i = 1, u, v, w; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        e[i] = Edge(u, v, w);
    }
    sort(e+1, e+m+1);
    int cnt = 0, ans = 0;
    for (int i = 1; i <= m && cnt < n-1; i++)  // n个点要合并n-1次 
        if (mfs.unionn(e[i].u, e[i].v))
            ++cnt, ans += e[i].w;
    if (cnt < n-1) printf("orz\n");
    else printf("%d\n", ans);
    return 0;
}

