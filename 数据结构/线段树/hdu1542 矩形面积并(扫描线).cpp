#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 150;

struct Seg {
	int sgn;
	double l, r, h;
	Seg() {}
	Seg(double _l, double _r, double _h, int _sgn): l(_l), r(_r), h(_h), sgn(_sgn) {}
	bool operator<(const Seg &t) const { return h < t.h; }  // 按y坐标排序，从下往上扫 
}seg[N<<1];
double all[N<<1];
int add[N<<3];
double sum[N<<3];

void pushup(int u, int ul, int ur) {
	/*
	这题的线段树很玄学，不需要下传标记，而是用了add和sum数组
	add数组表示整个区间被加了几次，sum数组保存覆盖区间个数
	如果add不为0，则整个区间肯定都被覆盖了，sum=len
	如果add为0，则用儿子的答案来更新sum 
	这样做可能会出现一个问题，就是对于区间(l,r)的修改没有影响到(l,r)的子树
	但其实这题这样搞并不会出问题，因为如果(l,r)的add改为非0，则(l,r)全被覆盖了，子树的sum对答案无影响 
	如果(l,r)的add改为0，则(l,r)被改了一圈又回到初始状态，那些对(l,r)的修改自然对子树无影响 
	*/ 
	if (add[u]) sum[u] = all[ur+1] - all[ul];
	else if (ul == ur) sum[u] = 0;
	else sum[u] = sum[u<<1] + sum[u<<1|1];
}

void update(int u, int ul, int ur, int l, int r, int sgn) {
	if (ul == l && ur == r) {
		add[u] += sgn;
		pushup(u, ul, ur);
		return;
	}
	int mid = (ul + ur) >> 1;
	if (l <= mid) update(u<<1, ul, mid, l, min(r, mid), sgn);
	if (r > mid) update(u<<1|1, mid+1, ur, max(l, mid+1), r, sgn);
	pushup(u, ul, ur);
}

int main() {
	// 本题题意为求若干矩形面积并，做法是离散化+扫描线+线段树 
	for (int n, cas = 1; scanf("%d", &n) == 1 && n; cas++) {
		for (int i = 0; i < n; i++) {
			double r1, r2, r3, r4;
			scanf("%lf%lf%lf%lf", &r1, &r2, &r3, &r4);
			seg[i<<1] = Seg(r1, r3, r2, 1);  // 矩形底边 
			seg[i<<1|1] = Seg(r1, r3, r4, -1);  // 矩形顶边 
			all[i<<1] = r1; all[i<<1|1] = r3;  // 离散化x坐标 
		}
		n <<= 1;
		sort(seg, seg + n);
		sort(all, all + n);
		int m = unique(all, all + n) - all;  // 得到离散化后数的个数 
		memset(add, 0, sizeof(add));
		memset(sum, 0, sizeof(sum));
		double ans = 0;
		for (int i = 0; i < n - 1; i++) {
			int l = lower_bound(all, all + m, seg[i].l) - all;  // 二分求坐标离散化后的值 
			int r = lower_bound(all, all + m, seg[i].r) - all;
			/*
			这里跟普通线段树有一点区别，更新的是l~r-1而不是l~r
			因为线段树如果更新[1,2],[2,3]，则2这个点会被加两次，而(1,2)(2,3)这两条线段是不重叠的
			所以现在线段树不能表示一个点，而应该表示一段区间，才不会出现有公共端点的线段在树上重叠 
			这里采用左闭右开区间，线段树上点i表示区间[i, i+1)，更新时更新l~r-1表示[l, r)这条线段 
			*/ 
			if (l < r) update(1, 0, m - 1, l, r-1, seg[i].sgn);
			ans += sum[1] * (seg[i+1].h - seg[i].h);  // 省去询问操作，直接拿sum[1]表示总覆盖区间数 
		}
		printf("Test case #%d\nTotal explored area: %.2f\n\n", cas, ans);  
	}
    return 0;
}

