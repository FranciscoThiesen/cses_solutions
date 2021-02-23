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
 
template <typename T> struct seg
{
	int N;
	vector<T> Tree;
	T id;
 
	seg(int n, T dummy) : N(n), id(dummy) { Tree.assign(2 * N, id); }
 
	void build()
	{
		for (int idx = N - 1; idx > 0; --idx)
			Tree[idx] = Tree[(idx << 1)] * Tree[(idx << 1) | 1];
	}
 
	void update(int p, T val)
	{
		Tree[p += N] = val;
		while (p > 1)
		{
            if((p^1) > p) Tree[p >> 1] = Tree[p] * Tree[p ^ 1];
            else Tree[p >> 1] = Tree[p^1] * Tree[p];
			p >>= 1;
		}
	}
 
	// Query of [l, r)
	T query(int l, int r)
	{
		T res_r, res_l= id;
		for (l += N, r += N; l < r; l >>= 1, r >>= 1)
		{
			if (l & 1) res_l = res_l * Tree[l++];
			if (r & 1) res_r = Tree[--r] * res_r;
		}
		return res_l * res_r;
	}
};
 
struct node {
    ll bp, bo, bs, sum;
    node(ll _bp = 0ll, ll _bo = 0ll, ll _bs = 0ll, ll _sum = 0ll) : bp(_bp), bo(_bo), bs(_bs), sum(_sum) {}
    node operator* (const node& rhs) const {
        // Tenho que ensinar a combinar dois nós!
        ll new_best_prefix = max(bp, sum + rhs.bp);
        ll new_best_suffix = max(rhs.bs, rhs.sum + bs);
        ll new_best_overall = max(bo, max(rhs.bo, bs + rhs.bp));
        ll new_sum = sum + rhs.sum;
        return node(new_best_prefix, new_best_overall, new_best_suffix, new_sum);
    }
};
 
int main() 
{
    buff();
    int n, m;
    cin >> n >> m;
    
    auto S = seg<node>(n, node());
    for(int i = 0; i < n; ++i)
    {
        ll x;
        cin >> x;
        S.Tree[n + i] = node(x, x, x, x);
    }
 
    S.build();
    
    for(int i = 0; i < m; ++i)
    {
        int k; ll x;
        cin >> k >> x;
        --k;
        S.update(k, node(max(0ll, x), max(0ll, x), max(0ll, x), x));
        auto res = S.query(0, n);
        cout << res.bo << endl;
    }
    
    return 0; 
}