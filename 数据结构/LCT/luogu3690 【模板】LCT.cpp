#include <bits/stdc++.h>

const int N = 1e5+50;

struct Lct {
    struct Node {
        int fa, ch[2];
        int val, sum;
        bool revLazy;
    } tr[N];
    
    void init(int n, int val[]) {
        for (int i = 1; i <= n; i++)
            tr[i].val = tr[i].sum = val[i];
    }
    
    bool getlr(int x) {
        return tr[tr[x].fa].ch[1] == x;
    }
    
    bool isRoot(int x) {
    	// x不是父亲的儿子，说明x的fa是虚边，进而说明x是所在splay的根 
        return tr[tr[x].fa].ch[getlr(x)] != x;
    }
    
    void connect(int f, bool lr, int c) {
        if (c) tr[c].fa = f;
        if (f) tr[f].ch[lr] = c;
    }
    
    void update(int x) {
    	// 维护异或和 
        tr[x].sum = tr[x].val ^ tr[tr[x].ch[0]].sum ^ tr[tr[x].ch[1]].sum;
    }
    
    void Rotate(int x) {
        int y = tr[x].fa, z = tr[y].fa;
        bool lr = getlr(x);
        if (!isRoot(y))  // 如果y是根，则z是y虚边连接的父亲，z不能向y连边 
            tr[z].ch[getlr(y)] = x;
        tr[x].fa = z;
        connect(y, lr, tr[x].ch[!lr]);
        connect(x, !lr, y);
        update(y);
    }
    
    void PutRev(int x) {
    	tr[x].revLazy ^= 1;
    	std::swap(tr[x].ch[0], tr[x].ch[1]);
    }
    
    void PushDown(int x) {
        if (!tr[x].revLazy)
            return;
        tr[x].revLazy = false;
        for (int i = 0; i < 2; i++)
        	PutRev(tr[x].ch[i]);
    }
    
    void PushFromRoot(int x) {
        // 把splay的根到x路径上的标记推下来，保证节点x的信息是准确的 
        std::stack<int> st;
        st.push(x);
        for (int i = x; !isRoot(i); i = tr[i].fa)
            st.push(tr[i].fa);
        for (; !st.empty(); st.pop())
            PushDown(st.top());
    }
    
    void splay(int x) {
        for (PushFromRoot(x); !isRoot(x); Rotate(x))
            if (!isRoot(tr[x].fa))  // splay里的判根都要用isRoot(x)，不能用x!=0 
                Rotate(getlr(x) ^ getlr(tr[x].fa) ? x : tr[x].fa);
        update(x);
    }
    
    void access(int x) {
    	// 把x到原树根的路径单独拉成一棵splay 
        for (int pre = 0; x; pre = x, x = tr[x].fa) {
        	/*
            这里要做的是把x的实儿子置为pre 
            首先把x节点splay到根
            此时x节点的右子树就是链上x下面的节点
            把x的右子树置为pre，则x与实儿子的实边就被取消了，改成到pre的实边 
            但原来实儿子的fa还是x，所以到原来实儿子的边变成了虚边 
            改完记得update更新信息 
            */
            splay(x); 
            tr[x].ch[1] = pre;
            update(x);
        }
    }
    
    void makeRoot(int x) {
    	/*
        功能：在原树上把x拎起来成为根
        实质上就是把根到x的深度反序
        先access提出根到x的splay，然后把这棵树反序 
        */ 
    	access(x); 
    	splay(x);
    	PutRev(x);
    }
    
    int findRoot(int x) {
    	/*
        功能：找x所在原树的树根，目的是判断两个点是否连通
        相当于在x到根的splay上查找最小的点
        先access把树拉出来，splay一下保证复杂度，然后向左走找最小 
        */ 
    	access(x);
    	splay(x);
    	while (tr[x].ch[0]) {
    		PushDown(x);
            x = tr[x].ch[0];	
        }
        return x;
    }
    
    void link(int x, int y) {
    	makeRoot(x);  // 把x提到原树的根 
    	if (findRoot(y) != x)  // 若y所在原树的根不是x，则x,y不连通 
    		tr[x].fa = y;
    }
    
    void cut(int x, int y) {
        makeRoot(x);  // 把x提到原树的根 
        /*
        判断x,y是否有直接连边的方法： 
        findRoot中会做access(y),splay(y)
        若x,y有直接连边，则因为access，这棵splay上只有x,y两个点
        access后，保证了x的深度最小，y的深度最大，
        所以要判断的只有x和y之间没有点
        具体实现就是 tr[x].fa == y && tr[x].ch[1] == 0 
        */
        if (findRoot(y) == x && tr[x].fa == y && tr[x].ch[1] == 0) {
            tr[x].fa = tr[y].ch[0] = 0;
            update(y);
        }
    }
    
    void change(int x, int val) {
    	// 改节点值只需要splay操作即可 
        splay(x);
        tr[x].val = val;
        update(x);
    }
    
    int query(int x, int y) {
    	// 先把x提到原树根，然后把y到根的路径提出来，在这棵splay上查询 
        makeRoot(x);
        access(y);
        splay(y);
        return tr[y].sum;
    }
} lct;


int main() {
	using std::cin;
	using std::cout;
	using std::endl;
    std::ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    static int r[N];
    for (int i = 1; i <= n; i++)
        cin >> r[i];
    lct.init(n, r);
    for (int opt, x, y; m--; ) {
        cin >> opt >> x >> y;
        switch (opt) {
            case 0: cout << lct.query(x, y) << endl; break;  // 询问x到y路径异或和 
            case 1: lct.link(x, y);                  break;  // 连接x和y 
            case 2: lct.cut(x, y);                   break;  // 删除边(x,y) 
            case 3: lct.change(x, y);                break;  // 将点x上的权值改成y 
        }
    }
    return 0;
}

