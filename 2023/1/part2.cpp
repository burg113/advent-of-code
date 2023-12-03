#include <bits/stdc++.h>

using namespace std;

vector<pair<int,string>> nums = {{1,"one"},
                         {2,"two"},
                         {3,"three"},
                         {4,"four"},
                         {5,"five"},
                         {6,"six"},
                         {7,"seven"},
                         {8,"eight"},
                         {9,"nine"}
};


int main() {
    string s;
    int sum = 0;
    while (getline(cin, s)) {
        vector<int> first = {-1, -1};
        for (int j = 0; j < 2; j++) {
            vector<string> last = {"   ", "    ", "     "};
            for (char c: s) {
                if (first[j] != -1) break;
                last[0].erase(0, 1);
                last[1].erase(0, 1);
                last[2].erase(0, 1);
                last[0] += c;
                last[1] += c;
                last[2] += c;
                if ((c - '0') < 10) first[j] = (c - '0');
                for (auto [n,search]: nums) for (string l : last) {
                        if (l == search)first[j] = n;
                    }

            }
            for (auto it = nums.begin(); it != nums.end(); ++it) {
                std::reverse((*it).second.begin(), (*it).second.end());
            }

            reverse(s.begin(), s.end());
        }
        cerr << first[0] * 10 + first[1] << endl;
        sum += first[0] * 10 + first[1];
    }
    cout << sum;

    return 0;
}
