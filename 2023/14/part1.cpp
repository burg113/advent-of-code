#include <bits/stdc++.h>

using namespace std;


int32_t main() {
    string s;
    getline(cin, s);
    vector<int> stop(s.size(),0);

    int sum = 0;
    int c = 0;
    int h = 0;
    do {
        h++;
        for(int i=0;i<s.size();i++) {
            if (s[i] == '#') {
                stop[i] = h;
            }
            if (s[i] == 'O') {
                sum += (stop[i]++);
                c++;
            }
        }
    }while (getline(cin, s));

    sum = c*h - sum;
    cout << sum << endl;
    return 0;
}
