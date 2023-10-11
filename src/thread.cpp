
#include "pcb.h"
#include "thread.h"
#include "system.h"
#include "schedule.h"
#include "queue.h"
#include "semqueue.h"
#include "empty.h"
#include "pcblist.h"
Thread::Thread(StackSize stackSize, Time timeSlice)
{
#ifndef BCC_BLOCK_IGNORE
        lock
#endif
        myPCB = new PCB(stackSize, timeSlice);
        myPCB->thread = this;
#ifndef BCC_BLOCK_IGNORE
        unlock
#endif
}

Thread::~Thread()
{
        waitToComplete();
#ifndef BCC_BLOCK_IGNORE
        lock
#endif
        delete myPCB;
#ifndef BCC_BLOCK_IGNORE
        unlock
#endif
}

void dispatch()
{
#ifndef BCC_BLOCK_IGNORE
        lock
#endif
        System::dispatch();
#ifndef BCC_BLOCK_IGNORE
        unlock
#endif
}

void Thread::start()
{
#ifndef BCC_BLOCK_IGNORE
        lock
#endif
        if (myPCB->started)
        {
#ifndef BCC_BLOCK_IGNORE
        unlock
#endif
                return;
        }
        System::initStack(myPCB);
        if (myPCB != System::emptyThread->getPCB())
        {
                Scheduler::put(myPCB);
        }
        myPCB->started = 1;
#ifndef BCC_BLOCK_IGNORE
        unlock
#endif
}

void Thread::waitToComplete()
{
#ifndef BCC_BLOCK_IGNORE
        lock
#endif
        if (myPCB->status == FINISHED || myPCB->isNewThread())
        {
#ifndef BCC_BLOCK_IGNORE
        unlock
#endif
                return;
        }
        if (myPCB == System::running || myPCB == System::emptyThread->getPCB())
        {
#ifndef BCC_BLOCK_IGNORE
        unlock
#endif
                return;
        }
        myPCB->waitingToComplete->put(System::running);
        System::running->status = BLOCKED;
        dispatch();
#ifndef BCC_BLOCK_IGNORE
        unlock
#endif
}

ID Thread::getId(){
#ifndef BCC_BLOCK_IGNORE
        lock
#endif
        ID res = this->myPCB->id;
#ifndef BCC_BLOCK_IGNORE
        unlock
#endif
        return res;
}

ID Thread::getRunningId(){
#ifndef BCC_BLOCK_IGNORE
        lock
#endif
        ID res = System::running->id;
#ifndef BCC_BLOCK_IGNORE
        unlock
#endif
        return res;

}

Thread * Thread::getThreadById(ID id){
#ifndef BCC_BLOCK_IGNORE
        lock
#endif
        Thread * res = 0;
        PCB *pcb= System::listPCB->getByID(id);
        if (pcb)
            res = pcb->thread;
#ifndef BCC_BLOCK_IGNORE
        unlock
#endif
        return res;
}


