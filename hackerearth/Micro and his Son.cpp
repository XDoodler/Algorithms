/*Problem Link : https://www.hackerearth.com/problem/algorithm/micro-and-his-son-23/ */
#include<bits/stdc++.h>
#define int long long
using namespace std;


bool isPalindrome(string s) {
    int i = 0, j = s.size() - 1;
    while(i < j) {
        if(s[i] != s[j]) return false;
        ++i, --j;
    }
    return true;
}
int32_t main() {
    int T;
    cin >> T;
    while(T--) {
        string a, b;
        cin >> a >> b;
        int res = 0;
        while(a != b) {
            if(isPalindrome(a)) ++res;
            string hour = a.substr(0,2);
            string minute = a.substr(2,2);
            if(minute != "59") {
                stringstream typecast(minute);
                int val;
                typecast >> val;
                val++;
                minute = to_string(val);
                if(minute.size() == 1) minute = "0" + minute;
            }
            else {
                minute = "00";
                stringstream typecast(hour);
                int val;
                typecast >> val;
                val++;
                hour = to_string(val);
                if(hour.size() == 1) hour = "0" + hour;
            }
            a = "";
            a = hour + minute;
        }
        if(isPalindrome(a)) ++res;
        cout << res << endl;
    }
}
