// THIS TASK SUCKS

#include <bits/stdc++.h>

using namespace std;

struct Node {
    set<int> incoming;
    int type = 2;

    bool toggle = false;
    vector<int> allIncoming;

};

int32_t main() {
    string s;
    int lastAndNode;

    vector<vector<int>> edges;
    vector<Node> nodes;          // %:0, &:1, broadcaster:2
    map<string, int> nodeLookup;
    auto getInd = [&](string s) {
        if (!nodeLookup.count(s)) {
            nodeLookup[s] = (int) edges.size();
            nodes.emplace_back();
            edges.emplace_back();
        }
        return nodeLookup[s];
    };

    int start = -1;
    while (getline(cin, s)) {
        //cerr << s << endl;
        stringstream stream(s);
        string node;
        stream >> node;
        bool b =  (node[0] == '&');

        if (s[0] != 'b') node.erase(node.begin());
        int v = getInd(node);

        if (s[0] == 'b') {
            start = (int) nodes.size() - 1;
            nodes[v].type = 2;
        } else {
            nodes[v].type = b;
        }
        //cerr << v <<endl;

        string _, toNode;
        stream >> _;
        while (stream >> toNode) {
            if (toNode.back() == ',') toNode.pop_back();
            int u = getInd(toNode);
            //cerr << "# " << v << " to " << u << " (" << toNode << ")" << endl;
            edges[v].emplace_back(u);
            if (toNode == "rx") lastAndNode = v;
            //cerr << v << " " << u <<endl;
            nodes[u].incoming.emplace(v);
            nodes[u].allIncoming.emplace_back(v);
        }
    }


    map<int,int> firstOccurence;
    for(int i: nodes[lastAndNode].incoming) {
        vector<bool> visited(100,false);
        vector<int> list;
        queue<int> q;
        q.emplace(i);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            if (visited[v]) continue;
            visited[v] = true;
            list.emplace_back(v);
            for (int u: nodes[v].incoming) {
                q.emplace(u);
            }
        }
    }

    int lc = 0, hc = 0;
    int c = 0;
    auto simulatePress = [&](int v) {
        queue<pair<int, pair<int, bool>>> q;
        q.emplace(v, pair<int, bool>{-1, false});
        pair<int, bool> data;
        lc++;
        while (!q.empty()) {
            tie(v, data) = q.front();
            auto [par, set] = data;
            q.pop();

            //cerr << v << " " << pulse<<endl;

            bool newPulse = false;
            if (nodes[v].type == 1) {
                //cerr << "from "  << par << set << endl;
                if (set) {
                    nodes[v].incoming.erase(par);
                } else {
                    nodes[v].incoming.emplace(par);
                }
                newPulse = !nodes[v].incoming.empty();
                //cerr << newPulse<<endl;
            } else if (nodes[v].type == 0) {
                nodes[v].toggle ^= 1;
                newPulse = nodes[v].toggle;
            }
            if (set && v == lastAndNode) {
                //cout << "HI " << c << endl;
                vector<int> children;

                for(int child : nodes[v].allIncoming) {
                    bool present = false;
                    for(int i : nodes[v].incoming) if (i == child) present = true;
                    if (!present) {
                        if (firstOccurence[child] == 0)
                            firstOccurence[child] = c;
                    }
                }
                //cout <<endl;
            }

            if (newPulse) hc += (int) edges[v].size();
            else lc += (int) edges[v].size();

            for (int u: edges[v]) {
                // << v << " " << u << "  " << newPulse << endl;
                if (nodes[u].type != 0 || !newPulse) q.emplace(u, pair<int, bool>{v, newPulse});
            }
        }
    };
    while (firstOccurence.size() < nodes[lastAndNode].incoming.size() ) {
        c++;
        //cerr << firstOccurence.size();
        simulatePress(start);
    }
    long long num = 1;
    for(auto e : firstOccurence) {
        num = lcm(num,e.second);
    }
    cout << num << endl;
    return 0;
}
