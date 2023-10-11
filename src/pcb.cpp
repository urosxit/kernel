#include "pcb.h"
#include "queue.h"
#include "pcblist.h"
#include "system.h"

int PCB::posID = 1;


PCB::PCB(StackSize stackSize, Time timeSlice)
{
        if (stackSize > 65535UL)
                stackSize = 65535UL;
        this->stackSize = stackSize / sizeof(int);
        this->timeSlice = timeSlice;
        waitingToComplete = new Queue();
        stack = 0;
        status = READY;
        started = 0;
        thread = 0;
        //id i pos id
        id = posID++;
        System::listPCB->put(this);

}

PCB::~PCB()
{
        delete waitingToComplete;
        delete[] stack;
        
}


