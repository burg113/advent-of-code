#include <stdio.h>    
#include <string.h>
#define ll long long

int main() { 
    ll ans = 0;
    char str[1024];
    while (scanf("%s", str) > 0){
        ll opt[13];
        memset(opt,0,13 * sizeof(ll));
        char c = str[0];
        for (int i= 0;c != 0; c = str[++i]) {
            if (!c) break;
            int num = c - '0';
            for(int i=12;i>=0;i--) if (opt[i] *10 + num > opt[i+1]) opt[i+1] = opt[i]*10 + num; 
        }
        //printf("opt[12]=%lld\n",opt[12]);
        ans += opt[12]; 
    } 
    printf("%lld\n",ans);
    return 0;
}
