#include <bits/stdc++.h>
using namespace std;
#define TRACE(x) x
#define WATCH(x) TRACE( cout << #x" = " << x << endl)
#define PRINT(x) TRACE(printf(x))
#define WATCHR(a, b) TRACE( for(auto c = a; c != b;) cout << *(c++) << " "; cout << endl)
#define WATCHC(V) TRACE({cout << #V" = "; WATCHR(V.begin(), V.end());})
#define rep(i, a, b) for(int i = (a); (i) < (b); ++(i))
#define trav(a, x) for(auto& a : x)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) static_cast<int>(x.size())
#define mp make_pair
#define fi first
#define se second
 
using vi = vector<int>;
using vvi = vector<vi>;
using ll = long long;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
 
void buff() { ios::sync_with_stdio(false); cin.tie(nullptr); }
 
constexpr ll MOD = 1e9 + 7;
 
inline ll pow_mod(ll a, ll b, ll mod = MOD) {
    ll res = 1; a %= mod; assert(b >= 0);
    for(;b;b>>=1) {
        if(b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
    }
    return res;
}
 
template<typename T> inline void remin(T& x, const T& y) { x = min(x, y); }
template<typename T> inline void remax(T& x, const T& y) { x = max(x, y); }
 
template<typename T> ostream& operator<<(ostream &os, const vector<T>& v) {
    os << "{"; string sep; for(const auto& x : v) os << sep << x, sep = ", "; return os << "}"; 
}
 
template<typename T, size_t size> ostream& operator<<(ostream& os, const array<T, size>& arr) {
    os << "{"; string sep; for(const auto& x : arr) os << sep << x, sep = ", "; return os << "}"; 
}
 
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { 
    return os << '(' << p.first << ", " << p.second << ')'; 
}
 
inline int64_t gilbert_order(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = gilbert_order(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}
 
struct query {
    int l, r, i;
    int64_t ord;
    query(int l, int r, int i) : l(l), r(r), i(i) {
        ord = gilbert_order(l, r, 19, 0);
    }
};
 
inline bool operator<(const query& a, const query& b) {
    return a.ord < b.ord;
}
 
constexpr int ms = 2e5 + 13;
int f[ms];
 
int main() {
    buff();
    int n, m;
    cin >> n >> m;
    vector<int> v(n), cpy;
    for(int i = 0; i < n; ++i) {
        cin >> v[i];
        cpy.push_back(v[i]);
    }
    sort(all(cpy)); 
    cpy.erase(unique(all(cpy)), cpy.end());
    for(int i = 0; i < n; ++i) {
        v[i] = (int) (lower_bound(all(cpy), v[i]) - cpy.begin());
    }
    
    vector< query > q;
    for(int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y; --x; --y;
        q.push_back(query(x, y, i));
    }
    
    sort(all(q));
    
    int l = 0, r = 0;
    vector<int> ans(m, 0);
    int cur_val = 0;
 
    auto add = [&] (int id) {
        f[v[id]]++;
        if(f[v[id]] == 1) cur_val++;
    };
 
    auto remove = [&] (int id) {
        f[v[id]]--;
        if(f[v[id]] == 0) cur_val--;
    };
    
    add(0);
    for(const auto& qry : q) {
        while(l < qry.l) {
            remove(l);
            ++l;
        }
        while(l > qry.l) {
            --l; 
            add(l);
        }
        while(r < qry.r) {
            ++r;
            add(r);
        }
        while(r > qry.r) {
            remove(r);
            r--;
        }
        ans[qry.i] = cur_val;
    }
 
    for(const auto& val : ans) cout << val << endl;
    return 0;
}