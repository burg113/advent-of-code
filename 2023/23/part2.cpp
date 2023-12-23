#include <bits/stdc++.h>

using namespace std;
//#define int long long

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
                    edges[v].emplace_back(u);
                    edges[u].emplace_back(v);
                }
                if (field.back().size() > 1 && field[field.size()-1][field.back().size()-2] != -1) {
                    int u = field[field.size()-1][field.back().size()-2];
                    edges[v].emplace_back(u);
                    edges[u].emplace_back(v);
                }
            }
        }
    }
    int n = (int)edges.size();
    int count = 0;
    vector<int> map(n);
    vector<vector<pair<int,int>>> graphEdges;
    vector<bool> visited(n,false);

    int goal = 0;
    function<void(int,int,int)> dfs = [&] (int v,int par,int num){
        //cerr << "vert " << v <<endl;
        visited[v] = true;
        count++;
        if (edges[v].size() != 2 && par != -1) {
            if (edges[v].size() < 2) goal = graphEdges.size();
            //cerr << "emplace node with count" <<count<<endl;
            graphEdges[num].emplace_back(graphEdges.size(),count);
            graphEdges.emplace_back();
            graphEdges.back().emplace_back(num,count);
            num = (int)graphEdges.size()-1;
            count = 0;
        }
        map[v] = num;
        for(int u : edges[v]) {
            if (u == par) continue;
            if (visited[u]) {
                if (count > 0) {
                    graphEdges[num].emplace_back(map[u], count+1);
                    graphEdges[map[u]].emplace_back(num, count+1);
                    count = 0;
                }
                continue;
            }
            dfs(u,v,num);
        }
    };
    graphEdges.emplace_back();
    dfs(0,-1,0);


    vector<bool> active(graphEdges.size(),false);
    function<int(int)> maxLengthDFS = [&](int v){
        active[v] = true;
        int ma = 0;
        for(auto [u,w] : graphEdges[v]) {
            if (!active[u]) ma = max(ma,maxLengthDFS(u)+w);
        }
        active[v] = false;
        if (ma == 0 && v != goal) return (int)-1e9;
        return ma;
    };

    //for(int i=0;i<graphEdges.size();i++) {
    //    for(auto [u,w] : graphEdges[i]) cout << i + 1 << " " << u + 1 << "   "<< w << endl;
    //}
    cout << maxLengthDFS(0)<<endl;


    return 0;
}
