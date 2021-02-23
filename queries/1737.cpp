#include <bits/stdc++.h>
 
using namespace std;
 
struct Node;
 
std::deque<Node> cache;
 
Node* fetch_new() {
    cache.emplace_back();
    return &cache.back();
}
 
Node* fetch_new(Node const& node) {
    cache.emplace_back(node);
    return &cache.back();
}
 
struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    long long data = 0;
 
    void build(int l, int r) {
        if (l + 1 < r) {
            int m = (l + r) / 2;
            left = fetch_new();
            right = fetch_new();
            left->build(l, m);
            right->build(m, r);
        }
    }
 
    Node* set(int pos, int x, int l, int r) {
        Node* neww = fetch_new(*this);
        if (l + 1 == r) neww->data = x;
        else {
            int m = (l + r) / 2;
            if (pos < m) neww->left = neww->left->set(pos, x, l, m);
            else neww->right = neww->right->set(pos, x, m, r);
            neww->data = neww->left->data + neww->right->data;
        }
        return neww;
    }
 
    long long qry(int bl, int br, int l, int r) {
        if (bl >= r || br <= l) return 0ll;
        if (bl <= l && r <= br) return data;
        int m = (l + r) / 2;
        return left->qry(bl, br, l, m) + right->qry(bl, br, m, r);
    }
};
 
int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;
    auto root = fetch_new();
    root->build(0, n);
    
    for(int i = 0; i < n; ++i)
    {
        long long v;
        cin >> v;
        auto new_root = root->set(i, v, 0, n);
        root = new_root;
    }
 
    vector< Node* > heads;
    heads.emplace_back(root);
 
    for(int i = 0; i < q; ++i)
    {
        int t;
        cin >> t;
        if(t == 1)
        {
            int k, a; long long x;
            cin >> k >> a >> x;
            --k; --a;
            auto new_head = heads[k]->set(a, x, 0, n);
            // aqui que em tese rolou a mudança!
            heads[k] = new_head; 
        }
        else if(t == 2)
        {
            int k, a, b;
            cin >> k >> a >> b;
            --k; --a; --b;
            cout << heads[k]->qry(a, b + 1, 0, n) << '\n';
        }
        else
        {
            int k; cin >> k;
            heads.emplace_back(fetch_new(*heads[k - 1]));
        }
    }
    return 0;
 
}