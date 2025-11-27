/* Homework 01 - RREF compare and rank */
#include <bits/stdc++.h>
using namespace std;

/* Pragma */
#pragma GCC optimize("Ofast")
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

/* Self Define */
#define IO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define MEM(_array, _value) memset(_array, _value, sizeof(_array));
#define ALL(_array) _array.begin(), _array.end()
#define LB(_array, v) lower_bound(ALL(_array), v)
#define UB(_array, v) upper_bound(ALL(_array), v)
#define vc(_data) vector<_data>
#define pii pair<int, int>
#define pdd pair<double, double>
#define mkp make_pair
#define sz size()
#define pb push_back
#define F first
#define S second
#define int long long
#define ll long long
#define ld long double
#define tpn typename

/* Self Define Template Function */
template <typename T> void pV(vector<T> _vector ) {
    for( auto _it : _vector ) cout << _it << " ";
    cout << "\n";
}

template <typename A, typename B> bool boundry( pair<A, B> &_pair, int _n, int _m ){
    return 1 <= _pair.F && _pair.F <= _n && 1 <= _pair.S && _pair.S <= _m;
}

template <typename A, typename B> istream& operator>>( istream& _is, pair<A, B> &_pair ){ 
    return _is >> _pair.F >> _pair.S;
}

template <typename A, typename B> ostream& operator<<( ostream& _os, pair<A, B> _pair ){ 
    return _os << '(' << _pair.F << " " << _pair.S << ')';
}

/* Self Define Const */
const auto dir = vector< pair<int, int> > { {1, 0}, {0, 1},  {-1, 0}, {0, -1}, 
                                            {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
const int         MAXN = 10 + 50;
const int          Mod = 1e9 + 7;
const int          INF = 0x7FFFFFFF;
const ll         LLINF = 0x7FFFFFFFFFFFFFFF;
const int       MEMINF = 0x3F;
const int   MEMINF_VAL = 0x3F3F3F3F;
const ll  MEMLLINF_VAL = 0x3F3F3F3F3F3F3F3F;
const double EPS = 1e-9;

int n, m;
double MA[MAXN][MAXN], MB[MAXN][MAXN];
char x; // 讀入 "n x m" 中的 'x'

// 將 A 轉為 RREF（化簡列階梯形）
void toRREF(double A[MAXN][MAXN]) {
    int row = 0, col = 0;
    while (row < n && col < m) {
        // 1) 於當前欄找 pivot（絕對值最大）
        int sel = row;
        for (int i = row; i < n; ++i)
            if (fabs(A[i][col]) > fabs(A[sel][col])) sel = i;

        // 此欄近似全 0，換下一欄
        if (fabs(A[sel][col]) < EPS) { ++col; continue; }

        // 2) 交換到目前的 row
        for (int j = 0; j < m; ++j) swap(A[sel][j], A[row][j]);

        // 3) pivot 歸一
        double div = A[row][col];
        for (int j = 0; j < m; ++j) A[row][j] /= div;

        // 4) 消去其他列
        for (int i = 0; i < n; ++i) {
            if (i == row) continue;
            double factor = A[i][col];
            if (fabs(factor) < EPS) continue;
            for (int j = 0; j < m; ++j) A[i][j] -= factor * A[row][j];
        }

        ++row; ++col;
    }

    // 將極小值壓成 0，避免殘差
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (fabs(A[i][j]) < EPS) A[i][j] = 0.0;
}

// 判斷兩個矩陣（已做 RREF）是否元素皆近似相等
bool same(double A[MAXN][MAXN], double B[MAXN][MAXN]) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (fabs(A[i][j] - B[i][j]) > EPS) return false;
    return true;
}

// 在 RREF 後計算 rank（非零列數）
int getRank(double A[MAXN][MAXN]) {
    int r = 0;
    for (int i = 0; i < n; ++i) {
        bool nz = false;
        for (int j = 0; j < m; ++j)
            if (fabs(A[i][j]) > EPS) { nz = true; break; }
        if (nz) ++r;
    }
    return r;
}

int cnt = 0;

signed main(int argc, char* argv[]) {
    ifstream fin;
    fin.open(argv[1]);

    // if( !fin ){
    //     cout << "in_1.txt couldn't be open." << endl;
    // }

    // 反覆讀：n x m，接著兩個 n×m 矩陣
    while (fin >> n >> x >> m) {            // 例如 4 x 9

        for (int i = 0; i < n; ++i)         // 第一個矩陣 A
            for (int j = 0; j < m; ++j)
                fin >> MA[i][j];

        for (int i = 0; i < n; ++i)         // 第二個矩陣 B
            for (int j = 0; j < m; ++j)
                fin >> MB[i][j];

        toRREF(MA);
        toRREF(MB);

        bool eq = same(MA, MB);

        if (cnt++ > 0) cout << "\n";

        if(eq) cout << "Yes," << getRank(MA);
        else cout << "No,"  << getRank(MA) << "," << getRank(MB);
    }
} 