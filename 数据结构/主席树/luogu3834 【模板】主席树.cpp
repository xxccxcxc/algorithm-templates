#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 200050, INF = 1e9;

struct Node {
    int ls, rs, sum;
    Node(): ls(0), rs(0), sum(0) {}
}tr[N*40];  // nlogL
int top = 1, root[N];

void insert(int &cur, int pre, int val, int L, int R) {  // &cur方便更改父节点的儿子 
    (tr[cur = top++] = tr[pre]).sum++;  // insert访问到的结点一定需要新开 
    if (L == R) return;
    int mid = (L + R) >> 1;
    // 哪边要改就改哪边，另一边用原来的 
    if (val <= mid) insert(tr[cur].ls, tr[pre].ls, val, L, mid);
    else insert(tr[cur].rs, tr[pre].rs, val, mid + 1, R);
}

int kth(int lu, int ru, int L, int R, int k) {  // 标准权值线段树第k大，不过sum要用r和l-1相减 
    if (L == R) return L;
    int lCnt = tr[tr[ru].ls].sum - tr[tr[lu].ls].sum, mid = (L + R) >> 1;
    if (k <= lCnt) return kth(tr[lu].ls, tr[ru].ls, L, mid, k);
    return kth(tr[lu].rs, tr[ru].rs, mid + 1, R, k - lCnt);
}

/*
题目大意：静态区间第k大
分析：
要解决区间第k大问题，只要构造出区间l~r的权值线段树，然后对区间进行二分查找即可
再转化一下，只要得到1~l-1和1~r这两棵线段树，然后用前缀和的方法就能得到l~r的树 
主席树，全名可持久化线段树，作用是同时保存1~1,1~2,...,1~n这n个区间的权值线段树
因为第i棵数比第i-1棵树只多加入了一个数，则第i棵树大部分结点可以直接用第i-1棵的
时间O(nlogL)（操作与普通线段树相同），空间O(nlogL)（动态开点，每插入一个点空间是log的） 
这里L是数字范围，不过可以离散化 
*/
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int t, i = 1; i <= n; i++) {
        scanf("%d", &t);
        insert(root[i], root[i-1], t, -INF, INF);
    }
    for (int l, r, k; m--; ) {
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", kth(root[l-1], root[r], -INF, INF, k));
    }
    return 0;
}

