#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long LL;
const int N = 1e5+50;

struct SegmentTree {
    struct Node {
        int l, r; LL sum, add;
        int size() { return r - l + 1; }
        int mid() { return l + r >> 1; }
    } tr[N<<2];
    
    int son(int u, bool p) { return u << 1 | p; }
    
    void Build(LL *a, int u, int L, int R) {
        tr[u].l = L; tr[u].r = R;
        if (L == R) { tr[u].sum = a[L]; return; }
        int mid = L + R >> 1;
        Build(a, son(u, 0), L, mid);
        Build(a, son(u, 1), mid + 1, R);
        tr[u].sum = tr[son(u, 0)].sum + tr[son(u, 1)].sum;
    }
    
    void Build(int n, LL *a) {
        Build(a, 1, 1, n);
    }
    
    void Add(int u, int l, int r, LL val) {
        tr[u].sum += val * (r - l + 1);
        if (tr[u].l == l && tr[u].r == r) {
            tr[u].add += val; return;
        }
        int mid = tr[u].mid();
        if (l <= mid) Add(son(u, 0), l, min(r, mid), val);
        if (r > mid) Add(son(u, 1), max(l, mid + 1), r, val);
    }
    
    void Add(int l, int r, LL val) {
        Add(1, l, r, val);
    }
    
    LL Query(int u, int l, int r, LL add) {
        if (tr[u].l == l && tr[u].r == r) {
            return tr[u].sum + add * tr[u].size();
        }
        int mid = tr[u].mid(); LL ret = 0;
        if (l <= mid) ret += Query(son(u, 0), l, min(r, mid), add + tr[u].add);
        if (r > mid) ret += Query(son(u, 1), max(l, mid + 1), r, add + tr[u].add);
        return ret;
    }
    
    LL Query(int l, int r) {
        return Query(1, l, r, 0);
    }
} tree;

LL init[N];

int main() {
    ios::sync_with_stdio(false);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> init[i];
    tree.Build(n, init);
    for (int opt, l, r; m--; ) {
        cin >> opt >> l >> r;
        if (opt == 1) {
            LL val; cin >> val;
            tree.Add(l, r, val);
        }
        else cout << tree.Query(l, r) << endl;
    }
    return 0;
}

