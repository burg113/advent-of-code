#include <stdio.h>   
#include <sys/param.h> 
#include <string.h>
#define ll long long
char visited[1024];
ll start[1024];
ll end[1024];
int cnt = 0;


ll mi, ma;
void dfs(int u) {
    mi = MIN(mi,start[u]), ma = MAX(ma,end[u]);
    for (int v=0;v<cnt;v++) {
        if (!visited[v] && MAX(start[u],start[v]) <= MIN(end[u],end[v])) {
            visited[v] = 1;
            dfs(v);
        }
    }
}

int main() { 
    ll ans = 0;
    while (scanf("%lld-%lld", &start[cnt],&end[cnt]) > 0) {
        if (end[cnt] == -1) break;
        cnt++;
        end[cnt] = -1;
    }
    memset(visited,0,1024);
    for (int i=0;i<cnt;i++) {
        if (visited[i]) continue;
        ma = mi = start[i];
        dfs(i);
        ans += ma - mi + 1;    
    }    
 
    printf("%lld\n",ans);
    return 0;
}
