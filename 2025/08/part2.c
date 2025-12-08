#include <stdio.h>    
#include <string.h>
#define ll long long

#define GOAL 1000
int x[1024],y[1024],z[1024];
int n = 0;
char vis[1024];

int dfs(int u, ll maxlen) {
    vis[u] = 1;
    int cnt = 1;
    for(int v = 0;v<n;v++) {
        ll dist = (ll)(x[u]-x[v])*(x[u]-x[v]) + (ll)(y[u]-y[v])*(y[u]-y[v]) + (ll)(z[u]-z[v])*(z[u]-z[v]);
        if (dist <= maxlen && !vis[v]) cnt += dfs(v,maxlen);
    }
    return cnt;
}


 
int main() { 
    while(scanf("%d,%d,%d",&x[n],&y[n],&z[n]) > 0) n++;
    ll low = 0, high = ((ll)1) << 60;
    while(low+1 < high) {
        ll piv = (low+high)/2;
        int cnt = 0;
        memset(vis,0,sizeof(vis));
        if (dfs(0,piv) < n) low = piv;
        else high = piv;
    }
    
    for(int i=0;i<n;i++) {
        for(int j=i+1;j<n;j++) {
            ll dist = (ll)(x[i]-x[j])*(x[i]-x[j]) + (ll)(y[i]-y[j])*(y[i]-y[j]) + (ll)(z[i]-z[j])*(z[i]-z[j]);
            if (dist == high) {
                printf("%lld\n",(ll)x[i]*x[j]);
                return 0;
            }
        }
    }
    return 0;
}
