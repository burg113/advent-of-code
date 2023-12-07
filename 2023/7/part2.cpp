#include <bits/stdc++.h>

using namespace std;

int power(string str) {
    map<char, int> m;
    for (char c: str) m[c]++;
    bool already2 = false;
    bool already3 = false;
    for (auto [c, a]: m) {
        if (c == 'J') continue;

        if (a == 5) return 6;
        if (a == 4) {
            if (m['J'] == 1)return 6;
            return 5;
        }
        if (a == 3) {
            if (already2) return 4;
            already3 = true;
        }
        if (a == 2) {
            if (already2) {
                if(m['J'] == 1)
                    return 4;
                return 2;
            }
            if (already3) return 4;
            already2 = true;
        }

    }
    if (already3) {
        if (m['J'] >= 2) return 6;
        if (m['J'] == 1) return 5;
        return 3;
    }
    if (already2) {
        if (m['J'] == 3) return 6;
        if (m['J'] == 2) return 5;
        if (m['J'] == 1) return 3;
        return 1;
    }
    if (m['J'] == 5) return 6;
    if (m['J'] == 4) return 6;
    if (m['J'] == 3) return 5;
    if (m['J'] == 2) return 3;
    if (m['J'] == 1) return 1;
    return 0;
}

string lexStr(string s) {
    map<char, char> m;
    m['A'] = 'o';
    m['K'] = 'n';
    m['Q'] = 'm';
    m['T'] = 'l';
    m['0'] = 'k';
    m['9'] = 'j';
    m['8'] = 'i';
    m['7'] = 'h';
    m['6'] = 'g';
    m['5'] = 'f';
    m['4'] = 'e';
    m['4'] = 'd';
    m['3'] = 'c';
    m['2'] = 'b';
    m['J'] = 'a';

    string s2;
    for (char c: s) s2.push_back(m[c]);

    return s2;
}


int32_t main() {
    string s;
    int i;
    vector<pair<pair<int,string>, int>> people;
    while (getline(cin, s)) {
        stringstream stream(s);
        stream >> s >> i;
        people.emplace_back(pair<int,string>{power(s), lexStr(s)}, i);
        cerr << s << "  " << power(s) << " "  << lexStr(s) << endl;
    }



    std::sort(people.begin(), people.end());
    int count = 0;
    int ans = 0;
    for(auto[_,j] : people) {
        cerr << _.first<<"  " << _.second <<"\t\t" << j<<endl;
        ans += (++count) * j;
    }
    cout << ans<<endl;
    return 0;
}
