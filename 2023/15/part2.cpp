#include <bits/stdc++.h>

using namespace std;


int32_t main() {
    string s;
    getline(cin, s);

    vector<vector<pair<string,int>>> boxes(256);

    auto comp = [&](int lens, int box, const string& label) {
        bool repl = false;
        if (lens > 0) {
            for(auto it = boxes[box].begin();it!=boxes[box].end();it++) {
                if (it->first == label) {
                    it->second = lens;
                    repl = true;
                    break;
                }
            }
            if (!repl) boxes[box].emplace_back(label,lens);
        }
        else {
            for(auto it = boxes[box].begin();it!=boxes[box].end();it++) {

                if (it->first == label) {
                    boxes[box].erase(it);
                    break;
                }
            }
        }
        /*cerr <<endl<<endl<< "comp " << lens << "  " << box << "  "<< label<< endl;
        for(int i=0;i<boxes.size();i++) {
            if (boxes[i].size() > 0) {
                cerr << "BOX " << i << "  ";
                for(auto e : boxes[i]) cerr << e.second << " ";
                cerr << endl;
            }
        }*/
    };

    int val = 0;
    int lens;
    string label;
    for (char c: s) {
        if (c == ',') {
            comp(lens, val, label);
            val = 0, lens = -1;
            label = "";
            continue;
        }
        if (c == '=' || c == '-') continue;

        if (c - '0' >= 0 && '9' - c >= 0) lens = c - '0';
        else {
            label += c;
            val = (val + (int) c) * 17 % 256;
        }

    }
    comp(lens, val, label);

    int ans = 0;
    for(int i=0;i<boxes.size();i++) {
        for(int j = 0;j< boxes[i].size();j++){
            ans += (i+1) * boxes[i][j].second * (j+1);
        }
    }

    cout << ans << endl;

    return 0;
}
