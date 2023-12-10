#include <bits/stdc++.h>

using namespace std;


int32_t main() {
    int w;
    string s;
    vector<vector<int>> edges(1e5);
    int count = 0;
    int start = 0;
    vector<bool> cons(1e5);
    while (getline(cin, s)) {
        w = (int) s.size();
        for (char c: s) {
            vector<int> neighbours;
            cons[count] = true;
            if (c == '|')
                neighbours.emplace_back(-w), neighbours.emplace_back(w);
            if (c == '-')
                neighbours.emplace_back(-1), neighbours.emplace_back(1), cons[count] = false;
            if (c == 'L')
                neighbours.emplace_back(-w), neighbours.emplace_back(1),cons[count] = false;
            if (c == 'J')
                neighbours.emplace_back(-w), neighbours.emplace_back(-1),cons[count] = false;
            if (c == '7')
                neighbours.emplace_back(-1), neighbours.emplace_back(w);
            if (c == 'F')
                neighbours.emplace_back(w), neighbours.emplace_back(1);
            if (c == '.');
            if (c == 'S') {
                neighbours.emplace_back(-1), neighbours.emplace_back(-w);
                neighbours.emplace_back(1), neighbours.emplace_back(w);
                start = count;
                cerr << "START " << start << endl << endl;
            }

            for (int u: neighbours) {
                u += count;
                cerr << "v " << count << "   u " << u << endl;
                edges[count].emplace_back(u);
            }

            count++;
        }
    }
    vector<int> newConsForStart;
    cons[start] = false;
    for (int v: edges[start]) {
        bool b = false;
        for (int u: edges[v])
            if (u == start) b = true;
        if (b) {
            if (v - start == w)
                cons[start] = true;
            newConsForStart.emplace_back(v);
        }
    }
    edges[start] = newConsForStart;

    vector<bool> visited(edges.size(), false);
    vector<bool> sol(edges.size(), false);
    function<int(int, int, int)> dfs = [&](int v, int par, int d) {
        visited[v] = true;
        cerr << "edge " << par << "  " << v << endl;
        int m = -edges.size();

        if (d > edges.size()) return m;

        for (int u: edges[v]) {
            if (u == par) continue;
            if (u == start) {
                sol[v] = true;
                return 0;
            }
            if (visited[u])
                continue;
            m = max(m, dfs(u, v, d + 1) + 1);
        }
        if (m > 0) sol[v] = true;
        return m;
    };
    int a = dfs(start, -1, 0);

    int ans = 0;
    for (int y = 0; y < count / w; y++) {
        bool inside = false;
        for (int x = 0; x < w; x++) {
            if (sol[x + y * w] && cons[x + y * w]) {
                cerr<< "flipped " << x << " " << y << " "<<endl;
                inside = !inside;
            }
            if (!sol[x + y * w] && inside) {
                cerr << x << " " << y<<endl;
                ans++;
            }
        }
    }
    cout << ans<<endl;

    return 0;
}
