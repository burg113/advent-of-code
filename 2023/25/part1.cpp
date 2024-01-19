#include <bits/stdc++.h>

using namespace std;
#define ll long long

map<string, int> mapping;

struct Edge {
    int to, rev;
    ll f, c;
};

vector<vector<Edge>> edges;
int s, t;
vector<int> pt, dist;

int getIndex(string &s) {
    if (mapping.count(s)) return mapping[s];
    edges.emplace_back();
    return mapping[s] = (int) edges.size() - 1;
}

void addEdge(int u, int v, ll c) {
    edges[u].push_back({v, (int) edges[v].size(), 0, c});
    edges[v].push_back({u, (int) edges[u].size() - 1, 0, c});
}

bool bfs(ll lim) {
    dist.assign((int) edges.size(), -1);
    dist[s] = 0;
    queue<int> q({s});
    while (!q.empty() && dist[t] < 0) {
        int v = q.front();
        q.pop();
        for (Edge &e: edges[v]) {
            if (dist[e.to] < 0 && e.c - e.f >= lim) {
                dist[e.to] = dist[v] + 1;
                q.push(e.to);
            }
        }
    }
    return dist[t] >= 0;
}

bool dfs(int v, ll flow) {
    if (v == t) return true;
    for (; pt[v] < (int) edges[v].size(); pt[v]++) {
        Edge &e = edges[v][pt[v]];
        if (dist[e.to] != dist[v] + 1) continue;
        if (e.c - e.f >= flow && dfs(e.to, flow)) {
            e.f += flow;
            edges[e.to][e.rev].f -= flow;
            return true;
        }
    }
    return false;
}

ll maxFlow(int source, int target) {
    s = source, t = target;
    ll flow = 0;
    for (ll lim = (1LL << 62); lim >= 1; lim /= 2) {
        while (bfs(lim)) {
            pt.assign((int) edges.size(), 0);
            while (dfs(s, lim)) flow += lim;
        }
    }
    return flow;
}


int32_t main() {
    string s;

    int count = 0;

    while (getline(cin, s)) {
        stringstream stream(s);
        string node, other;
        string n;
        stream >> node;
        for (int i = 0; i < node.size() - 1; i++) n.push_back(node[i]);
        int v = getIndex(n);
        while (stream >> other) {
            int u = getIndex(other);
            addEdge(u, v, 1);
            count++;
        }
    }
    vector<vector<Edge>> old = edges;

    int u = (int) edges.size();
    for (; u >= 0; u--) {
        cerr << u << " " << maxFlow(0, u) << endl;
        edges = old;
        if (maxFlow(0, u) == 3) break;
        else edges = old;
    }

    vector<bool> visited(edges.size(), false);
    function<int(int)> fill = [&](int v) {
        visited[v] = true;
        int c = 1;
        for (auto e: edges[v]) {
            if (!visited[e.to] && e.f < e.c) c += fill(e.to);
        }
        return c;
    };

    int a1 = fill(0);
    cout << a1 * ((int)edges.size()-a1) << endl;
    //cout << count << endl;

    return 0;
}
