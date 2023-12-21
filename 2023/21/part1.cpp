#include <bits/stdc++.h>

struct Edge {
    int to;
};

using namespace std;


int32_t main() {
    string s;

    vector<vector<int>> field;
    int startX = 0, startY = 0;
    int width = 0;
    int height = 0;
    while (getline(cin, s)) {
        width = s.size();

        field.emplace_back();
        for (char c: s) {
            if (c == 'S') {
                startX = field.back().size();
                startY = height;
            }
            field.back().emplace_back(c == '#');
        }
        height++;
    }

    int count = 0;
    vector<vector<bool>> visited(height, vector<bool>(width, false));
    function<void(int, int, int)> fill = [&](int x, int y, int remainingSteps) {
        queue<pair<pair<int, int>, int>> q;
        q.emplace(pair<int,int>{x, y},remainingSteps);
        while (!q.empty()) {
            auto [pos, rem] = q.front();
            tie(x, y) = pos;
            q.pop();

            if (visited[y][x] || field[y][x] == 1) {
                continue;
            }
            visited[y][x] = true;
            if (rem % 2 == 0) {
                count++;
            }

            if (rem <= 0) continue;

            if (x > 0)
                q.emplace(pair<int, int>{x - 1, y}, rem - 1);
            if (y > 0)
                q.emplace(pair<int, int>{x, y - 1}, rem - 1);
            if (x + 1 < field.front().size())
                q.emplace(pair<int, int>{x + 1, y}, rem - 1);
            if (y + 1 < field.size())
                q.emplace(pair<int, int>{x, y + 1}, rem - 1);
        }
    };
    fill(startX, startY, 64);
    cout << count << endl;
    for (int y = 0; y < visited.size(); y++) {
        for (int x = 0; x < visited.front().size(); ++x) {
            cout << (visited[y][x] ? 'O' : (field[y][x] == 1) ? '#' : '.') << " ";
        }
        cout << endl;
    }
    return 0;
}
