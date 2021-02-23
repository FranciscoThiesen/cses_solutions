#include <bits/stdc++.h>
 
using namespace std;
 
template<typename T>
struct segment_tree {
  int n;
  T id;
  vector<T> tree;
  
  segment_tree(int sz, T _id) : n(sz), id(_id) {
    tree.assign(4 * n, id); 
  }
 
  T combine(const T& a, const T& b) {
    return a ^ b; 
  }
 
  void build(int L, int R, int index, const vector<T>& leaves) {
    if(L == R) tree[index] = leaves[L];
    else {
      int mid = (L + R) / 2;
      int left_kid = index * 2 + 1;
      int right_kid = index * 2 + 2;
      build(L, mid, left_kid, leaves);
      build(mid + 1, R, right_kid, leaves);
      tree[index] = combine(tree[left_kid], tree[right_kid]); 
    }
  }
  
  void build(const vector<T>& leaves) {
    assert(static_cast<int>(leaves.size()) == n);
    build(0, n - 1, 0, leaves); 
  }
 
  void update(int L, int R, int index, int upd_id, const T new_val) {
    if(L == R) tree[index] = new_val;
    else {
      int mid = (L + R) / 2;
      int left_kid = index * 2 + 1;
      int right_kid = index * 2 + 2;
      if(upd_id <= mid) update(L, mid, left_kid, upd_id, new_val); 
      else update(mid + 1, R, right_kid, upd_id, new_val);
      tree[index] = combine(tree[left_kid], tree[right_kid]);
    }
  }
 
  void update(int pos, const T new_val) {
    update(0, n - 1, 0, pos, new_val); 
  }
 
  T query(int L, int R, int index, int query_l, int query_r) {
    if(L > query_r || R < query_l) return id;
    if(L >= query_l && R <= query_r) return tree[index];
    int mid = (L + R) / 2;
    int left_kid = index * 2 + 1;
    int right_kid = index * 2 + 2;
    T QL = query(L, mid, left_kid, query_l, query_r);
    T QR = query(mid + 1, R, right_kid, query_l, query_r);
    return combine(QL, QR);
  }
 
  T query(int l, int r) { return query(0, n - 1, 0, l, r); }
 
};
 
int main()
{
  ios::sync_with_stdio(false); cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<int> leaves(n);
  for(int& x : leaves) cin >> x;
  auto seg = segment_tree(n, 0);
  seg.build(leaves);
 
  for(int i = 0; i < q; ++i) {
    int l, r;
    cin >> l >> r;
    --l; --r;
    cout << seg.query(l, r) << '\n';
  }
  
  return 0;
}