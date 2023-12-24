#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define double long double

double cross(complex<double> a, complex<double> b) { return imag(conj(a) * b); }

complex<double> lineIntersection(complex<double> p0, complex<double> p1, complex<double> p2, complex<double> p3) {
    double a = cross(p1 - p0, p3 - p2);
    double b = cross(p2 - p0, p3 - p2);
    return {p0 + b / a * (p1 - p0)};
}

struct Line {

    ll x, y, z, dx, dy, dz;

    complex<double> intersect(const Line &o) {

        if (dx * o.dy == dy * o.dx) return complex<double>(-1,-1);
        complex<double> res = lineIntersection(complex<double>(x, y), complex<double>(x + dx, y + dy),
                                         complex<double>(o.x, o.y), complex<double>(o.x + o.dx, o.y + o.dy));
        if (((real(res)) - x)*dx > 0 && (real(res)-o.x)*o.dx > 0) return res;
        return complex<double>(-1,-1);




        /*ll nx = x - other.x, ny = y - other.y;
        ll ndx = dx - other.dx, ndy = dy - other.dy;



        if ((ndx == 0 && nx != 0) && (ndy == 0 && ny != 0)) {
            return {-1, -1};
        }
        cerr << x<< "-"<< ((dx == 0) ? 0 : ((double)nx / (double)dx))<<endl;
        return {(double)x - ((dx == 0) ? 0 : ((double)nx / (double)dx)), (double)y - ((dy == 0) ? 0 : ((double)ny / (double)dy))};*/
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
    for (int i = 0; i < lines.size(); i++) {
        for (int j = i + 1; j < lines.size(); j++) {
            complex<double> res = lines[i].intersect(lines[j]);
            double x = real(res), y = imag(res);
            //cerr << x << " " << y << endl;
            if(x >= 200000000000000 && x <= 400000000000000 && y >= 200000000000000 && y <= 400000000000000)
                count++;
        }
    }
    cout << count << endl;

    return 0;
}
