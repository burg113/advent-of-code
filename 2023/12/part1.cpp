#include <bits/stdc++.h>

using namespace std;


bool match(string& s, vector<int>& pattern) {
    int count = 0;
    vector<int> p;
    for(char c : s) {
        if (c == '#') count ++;
        else if (count > 0) {
            p.emplace_back(count);
            count = 0;
        }
    }
    if (count > 0) {
        p.emplace_back(count);
    }

    if (p.size() != pattern.size()) return false;
    for(int i=0;i<p.size();i++) {
        if (p[i] != pattern[i]) return false;
    }
    return true;
}

vector<string> gen(string& templateString) {
    vector<string> curr({""});
    vector<string> next;
    for(char c : templateString) {
        if (c == '?') {
            for (const string& s : curr) {
                next.emplace_back(s + '.');
                next.emplace_back(s + '#');
            }
            curr = next;
            next = vector<string>();
        }else {
            for (string& s : curr) {
                s.push_back(c);
            }
        }
    }
    return curr;
}


int32_t main() {
    string s;
    int count  = 0;
    while (getline(cin, s)) {
        string str;
        int co = 0;
        for(char c : s) {
            if (c == '?') co++;
            if (c == ' ') break;
            else str.push_back(c);
        }
        char _;
        stringstream  stream(s);
        for(int i=0;i<str.size();i++) stream >> _;

        char c;
        vector<int> nums;
        int num;
        do {
            stream >> num;
            nums.emplace_back(num);
        }while (stream >> c);

        cerr <<str <<"  "<< co << endl;
        for (string& currStr : gen(str)) {
            //cerr <<currStr <<"  "<< count << endl;

            if (match(currStr,nums)) {
                count++;
                //cerr <<currStr <<"  "<< count <<endl;
            }
        }
    }
    cout << count << endl;

    return 0;
}
