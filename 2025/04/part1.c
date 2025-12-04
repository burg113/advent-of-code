#include <stdio.h>    
#include <string.h>
#define ll long long

int main() { 
    ll ans = 0;
    char str[1023];
    char field[1024][1024];
    memset(field,'.',1024 * 1024);
    int w,h=1;
    while (scanf("%s", str) > 0) {
        memcpy(field[h++]+1,str,1023);
        int width = 0;
        while(str[width]) width++;
        if (h > 2 && w != width+1) return 1;
        w = width+1;
    }
    for(int i=1;i<h;i++) for(int j=1;j<w;j++){
            if(field[i][j] == '.') continue;
            int cnt = 0;
            for(int di=-1;di<=1;di++) for(int dj=-1;dj<=1;dj++) {
                   if (di || dj) cnt += field[i+di][j+dj] == '@';
           }
            ans += cnt < 4;
        }
    printf("%lld\n",ans);
    return 0;
}
