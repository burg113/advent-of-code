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

bool lexComp(string s1, string s2) {
    map<char, char> m;
    m['A'] = 'a';
    m['K'] = 'b';
    m['Q'] = 'c';
    m['J'] = 'p';
    m['T'] = 'e';
    m['0'] = 'f';
    m['9'] = 'g';
    m['8'] = 'h';
    m['7'] = 'i';
    m['6'] = 'j';
    m['5'] = 'k';
    m['4'] = 'l';
    m['4'] = 'm';
    m['3'] = 'n';
    m['2'] = 'o';

    string s3, s4;
    for (char c: s1) s3.push_back(m[c]);
    for (char c: s2) s4.push_back(m[c]);

    cerr << s3 << "   " << s4<<endl;

    return s3.compare(s4) == 1;
}


int32_t main() {
    string s;
    int i;
    vector<pair<string, int>> people;
    while (getline(cin, s)) {
        stringstream stream(s);
        stream >> s >> i;
        people.emplace_back(s, i);
        cerr << s << "  " << power(s) << endl;
    }



    std::sort(people.begin(), people.end(), [&](const pair<string, int> &first, const pair<string, int> &second) {
        if (power(first.first) != power(second.first))
            return power(first.first) < power(second.first);


        return lexComp(first.first,second.first);
    });
    int count = 0;
    int ans = 0;
    for(auto[_,j] : people) {
        cerr << j <<endl;
        ans += (++count) * j;
    }
    cout << ans<<endl;
    return 0;
}
