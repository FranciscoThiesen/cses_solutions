#include <bits/stdc++.h>
 
using namespace std;
 
int main()
{
  ios::sync_with_stdio(false); cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<long long> v(n);
  for(auto& x : v) cin >> x;
  vector<long long> p_sum(n);
  partial_sum(v.begin(), v.end(), p_sum.begin());
  for(int i = 0; i < q; ++i) {
    int a, b;
    cin >> a >> b;
    --a; --b;
    cout << p_sum[b] - (a > 0 ? p_sum[a - 1] : 0ll) << '\n';
  }
  return 0;
}
