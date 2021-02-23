#include <bits/stdc++.h>
 
#define all(v) (v).begin(), (v).end()
 
using namespace std;
using ll = long long;
 
/* Lazy segtree.
   Garantir que:
   1 - Combinar nós é uma operação associativa
   2 - Updates são comutativos
*/
 
constexpr long long ms = 2e5 + 13;
 
long long n;
 
struct node {
    long long S, lz, lz2;
    node(ll _S = 0ll, ll _lz = 0ll, ll _lz2 = 0ll) : S(_S), lz(_lz), lz2(_lz2) {}
} st[4 * ms];
 
node combine(const node& L, const node& R) {
    return node(L.S + R.S); 
}
 
void build(const vector<node>& leaves, long long pos = 1ll, long long tl = 0, long long tr = n - 1) {
    if(tl == tr) st[pos] = leaves[tl];
    else {
        long long tm = (tl + tr) / 2;
        build(leaves, pos * 2, tl, tm);
        build(leaves, pos * 2 + 1, tm + 1, tr);
        st[pos] = combine(st[pos * 2], st[pos * 2 + 1]); 
    }
}
 
void app(long long pos, long long x1, long long x2, long long l2, long long r2)
{
    st[pos].S += x1 * (r2 - l2 + 1);
    long long soma_pa = (r2 * (r2 + 1ll ) ) / 2ll - ( l2 * (l2 - 1ll) ) / 2ll;
    st[pos].S += soma_pa * x2;
    st[pos].lz += x1;
    st[pos].lz2 += x2;
}
 
void push(long long pos, long long l2, long long m2, long long r2) {
    app(2 * pos, st[pos].lz, st[pos].lz2, l2, m2);
    app(2 * pos + 1, st[pos].lz, st[pos].lz2, m2 + 1, r2);
    st[pos].lz = st[pos].lz2 = 0;
}
 
void upd(long long l1, long long r1, long long x, long long x2, long long i = 1, long long l2 = 0, long long r2 = n - 1)
{
    if(l1 <= l2 && r2 <= r1) {
        app(i, x, x2, l2, r2);
        return;
    }
    long long m2 = (l2 + r2) / 2ll;
    push(i, l2, m2, r2);
    if(l1 <= m2) upd(l1, r1, x, x2, 2 * i, l2, m2);
    if(m2 < r1) upd(l1, r1, x, x2, 2 * i + 1, m2 + 1, r2);
    st[i].S = st[2 * i].S + st[2 * i + 1].S;
}
 
long long query(long long l1, long long r1, long long i = 1, long long l2 = 0, long long r2 = n - 1)
{
    if(l1 <= l2 && r2 <= r1) return st[i].S;
    int m2 = (l2 + r2) / 2ll;
    push(i, l2, m2, r2);
    long long ret = 0ll;
    if(l1 <= m2) ret += query(l1, r1, 2 * i, l2, m2);
    if(m2 < r1) ret += query(l1, r1, 2 * i + 1, m2 + 1, r2);
    return ret;
}
 
int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int q;
    cin >> n >> q;
    vector< node > leaves(n);
    for(int i = 0; i < n; ++i) cin >> leaves[i].S;
    build(leaves);
 
    for(int i = 0; i < q; ++i)
    {
        int t, a, b;
        cin >> t >> a >> b, --a, --b;
        if(t == 1) {
            upd(a, b, 1 - a, 1);        
        }
        else {
            cout << query(a, b) << endl;
        }
    }
    return 0;
}