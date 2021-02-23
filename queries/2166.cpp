#include <bits/stdc++.h>
 
using namespace std;
 
template <typename T> struct seg_tree
{
	int S;
 
	T identity;
	vector<T> value;
 
	seg_tree<T>(int _S, T _identity = T())
	{
		S = _S, identity = _identity;
		value.resize(2 * S + 1, identity);
	}
 
	void set_leaves(vector<T>& leaves)
	{
		copy(leaves.begin(), leaves.end(), value.begin() + S);
 
		for (int i = S - 1; i > 0; i--)
			value[i] = value[2 * i] * value[2 * i + 1];
	}
 
	void upd(int i, T v)
	{
		i += S;
		value[i] = v;
		while (i > 1)
		{
			i /= 2;
			value[i] = value[2 * i] * value[2 * i + 1];
		}
	}
 
	// query is about closed ranges [i, j]
	T query(int i, int j)
	{
		T res_left = identity, res_right = identity;
		for (i += S, j += S; i <= j; i /= 2, j /= 2)
		{
			if ((i & 1) == 1) res_left = res_left * value[i++];
			if ((j & 1) == 0) res_right = value[j--] * res_right;
		}
		return res_left * res_right;
	}
};
 
struct Node {
    int len;
    long long max_pref, max_suff, full_sum;
    Node(int _len = 1, long long _max_pref = 0ll, long long _max_suff = 0ll, long long _full_sum = 0ll) :
        len(_len), max_pref(_max_pref), max_suff(_max_suff), full_sum(_full_sum) {}
    
    Node(long long val) {
        len = 1;
        max_pref = max(0ll, val); max_suff = max(0ll, val);
        full_sum = val;
    }
 
    Node operator* (const Node& rhs)
    {
        int new_len = len + rhs.len;
        long long m_pref = max(0ll, max(full_sum + rhs.max_pref, max_pref));
        long long m_suff = max(0ll, max(rhs.full_sum + max_suff, rhs.max_suff));
        long long fs = full_sum + rhs.full_sum;
        return Node(new_len, m_pref, m_suff, fs); 
    }
};
 
int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector< Node > V(n);
    for(int i = 0; i < n; ++i)
    {
        V[i].len = 1;
        cin >> V[i].full_sum;
        V[i].max_pref = max(0ll, V[i].full_sum);
        V[i].max_suff = max(0ll, V[i].full_sum);
    }
    
    seg_tree<Node> ST(n);
    ST.set_leaves(V);
    
    for(int i = 0; i < q; ++i)
    {
        int t;
        cin >> t;
        if(t == 1) 
        {
            long long k, u;
            cin >> k >> u;
            ST.upd(k - 1, Node(u));
        }
        else
        {
            int a, b;
            cin >> a >> b;
            cout << ST.query(a - 1, b - 1).max_pref << '\n';
        }
    }
    return 0;
}