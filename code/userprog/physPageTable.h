// physPageTable.h
// Data Structers to keep track of physical page table.
//
//@shungfu: Edit at Hw3

#ifndef PHYSPAGETABLE_H
#define PHYSPAGETABLE_H

#include "copyright.h"

#define NOT_USED false
#define USED true

class PhysPageTable{
    public:
        PhysPageTable();
        ~PhysPageTable();

        bool *used;    // Used to record the physical page table that have been used, default set not used
        int *load_time;  // used to record load time at FIFO
        int *virtPage; // back points to virtual Page#
        int numFreePhyPages;    // Number of physical pages can be used
        void CleanUp(int page); // Clean up when a userprog is returned
};
#endif
