#include <stdio.h>    

#define ll long long

int digits(ll a) {
    int ans = 0;
    while(a) a /= 10, ans++;
    return ans;
}

int main() { 
    ll ans = 0;
    do{
        ll l,h;
        scanf("%lld-%lld", &l, &h);

        ll s = l, e = h;
        for (int i= 0;i < (digits(l)+1)/2; i++) s/=10;
        for (int i= 0;i < digits(h)/2;i++) e/=10; 
        printf("from %lld to %lld\n",s,e);         
        for(ll can = s;can<=e;can++) {
            ll n = can;
            for(int i=0;i<digits(can);i++) n*=10;
            n += can;
            if (n >= l && n <= h) ans+=n;
        } 
    } while(scanf(" %c") > 0);
    printf("%lld\n",ans);
    return 0;
}
