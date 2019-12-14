// addrspace.h 
//	Data structures to keep track of executing user programs 
//	(address spaces).
//
//	For now, we don't keep any information about address spaces.
//	The user level CPU state is saved and restored in the thread
//	executing the user program (see thread.h).
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef ADDRSPACE_H
#define ADDRSPACE_H

#include "copyright.h"
#include "filesys.h"
#include <string.h>

#define UserStackSize		1024 	// increase this as necessary!

// @shungfu: Edit at HW2
#define NOT_USED false
#define USED true

class AddrSpace {
  public:
    AddrSpace();			// Create an address space.
    ~AddrSpace();			// De-allocate an address space

    void Execute(char *fileName);	// Run the the program
					// stored in the file "executable"

    void SaveState();			// Save/restore address space-specific
    void RestoreState();		// info on a context switch 

  private:
// @shungfu : Edit at Hw2
    static bool physPageTable[NumPhysPages];    // Used to record the physical page that have been used, default not used.
    static int numFreePhyPages;     // Number of physical pages can be used

    TranslationEntry *pageTable;	// Assume linear page table translation
					// for now!
    unsigned int numPages;		// Number of pages in the virtual 
					// address space

    bool Load(char *fileName);		// Load the program into memory
					// return false if not found

    void InitRegisters();		// Initialize user-level CPU registers,
					// before jumping to user code
//@shungfu: Edit at HW3
    bool PT_Load; //Used to check if load file success
};

#endif // ADDRSPACE_H
