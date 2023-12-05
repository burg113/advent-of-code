#include <bits/stdc++.h>
#define int long long
#define ii pair<int,int>
using namespace std;


int32_t main() {
    string s,_;
    vector<int> pot2;
    cin >> s;

    getline(cin, s);
    stringstream stream(s);
    //cerr << s;
    set<ii> nums;
    int i;
    while (stream >> i) {
        int l;
        stream >> l;
        nums.emplace(i,i+l);
    }


    getline(cin, s);
    //cerr << "1 throw away: " << s;
    while (getline(cin, s)) {
        //cerr << "throw away: " << s<<endl<<endl<<endl;
        set<ii> newNums;
        while (getline(cin, s) && !s.empty()) {
            //cerr << "read " << s <<endl;
            stream = stringstream (s);
            int x,y,d;
            stream >> y >> x >> d;
            //cerr << _ <<" | "<< x<<" | " << y <<" | "<< d<<endl;
            vector<pair<ii,ii>> del;
            for(ii range : nums) {
                //cerr <<"  range: "<< range.first << "  "<< range.second<<endl;
                int l = max(range.first,x);
                int r = min(range.second,x+d);
                //cerr <<"  "<< l <<" "<< r <<endl;
                if (l < r) {
                    //cerr <<"  mapped: "<< l << " " << r << "  to  " << l-x+y<< " " << r-x+y<<endl;
                    newNums.emplace(l-x+y,r-x+y);
                    del.emplace_back(range,ii{l,r});
                }
            }

            for(auto[range,part] : del) {
                nums.erase(range);
                int l1 = range.first,r1 = part.first;
                int l2 = part.second, r2 = range.second;
                if (l1 < r1) nums.emplace(l1,r1);
                if (l2 < r2) nums.emplace(l2,r2);
            }

        }
        for(auto e : nums) newNums.emplace(e);
        nums = newNums;

        /*cerr << "new Nums: ";
        for(auto num : nums) cerr << num.first << " "<< num.second << "      ";
        cerr << endl;*/
    }
    cout << (nums.begin())->first<<endl;

    return 0;
}
