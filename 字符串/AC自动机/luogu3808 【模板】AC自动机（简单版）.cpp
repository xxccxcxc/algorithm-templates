#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
const int N = 1e6+50;

struct AC {
	int top, ch[N][26], cnt[N], fail[N];
	
	void Insert(char *s) {  // Trie树插入 
		int len = strlen(s), u = 0;
		for (int i = 0; i < len; i++) {
			int t = s[i] - 'a';
			if (!ch[u][t]) ch[u][t] = ++top;
			u = ch[u][t];
		}
		cnt[u]++;
	}
	
	void Build() {  // 初始化fail指针 
		queue<int> q;
		for (int i = 0; i < 26; i++)
			if (ch[0][i]) q.push(ch[0][i]);  // 与根相连的点，fail指针都指向根 
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = 0; i < 26; i++)
				if (ch[u][i]) {
					fail[ch[u][i]] = ch[fail[u]][i];
					q.push(ch[u][i]);
				}
				// 对需要跳多次失配边的情况进行路径压缩（类似并查集） 
				else ch[u][i] = ch[fail[u]][i]; 
		}
	}
	
	int Query(char *s) {
		int len = strlen(s), u = 0, ret = 0;
		for (int i = 0; i < len; i++)
			// 因为已经进行了路径压缩，所以不用fail数组，直接通过ch来转移 
			for (int t = u = ch[u][s[i]-'a']; t && ~cnt[t]; t = fail[t])
				// 因为此题问的是模式串是否出现，则访问过的串不用重复访问，置为-1 
				ret += cnt[t], cnt[t] = -1;  
		return ret;
	}
} ac;

char r[N];

int main() {
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%s", r), ac.Insert(r);
	ac.Build();
	scanf("%s", r);
	printf("%d\n", ac.Query(r));
    return 0;
}

