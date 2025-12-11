#include <stdio.h>    
#include <string.h>
#include <assert.h>
#include <sys/param.h>
#define ll long long

int readList(int *out) {
    int pos = 0;
    while(scanf("%d,",&out[pos])) printf("%d\t",out[pos]),pos++;
    printf("\n");
    return pos;
}


int main() { 
    char c;
    int x[1024],y[1024], n = 0;
    int ans = 0;
    while(scanf("%c",&c) != EOF) {
        if (c != '[') {
            printf("c:%c %d\n",c,c);
            continue;
        }
        printf("start line\n");
        char s[16];
        scanf("%15s",s);
        printf("s:%s\n",s);
        for(int i=0;i<16;i++) if (s[i] == ']') s[i] = 0;
        int buttons[16][16], cnt = 0;
        int voltages[16];
        while (1) {
            scanf("%c",&c);
            if (c == '{') break;
            if (c != '(') continue;
            buttons[cnt][0] = readList(buttons[cnt]+1);
            cnt++;
            scanf(")");
        }
        readList(voltages);
        scanf("%c",&c);
        
        int opt = 16;
        for(int m=0;m<(1<<cnt);m++) {
            int pcnt = 0;
            int res[16];
            memset(res,0,64);
            for(int j =0;j<cnt;j++) {
                if (m & (1<<j)) {
                    pcnt++;
                    for(int i=1;i<=buttons[j][0];i++) res[buttons[j][i]] ^= 1;
                }
            }
            printf("s:%s\n",s);
            printf("mask:%d, pcnt:%d\n",m,pcnt);
            for(int i=0;s[i];i++) printf("%d ",res[i]);
            printf("\n");
            
            for(int i=0;s[i];i++) {
                if ((s[i] == '#') ^ res[i]) pcnt+=16;
            }
            opt = MIN(opt,pcnt);
        }
        ans += opt;
    }
    printf("%d\n",ans);
    return 0;
}
