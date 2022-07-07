#include <stdio.h>
#include <unistd.h>

int main(){
    int num;
    printf("Give me a num: ");
    scanf("%d", &num);
    for(int i = 0 ; i < num ; i++){
        int ans = i * 2;
        printf("%d\n", ans);
    }
    printf("Goodbye\n");
}

