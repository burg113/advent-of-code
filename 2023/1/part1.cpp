#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    int sum = 0;
    int a = -1,b = -1;
    while (getline(cin,s)) {
        for (char c : s) {
            if ((c -'0') < 10) {
                if (a == -1) a = (c -'0');
                b = (c -'0');
            }
        }
        sum += a*10 + b, a = -1;
    }
    cout << sum;

    return 0;
}
