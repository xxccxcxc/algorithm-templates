#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+50;

struct LCT {
    struct Node {
        int fa, ch[2];
        int val, sum;
        bool revLazy;
    } tr[N];
    
    void Init(int n, int val[]) {
        for (int i = 1; i <= n; i++)
            tr[i].val = tr[i].sum = val[i];
    }
    
    bool Getlr(int x) {
        return tr[tr[x].fa].ch[1] == x;
    }
    
    bool IsRoot(int x) {
        return tr[tr[x].fa].ch[Getlr(x)] != x;
    }
    
    void Connect(int f, bool lr, int c) {
        if (c) tr[c].fa = f;
        if (f) tr[f].ch[lr] = c;
    }
    
    void Update(int x) {
        tr[x].sum = tr[x].val ^ tr[tr[x].ch[0]].sum ^ tr[tr[x].ch[1]].sum;
    }
    
    void Rotate(int x) {
        int y = tr[x].fa, z = tr[y].fa;
        bool lr = Getlr(x);
        if (!IsRoot(y)) tr[z].ch[Getlr(y)] = x;
        tr[x].fa = z;
        Connect(y, lr, tr[x].ch[!lr]);
        Connect(x, !lr, y);
        Update(y);
    }
    
    void PutRev(int x) {
    	tr[x].revLazy ^= 1;
    	swap(tr[x].ch[0], tr[x].ch[1]);
    }
    
    void PushDown(int x) {
        if (!tr[x].revLazy) return;
        tr[x].revLazy = false;
        for (int i = 0; i < 2; i++)
        	PutRev(tr[x].ch[i]);
    }
    
    void PushFromRoot(int x) {
        stack<int> st; st.push(x);
        for (int i = x; !IsRoot(i); i = tr[i].fa)
            st.push(tr[i].fa);
        for (; !st.empty(); st.pop())
            PushDown(st.top());
    }
    
    void Splay(int x) {
        for (PushFromRoot(x); !IsRoot(x); Rotate(x))
            if (!IsRoot(tr[x].fa))
                Rotate(Getlr(x) ^ Getlr(tr[x].fa) ? x : tr[x].fa);
        Update(x);
    }
    
    void Access(int x) {
        for (int pre = 0; x; pre = x, x = tr[x].fa) {
            Splay(x);
            tr[x].ch[1] = pre;
            Update(x);
        }
    }
    
    void MakeRoot(int x) {
    	Access(x);
    	Splay(x);
    	PutRev(x);
    }
    
    int FindRoot(int x) {
    	Access(x);
    	Splay(x);
    	while (tr[x].ch[0]) {
    		PushDown(x);
            x = tr[x].ch[0];	
        }
        return x;
    }
    
    void Link(int x, int y) {
    	MakeRoot(x);
    	if (FindRoot(y) != x)
    		tr[x].fa = y;
    }
    
    void Cut(int x, int y) {
        MakeRoot(x);
        if (FindRoot(y) == x && tr[x].fa == y && tr[x].ch[1] == 0) {
            tr[x].fa = tr[y].ch[0] = 0;
            Update(y);
        }
    }
    
    void Change(int x, int val) {
        Splay(x);
        tr[x].val = val;
        Update(x);
    }
    
    int Query(int x, int y) {
        MakeRoot(x);
        Access(y);
        Splay(y);
        return tr[y].sum;
    }
} lct;

int r[N];

int main() {
    ios::sync_with_stdio(false);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> r[i];
    lct.Init(n, r);
    for (int opt, x, y; m--; ) {
        cin >> opt >> x >> y;
        switch (opt) {
            case 0: cout << lct.Query(x, y) << endl; break;
            case 1: lct.Link(x, y); break;
            case 2: lct.Cut(x, y); break;
            case 3: lct.Change(x, y); break;
        }
    }
    return 0;
}

