#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N = 10050, M = 500050, INF = 0x3f3f3f3f;
struct Edge {
    int to, w, nxt;
    Edge() {}
    Edge(int _to, int _w, int _nxt): to(_to), w(_w), nxt(_nxt) {}
}e[M];

int ecnt, head[N];  // 记得赋初值 
int dis[N];
bool vis[N];

void add(int u, int v, int w) {
    e[ecnt] = Edge(v, w, head[u]);
    head[u] = ecnt++;
}

void SPFA(int s) {
    memset(dis, 0x3f, sizeof(dis));
    queue<int> q;
    q.push(s); dis[s] = 0; vis[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = head[u]; ~i; i = e[i].nxt) {
            int v = e[i].to;
            if (dis[u] + e[i].w < dis[v]) {
                dis[v] = dis[u] + e[i].w;
                if (!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        vis[u] = false;  // 记得退出时把vis置0 
    }
}

int main() {
    memset(head, -1, sizeof(head));
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);
    for (int u, v, w; m--; ) {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);  // 这里用 add(read(), read(), read()) 读进来是反的，逗号很迷，最好别这样写 
    }
    SPFA(s);
    for (int i = 1; i <= n; i++) {
        if (dis[i] == INF) dis[i] = 2147483647;
        printf("%d ", dis[i]);
    }
    return 0;
}
