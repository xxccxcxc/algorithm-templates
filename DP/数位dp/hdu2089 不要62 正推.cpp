#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int L = 7;
int f[L+5][10][2];

int dp(int n) {
	int len, num[L+5] = {0};
	for (len = 0; n; n /= 10)
		num[++len] = n % 10;
	memset(f, 0, sizeof(f));
	f[len+1][0][1] = 1;
	for (int i = len; i >= 1; i--)
		for (int j = 0; j <= 9; j++)
			for (int p = 0; p <= 1; p++)
				for (int k = p ? num[i] : 9; k >= 0; k--)
					if (k != 4 && !(j == 6 && k == 2))
						f[i][k][p&&k==num[i]] += f[i+1][j][p];
	int ret = f[1][num[1]][1];
	for (int j = 0; j <= 9; j++) 
		ret += f[1][j][0];
	return ret;
}

int main() {
	for (int l, r; cin >> l >> r && l + r; )
		cout << dp(r) - dp(l - 1) << endl;
	return 0;
}
