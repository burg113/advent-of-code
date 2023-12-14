#include <bits/stdc++.h>

using namespace std;

void rotate(vector<vector<bool>>& field,vector<vector<bool>>& stops) {
    for(int y = 0;y < field.front().size();y++) {
        for(int x = 0; x < field.size(); x++) {
            if (field[x][y]) {
                field[x][y] = false;
                int ty = y;
                while (ty > 0 && !field[x][ty-1] && ! stops[x][ty-1]) ty --;
                field[x][ty] = true;
            }
        }
    }
    for (int x = 0; x < field.size(); ++x) {
        for (int y = 0; y < field.front().size(); ++y) {
            if (field[x][y]) {
                field[x][y] = false;
                int tx = x;
                while (tx > 0&& !field[tx-1][y] && !stops[tx-1][y]) tx--;
                field[tx][y] = true;
            }
        }
    }

    int h = (int)field.size() -1;
    for(int y = 0;y < field.front().size();y++) {
        for(int x = 0; x < field.size(); x++) {
            if (field[x][h-y]) {
                field[x][h-y] = false;
                int ty = y;
                while (ty > 0 && !field[x][h - (ty-1)] && ! stops[x][h - (ty-1)]) ty --;
                field[x][h - ty] = true;
            }
        }
    }

    int w = (int) field.size()-1;
    for (int x = 0; x < field.size(); ++x) {
        for (int y = 0; y < field.front().size(); ++y) {
            if (field[w-x][y]) {
                field[w-x][y] = false;
                int tx = x;
                while (tx > 0&& !field[w - (tx-1)][y] && !stops[w - (tx-1)][y]) tx--;
                field[w-tx][y] = true;
            }
        }
    }
}


int32_t main() {
    string s;
    getline(cin, s);
    vector<vector<bool>> stops(s.size());
    vector<vector<bool>> field(s.size());

    int y = 0;
    do {
        for(int x=0; x < s.size(); x++) {
            stops[x].emplace_back(s[x] == '#');
            field[x].emplace_back(s[x] == 'O');
        }
        y++;
    }while (getline(cin, s));

    int remaining = 1000000000;
    map<vector<vector<bool>>,int> firstOcc;
    int count = 0;

    while (remaining > 0) {
        if (firstOcc.count(field)) {
            remaining = remaining%(count - firstOcc[field]);
            count += 1000000000 - remaining;
        }
        firstOcc[field] = count;
        rotate(field,stops);
        remaining--;
        count++;
    }

    int ans = 0;
    for(int y = 0;y < field.front().size();y++)
        for(int x = 0; x < field.size(); x++)
            if (field[x][y]) ans += (int)field.front().size() - y;
    cout << ans << endl;


    return 0;
}
