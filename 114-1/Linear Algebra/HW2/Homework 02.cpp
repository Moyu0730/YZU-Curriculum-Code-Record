#include <bits/stdc++.h>
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
using namespace std;
using namespace cv;

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
const int         MAXN = 1e7 + 50;
const int          Mod = 1e9 + 7;
const int          INF = 0x7FFFFFFF;
const ll         LLINF = 0x7FFFFFFFFFFFFFFF;
const int       MEMINF = 0x3F;
const int   MEMINF_VAL = 0x3F3F3F3F;
const ll  MEMLLINF_VAL = 0x3F3F3F3F3F3F3F3F;

struct Atom {
    string type;
    double x, y, z;
};

vector<Atom> read_atoms(const string& filename) {
    vector<Atom> atoms;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Atom a;
        if( ss >> a.x >> a.y >> a.z >> a.type ){
            atoms.push_back(a);
        }
    }

    return atoms;
}

void kabsch_superposition(const vector<Atom>& input, const vector<Atom>& ref_atoms, const vector<size_t>& indices, vector<Atom>& output_atoms) {
    size_t N = indices.size();
    
    Mat P(N, 3, CV_64F);
    Mat Q(N, 3, CV_64F);
    Mat centeredP = Mat::zeros(1, 3, CV_64F);
    Mat centeredQ = Mat::zeros(1, 3, CV_64F);
    for (size_t idx = 0; idx < N; ++idx) {
        const Atom& atomP = input[indices[idx]];
        const Atom& atomQ = ref_atoms[idx];
        
        P.at<double>(idx, 0) = atomP.x;
        P.at<double>(idx, 1) = atomP.y;
        P.at<double>(idx, 2) = atomP.z;
        Q.at<double>(idx, 0) = atomQ.x;
        Q.at<double>(idx, 1) = atomQ.y;
        Q.at<double>(idx, 2) = atomQ.z;
        
        if( idx == 1 || idx == 4 ){
            centeredP.at<double>(0, 0) += atomP.x;
            centeredP.at<double>(0, 1) += atomP.y;
            centeredP.at<double>(0, 2) += atomP.z;
            centeredQ.at<double>(0, 0) += atomQ.x;
            centeredQ.at<double>(0, 1) += atomQ.y;
            centeredQ.at<double>(0, 2) += atomQ.z;
        }
    }
    
    centeredP /= 2.0;
    centeredQ /= 2.0;
    
    Mat P_centered = P.clone();
    Mat Q_centered = Q.clone();
    for (size_t i = 0; i < N; ++i) {
        P_centered.row(i) -= centeredP;
        Q_centered.row(i) -= centeredQ;
    }
    
    Mat H = P_centered.t() * Q_centered;
    
    Mat U, W, Vt;
    SVD::compute(H, W, U, Vt);
    Mat V = Vt.t();
    
    Mat R_init = V * U.t();
    double det = determinant(R_init);
    
    if (det < 0) {
        Mat M = Mat::eye(3, 3, CV_64F);
        M.at<double>(2, 2) = -1.0;
        
        R_init = V * M * U.t();
    }

    Mat R = R_init;
    
    Mat t = centeredQ.t() - R * centeredP.t();
    
    output_atoms.clear();
    output_atoms.reserve(input.size());
    for (const Atom& atom : input) {
        Mat p_orig = ( Mat_<double>(3, 1) << atom.x, atom.y, atom.z );
        Mat p_new = R * p_orig + t;
        Atom newAtom;
        newAtom.type = atom.type;
        
        double nx = p_new.at<double>(0, 0);
        double ny = p_new.at<double>(1, 0);
        double nz = p_new.at<double>(2, 0);
        
        if( fabs(nx) < 5e-5 ) nx = 0.0;
        if( fabs(ny) < 5e-5 ) ny = 0.0;
        if( fabs(nz) < 5e-5 ) nz = 0.0;
        newAtom.x = nx;
        newAtom.y = ny;
        newAtom.z = nz;
        output_atoms.push_back(newAtom);
    }
}

signed main(int argc, char* argv[]) {
    IO;

    string case_file = argv[1];
    string ref_file = argv[2];
    
    vector<Atom> input = read_atoms(case_file);
    vector<Atom> ref_atoms = read_atoms(ref_file);
    
    vector<size_t> indices(12);
    iota(indices.begin(), indices.end(), 0);
    
    vector<Atom> output_atoms;
    kabsch_superposition(input, ref_atoms, indices, output_atoms);
    
    cout << fixed << setprecision(4);
    for (const Atom& atom : output_atoms) {
        cout << atom.x << " " << atom.y << " " << atom.z << " " << atom.type << "\n";
    }
}