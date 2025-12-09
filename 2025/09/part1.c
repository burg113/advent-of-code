#include <stdio.h>    
#include <stdlib.h>
#include <sys/param.h>
#define ll long long
 
int main() { 
    int x[1024],y[1024], n = 0;

    while(scanf("%d,%d",&x[n],&y[n]) > 0) n++;
    ll ans = 0;
    for (int i=0;i<n;i++) for(int j=0;j<n;j++) {
            ans = MAX(ans,(ll)(abs(x[i]-x[j])+1) * (abs(y[i]-y[j])+1));
        }   
    printf("%lld\n",ans);
    return 0;
}
