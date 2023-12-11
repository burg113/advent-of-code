#include <bits/stdc++.h>

#define int long long
using namespace std;

int32_t main() {
    string s;
    vector<bool> emptyRow(1e4,true);
    vector<bool> emptyCol(1e4,true);

    vector<pair<int,int>> pos;

    int x = 0,y = 0;
    while (getline(cin, s)) {
        x = 0;
        for(char c : s) {
            if (c != '.') {
                emptyCol[x] = false;
                emptyRow[y] = false;
                pos.emplace_back(x,y);
            }
            x++;
        }
        y++;
    }

    vector<pair<int,int>> truePos;
    for(auto [x,y] : pos) {
        int dx = 0,dy =  0;
        for(int a = 0;a<x;a++) {
            if(emptyCol[a]) dx+=1000000-1;
        }
        for(int b = 0;b<y;b++) {
            if(emptyRow[b]) dy+=1000000-1;
        }
        truePos.emplace_back(x+dx,y+dy);

    }

    int ans = 0;
    for(int i=0;i< truePos.size();i++) {
        for(int j= i+1;j<truePos.size();j++) {
            ans += abs(truePos[i].first - truePos[j].first) + abs(truePos[i].second - truePos[j].second);
        }
    }

    cout << ans << endl;


    return 0;
}
