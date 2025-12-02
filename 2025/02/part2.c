#include <stdio.h>    

#define ll long long

int digits(ll a) {
    int ans = 0;
    while(a) a /= 10, ans++;
    return ans;
}
int repeats(ll n) {
    ll pot = 10;
    for(int l =1;l<digits(n);l++,pot*=10) {
        if (digits(n)%l) continue;
        ll p = n%pot;
        ll rec = 0;
        for(int i=0;i<digits(n)/l;i++) rec = rec*pot + p;
        //printf("p %lld, rec %lld, n %lld\n",p,rec,n);
        if (rec == n) return 1;
    }
    return 0;
}

int main() { 
    // Displays the string inside quotations
    ll ans = 0;
    do{
        ll l,h;
        scanf("%lld-%lld", &l, &h);
        for (int num = 2;num<=digits(h);num++) {
            for (int can = 1;;can++) {
                if (digits(can) * num > 12) break;
                if (repeats(can)) continue;
                ll n = 0;
                for (int j=0;j<num;j++) {
                    for(int _=0;_<digits(can);_++,n*=10);
                    n+= can;
                }
                if (n > h) break;
                if (n >= l) {
                    printf("%lld,", n);
                    ans += n;
                }            
            }
        }
        printf("\n");
   } while(scanf(" %c") > 0);
    printf("ans: %lld\n",ans);
    return 0;
}
