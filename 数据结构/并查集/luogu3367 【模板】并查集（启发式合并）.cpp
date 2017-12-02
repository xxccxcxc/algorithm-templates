#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 10050;

struct MFS {
    int fa[N], siz[N];
    void init(int n) { for (int i = 1; i <= n; i++) fa[i] = i; }
    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    void unionn(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return;
        if (siz[fx] < siz[fy]) swap(fx, fy);  // 启发式合并：把小的合并到大的上，使深度增长尽量慢 
        fa[fy] = fx; siz[fx] += siz[fy];
    }
}mfs;

int main() {
    ios::sync_with_stdio(false);
    int n, m; cin >> n >> m; mfs.init(n);
    for (int opt, x, y; m--; ) {
        cin >> opt >> x >> y;
        if (opt == 1) mfs.unionn(x, y);
        else cout << (mfs.find(x) == mfs.find(y) ? 'Y' : 'N') << endl;
    }
    return 0;
}

