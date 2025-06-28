#include <algorithm>
#include <iostream>
#include <vector>
#include "WaveletTree.cpp"
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    vector<int> nums(n);
    for (int &i : nums) cin >> i;
    int mn = 1e9 + 7, mx = -1e9 - 7;
    for (int i = 0; i < n; ++i) {
        mn = min(nums[i], mn);
        mx = max(nums[i], mx);
    }
    for (int &i: nums) {
        cout << i << ' ';
    }
    cout << '\n';
    WaveletTree *tree = new WaveletTree(nums.begin(), nums.end(), mn, mx);
    bool b = true;
    while (q--) {
        string type;
        cin >> type;
        int l, r, k;
        cin >> l >> r >> k;
        string _;
        int res;
        cin >> _ >> res;
        int ans;
        if (type == "kth") ans = tree->kth_smallest(l, r, k);
        else if (type == "rank") ans = tree->rank(l, r, k);
        else if (type == "upper") ans = tree->upper_bound(l, r, k);
        else if (type == "lower") ans = tree->lower_bound(l, r, k);
        else cout << "invalid query\n";

        cout << "expected: " << res << " : result: " << ans << '\n';
        if (ans != res) {
            b = false;
            cout << "fail\n";
        }
    }
    if (b) {
        cout << "All tests passed\n";
    } else {
        cout << "gitgud brochacho\n";
    }
}
