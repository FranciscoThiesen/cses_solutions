#include <bits/stdc++.h>
 
using namespace std;
 
#define all(x) (x).begin(), (x).end()
 
template <typename T, typename U> struct seg_lazy
{
	int S, H;
	T identity;
	vector<T> value;
 
	U noop;
	vector<bool> dirty;
	vector<U> prop;
 
	seg_lazy<T, U>(int _S, T _identity = T(), U _noop = U())
	{
		identity = _identity, noop = _noop;
		for (S = 1, H = 1; S < _S;) S *= 2, H++;
 
		value.assign(2 * S, identity);
		dirty.assign(2 * S, false);
		prop.assign(2 * S, noop);
	}
 
	void set_leaves(vector<T>& leaves)
	{
		copy(all(leaves), value.begin() + S);
		for (int i = S - 1; i > 0; --i)
			value[i] = value[2 * i] * value[2 * i + 1];
		dirty.assign(2 * S, false);
		prop.assign(2 * S, noop);
	}
 
	void apply(int i, U& update)
	{
		value[i] = update(value[i]);
		if (i < S)
		{
			prop[i] = prop[i] + update;
			dirty[i] = true;
		}
	}
 
	void rebuild(int i)
	{
		for (int l = i / 2; l; l /= 2)
		{
			T combined = value[2 * l] * value[2 * l + 1];
			value[l] = prop[l](combined);
		}
	}
 
	void propagate(int i)
	{
		for (int h = H; h > 0; --h)
		{
			int l = (i >> h);
			if (dirty[l])
			{
				apply(2 * l, prop[l]);
				apply(2 * l + 1, prop[l]);
				prop[l] = noop;
				dirty[l] = false;
			}
		}
	}
 
	void upd(int i, int j, U update)
	{
		i += S, j += S;
		propagate(i), propagate(j);
		for (int l = i, r = j; l <= r; l /= 2, r /= 2)
		{
			if ((l & 1) == 1) apply(l++, update);
			if ((r & 1) == 0) apply(r--, update);
		}
		rebuild(i), rebuild(j);
	}
 
	T query(int i, int j)
	{
		i += S, j += S;
		propagate(i), propagate(j);
 
		T res_left = identity, res_right = identity;
		for (; i <= j; i /= 2, j /= 2)
		{
			if ((i & 1) == 1) res_left = res_left * value[i++];
			if ((j & 1) == 0) res_right = value[j--] * res_right;
		}
        return res_left * res_right;
	}
};
 
// node tem que ter construtor e operador *
struct Node
{
	long long val, length;
	Node(long long _val = 0, long long _length = 0) : val(_val), length(_length) {}
	Node operator*(const Node& rhs) const
	{
		return Node(val + rhs.val, length + rhs.length);
	}
};
 
struct Op
{
	long long kind, inc;
	Op(long long _kind = 0, long long _inc = 0) : kind(_kind), inc(_inc) {}
	
    Node operator()(const Node& rhs) const
	{
        if(kind == 0) return Node(rhs.val + inc * rhs.length, rhs.length);
        else return Node(inc * rhs.length, rhs.length);
	}
	
    Op operator+(const Op& rhs) const 
    {
        if(kind == 0 && rhs.kind == 1) return Op(rhs.kind, rhs.inc);
        else if(kind == 1 && rhs.kind == 0) return Op(1, inc + rhs.inc);
        else if(kind == 0 && rhs.kind == 0) return Op(0, inc + rhs.inc);
        return Op(rhs.kind, rhs.inc);
    }
};
 
int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    auto ST = seg_lazy<Node, Op>(n);
    vector< Node > values(n);
    
    for(auto& v : values)
    {
        v.length = 1;
        cin >> v.val;
    }
 
    ST.set_leaves(values);
 
    for(int i = 0; i < q; ++i)
    {
        int t;
        cin >> t;
        if(t == 1)
        {
            int a, b, x;
            cin >> a >> b >> x;
            --a; --b;
            ST.upd(a, b, Op(0, x));
        }
        else if(t == 2)
        {
            int a, b, x;
            cin >> a >> b >> x;
            --a; --b;
            ST.upd(a, b, Op(1, x));
        }
        else
        {
            int a, b;
            cin >> a >> b; --a; --b;
            cout << ST.query(a, b).val << '\n';
        }
    }
    return 0;
}