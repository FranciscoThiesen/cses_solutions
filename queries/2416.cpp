#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int ms = 2e5 + 13;
 
const long long INF = 1e18;
 
int n, q;
long long x[ms], pref[ms], ans[ms], contrib[ms], bit[ms];
vector< pair<int, int> > queries_per_startpoint[ms];
 
inline void update(int pos, long long val) {
    for(; pos <= n; pos += pos & -pos) bit[pos] += val;
}
 
long long query(int a, int b) {
    long long ans = 0;
    for(; b; b -= b & -b) ans += bit[b];
    for(a--; a; a -= a & -a) ans -= bit[a];
    return ans;
}
 
int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) {
        cin >> x[i];
        pref[i] = pref[i - 1] + x[i];
    }
    x[n + 1] = INF;
    pref[n + 1] = pref[n] + x[n + 1];
    
    for(int i = 0; i < q; ++i)
    {
        int a, b;
        cin >> a >> b;
        queries_per_startpoint[a].emplace_back(b, i);
    }
 
    deque<int> st = {n + 1};
    for(int i = n; i; i--) {
        while(!st.empty() && x[i] >= x[st.front()]) {
            update(st.front(), - contrib[st.front()]);
            st.pop_front();
        }
        contrib[i] = (st.front() - 1 - i) * x[i] - (pref[st.front() - 1] - pref[i]);
        update(i, contrib[i]);
        st.push_front(i);
        for(pair<int, int>& j : queries_per_startpoint[i]) {
            int pos = upper_bound(st.begin(), st.end(), j.first) - st.begin() - 1;
            ans[j.second] = (pos ? query(i, st[pos - 1]) : 0) + (j.first - st[pos]) * x[st[pos]] - (pref[j.first] - pref[st[pos]]);
        }
    }
    for(int i = 0; i < q; ++i) cout << ans[i] << '\n';
    return 0;
}