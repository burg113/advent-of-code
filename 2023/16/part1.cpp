#include <bits/stdc++.h>

using namespace std;

map<char, int> lookup;

int32_t main() {
    lookup['\\'] = 0;
    lookup['/'] = 1;
    lookup['|'] = 2;
    lookup['-'] = 3;

    string s;
    vector<int> field;
    int w = 0;
    while (getline(cin, s)) {
        w = (int) s.size();
        for (char c: s) field.emplace_back((lookup.count(c)) ? lookup[c] : -1);
    }

    map<int, int> dif;
    dif[0] = 1;
    dif[1] = -1;
    dif[2] = w;
    dif[3] = -w;

    vector<vector<bool>> visited(field.size(), vector<bool>(4, false));
    function<void(int, int)> fill = [&](int pos, int dir) {
        if (pos % w == 0 && dir == 1) return;
        if (pos % w == w - 1 && dir == 0) return;
        if (pos + dif[dir] >= field.size() || pos + dif[dir] < 0) return;

        pos += dif[dir];

        if (visited[pos][dir]) return;
        visited[pos][dir] = true;

        if (field[pos] == -1) {             //  .
            fill(pos, dir);
        } else if ((field[pos] & 2) == 0) {    //  \ or /
            int nDir = (dir+2)%4 ^ field[pos];
            cerr << dir << " " << nDir <<endl;
            fill(pos, nDir);
        } else {
            if ((dir ^ (field[pos] << 1)) & 2) fill(pos, dir);
            else {
                int nDir = (dir + 2) % 4;
                fill(pos, nDir);
                fill(pos, nDir ^ 1);
            }
        }
    };
    fill(-1, 0);

    int c = 0;
    for (vector<bool> v: visited) {
        if (any_of(v.begin(), v.end(), [](bool v) { return v; })) c++;
    }
    for (int y = 0; y < field.size() / w; ++y) {
        for (int x = 0; x < w; x++)
            cout << (any_of(visited[y * w + x].begin(), visited[y * w + x].end(),
                            [](bool v) { return v; }) ? '#': '.');
        cout << endl;
    }

    cout << c << endl;

    return 0;
}
