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


    getline(cin, s);

    stream = stringstream(s);
    stream >> _;


    int ans = 1,curr= 0;
    int i =0;
    map<int,int> ress;
    while (stream >> num) {
        curr = 0;
        cerr << num << endl;
        for(int j = 1;j<times[i];j++) {
            int res = j * (times[i]-j);
            if (res > num) curr++;
        }
        ans *= curr;
        i++;
    }
    cout << ans;
    return 0;
}
