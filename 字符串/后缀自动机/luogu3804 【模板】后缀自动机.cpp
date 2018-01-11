#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int L = 1e6+50, SIZ = L << 1;

struct SAM {
    int top, last, ch[SIZ][26], fa[SIZ], mx[SIZ], cnt[SIZ];
    int bucket[L], t[SIZ];
    
    SAM() { last = top = 1; }
    
    void Extend(char c) {
        int x = c - 'a', p = last, np = last = ++top;
        mx[np] = mx[p] + 1; cnt[np] = 1;
        for (; p && !ch[p][x]; p = fa[p]) ch[p][x] = np;
        if (!p) { fa[np] = 1; return; }
        int q = ch[p][x];
        if (mx[q] == mx[p] + 1) { fa[np] = q; return; }
        int nq = ++top; mx[nq] = mx[p] + 1;
        fa[nq] = fa[q]; fa[q] = fa[np] = nq;
        memcpy(ch[nq], ch[q], sizeof(ch[nq]));
        for (; ch[p][x] == q; p = fa[p]) ch[p][x] = nq;
    }
    
    int Work() {
        for (int i = 1; i <= top; i++) bucket[mx[i]]++;
        for (int i = mx[last] - 1; i >= 0; i--) bucket[i] += bucket[i+1];
        for (int i = top; i; i--) t[bucket[mx[i]]--] = i;
        int ret = 0;
        for (int i = 1; i <= top; i++) {
            int u = t[i];
            cnt[fa[u]] += cnt[u];
            if (cnt[u] > 1)
                ret = max(ret, cnt[u] * mx[u]);
        }
        return ret;
    }
} sam;

int main() {
    string r; cin >> r;
    for (int len = r.size(), i = 0; i < len; i++)
        sam.Extend(r[i]);
    printf("%d\n", sam.Work());
    return 0;
}

