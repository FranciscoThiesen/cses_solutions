#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int ms = 1013;
 
int mat[ms][ms];
 
inline int solve(int y1, int x1, int y2, int x2) {
  int res = mat[y2][x2] - mat[y1 - 1][x2] - mat[y2][x1 - 1] + mat[y1 - 1][x1 - 1]; 
  return res;
}
 
int main() {
  ios::sync_with_stdio(false); cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  memset(mat, 0, sizeof mat); 
  for(int i = 1; i <= n; ++i) {
    string s;
    cin >> s;
    for(int j = 0; j < n; ++j) {
      if(s[j] == '*') mat[i][j + 1] = 1;
    }
  }
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= n; ++j) {
      mat[i][j] += (mat[i - 1][j] + mat[i][j - 1] - mat[i - 1][j - 1]); 
    } 
  }
  for(int i = 0; i < q; ++i)
  {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    cout << solve(a, b, c, d) << '\n';
  }
  return 0;
}