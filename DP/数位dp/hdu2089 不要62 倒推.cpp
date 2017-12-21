#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int L = 7;
int f[L+5][L+5];  // f[i][j]表示有i位且最高位为j的满足条件的数的个数 

void init() {
    f[0][0] = 1;
    for (int i = 1; i <= L; i++)
        for (int j = 0; j <= 9; j++)
            for (int k = 0; k <= 9; k++)
                if (j != 4 && !(j == 6 && k == 2))
                    f[i][j] += f[i-1][k];
}

int dp(int n) {  // 求小于n的合法数的个数，注意这里没有取等 
    int len, num[L+5] = {0}, ans = 0;
    for (len = 0; n; n /= 10)
        num[++len] = n % 10;
    for (int i = len; i >= 1; i--) {
        for (int j = 0; j < num[i]; j++)
            if (!(num[i+1] == 6 && j == 2))  // 这里不用防4，因为f[i][4]=0，但f[i][2]不一定为0
                ans += f[i][j];
        if (num[i] == 4 || num[i+1] == 6 && num[i] == 2) break;  // 如果枚举到1234xx或者12362xx就退 
    }
    return ans;
}

int main() {
	// 题意：求[l,r]区间内没有4和62的数的个数 
	// 数位dp 
	init();
	for (int l, r; cin >> l >> r && l + r; )
		cout << dp(r + 1) - dp(l) << endl;
	return 0;
}

