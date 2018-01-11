#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;

struct SPLAY {
    static const int N = 5e5+50, INF = 0x3f3f3f3f;
    
    struct Node {
        int fa, ch[2];
        int num, siz, sum, mx, mxL, mxR;
        bool sameLazy, revLazy;
        Node() { fa = ch[0] = ch[1] = num = siz = sum = mx = mxL = mxR = sameLazy = revLazy = 0; }
        Node(int _num) {
            fa = ch[0] = ch[1] = 0; siz = 1;
            num = sum = mx = mxL = mxR = _num;
            sameLazy = revLazy = false;
        }
    } tr[N];
    int top, root;
    stack<int> pool;
    
    SPLAY() {
        top = 1; tr[0].mx = tr[0].mxL = tr[0].mxR = -INF;
        int head = NewNode(-INF), tail = NewNode(-INF);
        tr[head].sum = tr[tail].sum = 0;
        Connect(0, 0, head); Connect(head, 1, tail); root = head;
    }
    
    int NewNode(int num) {
        int x;
        if (!pool.empty()) {
            x = pool.top(); pool.pop();
            if (tr[x].ch[0]) pool.push(tr[x].ch[0]);
            if (tr[x].ch[1]) pool.push(tr[x].ch[1]);
        }
        else x = top++;
        tr[x] = Node(num); return x;
    }
    
    void Connect(int f, bool lr, int c) {
        if (f) tr[f].ch[lr] = c;
        if (c) tr[c].fa = f;
    }
    
    bool Getlr(int x) { return tr[tr[x].fa].ch[1] == x; }
    
    void Update(int x) {
        if (!x) return;
        int lc = tr[x].ch[0], rc = tr[x].ch[1];
        tr[x].siz = tr[lc].siz + tr[rc].siz + 1;
        tr[x].sum = tr[lc].sum + tr[rc].sum + tr[x].num;
        tr[x].mxL = max(tr[lc].mxL, tr[lc].sum + tr[x].num + max(tr[rc].mxL, 0));
        tr[x].mxR = max(tr[rc].mxR, tr[rc].sum + tr[x].num + max(tr[lc].mxR, 0));
        tr[x].mx = max(max(tr[lc].mx, tr[rc].mx), max(tr[lc].mxR, 0) + tr[x].num + max(tr[rc].mxL, 0));
    }
    
    int Build(int l, int r) {
        if (l > r) return 0;
        int mid = l + r >> 1, lc = Build(l, mid - 1);
        int num; scanf("%d", &num); int x = NewNode(num);
        Connect(x, 0, lc); Connect(x, 1, Build(mid + 1, r));
        Update(x); return x;
    }
    
    void PutSame(int x, int num) {
        if (!x) return;
        tr[x].sameLazy = true;
        tr[x].num = num;
        tr[x].sum = num * tr[x].siz;
        tr[x].mx = tr[x].mxL = tr[x].mxR = max(tr[x].sum, num);
        tr[x].revLazy = false;
    }
    
    void PutRev(int x) {
        if (!x) return;
        tr[x].revLazy ^= 1;
        swap(tr[x].ch[0], tr[x].ch[1]);
        swap(tr[x].mxL, tr[x].mxR);
    }
    
    void PushDown(int x) {
        if (!x) return;
        if (tr[x].sameLazy) {
            PutSame(tr[x].ch[0], tr[x].num);
            PutSame(tr[x].ch[1], tr[x].num);
        }
        if (tr[x].revLazy) {
            PutRev(tr[x].ch[0]);
            PutRev(tr[x].ch[1]);
        }
        tr[x].sameLazy = tr[x].revLazy = false;
    }
    
    void Rotate(int x) {
        bool lr = Getlr(x);
        int y = tr[x].fa, z = tr[y].fa;
        Connect(z, Getlr(y), x);
        Connect(y, lr, tr[x].ch[!lr]);
        Connect(x, !lr, y);
        Update(y);
    }
    
    void Splay(int x, int tofa=0) {
        PushDown(x);
        for (int y; (y = tr[x].fa) != tofa; Rotate(x))
            if (tr[y].fa != tofa)
                Rotate(Getlr(x) ^ Getlr(y) ? x : y);
        Update(x);
		if (!tofa) root = x;
    }
    
    void Kth(int x, int k) {
        PushDown(x);
        int tofa = tr[x].fa;
        for (int lSiz; k != (lSiz = tr[tr[x].ch[0]].siz) + 1; PushDown(x))
            if (k <= lSiz) x = tr[x].ch[0];
            else k -= lSiz + 1, x = tr[x].ch[1];
        Splay(x, tofa);
    }
    
    int Split(int pos, int tot) {
        Kth(root, pos);
        Kth(tr[root].ch[1], tot + 1);
        return tr[tr[root].ch[1]].ch[0];
    }
    
    void Insert(int pos, int tot) {
        Kth(root, pos + 1);
        Kth(tr[root].ch[1], 1);
        int x = Build(1, tot);
        Connect(tr[root].ch[1], 0, x);
        Splay(x);
    }
    
    void Delete(int pos, int tot) {
        int x = Split(pos, tot), y = tr[x].fa;
        pool.push(x); tr[y].ch[0] = 0;
        Splay(y);
    }
    
    void MakeSame(int pos, int tot, int num) {
        int x = Split(pos, tot);
        PutSame(x, num); Splay(x);
    }
    
    void Reverse(int pos, int tot) {
        int x = Split(pos, tot);
        PutRev(x); Splay(x);
    }
    
    int GetSum(int pos, int tot) {
		return tr[Split(pos, tot)].sum;
	}
    
    int MaxSum() {
        int x = Split(1, tr[root].siz - 2);
        return tr[x].mx;
    }
} splay;

int main() {
    int n, m; scanf("%d%d", &n, &m);
    splay.Insert(0, n);
    while (m--) {
        char r[10], opt; scanf("%s", r); opt = r[2];
        if (opt == 'X') { printf("%d\n", splay.MaxSum()); continue; }
        int pos, tot, num; scanf("%d%d", &pos, &tot);
        switch (opt) {
            case 'S': splay.Insert(pos, tot); break;
            case 'L': splay.Delete(pos, tot); break;
            case 'K': scanf("%d", &num); splay.MakeSame(pos, tot, num); break;
            case 'V': splay.Reverse(pos, tot); break;
            case 'T': printf("%d\n", splay.GetSum(pos, tot)); break;
        }
    }
    return 0;
}

