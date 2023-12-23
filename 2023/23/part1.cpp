#include <bits/stdc++.h>

using namespace std;
#define int long long

int32_t main() {
    string s;
    vector<vector<int>> field;
    vector<int> dir;
    vector<vector<int>> edges;
    getline(cin, s);
    map<char,int> dirLookup = {{'.',-1},{'^',0},{'v',1},{'<',2},{'>',3}};

    while (getline(cin, s)) {
        field.emplace_back();
        for (char c :s) {
            if (c == '#')
                field.back().emplace_back(-1);
            else {
                int v = edges.size();
                field.back().emplace_back(v);
                dir.emplace_back(dirLookup[c]);
                edges.emplace_back();
                if (field.size() > 1 && field[field.size()-2][field.back().size()-1] != -1) {
                    int u = field[field.size()-2][field.back().size()-1];
                    if (dir[v] != 1&&dir[u] != 1) edges[v].emplace_back(u);
                    if (dir[v] != 0&&dir[u] != 0) edges[u].emplace_back(v);
                }
                if (field.back().size() > 1 && field[field.size()-1][field.back().size()-2] != -1) {
                    int u = field[field.size()-1][field.back().size()-2];
                    if (dir[v] != 3&&dir[u] != 3) edges[v].emplace_back(u);
                    if (dir[v] != 2&&dir[u] != 2) edges[u].emplace_back(v);
                }
            }
        }
    }
    int n = edges.size();
    vector<int> deg(n);
    vector<vector<int>> dagEdges(n);
    function<void(int,int)> dfs = [&] (int v,int par){
        for(int u : edges[v]) {
            if (u == par) continue;
            dagEdges[u].emplace_back(v);
            dfs(u,v);
            deg[v]++;
        }
    };
    dfs(0,-1);

    vector<int> dp(n,0);
    queue<int> outNodes;
    for(int i=0;i<n;i++) {
        if (deg[i] == 0) outNodes.emplace(i);
        for(int u : dagEdges[i]) cerr << i+1<<" " << u+1<<endl;
    }

    while (!outNodes.empty()) {
        int v = outNodes.front();
        cerr << v <<endl;
        outNodes.pop();
        for(int u : dagEdges[v]) {
            dp[u] = max(dp[u],dp[v]+1);
            deg[u]--;
            if(deg[u] == 0) outNodes.emplace(u);
        }
    }
    int ma = 0;
    for(int i : dp) ma = max(ma,i);

    cout << ma + 1<<endl;

    return 0;
}
