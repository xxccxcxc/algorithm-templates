/*
luoguU20011 day5T1 同余(exclaim) 100pts

题意：求1<=a<=b<=c<=n且a+b^2同余c^3的(a,b,c)个数

解法：把[b^2+1,b^2+b]每个数%mod加入树状数组，枚举c做单点查询
加入的方法：区间存在循环节，答案先加上完整的循环节个数，然后头尾做区间修改 
*/ 
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+50;
int n, mod;

struct Bit {  // 区间修改单点查询 
    int siz, tr[N];
    void Init(int _siz) { siz = _siz; memset(tr, 0, sizeof(tr)); }
    int Lowbit(int x) { return x & -x; }
    void Add(int pos, int val) {
        for (int i = ++pos; i <= siz; i += Lowbit(i))  // pos是从0开始的，要+1 
            tr[i] += val;
    }
    void Add(int l, int r, int val) {
        Add(l, val); Add(r+1, -val);
    }
    int Query(int pos) {
        int ret = 0;
        for (int i = ++pos; i; i -= Lowbit(i))
            ret += tr[i];
        return ret;
    }
} bit;

void Insert(int l, int r) {
    if (l > r) Insert(0, r), Insert(l, mod-1);  // 边角分类讨论 
    else bit.Add(l, r, 1);
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    for (int cas = 1; cas <= T; cas++) {
        cin >> n >> mod;
        bit.Init(mod);
        long long ans = 0, cnt = 0;
        for (int i = 1; i <= n; i++) {
            cnt += i / mod;  // 答案加上完整循环节个数i/mod 
            if (i % mod) Insert((1LL*i*i+1) % mod, (1LL*i*i+i) % mod);
            ans += cnt + bit.Query(1LL*i*i%mod*i%mod);
        }
        cout << "Case " << cas << ": " << ans << endl;
    }
    return 0;
}

