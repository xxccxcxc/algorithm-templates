#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N = 5050, M = 200050, INF = 0x3f3f3f3f;
struct Node {
    int u, w;
    Node(int _u = 0, int _w = 0): u(_u), w(_w) {}
    bool operator<(const Node &t) const { return w > t.w; }
};

struct Edge {
    int to, w, nxt;
    Edge(int _to = 0, int _w = 0, int _nxt = 0): to(_to), w(_w), nxt(_nxt) {}
}e[M<<1];

int ecnt, head[N];
bool ma[N][N], vis[N];
int dis[N];

void add1(int u, int v, int w) {
    e[ecnt] = Edge(v, w, head[u]);
    head[u] = ecnt++;
}

void add(int u, int v, int w) {
    add1(u, v, w);
    add1(v, u, w);
}

int main() {  // 堆优化Prim 
    memset(head, -1, sizeof(head));
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v, w; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
    }
    memset(dis, 0x3f, sizeof(dis));
    dis[1] = 0;
    priority_queue<Node> q;
    q.push(Node(1, 0));
    bool die = false;
    int ans = 0;
    for (int _ = 1; _ <= n; _++) {
        while (!q.empty() && vis[q.top().u]) q.pop();
        if (q.empty()) {
            die = true;
            break;
        }
        int u = q.top().u; ans += q.top().w; q.pop();
        vis[u] = true; 
        for (int i = head[u]; ~i; i = e[i].nxt) {
            int v = e[i].to;
            if (!vis[v] && e[i].w < dis[v]) {
            	dis[v] = e[i].w;
            	q.push(Node(v, dis[v]));
            	//这里dis的含义是到已访问点的最短距离，而dij中是到起点最短距离 
			}
        }
    }
    if (die) printf("orz\n");
    else printf("%d\n", ans);
    return 0;
}

