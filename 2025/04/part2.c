#include <stdio.h>    
#include <string.h>
#define ll long long

char field[1024][1024];
short deg[1024][1024];

int dfs(int i, int j) {
    int res = 1;
    deg[i][j] = -1;
    for(int di=-1;di<=1;di++) for(int dj=-1;dj<=1;dj++) {
        if ((di || dj) && field[i+di][j+dj] == '@') if(--deg[i+di][j+dj] == 3) res+=dfs(i+di,j+dj);
    }
    return res;
}

int main() { 
    ll ans = 0;
    char str[1023];
    memset(field,'.',1024 * 1024);
    memset(deg,0,1024 * 1024 * sizeof(short));
    
    int w,h=1;
    while (scanf("%s", str) > 0) {
        memcpy(field[h++]+1,str,1023);
        int width = 0;
        while(str[width]) width++;
        if (h > 2 && w != width+1) return 1;
        w = width+1;
    }
    
    for(int i=1;i<h;i++) for(int j=1;j<w;j++){
            if(field[i][j] == '.') {
                deg[i][j] = -1;
                continue;
            }
            int cnt = 0;
            for(int di=-1;di<=1;di++) for(int dj=-1;dj<=1;dj++) {
                   if (di || dj) deg[i][j] += field[i+di][j+dj] == '@';
           }
        }
    for(int i=0;i<h;i++) for(int j=0;j<w;j++) if(field[i][j] == '@' && deg[i][j] >= 0 && deg[i][j] < 4) ans += dfs(i,j); 
    printf("%lld\n",ans);
    return 0;
}
