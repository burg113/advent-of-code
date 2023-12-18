#include <bits/stdc++.h>

#define ll long long

using namespace std;

int32_t main() {
    string s;

    int w;
    vector<int> field;
    int h = 0;
    vector<vector<pair<int, int>>> edges;
    auto addEdge = [&](int u, int v, int weight) {
        u *= 4, v *= 4;
        while (edges.size() < max(u, v) + 4) edges.emplace_back();
        if (abs(u - v) < 4*w) {    // horizontal
            if (u < v) {
                edges[u + 1].emplace_back(v, weight);
                edges[u + 3].emplace_back(v, weight);
            } else {
                edges[u + 1].emplace_back(v + 2, weight);
                edges[u + 3].emplace_back(v + 2, weight);
            }
        } else {                    // vertical
            if (u < v) {
                edges[u + 0].emplace_back(v + 1, weight);
                edges[u + 2].emplace_back(v + 1, weight);
            } else {
                edges[u + 0].emplace_back(v + 3, weight);
                edges[u + 2].emplace_back(v + 3, weight);
            }
        }
    };

    while (getline(cin, s)) {
        w = (int) s.size();
        for (char c: s)
            if (c - '0' >= 0 && '9' - c >= 0) {
                field.emplace_back(c - '0');
                int ind = (int) field.size() - 1;

                int weight = 0;
                for (int i = 0; i <= min(10, h); i++) {
                    weight += field[ind - w * i];
                    if (i >= 4) {
                        addEdge(ind, ind - w * i, weight - field[ind]);
                        addEdge(ind - w * i, ind, weight - field[ind - w * i]);
                    }
                }
                weight = 0;
                for (int i = 0; i <= min(10, ind % w); i++) {
                    weight += field[ind - i];
                    if (i >= 4) {
                        addEdge(ind, ind - i, weight - field[ind]);
                        addEdge(ind - i, ind, weight - field[ind - i]);
                    }
                }
            }
        h++;
    }
    edges.emplace_back();
    for (int i = 0; i < 4; i++) edges.back().emplace_back(i, 0);
    edges.emplace_back();
    for (int i = 0; i < 4; i++) edges[4 * (field.size() - 1) + i].emplace_back(edges.size() - 1, 0);

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

    cout << dist[edges.size() - 1] << endl;


    return 0;
}
