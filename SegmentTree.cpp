#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
struct SegmentTree {
  private:
    vector<ll> nums;
    struct Node {
        ll sum, lazy;
        bool has;
        Node() : sum(0), lazy(0), has(false) {}
    };
    vector<Node> tree;
    int n;
    void push(int i, int L, int R) {
        if (!tree[i].has || L == R) return;
        int m = (L + R) / 2;
        int x = 2 * i + 1, y = x + 1;
        tree[x].has = tree[y].has = true;
        tree[i].has = false;

        tree[x].lazy = tree[y].lazy = tree[i].lazy;
        tree[i].lazy = 0;

        tree[x].sum = (ll)(m - L + 1) * tree[x].lazy;
        tree[y].sum = (ll)(R - m) * tree[y].lazy;
        tree[i].sum = tree[x].sum + tree[y].sum;
    }
    void merge(int x, int y) {
        int p = (x - 1) / 2;
        tree[p].sum = tree[x].sum + tree[y].sum;
    }
    void build(int i, int L, int R) {
        if (L == R) {
            tree[i].sum = nums[L];
            tree[i].lazy = 0;
            tree[i].has = false;
            return;
        }
        push(i, L, R);
        int m = (L + R) / 2;
        int x = 2 * i + 1, y = x + 1;
        build(x, L, m);
        build(y, m + 1, R);
        merge(x, y);
    }
    ll query(int i, int L, int R, int l, int r) {
        if (L == l && r == R) {
            return tree[i].sum;
        }
        push(i, L, R);
        int m = (L + R) / 2;
        int x = 2 * i + 1, y = x + 1;
        if (r <= m) {
            return query(x, L, m, l, r);
        } else if (l > m) {
            return query(y, m + 1, R, l, r);
        } else {
            ll q1 = query(x, L, m, l, m);
            ll q2 = query(y, m + 1, R, m + 1, r);
            return q1 + q2;
        }
    }
    void update(int i, int L, int R, int l, int r, ll v) {
        if (L == l && r == R) {
            tree[i].sum = (ll)(R - L + 1) * v;
            tree[i].lazy = v;
            tree[i].has = true;
            return;
        }
        push(i, L, R);
        int m = (L + R) / 2;
        int x = 2 * i + 1, y = x + 1;
        if (r <= m) {
            update(x, L, m, l, r, v);
        } else if (l > m) {
            update(y, m + 1, R, l, r, v);
        } else {
            update(x, L, m, l, m, v);
            update(y, m + 1, R, m + 1, r, v);
        }
        merge(x, y);
    }

  public:
    // Construct empty segment tree with size as parameter
    // Supports range assignment and range sum
    SegmentTree(int sz) {
        n = sz;
        tree.assign(4 * n, Node());
    }
    // Construct segment tree with given vector elements
    // Supports range assignment and range sum
    SegmentTree(vector<ll> &v) {
        n = v.size();
        nums = v;
        tree.assign(4 * n, Node());
        build(0, 0, n - 1);
    }
    // assigns value v to elements in range [l, r]. (0 indexed)
    void update(int l, int r, ll v) { update(0, 0, n - 1, l, r, v); }
    // retrieves sum in range [l, r]. (0 indexed)
    ll query(int l, int r) { return query(0, 0, n - 1, l, r); }
};