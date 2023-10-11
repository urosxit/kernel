#include "system.h"
#include "pcb.h"
#include "schedule.h"
#include <dos.h>
#include "queue.h"
#include "semqueue.h"
#include "kernelse.h"
#include "empty.h"

#define PSW 0x200
#ifndef BCC_BLOCK_IGNORE
#define WRAPPER_SEG FP_SEG(System::wrapper);
#define WRAPPER_OFF FP_OFF(System::wrapper);
#endif

void tick();

PCB* System::running = 0;
pInterrupt System::oldTimer = 0;
Time System::timeRunning = 0;
EmptyThread* System::emptyThread = 0;
IVTEntry* System::entries[256] = {0};

Thread* System::mainThread = 0;
PCBlist* System::listPCB = 0;
SemList* System::semList = 0;

void System::dispatch()
{
#ifndef BCC_BLOCK_IGNORE
        lock
#endif
        System::_dispatch();
#ifndef BCC_BLOCK_IGNORE
        unlock
#endif
}

void interrupt System::_dispatch()
{
        static unsigned int tmpbp, tmpss, tmpsp;
#ifndef BCC_BLOCK_IGNORE
        asm {
                mov tmpbp, bp;
                mov tmpss, ss;
                mov tmpsp, sp;
        }
#endif
        running->bp = tmpbp;
        running->ss = tmpss;
        running->sp = tmpsp;



        if (running->status == READY && running != emptyThread->getPCB())
                Scheduler::put(running);
        running = Scheduler::get();
        if (running == 0)
        {
                running = emptyThread->getPCB();
        }


        tmpbp = running->bp;
        tmpss = running->ss;
        tmpsp = running->sp;
#ifndef BCC_BLOCK_IGNORE
        asm {
                mov bp, tmpbp;
                mov ss, tmpss;
                mov sp, tmpsp;
        }
#endif



        timeRunning = 0;


}

void System::initStack(PCB* pcb)
{
         if (pcb)
        {
                StackSize size = pcb->stackSize;
                int* stack = new int[size];

                stack[size - 1] = PSW;
#ifndef BCC_BLOCK_IGNORE
                stack[size - 2] = WRAPPER_SEG;
                stack[size - 3] = WRAPPER_OFF;

                pcb->bp = FP_OFF(stack + size - 12);
                pcb->sp = FP_OFF(stack + size - 12);
                pcb->ss = FP_SEG(stack + size - 12);
#endif
                pcb->stack = stack;
        }
}

void System::wrapper()
{
        running->thread->run();

#ifndef BCC_BLOCK_IGNORE
        lock
#endif
        while (running->waitingToComplete->first)
        {
                PCB* pcb = running->waitingToComplete->get();
                pcb->status = READY;
                Scheduler::put(pcb);
        }
        running->status = FINISHED;
        dispatch();
#ifndef BCC_BLOCK_IGNORE
        unlock
#endif
}

void interrupt System::timer()
{
        if (oldTimer)
        {
                (*oldTimer)();
        }


        for(SemList::Elem* curSem = semList->first; curSem!=0; curSem = curSem->next)
        {
            int diff = curSem->sem->blocked->update();
            curSem->sem->val+= diff;
        }

        tick();

        if (running == emptyThread->getPCB())
        {
                dispatch();
        }
        else if (running->timeSlice != 0)
        {
                ++timeRunning;
                if (timeRunning >= running->timeSlice)
                        dispatch();
        }
}

pInterrupt System::replaceInterrupt(IVTNo ivtNo, pInterrupt newInterrupt)
{
#ifndef BCC_BLOCK_IGNORE
        lock
#endif
        pInterrupt oldInterrupt = 0;
#ifndef BCC_BLOCK_IGNORE
        unsigned num = ivtNo * 4;
        unsigned newSeg = FP_SEG(newInterrupt);
        unsigned newOff = FP_OFF(newInterrupt);
        unsigned oldSeg, oldOff;

        asm {
                push es;
                push ax;
                push bx;

                mov ax, 0;
                mov es, ax;

                mov bx, num;

                mov ax, word ptr es:bx;
                mov oldOff, ax;
                add bx, 2;
                mov ax, word ptr es:bx;
                mov oldSeg, ax;

                mov ax, newSeg;
                mov word ptr es:bx, ax;
                sub bx, 2;
                mov ax, newOff;
                mov word ptr es:bx, ax;

                pop bx;
                pop ax;
                pop es;
        }
        oldInterrupt = (pInterrupt)MK_FP(oldSeg, oldOff);
        unlock
#endif
        return oldInterrupt;
}

