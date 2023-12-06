#include <bits/stdc++.h>
#define int long long
using namespace std;


int32_t main() {
    string s, _;

    vector<int> times;
    getline(cin, s);
    stringstream stream(s);
    stream >> _;
    int num;
    while (stream >> num) times.emplace_back(num);

    int time = 0;
    for(int t : times) {
        int tmp = (int)to_string(t).size();
        while (tmp--) time *= 10;
        time += t;
    }

    getline(cin, s);

    stream = stringstream(s);
    stream >> _;

    vector<int> dists;
    while (stream >> num) dists.emplace_back(num);

    int dist = 0;
    for(int t : dists) {
        int tmp = (int)to_string(t).size();
        while (tmp--) dist *= 10;
        dist += t;
    }
    cerr << time<< "     " << dist<<endl;

    int l = -1,r = time/2;
    while (l+1<r) {
        int piv = (l+r)/2;
        __int128 i = ((__int128)piv * (__int128)(time - piv));
        cerr << piv << "  "<< (long long )i << " >= " << dist << endl;
        if ((__int128)piv * (__int128)(time - piv) >= (__int128)dist) r = piv;
        else l = piv;
        cerr << l << "  "<< r<<endl;
    }

    cout << (time+ 1 - 2*r) <<endl;

    return 0;
}
