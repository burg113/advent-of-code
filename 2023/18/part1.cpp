#include <bits/stdc++.h>

#define ll long long
#define ii pair<int,int>

using namespace std;

int32_t main() {
    string s;
    map<char, int> lookup = {{'R', 1},
                             {'L', 0},
                             {'U', 3},
                             {'D', 2}};

    vector<ii > moves;
    ii mi = {0, 0}, ma = {0, 0};

    ii cur = {0, 0};
    while (getline(cin, s)) {
        stringstream stringstream(s);
        char c;
        int dist;
        stringstream >> c >> dist;
        if (lookup[c] < 2) {
            moves.emplace_back((lookup[c] * 2 - 1) * dist, 0);
            cur.first += (lookup[c] * 2 - 1) * dist;
            mi.first = min(mi.first, cur.first);
            ma.first = max(ma.first, cur.first);
        } else {
            moves.emplace_back(0, ((lookup[c] & 1) * 2 - 1) * dist);
            cur.second += ((lookup[c] & 1) * 2 - 1) * dist;
            mi.second = min(mi.second, cur.second);
            ma.second = max(ma.second, cur.second);
        }
        //cerr << moves.back().first << " " << moves.back().second<<endl;
    }
    mi.first--, mi.second--, ma.first++, ma.second++;
    vector<vector<int>> field(ma.second - mi.second + 1, vector<int>(ma.first - mi.first + 1, 0));
    cur = {-mi.first, -mi.second};
    for (ii m: moves) {
        cerr << m.first << " " << m.second << endl;
        int l = max(abs(m.first), abs(m.second));
        for (int i = 0; i < l; i++) {
            int x = cur.first + m.first / l * i;
            int y = cur.second + m.second / l * i;
            //cerr << "(" << x << "," << y << ") ";
            field[y][x] = 1;
        }
        cerr << endl;
        cur.first += m.first, cur.second += m.second;
        //cerr << cur.first << " " << cur.second<<endl;
    }

    int count = 0;
    function<void(int, int)> fill = [&](int x, int y) {
        if (field[y][x] == 0){
            count++;
            field[y][x] = 2;
        }else return;
        if (x > 0) fill(x - 1, y);
        if (y > 0) fill(x, y - 1);
        if (x + 1 < field.front().size()) fill(x + 1, y);
        if (y + 1 < field.size()) fill(x, y + 1);

    };
    fill(0,0);

    for (int y = 0; y < field.size(); y++) {
        for (int x = 0; x < field[y].size(); x++) {
            cout << ((field[y][x]==1) ? '#' : (field[y][x] == 0)?'.': '+');
        }
        cout << endl;
    }

    cout << field.size() * field.front().size() - count <<endl;

    return 0;
}
