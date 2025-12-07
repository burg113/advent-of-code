#include <stdio.h>    
#include <string.h>
#define ll long long

int main() { 
    ll ans = 0;
    char lines[1024][1024];
    int h = 0;
    while(fgets(lines[h],sizeof(lines[h]),stdin)) h++;
    ll pos[1024],newpos[1024];
    memset(newpos,0,sizeof(newpos));
    for (int y=0;y<h;y++) {
        for(int x=0;;x++) {
            if (!lines[y][x]) break;
            if (lines[y][x] == 'S') newpos[x] = 1;
            if (pos[x]){
                if(lines[y][x] == '^') newpos[x+1] += pos[x], newpos[x-1] += pos[x];
                else newpos[x] += pos[x];
            }
        }
        memcpy(pos,newpos,sizeof(pos));
        memset(newpos,0,sizeof(newpos));
    }
    for(int i=0;i<1024;i++) ans+=pos[i];
    printf("%lld\n",ans);
    return 0;
}
