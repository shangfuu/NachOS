// physPageTable.cc
//
//@shungfu: Edit at Hw3
#include "copyright.h"
#include "debug.h"
#include "physPageTable.h"
#include "main.h"


PhysPageTable::PhysPageTable(){
    used = new bool[NumPhysPages];
    load_time = new int[NumPhysPages];
    virtPage = new int [NumPhysPages];
    numFreePhyPages = NumPhysPages;
    for(int i =0; i<NumPhysPages;i++){
        used[i] = NOT_USED;
        load_time[i] = 0;
        virtPage[i] = 0;
    }
    DEBUG(dbgHw3,"physPageTable::NumFreePhyPages = " << numFreePhyPages);
}

PhysPageTable::~PhysPageTable(){

}

