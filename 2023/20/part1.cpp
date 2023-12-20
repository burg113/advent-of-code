#include <bits/stdc++.h>

#define ii pair<int,int>
using namespace std;

struct Node {
    int type = 2;
    bool toggle = false;
    set<int> incoming;

};

int32_t main() {
    string s;

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
        cerr << s << endl;
        stringstream stream(s);
        string node;
        stream >> node;
        bool b = (node[0] == '&');
        if (s[0] != 'b') node.erase(node.begin());
        int v = getInd(node);

        if (s[0] == 'b') {
            start = (int) nodes.size() - 1;
            nodes[v].type = 2;
        } else nodes[v].type = b;


        string _, toNode;
        stream >> _;
        while (stream >> toNode) {
            if (toNode.back() == ',') toNode.pop_back();
            int u = getInd(toNode);
            cerr << "# " << v << " to " << u << " (" << toNode << ")" << endl;
            edges[v].emplace_back(u);
            nodes[u].incoming.emplace(v);
        }
    }


    int lc = 0, hc = 0;
    auto simulatePress = [&](int v) {
        queue<pair<int, pair<int,bool>>> q;
        q.emplace(v, pair<int,bool>{-1,false});
        pair<int,bool> data;
        lc++;
        while (!q.empty()) {

            tie(v, data) = q.front();
            auto [par,set] = data;
            q.pop();

            //cerr << v << " " << pulse<<endl;

            bool newPulse = false;
            if (nodes[v].type == 1) {
                //cerr << "from "  << par << set << endl;
                if (set) {
                    nodes[v].incoming.erase(par);
                }else {
                    nodes[v].incoming.emplace(par);
                }
                newPulse = !nodes[v].incoming.empty();
                //cerr << newPulse<<endl;
            }else if (nodes[v].type == 0) {
                nodes[v].toggle ^= 1;
                newPulse = nodes[v].toggle;
            }

            if (newPulse) hc += (int) edges[v].size();
            else lc += (int) edges[v].size();

            for (int u: edges[v]) {
                // << v << " " << u << "  " << newPulse << endl;
                if (nodes[u].type != 0 || !newPulse) q.emplace(u, pair<int,bool>{v,newPulse});
            }
        }
    };

    for (int i = 0; i < 1000; i++) {
        // cerr << endl;
        simulatePress(start);

    }

    cerr << endl << lc << " * " << hc << endl;
    cout << lc * hc << endl;
    return 0;
}
