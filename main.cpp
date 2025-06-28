#include <algorithm>
#include <iostream>
#include <vector>
// #include "WaveletTree.cpp"
#include "SegmentTree.cpp"
typedef long long ll;
using namespace std;



signed main() {
    cin.tie(0)->sync_with_stdio(0);
    ll n, q;
    cin >> n >> q;
    SegmentTree *tree = new SegmentTree(n);
    while (q--) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll l, r, v;
            cin >> l >> r >> v;
            tree->update(l, r - 1, v);
        } else {
            ll l, r;
            cin >> l >> r;
            ll res = tree->query(l, r - 1);
            cout << res << '\n';
        }
    }
}
