#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 100050, INF = 0x3f3f3f3f;

struct Node {
	int fa, ch[2], num, size, cnt;
}tr[N];

int top = 1, root; 

int newNode(int num) {
	tr[top].num = num;
	tr[top].size = tr[top].cnt = 1;
	return top++;
}

bool getlr(int x) {
	return tr[tr[x].fa].ch[1] == x;
}

void update(int x) {
	tr[x].size = tr[tr[x].ch[0]].size + tr[tr[x].ch[1]].size + tr[x].cnt;
}

void connect(int f, bool lr, int c) {
	if (f) tr[f].ch[lr] = c;
	if (c) tr[c].fa = f;
}

void rotate(int x) {
	bool lr = getlr(x);  // 0左旋1右旋 
	int y = tr[x].fa, z = tr[y].fa;
	connect(z, getlr(y), x);  // 这里是getlr(y)不是lr 
	connect(y, lr, tr[x].ch[!lr]);
	connect(x, !lr, y);
	update(y);
}

void splay(int x, int tofa=0) {  // 由于一般是splay到根，所以tofa可以设默认值 
	for (; tr[x].fa != tofa; rotate(x))
		if (tr[tr[x].fa].fa != tofa)
			rotate(getlr(x) ^ getlr(tr[x].fa) ? x : tr[x].fa);
	update(x);
	if (!tofa) root = x;
}

void insert(int num) {
	int x = root, y = 0;
	while (x && tr[x].num != num)
		y = x, x = tr[x].ch[num > tr[x].num];
	if (x) ++tr[x].cnt;
	else connect(y, num > tr[y].num, x = newNode(num));
	splay(x);
}


void find(int num) {  // 此题保证num一定存在 
	int x = root;
	while (tr[x].num != num && tr[x].ch[num > tr[x].num])
	// 因为find还可能用在找前驱后继里，所以要加后面的判断 
		x = tr[x].ch[num > tr[x].num];
	splay(x);
}

int nop(int num, bool np) {  // 0前驱1后继，返回目标结点编号 
	find(num);
	if (tr[root].num != num && (tr[root].num > num) == np)
		return root;
	int x = tr[root].ch[np];
	while (tr[x].ch[!np])
		x = tr[x].ch[!np];
	return x;
}

void del(int num) {
	int pre = nop(num, 0), nxt = nop(num, 1);
	splay(pre); splay(nxt, pre);
	int x = tr[nxt].ch[0];
	if (--tr[x].cnt) splay(x);
	else connect(nxt, 0, 0), splay(nxt, 0);
}

int rank(int num) {
	find(num);
	return tr[tr[root].ch[0]].size;
}

int kth(int k) {
	++k;
	int x = root;
	while (x) {
		int lsize = tr[tr[x].ch[0]].size;
		if (k > lsize && k <= lsize + tr[x].cnt) {  // 注意是>和<= 
			splay(x);
			return tr[x].num;
		}
		if (k <= lsize) x = tr[x].ch[0];
		else k -= lsize + tr[x].cnt, x = tr[x].ch[1];
	}
}

int nxtOrPre(int num, bool np) {
	splay(nop(num, np));
	return tr[root].num;
}

int main() {
	int m;
	scanf("%d", &m);
	insert(-INF); insert(INF);  // 哨兵结点 
	for (int opt, x; m--; ) {
		scanf("%d%d", &opt, &x);
		switch (opt) {
			case 1: insert(x); break;
			case 2: del(x); break;
			case 3: printf("%d\n", rank(x)); break;
			case 4: printf("%d\n", kth(x)); break;
			default: printf("%d\n", nxtOrPre(x, opt - 5));
		}
	}
    return 0;
}

