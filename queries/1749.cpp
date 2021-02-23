#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
 
typedef tree<
  pair<int, int>,
  null_type,
  less< pair<int, int>>,
  rb_tree_tag,
  tree_order_statistics_node_update>
ordered_set;
 
int main() {
  ios::sync_with_stdio(false); cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> v(n);
  ordered_set SET; 
  for(int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    SET.insert({i, x});
  }
  
  for(int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    --x;
    auto vamo = SET.find_by_order(x);
    cout << vamo->second << " ";
    SET.erase(vamo);
  }
  cout << '\n';
  return 0;
 
}