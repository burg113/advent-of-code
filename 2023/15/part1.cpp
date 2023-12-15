#include <bits/stdc++.h>

using namespace std;


int32_t main() {
    string s;
    getline(cin, s);

    int sum = 0;
    int val = 0;
    for(char c : s) {
        if (c == ',') {
            sum += val;
            val = 0;
            continue;
        }
        val = (val + (int)c)*17%256;
        cerr << val<<endl;
    }
    sum += val;
    cout << sum<<endl;

    return 0;
}
