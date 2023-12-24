#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define double long double
#define EPS 1e-24

vector<vector<double>> mat;

void normalLine(int line) {
    double factor = mat[line][line];
    for (double &x: mat[line]) x /= factor;
}

void takeAll(int n, int line) {
    for (int i = 0; i < n; i++) {
        if (i == line) continue;
        double diff = mat[i][line];
        for (int j = 0; j < 2*n; j++) {
            mat[i][j] -= diff * mat[line][j];
        }
    }
}

bool gauss(int n) {
    vector<bool> done(n, false);
    for (int i = 0; i < n; i++) {
        int swappee = i;
        for (int j = 0; j < n; j++) {
            if (done[j]) continue;
            if (abs(mat[j][i]) > abs(mat[i][i])) swappee = j;
        }
        swap(mat[i], mat[swappee]);
        if (abs(mat[i][i]) > EPS) {
            normalLine(i);
            takeAll(n, i);
            done[i] = true;
        }
    }
    for (int i = 0; i < n; i++) {
        bool allZero = true;
        for (int j = i; j < n; j++) allZero &= abs(mat[i][j]) <= EPS;
        if (allZero && abs(mat[i][n]) > EPS) return 0;
        if (allZero && abs(mat[i][n]) <= EPS) return 0;
    }
    return 1;
}

vector<double> cross(vector<double> a, vector<double> b) {
    return {
            a[1] * b[2] - a[2] * b[1],
            a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0]
    };
}

vector<double> sub(vector<double> a, vector<double> b) {
    return {a[0] - b[0], a[1] - b[1], a[2] - b[2]};
}

struct Line {
    double x, y, z, dx, dy, dz;

    vector<double> pos() {
        return {x, y, z};
    }

    vector<double> dir() {
        return {dx, dy, dz};
    }
};


int32_t main() {
    string s;
    vector<Line> lines;
    while (getline(cin, s)) {
        lines.emplace_back();
        stringstream stream(s);
        Line *l = &lines.back();
        char _;
        stream >> l->x >> _ >> l->y >> _ >> l->z >> _ >> l->dx >> _ >> l->dy >> _ >> l->dz;
    }
    int count = 0;
    for (int i = 0; i < lines.size() - 1; i++) {
        mat = vector<vector<double>>();
        Line *l1 = &lines[i], *l2 = &lines[i + 1], *l3 = &lines[i + 2];
        vector<double> d1 = {l1->dx - l2->dx, l1->dy - l2->dy, l1->dz - l2->dz};
        vector<double> d2 = {l2->dx - l3->dx, l2->dy - l3->dy, l2->dz - l3->dz};
        vector<double> p1 = {l1->x - l2->x, l1->y - l2->y, l1->z - l2->z};
        vector<double> p2 = {l2->x - l3->x, l2->y - l3->y, l2->z - l3->z};
        int c = 0;
        // p x (di - dj) + (pi-pj) x d = pi x di - pj x dj
        for (auto [d, p]: vector<pair<vector<double>, vector<double>>>{{d1, p1},
                                                                       {d2, p2}}) {
            mat.emplace_back(vector<double>{0, d[2], -d[1], 0, -p[2], p[1]});
            for (int j = 0; j < 6; j++) mat.back().emplace_back(0);
            mat.emplace_back(vector<double>{-d[2], 0, d[0], p[2], 0, -p[0]});
            for (int j = 0; j < 6; j++) mat.back().emplace_back(0);
            mat.emplace_back(vector<double>{d[1], -d[0], 0, -p[1], p[0], 0});
            for (int j = 0; j < 6; j++) mat.back().emplace_back(0);
            cerr << "!" << 3 * c << " " << 6 + 3 * c << endl;
            mat[3 * c][6 + 3 * c] = 1;
            mat[3 * c + 1][6 + 3 * c + 1] = 1;
            mat[3 * c + 2][6 + 3 * c + 2] = 1;
            c++;
        }
        for (vector<double> row: mat) {
            for (int j =0;j<6;j++) cerr << setw(16) << row[j];
            cerr << endl;
        }
        cerr << endl;
        for (vector<double> row: mat) {
            for (auto d: row) cerr << setw(16) << d;
            cerr << endl;
        }
        cerr << endl;
        bool res = gauss(6);
        cerr << res << endl << endl;

        for (vector<double> row: mat) {
            for (auto d: row) cerr << setw(16) << d;
            cerr << endl;
        }
        cerr << endl;
        for (vector<double> row: mat) {
            for (int j =6;j<12;j++) cerr << setw(16) << row[j];
            cerr << endl;
        }
        cerr << endl << endl;
        if (res) {
            vector<double> vec = sub(cross(l1->pos(), l1->dir()), cross(l2->pos(), l2->dir()));
            for (double d: sub(cross(l2->pos(), l2->dir()), cross(l3->pos(), l3->dir())))
                vec.emplace_back(d);

            for(auto a : vec) cerr << a << endl;

            vector<double> ans;
            for (int y = 0; y < 6; y++) {
                double sum = 0;
                for (int x = 0; x < 6; x++) {
                    sum+=mat[y][x+6] * vec[x];
                }
                ans.emplace_back(sum);
            }

            cout << "\n\n____________________________________________________\n";
            for(auto a : ans)
                cout << a << endl;
            cout << "____________________________________________________\n";

            cout <<setprecision(20)<< round(ans[0] + ans[1] + ans[2]) << endl;

            break;
        }
    }
    //cout << count << endl;

    return 0;
}
