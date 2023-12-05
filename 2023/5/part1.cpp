#include <bits/stdc++.h>
#define int long long
using namespace std;


int32_t main() {
    string s,_;
    vector<int> pot2;
    cin >> s;

    getline(cin, s);
    stringstream stream(s);
    cerr << s;
    set<int> nums;
    int i;
    while (stream >> i) {
        nums.emplace(i);
    }


    getline(cin, s);
    cerr << "1 throw away: " << s;
    while (getline(cin, s)) {
        //cerr << "throw away: " << s<<endl<<endl<<endl;
        set<int> newNums;
        while (getline(cin, s) && !s.empty()) {
            //cerr << "read " << s <<endl;
            stream = stringstream (s);
            int x,y,d;
            stream >> y >> x >> d;
            //cerr << _ <<" | "<< x<<" | " << y <<" | "<< d<<endl;
            vector<int> del;
            for(int n : nums) {
                //cerr <<x<< " ? " << n << " ? " << x+d<<endl;
                if (n>=x && n<x+d) {

                    cerr <<"mapped: "<< n << "  to  " << n-x+y<<endl;
                    newNums.emplace(n-x+y);
                    del.emplace_back(n);
                }
            }
            for(int n : del) nums.erase(n);

        }
        for(int e : nums) newNums.emplace(e);
        nums = newNums;

        cerr << "new Nums: ";
        for(int num : nums) cerr << num << " ";
        cerr << endl;
    }

    return 0;
}
