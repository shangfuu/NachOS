#include "syscall.h"
#include <iostream>

int main(){
    int i;
    int size = 100;
//    static int yeee[700];
    int *yee = new int[10];
    int x[size];
    x[0] = 0;

    for(i=1;i<size;++i){
        x[i] = x[i-1] + i;
        PrintInt(x[i]);
    }
    return 0;
}
