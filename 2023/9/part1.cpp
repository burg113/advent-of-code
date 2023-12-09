#include <bits/stdc++.h>

using namespace std;


int32_t main() {
    string s;
    int sum = 0;
    while (getline(cin, s)) {
        cerr << s << endl;
        stringstream stream(s);
        vector<int> nums;
        int num;
        while (stream >> num) nums.push_back(num);

        vector<int> last;

        bool dif0 = false;
        while (!dif0) {
            last.emplace_back(nums.back());
            vector<int> curr;
            dif0 = true;
            for (int i = 1; i < nums.size(); i++) {
                if (nums[i] - nums[i - 1] != 0) dif0 = false;
                curr.emplace_back(nums[i] - nums[i - 1]);
            }
            nums = curr;
        }
        int res = 0;
        for (int e : last) res += e;
        cerr << res << endl;
        sum += res;
    }
    cout << sum << endl;


    return 0;
}
