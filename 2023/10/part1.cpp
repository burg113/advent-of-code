#include <bits/stdc++.h>

using namespace std;


int32_t main() {
    int w;
    string s;
    vector<vector<int>> edges(1e5);
    int count = 500;
    int start = 0;
    while (getline(cin, s)) {
        w = (int)s.size();
        for(char c : s) {
            vector<int> neighbours;
            if (c == '|')
                neighbours.emplace_back(-w),neighbours.emplace_back(w);
            if (c == '-')
                neighbours.emplace_back(-1),neighbours.emplace_back(1);
            if (c == 'L')
                neighbours.emplace_back(-w),neighbours.emplace_back(1);
            if (c == 'J')
                neighbours.emplace_back(-w),neighbours.emplace_back(-1);
            if (c == '7')
                neighbours.emplace_back(-1),neighbours.emplace_back(w);
            if (c == 'F')
                neighbours.emplace_back(w),neighbours.emplace_back(1);
            if (c == '.') ;
            if (c == 'S') {
                neighbours.emplace_back(-1),neighbours.emplace_back(-w);
                neighbours.emplace_back(-w),neighbours.emplace_back(1);
                start = count;
                cerr << "START " << start<<endl << endl;
            }

            for(int u : neighbours) {
                u+=count;
                cerr << "v " << count<<"   u " << u<<endl;
                edges[count].emplace_back(u);
            }
            count++;
        }
    }

    vector<bool> visited(edges.size(),false);
    function<int(int,int,int)> dfs = [&](int v,int par,int d) {
        visited[v] = true;
        cerr << "edge "<<par << "  "<< v << endl;
        int m = -edges.size();

        if (d > edges.size()) return m;

        for(int u:edges[v]) {
            if (u == par) continue;
            if (u == start) {
                return 0;
            }
            if (visited[u])
                continue;
            m = max(m,dfs(u,v,d+1) + 1);
        }
        return m;
    };
    cout << (dfs(start,-1,0)+1)/2 << endl;



    return 0;
}
