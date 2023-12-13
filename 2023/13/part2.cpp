#include <bits/stdc++.h>

using namespace std;

// note: only works if two empty lines at end of file

int32_t main() {
    string s;
    vector<vector<bool>> field;

    auto eq = [&](int m) {
        int rCount = 0;
        int r1 = m, r2 = m+1;
        while (true) {
            if (r1 < 0 || r2 >= field.front().size()) return rCount;
            for (int i = 0; i < field.size(); i++) {
                if (field[i][r1] != field[i][r2]) rCount++;
            }
            r1--,r2++;
        }
    };
    auto eq2 = [&](int m) {
        int rCount = 0;
        int r1 = m, r2 = m+1;
        while (true) {
            if (r1 < 0 || r2 >= field.size()) return rCount;

            for (int i = 0; i < field.front().size(); i++) {
                if (field[r1][i] != field[r2][i]) rCount++;
            }

            r1--,r2++;
        }
    };

    int ans = 0;
    while (getline(cin, s)) {
        if (s.empty()) {
            int w = (int) field.back().size();
            int h = (int) field.size();

            for (int i = 0; i < w - 1; i++) {
                if(eq(i) == 1)
                    ans += i+1;
            }
            cerr <<endl;
            for (int i = 0; i < h - 1; i++) {
                cerr << eq2(i) << endl;
                if(eq2(i) == 1)
                    ans += (i+1)* 100;
            }
            field = vector<vector<bool>>();
            continue;
        }
        field.emplace_back();
        for (char c: s) {
            if (c == '#') field.back().emplace_back(true);
            if (c == '.') field.back().emplace_back(false);
        }

    }

    cout << ans << endl;

    return 0;
}
