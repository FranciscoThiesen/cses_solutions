#include <bits/stdc++.h>
 
using namespace std;
 
template <typename T> struct BIT2D
{
	vector<vector<T>> table;
	int n, m;
	T id;
 
	BIT2D(int _n, int _m, T _id) : n(_n + 1), m(_m + 1), id(_id)
	{
		table.assign(n, vector<T>(m));
	}
 
	// 0-indexed!
	inline void modify(int i, int j, T delta)
	{
		++i, ++j;
		int x = i;
		while (x < n)
		{
			int y = j;
			while (y < m)
			{
				table[x][y] += delta;
				y |= (y + 1);
			}
			x |= (x + 1);
		}
	}
 
	inline T get(int i, int j)
	{
		T v = id;
		int x = i + 1;
 
		while (x > 0)
		{
            int y = j + 1;
			while (y > 0)
			{
				v += table[x][y];
				y = (y & (y + 1)) - 1;
			}
			x = (x & (x + 1)) - 1;
		}
		return v;
	}
 
    inline T get(int y1, int x1, int y2, int x2)
    {
        return get(y2, x2) - get(y1 - 1, x2) - get(y2, x1 - 1) + get(y1 - 1, x1 - 1);
    }
};
 
int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    auto B = BIT2D<int>(n + 1, n + 1, 0);
    
    vector< string > mat(n);
 
    for(int i = 0; i < n; ++i)
    {
        cin >> mat[i];
        for(int j = 0; j < n; ++j)
        {
            if(mat[i][j] == '*') B.modify(i, j, 1);
        }
    }
 
    for(int i = 0; i < q; ++i)
    {
        int t;
        cin >> t;
        if(t == 1)
        {
            int x, y;
            cin >> x >> y;
            --x; --y;
            if(mat[x][y] == '.')
            {
                mat[x][y] = '*';
                B.modify(x, y, 1);
            }
            else
            {
                mat[x][y] = '.';
                B.modify(x, y, -1);
            }
        }
        else
        {
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;
            --y1; --x1; --y2; --x2;
            cout << B.get(y1, x1, y2, x2) << '\n';
        }
    }
    return 0;
}