#include "syscall.h"

# define SIZE 700

int x[SIZE] = {0};

int main(){
    int i;
    static int yeee[100];
    int daa[SIZE];
    
    x[0] = 0;
    for(i=1;i<SIZE;++i){
        x[i] = x[i-1] + i;
        PrintInt(x[i]);
    }
    return 0;
}
