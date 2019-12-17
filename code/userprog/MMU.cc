#include "copyright.h"
#include "debug.h"
#include "MMU.h"
#include "main.h"

MMU::MMU(PagingType t)
{
    type = t;
//    victim = -1;  // out of save zone
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

    int victim = 0;

    if(kernel->physPageTable->numFreePhyPages > 0){ // Still got free Physical page
        
        while(victim < NumPhysPages && kernel->physPageTable->used[victim] == USED){
            victim++;
        }
        cout << "Found physical page " << victim << " free to use." << endl; 
        cout << "Swap in " << kernel->currentThread->getName() <<  "'s virtual page: " << vpn << endl;
        swap_in(vpn, victim);
    }
    else{
        if(type == FIFO){
            // get the smallest load time page as victim
            victim = getVictim();
          
            // copy victim's physical memory data into buf
            char *buf = new char [PageSize]; 
            bcopy(&kernel->machine->mainMemory[victim*PageSize], buf, PageSize); 
            
            // Get disk sec where victim to go
            int sec = kernel->machine->pageTable[vpn].physicalPage;

            // Get victim's virtaul page
            int virtPage = kernel->physPageTable->virtPage[victim];
            
            cout << "Swap out physical page: " << victim << endl;
            cout << "Swap in " << kernel->currentThread->getName() << "'s virtual page: " << vpn << endl;

            // swap in
            swap_in(vpn, victim);

            // swap out
            swap_out(buf, sec, virtPage);

        }
        else if(type == LRU){

        }
    }
}

int
MMU::getVictim(){
    int smallest = kernel->physPageTable->load_time[0];
    int victim = 0;
    for(int i=1;i <NumPhysPages;i++){
        if(smallest > kernel->physPageTable->load_time[i]){
            smallest = kernel->physPageTable->load_time[i];
            victim = i;
        }
    }
    return victim;
}

void
MMU::swap_in(unsigned int vpn, int victim){
    // Read disk data into buf
    char *buf = new char[PageSize];
    int sec = kernel->machine->pageTable[vpn].physicalPage;
    kernel->vmDisk->ReadSector(sec, buf);
 
    // save buf into physical memory
    bcopy(buf, &kernel->machine->mainMemory[victim*PageSize], PageSize);
    // Set disk sector as NOT USED
    kernel->vmDisk->SectorUsed[sec] = NOT_USED;

    // Update the pageTable information
    kernel->machine->pageTable[vpn].physicalPage = victim;
    kernel->machine->pageTable[vpn].valid = TRUE;
        
    // Update Physical Page table information
    kernel->physPageTable->numFreePhyPages--;
    kernel->physPageTable->used[victim] = USED;
    kernel->physPageTable->virtPage[victim] = vpn;
    kernel->physPageTable->load_time[victim] = kernel->memManageUnit->loading_time;
    kernel->memManageUnit->loading_time++;
}

void
MMU::swap_out(char* buf, int sec, int virtPage){
    // Write into disk
    kernel->vmDisk->WriteSector(sec,buf);
    
    // Set disk sector as USED
    kernel->vmDisk->SectorUsed[sec] = USED;

    // Update the pageTable information
    kernel->machine->pageTable[virtPage].physicalPage = sec;
    kernel->machine->pageTable[virtPage].valid = FALSE;
    kernel->machine->pageTable[virtPage].dirty = FALSE;

    kernel->physPageTable->numFreePhyPages++;
}
