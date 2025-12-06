#include <stdio.h>    
#include <string.h>
#define ll long long

int main() { 
    ll ans = 0;
    ll nums[4096];
    int cnt = 0;
    while (scanf("%lld", &nums[cnt]) > 0) cnt++;
    char c[1024];
    int cnt2 = 0;
    while (scanf(" %c",&c[cnt2]) > 0) cnt2++;
    
    for (int i=0;i<cnt2;i++) {
        ll res = c[i] == '*';
        for(int j =0;j<cnt/cnt2;j++) {
            if (c[i] == '*') res *= nums[i + j*cnt2];
            else res += nums[i+j*cnt2];
        }
        ans+=res;
    }
 
    printf("%lld\n",ans);
    return 0;
}
