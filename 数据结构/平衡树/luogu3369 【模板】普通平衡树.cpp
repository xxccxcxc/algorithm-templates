#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

struct SPLAY {
    static const int SIZ = 4e6+50, INF = 0x3f3f3f3f;
    
    struct Node {
        int fa, ch[2];
        int num, cnt, siz;
        Node(int _num=0) {
            fa = ch[0] = ch[1] = 0;
            num = _num; cnt = siz = 1;
        }
    } tr[SIZ];
    
    int top, root;
    
    SPLAY() {
        top = 1;      tr[0].cnt = tr[0].siz = 0;
        Insert(-INF); tr[1].cnt = tr[1].siz = 0;
        Insert(INF);  tr[2].cnt = tr[2].siz = 0;
        // 哨兵结点的siz设为0，会导致哨兵结点无法被提到根，但对这题无影响 
    }
    
    int NewNode(int num) { tr[top] = Node(num); return top++; }
    bool Getlr(int x) { return tr[tr[x].fa].ch[1] == x; }
    void Update(int x) { tr[x].siz = tr[tr[x].ch[0]].siz + tr[tr[x].ch[1]].siz + tr[x].cnt; }
    
    void Connect(int f, bool lr, int c) {
        if (f) tr[f].ch[lr] = c;
        if (c) tr[c].fa = f;
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
        for (int y; (y = tr[x].fa) != tofa; Rotate(x))
            if (tr[y].fa != tofa)
                Rotate(Getlr(x) ^ Getlr(y) ? x : y);
        Update(x); if (!tofa) root = x;
    }
    
    void Insert(int num) {
        int x = root, y = 0;
        while (x && tr[x].num != num)
            y = x, x = tr[x].ch[num > tr[x].num];
        if (x) tr[x].cnt++;
        else Connect(y, num > tr[y].num, x = NewNode(num));
        Splay(x);
    }
    
    void Find(int num) {  // 搜索数num并把它提到根，如果num不存在则找离它最近的一个 
        int x = root;
        for (int y; tr[x].num != num && (y = tr[x].ch[num > tr[x].num]); x = y);
        Splay(x);
    }
    
    int NearPos(int num, bool lr) {  // 返回前驱或后继的结点编号 
        Find(num);
        if (tr[root].num != num && (tr[root].num > num) == lr)
            return root;
        int x = tr[root].ch[lr];
        for (int y; y = tr[x].ch[!lr]; x = y);
        return x;
    }
    
    void Delete(int num) {
        int pre = NearPos(num, 0), nxt = NearPos(num, 1);
        Splay(pre); Splay(nxt, pre);
        int x = tr[nxt].ch[0];
        if (--tr[x].cnt) Splay(x);
        else Connect(nxt, 0, 0), Splay(nxt);
    }
    
    int Rank(int num) {
        Find(num);
        return tr[tr[root].ch[0]].siz + 1;
    }
    
    int Kth(int k) {
        int x = root;
        while (x) {
            int lSiz = tr[tr[x].ch[0]].siz;
            if (k > lSiz && k <= lSiz + tr[x].cnt) {
                Splay(x); return tr[x].num;
            }
            if (k <= lSiz) x = tr[x].ch[0];
            else k -= lSiz + tr[x].cnt, x = tr[x].ch[1];
        }
        return INF;
    }
    
    int Near(int num, int lr) {
        Splay(NearPos(num, lr));
        return tr[root].num;
    }
} splay;

int main() {
    int m; scanf("%d", &m);
    for (int opt, x; m--; ) {
        scanf("%d%d", &opt, &x);
        switch (opt) {
            case 1: splay.Insert(x); break;
            case 2: splay.Delete(x); break;
            case 3: printf("%d\n", splay.Rank(x)); break;
            case 4: printf("%d\n", splay.Kth(x)); break;
            default: printf("%d\n", splay.Near(x, opt - 5));
        }
    }
    return 0;
}

