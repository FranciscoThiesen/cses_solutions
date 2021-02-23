#include <bits/stdc++.h>
 
using namespace std;
 
constexpr int bs = 500;
constexpr long long inf = 0x3f3f3f3fLL;
 
int n, q;
 
 
int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> q; 
    vector< long long > price(n);
    for(auto& p : price) cin >> p;
    
    vector< long long  > cheap_left(bs, -1), cheap_right(bs, -1);
    
    for(long long i = 0; i < n; ++i)
    {
        int block_num = i / bs;
        
        long long left_dist = i + price[i];
        if(cheap_left[block_num] == -1) cheap_left[block_num] = i;
        else if(left_dist < price[cheap_left[block_num]] + cheap_left[block_num]) cheap_left[block_num]= i;
 
        long long right_dist = (n - i) + price[i];
        if(cheap_right[block_num] == -1) cheap_right[block_num] = i;
        else if(right_dist < price[cheap_right[block_num]] + (n - cheap_right[block_num])) cheap_right[block_num] = i;
    }
    
    auto update_block = [&] (int b_idx) 
    {
        int st = b_idx * bs;
        int nd = min(n, st + bs);
        cheap_left[b_idx] = cheap_right[b_idx] = -1;
        for(int i = st; i < nd; ++i)
        {
            long long left_dist = i + price[i];
            if(cheap_left[b_idx] == -1) cheap_left[b_idx] = i;
            else if(left_dist < price[cheap_left[b_idx]] + cheap_left[b_idx]) cheap_left[b_idx]= i;
 
            long long right_dist = (n - i) + price[i];
            if(cheap_right[b_idx] == -1) cheap_right[b_idx] = i;
            else if(right_dist < price[cheap_right[b_idx]] + (n - cheap_right[b_idx])) cheap_right[b_idx] = i;
        }
    };
    
    auto solve = [&] (int idx) 
    {
        int b_idx = idx / bs;
        int st = b_idx * bs;
        int nd = min(n, st + bs);
        long long ans = inf;
        for(int i = st; i < nd; ++i)
        {
            long long d = abs(i - idx) + price[i];
            ans = min(ans, d); 
        }
        
        for(int b = 0; b < bs; ++b)
        {
            if(b == b_idx || b * bs >= n) continue;
            if(b < b_idx)
            {
                long long d = price[cheap_right[b]] + (idx - cheap_right[b]);
                ans = min(ans, d);
            }
            else
            {
                long long d = price[cheap_left[b]] + (cheap_left[b] - idx);
                ans = min(ans, d);
            }
        }
        return ans;
    };
    
    for(int i = 0; i < q; ++i)
    {
        int t;
        cin >> t;
        if(t == 1)
        {
            int k; long long x;
            cin >> k >> x;
            // change of price
            --k;
            price[k] = x;
            update_block(k / bs);
        }
        else
        {
            int pos; cin >> pos;
            cout << solve(pos - 1) << '\n';
        }
    }
    return 0;
}