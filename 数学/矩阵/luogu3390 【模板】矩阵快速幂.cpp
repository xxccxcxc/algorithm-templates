#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;

class Matrix {
private:
    static const LL MOD = 1000000007;  // 静态成员变量，对于类的所有实例都是同一个变量 
    static const int N = 105;
    LL mat[N][N];
    int n, m;
    
public:
    Matrix(int _n=0, int _m=0) {
        n = _n; m = _m;
        memset(mat, 0, sizeof(mat));
    }
    
    Matrix operator*(const Matrix &b)const {
        if (m != b.n) {
            cout << "operator* error\n";
            return Matrix();
        }
        Matrix ret(n, b.m);
        for (int i = 0; i < ret.n; i++)
            for (int j = 0; j < ret.m; j++)
                for (int k = 0; k < m; k++)
                    ret.mat[i][j] = (ret.mat[i][j] + mat[i][k] * b.mat[k][j]) % MOD;
        return ret;
    }
    
    Matrix operator*=(const Matrix &b) {
        *this = *this * b;
        return *this;
    }
    
    Matrix operator^(LL k)const {
        Matrix tmp = *this, ret = *this;
        for (--k; k; k >>= 1, tmp *= tmp)  // --k是因为如果乘k次的话ret的初值应该是单位矩阵，懒得搞 
            if (k & 1)
                ret *= tmp;
        return ret;
    }
    
    friend istream& operator>>(istream&, Matrix&);
    friend ostream& operator<<(ostream&, const Matrix&);
};

istream& operator>>(istream &in, Matrix &a) {
    for (int i = 0; i < a.n; i++)
        for (int j = 0; j < a.m; j++)
            in >> a.mat[i][j];
    return in;
}

ostream& operator<<(ostream &out, const Matrix &a) {
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.m; j++)
            out << a.mat[i][j] << ' ';
        out << endl;
    }
    return out;
}

int main() {
    int n; LL k;
    cin >> n >> k;
    Matrix a(n, n);
	cin >> a; 
	// 这里如果 cin >> n >> k >> a 的话不知道为什么输不进来
    cout << (a ^ k);
    return 0;
}
