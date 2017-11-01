#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 200050, M = 200050;
struct Edge {
    int to, w, nxt;
}e[M*2];  // 双向边要开两倍

int head[N], ecnt;
bool ok, vis[N];
int dis[N];

void add(int u, int v, int w) {
    e[ecnt].to = v;
    e[ecnt].w = w;
    e[ecnt].nxt = head[u];
    head[u] = ecnt++;
}

int read() { int tmp; scanf("%d", &tmp); return tmp; }

void clear() {
    ecnt = 0;
    memset(head, -1, sizeof(head));
    ok = true;
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x3f, sizeof(dis));
}

void dfs(int u) {  // dfs版SPFA判负环 
    if (!ok) return;
    vis[u] = true;
    for (int i = head[u]; ~i && ok; i = e[i].nxt) {
        int v = e[i].to;
        if (dis[u] + e[i].w < dis[v]) {
            dis[v] = dis[u] + e[i].w;
            if (vis[v]) ok = false;  // 若访问到之前走过的点，说明这个环可以循环更新，也就是负环 
            else dfs(v);
        }
    }
    vis[u] = false;
}

int main() {
    for (int T = read(), n, m; T--; ) {
        clear();
        scanf("%d%d", &n, &m);
        for (int u, v, w; m--; ) {
            scanf("%d%d%d", &u, &v, &w);
            add(u, v, w);
            if (w >= 0) add(v, u, w);
        }
        for (int i = 1; i <= n && ok; i++)
            if (!vis[i]) dfs(i);
        printf(ok ? "N0\n" : "YE5\n");
    }
    return 0;
}

