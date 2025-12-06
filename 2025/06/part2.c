#include <stdio.h>    
#include <ctype.h>
#define ll long long

int main() { 
    ll ans = 0;
    char lines[16][4098];
    int l = 0;
    while(fgets(lines[l],sizeof(lines[l]),stdin)) {
        l++;
    }
    l--;
    char op;
    ll cur;
    for(int x = 0;;x++) {
        if (lines[l][x] != ' ') op = lines[l][x], ans += cur, cur = op=='*'; 
        if (!op) break;
        ll num = 0, emptyLine = 1;
        for(int y = 0;y < l;y++) {
            if (isdigit(lines[y][x])) num = 10*num + lines[y][x]-'0',emptyLine = 0; 
        }
        if (emptyLine) continue;
        if (op == '*') cur *= num;
        else cur += num;
    }    
    printf("%lld\n",ans);
    return 0;
}
