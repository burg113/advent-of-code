#include <bits/stdc++.h>

using namespace std;


int32_t main() {
    string s;
    int awns = 0;
    vector<int> amount(1000,1);
    int i = 0;
    while (getline(cin, s)) {
        awns+=amount[i];
        stringstream stream(s);
        string _;
        stream >> _ >> _;
        set<int> winning;
        for (int i = 0; i < 10; i++) {
            int n;
            stream >> n;
            winning.emplace(n);
        }
        stream >> _;
        cerr << _ << endl;
        int count = 0;
        int n;
        while (stream >> n) {
            if (winning.count(n)) count++;
        }

        for(int j=1;j<=count;j++) {
            amount[i+j] += amount[i];
        }

        i++;
    }
    cout << awns << endl;

    return 0;
}
