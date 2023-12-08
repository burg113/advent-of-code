#include <bits/stdc++.h>

using namespace std;

int co =0;
map<string,int> mapping;

int getIndex(string& s) {
    if (mapping[s]) return mapping[s];
    return mapping[s] = ++co;
}



int32_t main() {
    string s;
    getline(cin, s);
    vector<bool> walk;
    for(char c: s) walk.emplace_back(c == 'R');

    getline(cin, s);

    vector<vector<int>> edges(1000);

    int start,end;

    while (getline(cin, s)) {
        stringstream stream(s);
        string vs,c1s,c2s,t1,t2,_;
        stream >> vs >> _ >> t1 >> t2;
        for(char c : t1) if (c - 'A' >= 0 && 'Z'-c >= 0) c1s.push_back(c);
        for(char c : t2) if (c - 'A' >= 0 && 'Z'-c >= 0) c2s.push_back(c);

        int v = getIndex(vs), c1 = getIndex(c1s), c2 = getIndex(c2s);
        cerr << vs<< " " << v << "   " << c1s<<" "<<c1 << "    " << c2s<<" " << c2<<endl;
        edges[v] = {c1,c2};
        edges[v].emplace_back(c2);
        if (vs == "AAA") start = v;
        if (vs == "ZZZ") end = v;

    }

    int node = start;
    int count =0;
    while (node != end) {
        node = edges[node][walk[count%walk.size()]];
        count++;
    }
    cout << count<<endl;


    return 0;
}
