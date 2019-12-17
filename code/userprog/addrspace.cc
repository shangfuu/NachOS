// addrspace.cc 
//	Routines to manage address spaces (executing user programs).
//
//	In order to run a user program, you must:
//
//	1. link with the -n -T 0 option 
//	2. run coff2noff to convert the object file to Nachos format
//		(Nachos object code format is essentially just a simpler
//		version of the UNIX executable object code format)
//	3. load the NOFF file into the Nachos file system
//		(if you haven't implemented the file system yet, you
//		don't need to do this last step)
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "addrspace.h"
#include "machine.h"
#include "noff.h"

// @shungfu : Edit at HW2
// Can't initial at .h
//int AddrSpace::numFreePhyPages = NumPhysPages;
//bool AddrSpace::physPageTable[NumPhysPages] = {NOT_USED};

//----------------------------------------------------------------------
// SwapHeader
// 	Do little endian to big endian conversion on the bytes in the 
//	object file header, in case the file was generated on a little
//	endian machine, and we're now running on a big endian machine.
//----------------------------------------------------------------------

static void 
SwapHeader (NoffHeader *noffH)
{
    noffH->noffMagic = WordToHost(noffH->noffMagic);
    noffH->code.size = WordToHost(noffH->code.size);
    noffH->code.virtualAddr = WordToHost(noffH->code.virtualAddr);
    noffH->code.inFileAddr = WordToHost(noffH->code.inFileAddr);
    noffH->initData.size = WordToHost(noffH->initData.size);
    noffH->initData.virtualAddr = WordToHost(noffH->initData.virtualAddr);
    noffH->initData.inFileAddr = WordToHost(noffH->initData.inFileAddr);
    noffH->uninitData.size = WordToHost(noffH->uninitData.size);
    noffH->uninitData.virtualAddr = WordToHost(noffH->uninitData.virtualAddr);
    noffH->uninitData.inFileAddr = WordToHost(noffH->uninitData.inFileAddr);
}

//----------------------------------------------------------------------
// AddrSpace::AddrSpace
// 	Create an address space to run a user program.
//	Set up the translation from program memory to physical 
//	memory.  For now, this is really simple (1:1), since we are
//	only uniprogramming, and we have a single unsegmented page table
//----------------------------------------------------------------------

AddrSpace::AddrSpace()
{
//  @shungfu : Edit at Hw2
//-----------------------------------------------------
//  When Multiprocess we should just new the size we need.
//  The Origianl Code just dealing with the situation
//  when there is only one process is carry out.
//  When doing Mulitprocess, there's a static physical page table.
//  And all the virtual page table in defferent AddrSpace
//  will go and connect physical page table if there is 
//  empty pages enough to fill in all numPages in virtual.
//  So the deploy things we got to do, i put it in ::Load() func.
//-----------------------------------------------------

//  pageTable = new TranslationEntry[NumPhysPages];
//  PhysicalPage conflict so deploy at ::Load() function 
/*  for (unsigned int i = 0; i < NumPhysPages; i++) {
    	pageTable[i].virtualPage = i;	// for now, virt page # = phys page #
    	pageTable[i].physicalPage = i;
    //	PageTable[i].physicalPage = 0;
    	pageTable[i].valid = TRUE;
    //	pageTable[i].valid = FALSE;
    	pageTable[i].use = FALSE;
    	pageTable[i].dirty = FALSE;
    	pageTable[i].readOnly = FALSE;  
    }
 */
   
    // zero out the entire address space
//    bzero(kernel->machine->mainMemory, MemorySize);
}

//----------------------------------------------------------------------
// AddrSpace::~AddrSpace
// 	Dealloate an address space.
//----------------------------------------------------------------------

AddrSpace::~AddrSpace()
{
// @shungfu : Edit at Hw2
    DEBUG(dbgHw3, "\nPhysical page cleaning up =======>");
    // Free physPageTable we have used, just turn the state to NOT_USED.
    for(int i = 0; i < numPages; i++){
        int physPage = pageTable[i].physicalPage;
        if(pageTable[i].valid == TRUE){    // Clean up physical page
            kernel->physPageTable->CleanUp(physPage);
            cout << "Physical page " << physPage << " cleaning up." << endl;
        }
        else{   // clean up Vm Disk
            kernel->vmDisk->SectorUsed[physPage] = NOT_USED;
        }
    }
    delete pageTable;
}


//----------------------------------------------------------------------
// AddrSpace::Load
// 	Load a user program into memory from a file.
//
//	Assumes that the page table has been initialized, and that
//	the object code file is in NOFF format.
//
//	"fileName" is the file containing the object code to load into memory
//  @shungfu : Edit at HW2  -> To Solve the Multiprogram memory conflict.
//----------------------------------------------------------------------

bool 
AddrSpace::Load(char *fileName) 
{
    OpenFile *executable = kernel->fileSystem->Open(fileName);
    NoffHeader noffH;
    unsigned int size;

    if (executable == NULL) {
	cerr << "Unable to open file " << fileName << "\n";
	return FALSE;
    }
    
    executable->ReadAt((char *)&noffH, sizeof(noffH), 0);
    if ((noffH.noffMagic != NOFFMAGIC) && 
        (WordToHost(noffH.noffMagic) == NOFFMAGIC)) {
    	SwapHeader(&noffH);
    }

    ASSERT(noffH.noffMagic == NOFFMAGIC);

// how big is address space?
    size = noffH.code.size + noffH.initData.size + noffH.uninitData.size 
			+ UserStackSize;	// we need to increase the size
						// to leave room for the stack
    numPages = divRoundUp(size, PageSize); // Number of pages used in this addr
//	cout << "number of pages of " << fileName<< " is "<<numPages<<endl;
    size = numPages * PageSize;

// @shungfu : Edit at HW2/HW3
    DEBUG(dbgHw3,"\n-----------------------");
    cout <<  "Used " << numPages << " Pages\n";
    DEBUG(dbgHw3, "code size:" << noffH.code.size << "\ninitData size: " << noffH.initData.size << 
                    "\nUninitData size: " << noffH.uninitData.size);
    DEBUG(dbgHw3, "size of AddrSpace: " << size);
    DEBUG(dbgHw3,"-----------------------" << endl);
//    ASSERT(numPages <= NumPhysPages);  // check we're not trying
						              // to run anything bigger
                                      // than number of  physical pages
                                      // in physicalPageTable 
    
    DEBUG(dbgAddr, "Initializing address space: " << numPages << ", " << size);


    DEBUG(dbgHw3, "------- Initializing address space -------");
//@shungfu : Edit at Hw3        
    pageTable = new TranslationEntry[numPages];     // PageTable initial
    
    // Deploy the virtual and physical page tables.
    for(unsigned int i = 0; i < numPages; i++){

        // Same operation of Enough/Not Enough phyical memory page
        pageTable[i].virtualPage = i;
        pageTable[i].use = FALSE;
        pageTable[i].dirty = FALSE;
        pageTable[i].readOnly = FALSE;           

        if(kernel->physPageTable->numFreePhyPages < 1){    // Not enough Physical page
            int sec = 0;
            while(kernel->vmDisk->SectorUsed[sec] == USED){  // SynchDisk sector have been Used
                sec++;
            }

            ASSERT(sec < NumSectors);   // check if setor number is in safe zone
            kernel->vmDisk->SectorUsed[sec] = USED;  // set sector to USED

            pageTable[i].physicalPage = sec;    // points to the disk sector            
            pageTable[i].valid = FALSE;

            // Copy from Real disk to SynchDisk(Nachos), unit: page, ReadAt(char* into, int numBytes, int position)                                          
            char *buffer = new char [PageSize];
            DEBUG(dbgHw3, "No Free Physiacal Memory Page, get free disk sector: " << sec);
            executable->ReadAt( buffer, PageSize, noffH.code.inFileAddr + (i*PageSize) );
            kernel->vmDisk->WriteSector(sec, buffer);
        }        
        else {  // Remaining Pages        
            int ppn = 0;    // physical page number#
            
            // Deploy on only available index                        
            while(ppn < NumPhysPages && kernel->physPageTable->used[ppn] == USED){            
                ppn++;                
            }                        
            

            pageTable[i].physicalPage = ppn;                           
            pageTable[i].valid = TRUE;            
            kernel->physPageTable->numFreePhyPages--;            
            kernel->physPageTable->used[ppn] = USED;
            kernel->physPageTable->virtPage[ppn] = i;
            if(kernel->memManageUnit->getPagingType() == FIFO){     // FIFO used
                kernel->physPageTable->load_time[ppn] = kernel->memManageUnit->loading_time;
                kernel->memManageUnit->loading_time++; 
                DEBUG(dbgHw3, "Free Physical Memory page #" << ppn << ", loading time: " << kernel->memManageUnit->loading_time-1);
            }
            else{   // LRU used
                kernel->physPageTable->load_time[ppn] = kernel->memManageUnit->counter;
                kernel->memManageUnit->counter++;
                DEBUG(dbgHw3, "Free Physical Memory page #" << ppn << ", counter: " << kernel->memManageUnit->counter-1);
            }

            // Copy from Real disk to Physical Memory(Nachos), unit: page            
            executable->ReadAt( &(kernel->machine->mainMemory[ppn * PageSize]), PageSize, noffH.code.inFileAddr + (i*PageSize) );            
        }        
        DEBUG(dbgHw3, "Put " << kernel->currentThread->getName() << "'s vpn " << i << " in.");
    }

    DEBUG(dbgHw3, "--------------------------------------------\n");
//    DEBUG(dbgHw3,"\n-----------------------");
//    DEBUG(dbgHw3, "code.infileAddr: " << noffH.code.inFileAddr << ", code.virtualAddr: " << noffH.code.virtualAddr);

/*

Real Address:
mainMemory[pageTable[noffH.code.virtualAddr/PageSize].physicalPage * PageSize + (noffH.code.virtualAddr%PageSize)]

which page(p.physical) = #(virtualAddr/PageSize).physical
page base: which page * PageSize.
page offset:  code.address mod PageSize。
Real Address(physical): page base + page offset
*/


// then, copy in the code and data segments from disk into memory(physical)
	if (noffH.code.size > 0) {
        DEBUG(dbgAddr, "Initializing code segment.");
	    DEBUG(dbgAddr, noffH.code.virtualAddr << ", " << noffH.code.size);
                
//        executable->ReadAt(
//		&(kernel->machine->mainMemory[pageTable[noffH.code.virtualAddr/PageSize].physicalPage * PageSize + (noffH.code.virtualAddr % PageSize)]), 
//		  noffH.code.size, noffH.code.inFileAddr
//        );

//        DEBUG(dbgHw3,"Code Segment PhysicalPage: "<< pageTable[noffH.code.virtualAddr/PageSize].physicalPage << ", offset: " <<(noffH.code.virtualAddr % PageSize));
    }

	if (noffH.initData.size > 0) {
        DEBUG(dbgAddr, "Initializing data segment.");
	    DEBUG(dbgAddr, noffH.initData.virtualAddr << ", " << noffH.initData.size);
        
// @shungfu : Edit at Hw2
//        executable->ReadAt(
//		&(kernel->machine->mainMemory[pageTable[noffH.initData.virtualAddr/PageSize].physicalPage * PageSize + (noffH.initData.virtualAddr % PageSize)]),
//		  noffH.initData.size, noffH.initData.inFileAddr
//        );

//        DEBUG(dbgHw3,"InitData Segment PhysicalPage: "<< pageTable[noffH.initData.virtualAddr/PageSize].physicalPage << ", offset: " <<(noffH.initData.virtualAddr % PageSize));
    }
//    DEBUG(dbgHw3,"-----------------------" << endl);
    delete executable;			// close file
    return TRUE;			// success
}

//----------------------------------------------------------------------
// AddrSpace::Execute
// 	Run a user program.  Load the executable into memory, then
//	(for now) use our own thread to run it.
//
//	"fileName" is the file containing the object code to load into memory
//----------------------------------------------------------------------

void 
AddrSpace::Execute(char *fileName) 
{
    PT_Load = FALSE;
    if (!Load(fileName)) {
	cout << "inside !Load(FileName)" << endl;
	return;				// executable not found
    }

    //kernel->currentThread->space = this;
    this->InitRegisters();		// set the initial register values
    this->RestoreState();		// load page table register
    
    PT_Load = TRUE;
    kernel->machine->Run();		// jump to the user progam

    ASSERTNOTREACHED();			// machine->Run never returns;
					// the address space exits
					// by doing the syscall "exit"
}


//----------------------------------------------------------------------
// AddrSpace::InitRegisters
// 	Set the initial values for the user-level register set.
//
// 	We write these directly into the "machine" registers, so
//	that we can immediately jump to user code.  Note that these
//	will be saved/restored into the currentThread->userRegisters
//	when this thread is context switched out.
//----------------------------------------------------------------------

void
AddrSpace::InitRegisters()
{
    Machine *machine = kernel->machine;
    int i;

    for (i = 0; i < NumTotalRegs; i++)
	machine->WriteRegister(i, 0);

    // Initial program counter -- must be location of "Start"
    machine->WriteRegister(PCReg, 0);	

    // Need to also tell MIPS where next instruction is, because
    // of branch delay possibility
    machine->WriteRegister(NextPCReg, 4);

   // Set the stack register to the end of the address space, where we
   // allocated the stack; but subtract off a bit, to make sure we don't
   // accidentally reference off the end!
    machine->WriteRegister(StackReg, numPages * PageSize - 16);
    DEBUG(dbgAddr, "Initializing stack pointer: " << numPages * PageSize - 16);
}

//----------------------------------------------------------------------
// AddrSpace::SaveState
// 	On a context switch, save any machine state, specific
//	to this address space, that needs saving.
//
//	For now, don't need to save anything!
//----------------------------------------------------------------------

void AddrSpace::SaveState() 
{
    if(PT_Load){
        pageTable=kernel->machine->pageTable;
        numPages=kernel->machine->pageTableSize;
    }
}

//----------------------------------------------------------------------
// AddrSpace::RestoreState
// 	On a context switch, restore the machine state so that
//	this address space can run.
//
//      For now, tell the machine where to find the page table.
//----------------------------------------------------------------------

void AddrSpace::RestoreState() 
{
    kernel->machine->pageTable = pageTable;
    kernel->machine->pageTableSize = numPages;
}
