#include <bits/stdc++.h>

using namespace std;


int32_t main() {
    string s;
    vector<int> pot2;
    int val = 1;
    for (int i=0;i<20;i++) {
        pot2.emplace_back(val);
        val<<=1;
    }
    int awns = 0;
    while (getline(cin, s)) {
        stringstream stream(s);
        string _;
        stream >> _ >> _;
        set<int> winning;
        for(int i=0;i<10;i++){
            int n; stream >>n ;
            winning.emplace(n);
        }
        stream >> _;
        cerr << _ << endl;
        int count = 0;
        int n;
        while(stream >>n){
            if  (winning.count(n)) count++;
        }
        if (count) awns += pot2[count-1];
    }
    cout << awns<<endl;

    return 0;
}
