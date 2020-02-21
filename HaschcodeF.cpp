/* nuttela - Soham Chakrabarti */

#include <bits/stdc++.h>
using namespace std;

#define ff first
#define ss second
 
typedef struct library {
    int books, signupTime, booksPerDay;
    vector<int> bookind;
}data;

bool cmp(pair<int, pair<int, pair<int, int>>> s1, pair<int, pair<int, pair<int, int>>> s2) {
	if(s1.ff == s2.ff) {
		if(s1.ss.ff == s2.ss.ff) {
			return s1.ss.ss.ff > s2.ss.ss.ff;
		}
		return s1.ss.ff > s2.ss.ff;
	}
	return s1.ff < s2.ff;
}

int main() {
	// input
    int B,L,D;
        // B ~ Books
        // L ~ Libraries
        // D ~ Days
    cin >> B >> L >> D;
    int S[B];
    for (int i = 0; i < B; ++i)
        cin >> S[i];
    data lib[L];
    for(int i = 0; i < L; ++i) {
        cin >> lib[i].books >> lib[i].signupTime >> lib[i].booksPerDay;
        lib[i].bookind = vector<int>(lib[i].books);
        for(int j = 0; j < lib[i].books; ++j)
            cin >> lib[i].bookind[j];
    }


    // solution code
    vector<pair<int, pair<int, pair<int, int>>>> scores(L);
    for(int i = 0; i < L; ++i) {
        int n = lib[i].books;
        int sum = 0;
        for(int j = 0; j < n; ++j)
            sum += S[lib[i].bookind[j]];
        scores[i] = {lib[i].signupTime, {lib[i].booksPerDay, {sum, i}}};
    }
    sort(scores.begin(), scores.end(), cmp);


    // output

    cout << L << endl;

    for(int i = 0; i < L; ++i) {
    	int ind = scores[i].ss.ss.ss;
    	int n = lib[ind].books;
        cout << ind << ' ' << n << '\n';
        for(int j = 0; j < n; ++j)
            cout << lib[ind].bookind[j] << ' ';
        cout << endl;
    }

}
