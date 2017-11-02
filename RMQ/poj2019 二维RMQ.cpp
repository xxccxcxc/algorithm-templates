#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 300, S = 10;
int n, b, m, mx[N][N][S], mi[N][N][S];
/*
这题题意是给定三个数n,m,b和一个n*m的矩阵，有若干次询问，询问某个b*b的正方形中最大最小值之差
mx[i][j][k]表示以(i,j)为左上角，边长为2^k的正方形中的最大值
状态转移就把这个正方形分成四个边长为2^(k-1)的小正方形再取max
询问也是把询问的正方形分成四个边长为2^t的正方形（可能会重叠）
预处理O(n^2logn)，询问O(1)，空间O(n^2logn) 
如果正方形改成矩形，就需要开四维数组表示顶点横纵坐标、长和宽
预处理O(n^2log2n)，询问O(1)，空间O(n^2log2n) 
如果空间开不下，可以对每行进行一个一维RMQ，询问时O(n)枚举行取最大值
这样预处理O(n^2logn)，询问O(n)，空间O(n^2logn)（好像也没差多少） 
*/ 
int main() {
	scanf("%d%d%d", &n, &b, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			scanf("%d", &mx[i][j][0]);
			mi[i][j][0] = mx[i][j][0];
		}
	for (int k = 1; k <= log(b) / log(2); k++)
		for (int i = 1, len = 1 << (k - 1); i <= n - (1 << k) + 1; i++)
			for (int j = 1; j <= n - (1 << k) + 1; j++) {
				mx[i][j][k] = max(mx[i][j][k-1], max(mx[i+len][j][k-1], max(mx[i][j+len][k-1], mx[i+len][j+len][k-1])));
				mi[i][j][k] = min(mi[i][j][k-1], min(mi[i+len][j][k-1], min(mi[i][j+len][k-1], mi[i+len][j+len][k-1])));
			}
	for (int t = log(b) / log(2), py = b - (1 << t), x, y; m--; ) {
		scanf("%d%d", &x, &y);
		int maxx = max(mx[x][y][t], max(mx[x+py][y][t], max(mx[x][y+py][t], mx[x+py][y+py][t])));
		int minn = min(mi[x][y][t], min(mi[x+py][y][t], min(mi[x][y+py][t], mi[x+py][y+py][t])));
		printf("%d\n", maxx - minn);
	}
	return 0;
}
