#include "syscall.h"
int main(){
    int i;
    int size = 100;
//    int yee[8] = {1,2,3,4,5,6,7,8};
    static int yeee[700];
 /*
    static const unsigned char key[480] = 
    {0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
 
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
 
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x00,0x01,0x02,0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 
          0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
 
 };*/
    int x[size];
    x[0] = 0;

   for(i=1;i<size;++i){
        x[i] = x[i-1] + i;
        PrintInt(x[i]);
    }
    return 0;
}
