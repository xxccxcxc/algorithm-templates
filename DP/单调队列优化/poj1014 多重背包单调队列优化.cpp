#include <iostream>
#include <utility>
#include <cstring>
using namespace std;
typedef pair<int, int> Data;
const int N = 7, M = 2e5+50;
int n = 6, w[N] = {0, 1, 2, 3, 4, 5, 6}, c[N] = {0, 1, 2, 3, 4, 5, 6};
int cnt[N], m, f[M];
Data q[M];
int L, R;

void Solve() {
	m /= 2;
	memset(f, 0, sizeof(f));
	for (int i = 1; i <= n; i++) {
		for (int r = 0; r < w[i]; r++) {
			L = 1; R = 0;
			for (int j = r, k = 0; j <= m; j += w[i], k++) {
				while (L <= R && k - q[L].second > cnt[i]) L++;
				int val = f[j] - k * c[i];
				while (L <= R && q[L].first < val) R--;
				q[++R] = make_pair(val, k);
				f[j] = q[L].first + k * c[i];
			}
		}
	}
	if (f[m] == m) printf("Can be divided.\n\n");
	else printf("Can't be divided.\n\n");
}

int main() {
	for (int cas = 1; ; cas++) {
		m = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &cnt[i]);
			m += cnt[i] * c[i];
		}
		if (!m) break;
        printf("Collection #%d:\n", cas);
        if (m % 2) {
			printf("Can't be divided.\n\n");
			continue;
		}
		Solve();
	}
	return 0;
}

