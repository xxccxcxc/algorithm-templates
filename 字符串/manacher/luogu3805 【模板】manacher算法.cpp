#include <bits/stdc++.h>

const int N = 11000050; 

char r[N], s[N<<1];
int len[N<<1];

int main() {
	scanf("%s", r);
	int n = 0;
	s[0] = '^';
	for (int rlen = strlen(r), i = 0; i < rlen; i++) {
		s[++n] = '*';
		s[++n] = r[i];
	}
	s[++n] = '*';
	s[n+1] = '$';
	
	int mid, mx = 0, ans = 0;
	for (int i = 1; i <= n; i++) {
		len[i] = i <= mx ? std::min(len[mid*2-i], mx-i+1) : 1;
		while (s[i-len[i]] == s[i+len[i]])
			len[i]++;
		if (i+len[i]-1 > mx) {
			mx = i+len[i]-1;
			mid = i;
		}
		ans = std::max(ans, len[i]-1);
	}
	printf("%d\n", ans);
	return 0;
}

