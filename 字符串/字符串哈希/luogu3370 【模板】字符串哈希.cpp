#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
typedef unsigned long long ULL;
const int N = 10050;

struct Hash {
    ULL h1, h2;
    const static ULL SEED1 = 131, SEED2 = 163;  // 哈希种子，随便搞个质数 
    static ULL getHash(string s, ULL seed) {
        ULL ret = 0;
        for (int i = 0; i < s.size(); i++)
            ret = ret * seed + s[i];  // 这里利用ULL溢出自动切掉高位的特点省去mod 
        return ret;
    }
    Hash(){}
    Hash(string s): h1(getHash(s, SEED1)), h2(getHash(s, SEED2)) {}
    bool operator<(const Hash &t) const {
        return h1 < t.h1 || h1 == t.h1 && h2 < t.h2;
    }
}hash[N];

int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        hash[i] = Hash(s);
    }
    sort(hash + 1, hash + n + 1);
    int ans = 1;
    for (int i = 2; i <= n; i++)
        ans += hash[i-1] < hash[i];
    cout << ans << endl;
    return 0;
}

