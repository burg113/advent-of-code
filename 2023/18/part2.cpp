#include <bits/stdc++.h>

#define ll long long
#define int long long
#define ii pair<int,int>

using namespace std;

int32_t main() {
    string s;

    int x = 0;
    ll ans = 1;
    while (getline(cin, s)) {
        string distpart;
        int dir = 0;
        for(int i=1;i<s.size();i++){
            if ((s[i-1] == '#' || !distpart.empty())&&distpart.size() < 5) {
                distpart.push_back(s[i]);
                dir = s[i+1] - '0';
            }
        }
        int dist;
        stringstream stringstream;
        stringstream << hex << distpart;
        stringstream >> dist;

        cerr << distpart << "  " << dist << "    " << dir << endl;

        if (dir == 0) {
            x += dist;
        }
        if (dir == 2) {
            x -= dist;
            ans += dist;
        }

        if (dir == 1) {
            ans += (x+1) * (dist);
            cerr << ans<<endl;
        }
        if (dir == 3) {
            ans -= x * (dist);
            cerr << ans << endl;
        }
    }

    cout << ans <<endl;

    return 0;
}
