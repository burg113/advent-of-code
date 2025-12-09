#include <stdio.h>    
#include <stdlib.h>
#include <sys/param.h>
#include <string.h>

#define ll long long
#define INF 1000000000

int cmp(const void* a,const void* b) {
  	return *(int*)a - *(int*)b;
}

int compress(int *v,int n) {
    qsort(v,n,sizeof(int),cmp);
    int p =1;
    for(int i = 1;i<n;i++) {
        if (v[i-1] != v[i]) v[p++] = v[i];
    }
    return p;
}
int ind(int*v, int e) {
    for(int i=0;;i++) if(v[i] == e) return i;
}

int main() { 
    int x[1024],y[1024], n = 0;
    int cx[1024],cy[1024];
    char field[1024][1024];
    memset(field,0,sizeof(field));
    while(scanf("%d,%d",&x[n],&y[n]) > 0) n++;
    int xcpy[2024],ycpy[2024];
    memcpy(xcpy,x,sizeof(x));
    memcpy(ycpy,y,sizeof(y)); 
    compress(xcpy,n);
    compress(ycpy,n);
    
    for(int i=0;i<n;i++) {
        int j = (i+1)%n;
        int x1 = 2*ind(xcpy,x[i]), x2 = 2*ind(xcpy,x[j]);
        int y1 = 2*ind(ycpy,y[i]), y2 = 2*ind(ycpy,y[j]);
        for(int x = MIN(x1,x2);x<=MAX(x1,x2);x++) for(int y = MIN(y1,y2);y <= MAX(y1,y2);y++) {
            field[x][y] = 1;
        }
    }
    ll ans = 0;
    for(int i=0;i<n;i++) for (int j=i+1;j<n;j++){
        int x1 = 2*ind(xcpy,x[i]), x2 = 2*ind(xcpy,x[j]);
        int y1 = 2*ind(ycpy,y[i]), y2 = 2*ind(ycpy,y[j]);
        char valid = 1;
        for(int x = MIN(x1,x2)+1;x<MAX(x1,x2);x++) for(int y = MIN(y1,y2)+1;y < MAX(y1,y2);y++) {
            if(field[x][y]) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            ans = MAX(ans,(ll)(abs(x[i]-x[j])+1) * (abs(y[i]-y[j])+1));
        }
    }
    printf("%lld\n",ans);
    return 0;
}
