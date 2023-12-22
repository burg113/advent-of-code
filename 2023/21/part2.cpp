#include <bits/stdc++.h>

using namespace std;
#define int long long

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
    function<void(int, int, int, bool)> fill = [&](int x, int y, int remainingSteps, bool countEven) {
        queue<pair<pair<int, int>, int >> q;
        q.emplace(pair<int, int>{x, y}, remainingSteps);
        while (!q.empty()) {
            auto [pos, rem] = q.front();
            tie(x, y) = pos;
            q.pop();

            if (visited[y][x] || field[y][x] == 1) {
                continue;
            }
            visited[y][x] = true;
            if ((x+y) % 2 != countEven) {
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

    int a1, a2;

    count = 0;
    visited = vector<vector<bool>>(height, vector<bool>(width, false));
    fill(0, 0, width + height, false);
    a1 = count;

    count = 0;
    visited = vector<vector<bool>>(height, vector<bool>(width, false));
    fill(0, 0, width + height, true);
    a2 = count;

    int steps = 26501365;

    int leftOnBoarder = (steps - startX - 1) % width;
    int leftOnBoarder2 = (steps - 2*startX - 2) % width;
    int p = (steps - 2*startX - 2) / width;

    int amount = 1, amount2 = 0;
    int tmp = 0;
    for (int i = 0; i < p; i++) {
        tmp += 4;
        if (i & 1) amount += tmp;
        else amount2 += tmp;
    }
    int ans = amount * a1 + amount2 * a2;

    int s1 = 0,s2 = 0;
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            if (x == 0 && y == 0) continue;

            if (x == 0 || y == 0) {
                count = 0;
                visited = vector<vector<bool>>(height, vector<bool>(width, false));
                fill(startX + x * startX, startY + y * startY, leftOnBoarder, p % 2 == 0);
                s1 += count;
            } else {
                count = 0;
                visited = vector<vector<bool>>(height, vector<bool>(width, false));
                fill(startX + x * startX, startY + y * startY, leftOnBoarder+startX, p % 2 == 0);
                s2 += count * p;

                count = 0;
                visited = vector<vector<bool>>(height, vector<bool>(width, false));
                fill(startX + x * startX, startY + y * startY, leftOnBoarder2, p % 2 != 0);
                s2 += count * (p + 1);
            }
        }
    }

    cout << ans + s1 + s2 << endl;
    //cerr << ans << "   " << s1 <<"    "<< s2  << endl;

    return 0;
}
