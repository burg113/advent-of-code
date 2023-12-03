#include <bits/stdc++.h>

using namespace std;


int main() {
    string s;

    map<string, int> maxVals = {{"red",   12},
                                {"green", 13},
                                {"blue",  14}};
    int sum = 0;
    while (getline(cin, s)) {
        map<string, int> amount;
        stringstream stream(s);
        string _;
        int num,caseNum;
        string col;
        stream >> _ >> caseNum >> _;
        while (stream >> num) {
            stream >> col;
            if (col[col.size()-1]  <  'a')col.pop_back();
            amount[col] = max(num, amount[col]);
        }
        int p = 1;
        for (auto [key,val] : amount) {
            //cerr << key << "  " << val<<endl;
            p *= val;
        }
        sum += p;
    }

    cout<< sum;

    return 0;
}
