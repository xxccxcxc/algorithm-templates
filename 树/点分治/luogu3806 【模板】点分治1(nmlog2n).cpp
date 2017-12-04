#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set> 
using namespace std;
const int N = 10050, M = 150;

struct Graph {
    struct Edge {
        int to, w, nxt;
        Edge(int _to=0, int _w=0, int _nxt=0): to(_to), w(_w), nxt(_nxt) {}
    } e[N<<1];
    int head[N], top;
    
    Graph() { memset(head, -1, sizeof(head)); }
    void add1(int u, int v, int w) { e[top] = Edge(v, w, head[u]); head[u] = top++; }
    void add(int u, int v, int w) { add1(u, v, w); add1(v, u, w); }
};

struct PointDivide {
    Graph G;
    vector<int> q;
    bool ans[M];
    int n, siz[N], mx[N];
    bool vis[N];
    
    void addQ(int len) {
        q.push_back(len);
        ans[q.size()-1] = !len;
    }
    
    // 详细注释见另一份代码 
    int getRoot(int u, int fa, int n) {
        siz[u] = 1; mx[u] = 0;
        int ret = 0;
        for (int i = G.head[u]; ~i; i = G.e[i].nxt) {
            int v = G.e[i].to;
            if (v != fa && !vis[v]) {
                int vRoot = getRoot(v, u, n);
                siz[u] += siz[v];
                mx[u] = max(mx[u], siz[v]);
                if (!ret || mx[vRoot] < mx[ret])
                    ret = vRoot;  // 这里是vRoot而不是v 
            }
        }
        mx[u] = max(mx[u], n - siz[u]);
        if (!ret || mx[u] < mx[ret]) ret = u;
        return ret;
    }
    
    void getDis(int u, int fa, int curDis, vector<int> &d) {
        d.push_back(curDis);
        for (int i = G.head[u]; ~i; i = G.e[i].nxt) {
            int v = G.e[i].to;
            if (v != fa && !vis[v])
                getDis(v, u, curDis + G.e[i].w, d);
        }
    }
    
    void dfs(int u, int totSiz) {
        vis[u] = true;
        set<int> s; s.insert(0); 
        for (int i = G.head[u]; ~i; i = G.e[i].nxt) {
            int v = G.e[i].to;
            if (!vis[v]) {
                vector<int> d;
                getDis(v, u, G.e[i].w, d);
                int dcnt = d.size();
                for (int qcnt = q.size(), j = 0; j < qcnt; j++)
                    for (int k = 0; k < dcnt; k++)
                        if (s.count(q[j] - d[k])) {  // 判断这棵子树的答案和前几棵的答案能不能凑对 
                            ans[j] = true;
                            break;
                        }
                for (int j = 0; j < dcnt; j++)
                    s.insert(d[j]);  // 把这棵子树的距离扔进set，让后面的子树查 
            }
        }
        s.clear();  // 这里必须清空，不然会MLE 
        for (int i = G.head[u]; ~i; i = G.e[i].nxt) {
            int v = G.e[i].to;
            if (!vis[v]) {
                int vSiz = siz[v] <= siz[u] ? siz[v] : totSiz - siz[u];
                dfs(getRoot(v, 0, vSiz), vSiz);  // 继续递归分治 
            }
        }
    }
    
    void solve() { dfs(getRoot(1, 0, n), n); }
} tree;

// 题意：求树上距离<=K的点对数，多组询问
// 复杂度O(nmlog2n)，事实上常数很小 
int main() {
    int n, m; scanf("%d%d", &n, &m); tree.n = n;
    for (int u, v, w, i = 1; i < n; i++) {
        scanf("%d%d%d", &u, &v, &w);
        tree.G.add(u, v, w);
    }
    for (int len, i = 0; i < m; i++) {
        scanf("%d", &len);
        tree.addQ(len);
    }
    tree.solve();
    for (int i = 0; i < m; i++)
        printf(tree.ans[i] ? "AYE\n" : "NAY\n");
    return 0;
}

