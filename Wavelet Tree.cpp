
//=======================
const int MAX = 1e6;
vi g[N];
int a[N];
struct wavelet_tree{
	#define vi vector<int>
	#define pb push_back
	int lo, hi;
	wavelet_tree *l, *r;
	vi b;
 
	//nos are in range [x,y]
	//array indices are [from, to)
	wavelet_tree(int *from, int *to, int x, int y){
		lo = x, hi = y;
		if(lo == hi or from >= to) return;
		int mid = (lo+hi)/2;
		auto f = [mid](int x){
			return x <= mid;
		};
		b.reserve(to-from+1);
		b.pb(0);
		for(auto it = from; it != to; it++)
			b.pb(b.back() + f(*it));
		//see how lambda function is used here	
		auto pivot = stable_partition(from, to, f);
		l = new wavelet_tree(from, pivot, lo, mid);
		r = new wavelet_tree(pivot, to, mid+1, hi);
	}
 
	//kth smallest element in [l, r]
	int kth(int l, int r, int k){
		if(l > r) return 0;
		if(lo == hi) return lo;
		int inLeft = b[r] - b[l-1];
		int lb = b[l-1]; //amt of nos in first (l-1) nos that go in left 
		int rb = b[r]; //amt of nos in first (r) nos that go in left
		if(k <= inLeft) return this->l->kth(lb+1, rb , k);
		return this->r->kth(l-lb, r-rb, k-inLeft);
	}
 
	//count of nos in [l, r] Less than or equal to k
	int LTE(int l, int r, int k) {
		if(l > r or k < lo) return 0;
		if(hi <= k) return r - l + 1;
		int lb = b[l-1], rb = b[r];
		return this->l->LTE(lb+1, rb, k) + this->r->LTE(l-lb, r-rb, k);
	}
 
	//count of nos in [l, r] equal to k
	int count(int l, int r, int k) {
		if(l > r or k < lo or k > hi) return 0;
		if(lo == hi) return r - l + 1;
		int lb = b[l-1], rb = b[r], mid = (lo+hi)/2;
		if(k <= mid) return this->l->count(lb+1, rb, k);
		return this->r->count(l-lb, r-rb, k);
	}
	~wavelet_tree(){
		delete l;
		delete r;
	}
};
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	srand(time(NULL));
	int i,n,k,j,q,l,r;
	cin >> n;
	fo(i, n) cin >> a[i+1];
	wavelet_tree T(a+1, a+n+1, 1, MAX);
	cin >> q;
	while(q--){
		int x;
		cin >> x;
		cin >> l >> r >> k;
		if(x == 0){
			//kth smallest
			cout << "Kth smallest: ";
			cout << T.kth(l, r, k) << endl;
		}
		if(x == 1){
			//less than or equal to K
			cout << "LTE: ";
			cout << T.LTE(l, r, k) << endl;
		}
		if(x == 2){
			//count occurence of K in [l, r]
			cout << "Occurence of K: ";
			cout << T.count(l, r, k) << endl;
		}
	}
	return 0;
} 
 //=====================================================================================

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
