#include <bits/stdc++.h>

#define int long long

using namespace std;


int32_t main() {
    string s;
    vector<vector<int>> field;
    while (getline(cin, s)) {
        field.emplace_back();
        int numBuff = 0;
        for (char c: s) {
            if (c - '0' < 10 && c - '0' >= 0) numBuff = 10 * numBuff + c - '0';
            else {
                if (numBuff > 0) {
                    for (int i = 1; i <= numBuff; i *= 10) {
                        field[field.size() - 1].emplace_back(numBuff);
                    }
                    numBuff = 0;
                }
                if (c == '.')field[field.size() - 1].emplace_back(0);
                else field[field.size() - 1].emplace_back(-1);
            }
        }
        if (numBuff > 0) {
            for (int i = 1; i <= numBuff; i *= 10) {
                field[field.size() - 1].emplace_back(numBuff);
            }
            numBuff = 0;
        }

    }
    int awns = 0;
    for (int y = 0; y < field.size(); y++) {
        for (int x = 0; x < field[0].size(); x++) {
            if (field[y][x] <0) cout << "#";
            else if(field[y][x] == 0) cout << " ";
            else cout << 'N';

            if (field[y][x] == -1) {
                //cerr << "! " << x << " " << y<<endl;
                for (int dy = max(y - 1, 0ll); dy < min(y + 2, (int) field.size()); dy++) {
                    for (int dx = max(x - 1, 0ll); dx < min(x + 2, (int) field[0].size()); dx++) {
                        if (field[dy][dx] <= 0) continue;
                        awns += field[dy][dx];

                        for (int dxx = dx + 1; dxx < field[0].size() && field[dy][dxx] == field[dy][dx]; dxx++) {
                            field[dy][dxx] = 0;
                        }

                        for (int dxx = dx - 1; dxx >= 0 && field[dy][dxx] == field[dy][dx]; dxx--) {
                            field[dy][dxx] = 0;

                            field[dy][dx] = 0;
                        }
                    }
                }
            }

        }
        cout << endl;
    }
    cout << awns << endl;

    return 0;
}
