#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 105;
const double EPS = 1e-6;
int n;
double a[N][N];

int sgn(double x) {
	if (x > EPS) return 1;
	if (x < -EPS) return -1;  // 这里记得加负号 
	return 0;
}

void change(int j, int i) {  // 用第i行消第j行，把a[j][i]消成0 
	double t = a[j][i] / a[i][i];
	for (int k = 1; k <= n+1; k++)
		a[j][k] -= a[i][k] * t;
} 

bool gauss() {
	for (int i = 1; i <= n; i++) {
		int mx = i;
		for (int j = i+1; j <= n; j++)
			if (fabs(j) > fabs(mx)) mx = j;
		// 找绝对值最大的来消别的行，因为a[i][i]在change里是除数，如果太小会爆int 
		swap(a[i], a[mx]);
		if (!sgn(a[i][i])) return false;  // xi系数都是0就解不出xi了 
		for (int j = 1; j <= n; j++)
			if (j != i) change(j, i);
	}
	return true;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n+1; j++)
			cin >> a[i][j];
	if (!gauss()) puts("No Solution");
	else for (int i = 1; i <= n; i++)
		printf("%.2lf\n", a[i][n+1] / a[i][i]);
	return 0;
}

