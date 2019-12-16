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
        void Algo_FIFO(unsigned int vpn);
        void Algo_LRU(unsigned int vpn);

        int loading_time;   // used at FIFO, will increased while page fault happend
    private:
        PagingType type;    // Algorithm choosed
        int victim; // victim page        
};
#endif
