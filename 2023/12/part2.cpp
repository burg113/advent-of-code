#include <bits/stdc++.h>
#define int long long
using namespace std;


int32_t main() {
    string s;
    int count = 0;
    while (getline(cin, s)) {
        string str;
        for (char c: s) {
            if (c == ' ') break;
            else str.push_back(c);
        }
        char _;
        stringstream stream(s);
        for (int i = 0; i < str.size(); i++) stream >> _;

        char c;
        vector<bool> tpattern;
        int num;
        do {
            stream >> num;
            tpattern.emplace_back(false);
            for (int i = 0; i < num; i++)
                tpattern.emplace_back(true);
        } while (stream >> c);

        vector<bool> pattern = tpattern;
        string trueS = str;
        for(int i = 0;i<4;i++) {
            for(bool p : tpattern) pattern.emplace_back(p);
            trueS += '?' + str;
        }
        str = trueS;

        cerr << str << "  " << pattern.size() << endl;

        vector<vector<int>> dp(str.size() + 1, vector<int>(pattern.size() + 1, 0));
        dp[str.size()][pattern.size() - 1] = 1;
        for (int i = (int) str.size() - 1; i >= 0; i--) {
            if (str[i] == '.' || str[i] == '?') {
                dp[i][0] = dp[i + 1][0];
                dp[i][pattern.size() - 1] = dp[i + 1][pattern.size() - 1];
            }
            for (int j = 1; j < pattern.size(); j++) {
                if (str[i] == '.' || str[i] == '?') {
                    if (!pattern[j]) {
                        dp[i][j - 1] += dp[i + 1][j];
                        dp[i][j] += dp[i + 1][j];
                    }

                }
                if (str[i] == '#' || str[i] == '?') {
                    if (pattern[j]) {
                        dp[i][j - 1] += dp[i + 1][j];
                    }

                }
            }
        }
        int a = dp[0][0];
        cerr << a << endl;
        count += a;
    }
    cout << count << endl;

    return 0;
}
