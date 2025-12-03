#include <stdio.h>    

#define ll long long

int main() { 
    ll ans = 0;
    char str[1024];
    while (scanf("%s", str) > 0){
        int opt = 0; 
        int largest = -1,second = -1;
        char c = str[0];
        for (int i= 0;c != 0; c = str[++i]) {
            if (!c) break;
            int nu = c - '0';
            if (nu > second) {
                second = nu;
                if (10*largest+second > opt) opt = 10*largest+second; 
            }
            if(nu > largest) largest = nu, second = -1; 
        }
        ans += opt; 
    }   
    printf("%lld\n",ans);
    return 0;
}
