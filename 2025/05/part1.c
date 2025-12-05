#include <stdio.h>    
#include <string.h>
#define ll long long

int main() { 
    ll ans = 0;
    ll start[1024];
    ll end[1024];
    int cnt = 0;
    while (scanf("%lld-%lld", &start[cnt],&end[cnt]) > 0) {
        if (end[cnt] == -1) break;
        cnt++;
        end[cnt] = -1;    
    }
    ll num = start[cnt];
    do{
        for(int i=0;i<cnt;i++) if (start[i] <= num && end[i] >= num) {
                ans++;
                break;
            }
    }while (scanf("%lld",&num) > 0);
     
 
    printf("%lld\n",ans);
    return 0;
}
