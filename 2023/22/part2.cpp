#include <bits/stdc++.h>

using namespace std;
#define int long long

int32_t main() {
    vector<vector<vector<int>>> field(350, vector<vector<int>>(350, vector<int>(350, -1)));
    string s;

    vector<set<int>> edges;
    vector<set<int>> backEdges;
    vector<bool> del;
    vector<pair<int,vector<int>>> pieces;
    int mi = 1e9,ma = -1e9;
    while (getline(cin, s)) {
        int x1, y1, z1, x2, y2, z2;
        stringstream stream(s);
        char _;
        stream >> x1 >> _ >> y1 >> _ >> z1 >> _ >> x2 >> _ >> y2 >> _ >> z2;
        if (x2 < x1) swap(x1, x2);
        if (y2 < y1) swap(y1, y2);
        if (z2 < z1) swap(z1, z2);
        pieces.emplace_back(z1,vector<int>{x1,y1,z1,x2,y2,z2});
        for(int num : {x1,y1,z1,x2,y2,z2}) {
            mi = min(mi,num);
            ma = max(ma,num);

        }
    }
    std::sort(pieces.begin(), pieces.end());

    for(auto [_,p] : pieces) {
        int x1 = p[0],y1 = p[1],z1 = p[2];
        int x2 = p[3],y2 = p[4],z2 = p[5];
        int ind = (int) edges.size();

        del.emplace_back(true);
        edges.emplace_back();
        backEdges.emplace_back();
        while (true) {
            if (z1 == 1) break;
            z1--, z2--;
            assert(x1 <= x2);
            assert(y1 <= y2);
            assert(z1 <= z2);

            for (int x = x1; x <= x2; x++) {
                for (int y = y1; y <= y2; y++) {
                    for (int z = z1; z <= z2; z++) {
                        if (field[x][y][z] != -1) {
                            edges.back().emplace(field[x][y][z]);
                            backEdges[field[x][y][z]].emplace(ind);
                        }
                    }
                }
            }
            if (edges.back().empty()) continue;

            if (edges.back().size() == 1) del[*edges.back().begin()] = false;

            z1++, z2++;
            break;
        }
        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) {
                for (int z = z1; z <= z2; z++) {
                    assert(field[x][y][z] == -1);
                    field[x][y][z] = ind;
                    //cerr << ind<<" - " << x << " " << y << " " << z-1 <<endl;
                }
            }
        }
    }

    int ans = 0;
    for(int i=0;i<edges.size();i++) {
        vector<int> degree;
        for(auto &e : edges) degree.emplace_back(e.size());
        function<int(int)> dfs = [&](int v) {
            int total = 1;
            for(int u : backEdges[v]) {
                degree[u]--;
                if(degree[u] == 0)
                    total += dfs(u);
            }
            return total;
        };
        if(!del[i]) ans += dfs(i)-1;
    }

    cout << ans << endl;

    return 0;
}
