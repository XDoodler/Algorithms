#include <bits/stdc++.h>

using namespace std;

typedef vector <int>::iterator iter;

class WaveletTree {

public:
  WaveletTree *left = 0, *right = 0;
  int lo, hi, mid;
  vector <int> ct;

  WaveletTree(iter b, iter e, int lo_, int hi_) {
    lo = lo_, hi = hi_;
    mid = (lo + hi) >> 1;
    if (b >= e) return;
    ct.reserve(e - b + 1);
    ct.emplace_back(0);
    for (auto it = b; it != e; it++) {
      ct.emplace_back(ct.back() + ((*it) <= mid));
    }
    iter pivot = stable_partition(b, e, [=](const int& i) { return i <= mid; } );
    if (lo == hi) return;
    left = new WaveletTree(b, pivot, lo, mid);
    right = new WaveletTree(pivot, e, mid + 1, hi);
  };

  ~WaveletTree() {
    delete left;
    delete right;
  }

  int ocurrences(int a, int b, int k) {
    return ocurrences(b, k) - ocurrences(a - 1, k);
  }

  int kth(int a, int b, int k) {
    if (lo == hi) return lo;
    int inLeft = ct[b] - ct[a - 1];
    if (k <= inLeft) return left -> kth(ct[a - 1] + 1, ct[b], k);
    return right -> kth(a - ct[a - 1], b - ct[b], k - inLeft);
  }

  int range(int x, int y, int a, int b) {
    return range(x, y, b) - range(x, y, a - 1);
  }
    
private:
  int range(int x, int y, int b) {
    if (hi < x or y < lo) return 0;
    if (x <= lo and hi <= y) return b;
    int sum = 0;
    if (left) sum = left -> range(x, y, ct[b]);
    if (right) sum += right -> range(x, y, b - ct[b]);
    return sum;
  }

  int ocurrences(int b, int k) {
    if (k < lo or k > hi) return 0;
    if (lo == hi) return b;
    if (k <= mid) return left -> ocurrences(ct[b], k);
    return right -> ocurrences(b - ct[b], k);
  }
};
