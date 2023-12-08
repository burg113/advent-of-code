#include <bits/stdc++.h>
#define int long long
using namespace std;

int co = 0;
map<string, int> mapping;

int getIndex(string &s) {
    if (mapping[s]) return mapping[s];
    return mapping[s] = ++co;
}


int32_t main() {
    string s;
    getline(cin, s);
    vector<bool> walk;
    for (char c: s) {
        if (c == 'L' || c == 'R')
            walk.emplace_back(c == 'R');
    }

    getline(cin, s);

    vector<vector<int>> edges(1000);

    set<int> start;
    vector<bool> end(1000,false);
    while (getline(cin, s)) {
        stringstream stream(s);
        string vs, c1s, c2s, t1, t2, _;
        stream >> vs >> _ >> t1 >> t2;
        for (char c: t1) if (c - 'A' >= 0 && 'Z' - c >= 0) c1s.push_back(c);
        for (char c: t2) if (c - 'A' >= 0 && 'Z' - c >= 0) c2s.push_back(c);

        int v = getIndex(vs), c1 = getIndex(c1s), c2 = getIndex(c2s);
        //cerr << vs << " " << v << "   " << c1s << " " << c1 << "    " << c2s << " " << c2 << endl;
        edges[v] = {c1, c2};
        edges[v].emplace_back(c2);
        if (vs[2] == 'A') start.emplace(v);
        if (vs[2] == 'Z') end[v] = true;

    }

    //cerr << endl<<endl;
    vector<int> map(1000);
    vector<vector<pair<int,int>>> next;
    int c = 0;
    for(int v = 0;v<end.size();v++) {
        if (!end[v]) continue;
        //cerr << "calc end" << endl;
        map[v] = c++;
        next.emplace_back();
        for(int i=0;i<walk.size();i++) {

            int count = i;
            int node = edges[v][walk[count % walk.size()]];
            count++;
            while (!end[node] && count < 1e9l) {
                node = edges[node][walk[count % walk.size()]];
                count++;
            }

            //cerr << "map i:" << i << " v:"<< v << "   " << count - i <<" "<< node << endl;

            next[map[v]].emplace_back(count - i,node);
        }
    }


    vector<pair<int,int>> cur;
    c = 0;
    for(int v: start) {
        map[v] = c++;
        int node = v;
        int count = 0;
        while (!end[node]) {
            node = edges[node][walk[count % walk.size()]];
            count++;
        }
        cur.emplace_back(count,node);
    }

    while (true) {
        int m = 1e18, mI,mC;

        for (int i=0;i<cur.size();i++) {
            if (cur[i].first < m) {
                m = cur[i].first;
                mI = i;
                mC = 1;
            }else if (cur[i].first == m) {
                mC++;
            }
        }
        if (mC == cur.size()) break;

        auto &[d,v] = cur[mI];

        d += next[map[v]][d%walk.size()].first;
        v = next[map[v]][d%walk.size()].second;

    }

    cout<< cur[0].first<<endl;

    return 0;
}
