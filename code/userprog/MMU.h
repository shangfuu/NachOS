// MMU.h
// Memory Management Unit
// Used to handle the translation between virtual and physical page table.
//
//#shungfu: Edit at Hw3

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
        int getVictim();    // get the victim page (now is just for FIFO and LRU)
        PagingType getPagingType(){return type;};
        void swap_out(char* buf, int sec, int virtPage);
        void swap_in(unsigned int vpn, int victim);
        int loading_time;   // used at FIFO, will increased while page fault happend and initial memory
        int counter;    // used at LRU, will increased while access the physical memory frame
    private:
        PagingType type;    // Algorithm choosed 
};
#endif
