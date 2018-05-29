#include <bits/stdc++.h>

const int N = 3e5+50;

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
    	// x���Ǹ��׵Ķ��ӣ�˵��x��fa����ߣ�����˵��x������splay�ĸ� 
        return tr[tr[x].fa].ch[getlr(x)] != x;
    }
    
    void connect(int f, bool lr, int c) {
        if (c) tr[c].fa = f;
        if (f) tr[f].ch[lr] = c;
    }
    
    void update(int x) {
    	// ά������ 
        tr[x].sum = tr[x].val ^ tr[tr[x].ch[0]].sum ^ tr[tr[x].ch[1]].sum;
    }
    
    void Rotate(int x) {
        int y = tr[x].fa, z = tr[y].fa;
        bool lr = getlr(x);
        if (!isRoot(y))  // ���y�Ǹ�����z��y������ӵĸ��ף�z������y���� 
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
        // ��splay�ĸ���x·���ϵı������������֤�ڵ�x����Ϣ��׼ȷ�� 
        std::stack<int> st;
        st.push(x);
        for (int i = x; !isRoot(i); i = tr[i].fa)
            st.push(tr[i].fa);
        for (; !st.empty(); st.pop())
            PushDown(st.top());
    }
    
    void splay(int x) {
        for (PushFromRoot(x); !isRoot(x); Rotate(x))
            if (!isRoot(tr[x].fa))  // splay����и���Ҫ��isRoot(x)��������x!=0 
                Rotate(getlr(x) ^ getlr(tr[x].fa) ? x : tr[x].fa);
        update(x);
    }
    
    void access(int x) {
    	// ��x��ԭ������·����������һ��splay 
        for (int pre = 0, cur = x; cur; pre = cur, cur = tr[cur].fa) {
        	/*
            ����Ҫ�����ǰ�x��ʵ������Ϊpre 
            ���Ȱ�x�ڵ�splay����
            ��ʱx�ڵ����������������x����Ľڵ�
            ��x����������Ϊpre����x��ʵ���ӵ�ʵ�߾ͱ�ȡ���ˣ��ĳɵ�pre��ʵ�� 
            ��ԭ��ʵ���ӵ�fa����x�����Ե�ԭ��ʵ���ӵı߱������� 
            ����ǵ�update������Ϣ 
            */
            splay(cur);
            tr[cur].ch[1] = pre;
            update(cur);
        }
        splay(x);  // ��֤������� 
    }
    
    void makeRoot(int x) {
    	/*
        ���ܣ���ԭ���ϰ�x��������Ϊ��
        ʵ���Ͼ��ǰѸ���x����ȷ���
        ��access�������x��splay��Ȼ������������ 
        */ 
    	access(x); 
    	PutRev(x);
    }
    
    int findRoot(int x) {
    	/*
        ���ܣ���x����ԭ����������Ŀ�����ж��������Ƿ���ͨ
        �൱����x������splay�ϲ�����С�ĵ�
        ��access������������splayһ�±�֤���Ӷȣ�Ȼ������������С 
        */ 
    	access(x);
    	while (tr[x].ch[0]) {
    		PushDown(x);
            x = tr[x].ch[0];	
        }
        return x;
    }
    
    void link(int x, int y) {
    	makeRoot(x);  // ��x�ᵽԭ���ĸ� 
    	if (findRoot(y) != x)  // ��y����ԭ���ĸ�����x����x,y����ͨ 
    		tr[x].fa = y;
    }
    
    void cut(int x, int y) {
        makeRoot(x);  // ��x�ᵽԭ���ĸ� 
        /*
        �ж�x,y�Ƿ���ֱ�����ߵķ����� 
        findRoot�л���access(y),splay(y)
        ��x,y��ֱ�����ߣ�����Ϊaccess�����splay��ֻ��x,y������
        access�󣬱�֤��x�������С��y��������
        ����Ҫ�жϵ�ֻ��x��y֮��û�е�
        ����ʵ�־��� tr[x].fa == y && tr[x].ch[1] == 0 
        */
        if (findRoot(y) == x && tr[x].fa == y && tr[x].ch[1] == 0) {
            tr[x].fa = tr[y].ch[0] = 0;
            update(y);
        }
    }
    
    void change(int x, int val) {
    	// �Ľڵ�ֵֻ��Ҫsplay�������� 
        splay(x);
        tr[x].val = val;
        update(x);
    }
    
    int query(int x, int y) {
    	// �Ȱ�x�ᵽԭ������Ȼ���y������·��������������splay�ϲ�ѯ 
        makeRoot(x);
        access(y);
        return tr[y].sum;
    }
} lct;

int main() {
    int n, m;
    scanf("%d%d", &n, &m); 
    static int r[N];
    for (int i = 1; i <= n; i++)
    	scanf("%d", &r[i]);
    lct.init(n, r);
    for (int opt, x, y; m--; ) {
    	scanf("%d%d%d", &opt, &x, &y);
        switch (opt) {
            case 0: printf("%d\n", lct.query(x, y)); break;  // ѯ��x��y·������ 
            case 1: lct.link(x, y);                  break;  // ����x��y 
            case 2: lct.cut(x, y);                   break;  // ɾ����(x,y) 
            case 3: lct.change(x, y);                break;  // ����x�ϵ�Ȩֵ�ĳ�y 
        }
    }
    return 0;
}

