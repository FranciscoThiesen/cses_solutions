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
 
struct item {
    pair<int, int> key;
    int prior, cnt;
    item * l, * r;
    item() { }
    item (pair<int, int> key, int prior) : key(key), prior(prior), cnt(1), l(NULL), r(NULL) { }
};
 
typedef item * pitem;
 
inline int cnt (pitem t) {
    return t ? t->cnt : 0;
}
 
inline void upd_cnt (pitem t) {
    if (t) t->cnt = 1 + cnt(t->l) + cnt(t->r);
}
 
void split (pitem t, pair<int, int> key, pitem & l, pitem & r) {
    if (!t)
        l = r = NULL;
    else if (key < t->key)
        split (t->l, key, l, t->l),  r = t;
    else
        split (t->r, key, t->r, r),  l = t;
    upd_cnt(t);
}
 
void insert (pitem & t, pitem it) {
    if (!t)
        t = it;
    else if (it->prior > t->prior)
        split (t, it->key, it->l, it->r),  t = it;
    else
        insert (it->key < t->key ? t->l : t->r, it);
    upd_cnt(t);
}
 
void merge (pitem & t, pitem l, pitem r) {
    if (!l || !r)
        t = l ? l : r;
    else if (l->prior > r->prior)
        merge (l->r, l->r, r),  t = l;
    else
        merge (r->l, l, r->l),  t = r;
    upd_cnt(t);
}
 
void erase (pitem & t, pair<int, int> key) {
    if (t->key == key) {
        pitem th = t;
        merge (t, t->l, t->r);
        delete th;
    }
    else
        erase (key < t->key ? t->l : t->r, key);
    upd_cnt(t);
}
 
pitem unite (pitem l, pitem r) {
    if (!l || !r)  return l ? l : r;
    if (l->prior < r->prior)  swap (l, r);
    pitem lt, rt;
    split (r, l->key, lt, rt);
    l->l = unite (l->l, lt);
    l->r = unite (l->r, rt);
    return l;
}
 
 
int n, q, x, y;
char c;
 
int main() {
    buff();
    pitem root = nullptr;
    cin >> n >> q;
    vector<int> sal(n);
 
    for(int i = 0; i < n; ++i) {
        cin >> sal[i];
        pitem cur = new item(make_pair(sal[i], i), rand() - 1); 
        insert(root, cur);
    }
 
    // agora tenho que resolver as queries
    for(int i = 0; i < q; ++i) 
    {
        cin >> c >> x >> y;
        if(c == '?') 
        {
            pair<int, int> grande = {y + 1, -1};
            int ans = 0;
            pitem L, R;
            split(root, grande, L, R);
            ans += (L ? L->cnt : 0);
            merge(root, L, R);
            
            grande.first = x;
            split(root, grande, L, R);
            ans -= (L ? L->cnt : 0);
            merge(root, L, R);
            
            cout << ans << '\n';
        }
        else {
            int id = x - 1;
            erase(root, make_pair(sal[id], id));
            sal[id] = y;
            pitem cur = new item(make_pair(sal[id], id), rand() - 1);
            insert(root, cur);
        }
    }
    return 0;
}
 