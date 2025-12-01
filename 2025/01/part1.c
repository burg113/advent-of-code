#include <stdio.h>    
int main() { 
    // Displays the string inside quotations
    char c;
    int amnt;
    int cur = 50, ans = 0;
   while (scanf(" %c%d", &c, &amnt)>0) {
       if (c == 'L') amnt *= -1;
        cur = (100 + cur + amnt) % 100;
        if (!cur) ans++;
    }
    printf("%d\n",ans);
    return 0;
}
