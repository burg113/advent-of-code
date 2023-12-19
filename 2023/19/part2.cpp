#include <bits/stdc++.h>

#define ii pair<int,int>
#define ll long long
#define int long long

using namespace std;

// will take 2 - 10 min

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
    vector<vector<int>> importantVals(4);

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
                if (comp == '>')
                    importantVals[valueLookup[val]].emplace_back(num+1);
                if (comp == '<')
                    importantVals[valueLookup[val]].emplace_back(num);

                stream >> c >> c;
            }

            while (c != '}' && c != ',') {
                to += c;
                stream >> c;
            }
            addEdge(node, to, val, comp, num);
            next = c;
        } while (next == ',');
    }

    for(int i=0;i<4;i++) {
        importantVals[i].emplace_back(1);
        importantVals[i].emplace_back(4001);
        std::sort(importantVals[i].begin(), importantVals[i].end());
        importantVals[i].erase( unique( importantVals[i].begin(), importantVals[i].end() ), importantVals[i].end() );
    }

    cerr << importantVals[0].size() << " " << importantVals[1].size() << " "
    << importantVals[2].size() << " " << importantVals[3].size() << endl;
    cerr << importantVals[0].size()*  importantVals[1].size() *  importantVals[2].size() *  importantVals[3].size()<<endl;

    int A = getInd("A");
    int R = getInd("R");
    int in = getInd("in");

    ll ans = 0;
    for(int i1 = 0;i1<importantVals[0].size()-1;i1++) {
        cerr << (float)100*i1/importantVals[0].size() << "% done" <<endl;
        for (int i2 = 0; i2 < importantVals[1].size()-1; i2++) {
            for (int i3 = 0; i3 < importantVals[2].size()-1; i3++) {
                for (int i4 = 0; i4 < importantVals[3].size()-1; i4++) {
                    vector<int> vals = {importantVals[0][i1],
                                        importantVals[1][i2],
                                        importantVals[2][i3],
                                        importantVals[3][i4],};

                    int v = in;
                    while (v != A && v != R) {
                        for (auto [u, cond]: edges[v]) {
                            int val = (cond >> 1) & 3;
                            int comp = cond & 1;
                            int number = (cond >> 3);
                            if (comp == 0 && vals[val] < number) {
                                v = u;
                                break;
                            }
                            if (comp == 1 && vals[val] > number) {
                                v = u;
                                break;
                            }
                        }
                    }
                    int d1 = importantVals[0][i1+1] - importantVals[0][i1];
                    int d2 = importantVals[1][i2+1] - importantVals[1][i2];
                    int d3 = importantVals[2][i3+1] - importantVals[2][i3];
                    int d4 = importantVals[3][i4+1] - importantVals[3][i4];
                    if (v == A) {
                        ans += d1*d2*d3*d4;
                    }

                }
            }
        }
    }

    cout << ans <<endl<<endl;

    return 0;
}
