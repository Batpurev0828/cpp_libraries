#include <algorithm>
#include <stdexcept>
#include <vector>
using namespace std;
struct WaveletTree {
  private:
    WaveletTree *x = nullptr, *y = nullptr;
    int low, high, mid;
    vector<int> pref;
    typedef vector<int>::iterator iter;

  public:
    WaveletTree(iter L, iter R, int mn, int mx) : x(nullptr), y(nullptr), low(mn), high(mx) {
        if (low == high || L >= R) return;
        mid = (low + high) / 2;
        pref.push_back(0);
        // potentially replacable with fenwick tree to support certain types of updates
        // with log(N) to log^2(N) complexity which is mostly sufficient
        for (auto it = L; it != R; ++it) pref.push_back(pref.back() + (*it <= mid));
        auto pivot = stable_partition(L, R, [&](int x) { return x <= mid; });
        x = new WaveletTree(L, pivot, low, mid);
        y = new WaveletTree(pivot, R, mid + 1, high);
    }
    // kth smallest element in range [l, r]. (1 indexed)
    int kth_smallest(int l, int r, int k) {
        if (l > r) throw invalid_argument("invalid range");
        if (low == high) return low;
        int mapLeft = pref[l - 1];
        int mapRight = pref[r];
        int leftCount = mapRight - mapLeft;
        if (k <= leftCount) {
            return x->kth_smallest(mapLeft + 1, mapRight, k);
        } else {
            return y->kth_smallest(l - mapLeft, r - mapRight, k - leftCount);
        }
    }
    // occurence of element v in range [l, r]. (1 indexed)
    int rank(int l, int r, int v) {
        if (l > r || low > v || high < v) return 0;
        if (low == high) return r - l + 1;
        int mapLeft = pref[l - 1];
        int mapRight = pref[r];
        if (v <= mid) return x->rank(mapLeft + 1, mapRight, v);
        else return y->rank(l - mapLeft, r - mapRight, v);
    }
    // number of element greater than v in range [l, r]. (1 indexed)
    int upper_bound(int l, int r, int v) {
        if (l > r || high <= v) return 0;
        if (low > v) return r - l + 1;
        int mapLeft = pref[l - 1];
        int mapRight = pref[r];
        return x->upper_bound(mapLeft + 1, mapRight, v) + y->upper_bound(l - mapLeft, r - mapRight, v);
    }
    // number of element not less than v in range [l, r]. (1 indexed)
    int lower_bound(int l, int r, int v) {
        if (l > r || high < v) return 0;
        if (low >= v) return r - l + 1;
        int mapLeft = pref[l - 1];
        int mapRight = pref[r];
        return x->lower_bound(mapLeft + 1, mapRight, v) + y->lower_bound(l - mapLeft, r - mapRight, v);
    }

    ~WaveletTree() {
        delete x;
        delete y;
    }
};