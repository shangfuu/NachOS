#ifndef MMU_H
#define MMU_H

#include "copyright.h"

enum PagingType{
    FIFO,
    LRU,
};

class MMU{
    public:
        MMU(PagingType);
        ~MMU();

        void pageFault(unsigned int vpn);   // Will called by ExceptionHandler()
//        void Algo_FIFO(unsigned int vpn);
//        void Algo_LRU(unsigned int vpn);
        int getVictim();
        PagingType getPagingType(){return type;};
        void swap_out(char* buf, int sec, int virtPage);
        void swap_in(unsigned int vpn, int victim);
        int loading_time;   // used at FIFO, will increased while page fault happend
        int counter;
    private:
        PagingType type;    // Algorithm choosed
//        int victim; // victim page        
};
#endif
