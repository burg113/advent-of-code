#include <stdio.h>    
#include <string.h>
#define ll long long

int main() { 
    int ans = 0;
    char lines[1024][1024];
    int h = 0;
    while(fgets(lines[h],sizeof(lines[h]),stdin)) h++;
    char pos[1024],newpos[1024];
    memset(newpos,0,sizeof(newpos));
    for (int y=0;y<h;y++) {
        for(int x=0;;x++) {
            if (!lines[y][x]) break;
            if (lines[y][x] == 'S') newpos[x] = 1;
            if (pos[x]){
                if(lines[y][x] == '^') newpos[x+1] = newpos[x-1] = 1, ans++;
                else newpos[x] = 1;
            }
        }
        memcpy(pos,newpos,sizeof(pos));
        memset(newpos,0,sizeof(newpos));
    }

    printf("%d\n",ans);
    return 0;
}
