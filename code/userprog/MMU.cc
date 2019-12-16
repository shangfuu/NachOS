#include "copyright.h"
#include "debug.h"
#include "MMU.h"
#include "main.h"

MMU::MMU(PagingType t)
{
    type = t;
    victim = 0;
    loading_time = 0;
    DEBUG(dbgHw3, "MMU(" << type << ")");
}

MMU::~MMU()
{

}

void
MMU::pageFault(unsigned int vpn){
    DEBUG(dbgHw3, "MMU::pageFault vpn: " << vpn);
    DEBUG(dbgHw3, "MMU::PageTable: " << &kernel->machine->pageTable[vpn]);

    switch(type){
        case (FIFO):
            break;
        case (LRU):
            break;
    }
}

void
MMU::Algo_FIFO(unsigned int vpn){
    
}
