#include <bits/stdc++.h>

#define ii pair<int,int>

using namespace std;


int32_t main() {
    vector<vector<ii>> edges(3);
    map<string, int> nodeLookup = {{"R",  0},
                                   {"A",  1},
                                   {"in", 2}};
    auto getInd = [&](string s) {
        if (!nodeLookup.count(s)) {
            nodeLookup[s] = edges.size();
            edges.emplace_back();
        }
        return nodeLookup[s];
    };

    map<char, int> compLookup = {{'<', 0},
                                 {'>', 1}};
    map<char, int> valueLookup = {{'x', 0},{'m', 1},{'a', 2},{'s', 3}};
    auto addEdge = [&](string &s, string &s2, char val, char comp, int num) {
        int v = getInd(s), u = getInd(s2);
        edges[v].emplace_back(u, compLookup[comp] + (valueLookup[val] << 1)+ (num << 3));
    };

    string s;
    char next;
    while (getline(cin, s)) {
        cerr << s << endl;
        if (s.empty()) break;
        stringstream stream(s);
        string node;
        char c;
        stream >> c;
        while (c != '{') {
            node += c;
            stream >> c;
        }
        char comp;
        do {
            char val;
            stream >> val;
            stream >> comp;
            int num;

            string to;
            if (comp != '<' && comp != '>') {
                to += val;
                c = comp;

                val = 'x';
                comp = '>';
                num = -1;
            } else {
                stream >> num;
                stream >> c >> c;
            }

            while (c != '}' && c != ',') {
                to += c;
                stream >> c;
            }
            cerr << "add edge " << endl;
            addEdge(node, to, val, comp, num);
            next = c;
        } while (next == ',');
    }

    int ans = 0;
    while (getline(cin, s)) {
        stringstream stream(s);
        vector<int> vals(4);
        char c;
        stream >> c >> c >> c >> vals[0]
               >> c >> c >> c >> vals[1]
               >> c >> c >> c >> vals[2]
               >> c >> c >> c >> vals[3];

        cerr << s << endl;

        int v = getInd("in");
        while (v != getInd("A") && v != getInd("R")) {
            cerr << v << endl;
            for (auto [u, cond]: edges[v]) {
                int val = (cond >> 1)&3;
                int comp = cond & 1;
                int number = (cond >> 3);
                if (comp == 0 && vals[val] < number) {v = u;break;}
                if (comp == 1 && vals[val] > number) {v = u;break;}
            }
        }
        cout << "!!!  " << (v == getInd("A")) <<endl;
        if (v == getInd("A")) ans += vals[0]+vals[1]+vals[2]+vals[3];

    }

    cout << ans<<endl;

    return 0;
}
