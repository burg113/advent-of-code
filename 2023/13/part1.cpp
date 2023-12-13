#include <bits/stdc++.h>

using namespace std;

// note: only works if two empty lines at end of file

int32_t main() {
    string s;
    vector<vector<bool>> field;

    auto eq = [&] (int r1, int r2) {
        if (r1 < 0 || r2 >= field.front().size())
            return false;
        for(auto & i : field) {
            if (i[r1] != i[r2])
                return false;
        }
        return true;
    };

    int ans = 0;
    while (getline(cin, s)) {
        if (s.empty()) {
            int w = (int)field.back().size();
            int h = (int)field.size();
            int perfR = -1;
            int perfC = -1;
            for (int i = 0; i <w-1;i++) {
                int c = 0;
                for(;;c++) {
                    if (!eq(i-c,i+c+1)) break;
                }
                if (i-c < 0 || i+c+1 >= w)
                    perfC = i;
            }
            for (int i = 0; i <h-1;i++) {
                int c = 0;
                for(;;c++) {
                    if (i-c < 0 || i+c+1 >= field.size()) {
                        perfR = i;
                        break;
                    }else if (field[i-c] != field[i+c+1])
                        break;

                }
            }
            cerr << perfC << "  " << perfR << endl;
            if (perfC != -1 && perfR != -1) cerr << "PROBLEM" << endl;
            if (perfR != -1)
                ans+= (perfR+1)*100;
            else
                ans += (perfC+1);
            field = vector<vector<bool>>();
            continue;
        }
        field.emplace_back();
        for(char c : s) {
            if (c == '#') field.back().emplace_back(true);
            if (c == '.') field.back().emplace_back(false);
        }

    }

    cout << ans << endl;

    return 0;
}
