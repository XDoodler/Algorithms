/* Problem Link : https://www.hackerearth.com/practice/data-structures/advanced-data-structures/segment-trees/practice-problems/algorithm/help-the-avengers-6/ */
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 5;

int isp[N], a[N];

void pre() {
    for(int i = 0; i < N; ++i) isp[i] = 1;
    isp[0] = isp[1] = 0;

    for(long long i = 2; i <= N; ++i) {
        if(isp[i]) {
            for(long long j = i * i; j <= N; j += i) 
                isp[j] = 0;
        }
    }
}

class SegmentTree {
public:
    int tree[4 * N];
    void build(int node, int s, int e) {
        if(s == e) { // base case
            tree[node] = isp[a[s]];
            return;
        }
        int mid = (s + e) >> 1;
        build(node << 1, s, mid);
        build(node << 1 | 1, mid + 1, e);

        tree[node] = tree[node << 1] + tree[node << 1 | 1];
    }

    int query(int node, int s, int e, int l, int r) {
        if(e < l || s > r) return 0; // no overlap
        if(s >= l && e <= r) return tree[node]; // total overlap
        int mid = (s + e) >> 1;
        return query(node << 1, s, mid, l, r) + query(node << 1 | 1, mid + 1, e, l, r);
    }

    void update(int node, int s, int e, int position, int newValue) {
        if(s == e) {
            tree[node] = isp[newValue];
        }
        else {
            int mid = (s + e) >> 1;
            if(position <= mid) { // go to left of tree
                update(node << 1, s, mid, position, newValue);
            }
            else {
                update(node << 1 | 1, mid + 1, e, position, newValue);
            }

            tree[node] = tree[node << 1] + tree[node << 1 | 1];
        }

    }

};
int32_t main() {
    int T;
    cin >> T;
    pre();
    while(T--) {
        int N;
        cin >> N;
        for(int i = 0; i < N; ++i) cin >> a[i];
        int Q;
        cin >> Q;
        SegmentTree st;
        st.build(1, 0, N - 1);
        while(Q--) {
            char ch;
            cin >> ch;
            if(ch == 'A') {
                int l, r, ans;
                cin >> l >> r;
                ans = st.query(1, 0, N - 1, l - 1, r - 1);
                cout << ans << endl;
            } 
            else {
                int index, val;
                cin >> index >> val;
                st.update(1, 0, N - 1, index - 1, val);
            }
        }
    }
}
