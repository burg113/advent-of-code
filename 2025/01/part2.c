#include <stdio.h>    
int main() { 
    // Displays the string inside quotations
    char c;
    int amnt;
    int cur = 50, ans = 0;
   while (scanf(" %c%d", &c, &amnt)>0) {
        for(int i = 0; i < amnt; i++){
            int a = 1 - 2*(c=='L');
            cur = (100 + cur + a) % 100;
            if (!cur) ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
