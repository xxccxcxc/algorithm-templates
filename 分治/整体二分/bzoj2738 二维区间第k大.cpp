#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 550, M = 6e4+50;
 
struct BIT {
    int n, a[N][N];
     
    int Lowbit(int x) { return x & -x; }
     
    void Add1(int x, int y, int val) {
        for (int i = x; i <= n; i += Lowbit(i))
            for (int j = y; j <= n; j += Lowbit(j))
                a[i][j] += val;
    }
     
    int Query1(int x, int y) {
        int ret = 0;
        for (int i = x; i; i -= Lowbit(i))
            for (int j = y; j; j -= Lowbit(j))
                ret += a[i][j];
        return ret;
    }
     
    int Query(int x1, int y1, int x2, int y2) {
        return Query1(x2, y2) - Query1(x1-1, y2) - Query1(x2, y1-1) + Query1(x1-1, y1-1);
    }
     
    void Init(int _n) { n = _n; }
} bit;
 
struct Data {
    int x, y, val;
    bool operator < (const Data &b) const { return val < b.val; }
} num[N*N];
int tail, top;
 
struct Query {
    int x1, y1, x2, y2, k, ans;
    void Input() { scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &k); }
} q[M];
 
int id[M], tmp[M];
bool inLeft[M];
 
void Solve(int l, int r, int L, int R) {
    if (l > r || L > R) return;
    if (L == R) {
        for (int i = l; i <= r; i++)
            q[id[i]].ans = L;
        return;
    }
    int mid = L + R >> 1;
    while (tail < top && num[tail+1].val <= mid) {
        tail++; bit.Add1(num[tail].x, num[tail].y, 1);
    }
    while (tail && num[tail].val > mid) {
        bit.Add1(num[tail].x, num[tail].y, -1); tail--;
    }
    // 保证树状数组存的是1到mid的信息。
	// 另一种方法是每次把左区间的贡献统计到右区间内，就只需要记录L到mid的信息。 
    int lCnt = 0;
    for (int i = l; i <= r; i++) {
        Query &u = q[id[i]];
        int t = bit.Query(u.x1, u.y1, u.x2, u.y2);
        if (u.k <= t)
            inLeft[i] = true, lCnt++;
        else inLeft[i] = false;
    }
    int t1 = l, t2 = l + lCnt;
    for (int i = l; i <= r; i++)
        if (inLeft[i]) tmp[t1++] = id[i];
        else tmp[t2++] = id[i];
    for (int i = l; i <= r; i++)
        id[i] = tmp[i];
    Solve(l, t1 - 1, L, mid);
    Solve(t1, r, mid + 1, R); 
}
 
int main() {
    int n, m; scanf("%d%d", &n, &m); bit.Init(n);
    int mx = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            Data &cur = num[++top];
            cur.x = i; cur.y = j;
            scanf("%d", &cur.val);
            mx = max(mx, cur.val);
        }
    sort(num + 1, num + top + 1);
    for (int i = 1; i <= m; i++)
        q[i].Input(), id[i] = i;
    Solve(1, m, 0, mx);
    for (int i = 1; i <= m; i++)
        printf("%d\n", q[i].ans);
    return 0;
}
