#include <bits/stdc++.h>

#define ll long long

using namespace std;

int32_t main() {
    string s;

    int w;
    vector<int> field;
    int h = 0;
    vector<vector<pair<int, int>>> edges;
    auto addEdge = [&](int u, int v) {
        int weight = field[v];
        if (weight < 0)
            cerr << "!!!"<<endl;
        u *= 12, v *= 12;
        while (edges.size() < max(u,v) + 12) edges.emplace_back();
        if ((v - u) == 12) {
            edges[u].emplace_back(v + 1, weight);
            edges[u + 1].emplace_back(v + 2, weight);
            for (int i = 0; i < 12; i++) {
                if (i%6 == 0 || i%6 == 1 || i%6 == 2) continue;
                edges[u + i].emplace_back(v, weight);
            }
        } else if ((v - u) == -12) {
            edges[u + 6].emplace_back(v + 7, weight);
            edges[u + 7].emplace_back(v + 8, weight);
            for (int i = 0; i < 12; i++) {
                if (i%6 == 0 || i%6 == 1 || i%6 == 2) continue;
                edges[u + i].emplace_back(v + 6, weight);
            }
        } else if ((v - u) == w*12) {
            edges[u + 3].emplace_back(v + 4, weight);
            edges[u + 4].emplace_back(v + 5, weight);
            for (int i = 0; i < 12; i++) {
                if (i%6 == 3 || i%6 == 4 || i%6 == 5) continue;
                edges[u + i].emplace_back(v + 3, weight);
            }
        } else if ((v - u) == -w*12) {
            edges[u + 9].emplace_back(v + 10, weight);
            edges[u + 10].emplace_back(v + 11, weight);
            for (int i = 0; i < 12; i++) {
                if (i%6 == 3 || i%6 == 4 || i%6 == 5) continue;
                edges[u + i].emplace_back(v + 9, weight);
            }
        }else {
            cerr <<"";
        }
    };

    while (getline(cin, s)) {
        w = (int) s.size();
        for (char c: s)
            if (c - '0' >= 0 && '9' - c >= 0) {
                field.emplace_back(c - '0');
                int ind = (int) field.size()-1;
                if (h > 0) {
                    addEdge(ind, ind - w);
                    addEdge(ind - w, ind);
                }
                if (ind % w) {
                    addEdge(ind, ind - 1);
                    addEdge(ind - 1, ind);
                }
            }
        h++;
    }
    edges.emplace_back();
    for (int i = 0; i < 12; i++) edges.back().emplace_back(i, 0);
    edges.emplace_back();
    for (int i = 0; i < 12; i++) edges[12 * (field.size() - 1) + i].emplace_back(edges.size() - 1, 0);

    // todo: dijekstra

    int start = edges.size() - 2;

    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    vector<ll> dist(edges.size(), 1e18);
    vector<int> prev(edges.size(), -1);
    dist[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [dv, v] = pq.top();
        pq.pop();
        if (dv > dist[v]) continue;
        for (auto [u, du]: edges[v]) {
            ll newDist = dv + du;
            if (newDist < dist[u]) {
                dist[u] = newDist;
                prev[u] = v;
                pq.emplace(dist[u], u);
            }
        }
    }

    cout << dist[edges.size()-1]<<endl;


    return 0;
}
