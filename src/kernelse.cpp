#include "kernelse.h"
#include "queue.h"
#include "system.h"
#include "schedule.h"
#include "pcb.h"
#include "semqueue.h"



int KernelSem::wait(Time maxTimeToWait)
{
        
       
         System::running->semVal = 1;
              if(--val<0)
              {
                        blocked->put(System::running, maxTimeToWait);
                        System::running->status = BLOCKED;
                        dispatch();
                }
                
        return System::running->semVal;
}

int KernelSem::signal(int n)
{
        if (n <0) return n;
        if (n == 0)
        {
        if (val++ < 0)
        {
                PCB* pcb = blocked->get();
                pcb->status = READY;
                Scheduler::put(pcb);
                pcb->semVal = 1;
        }
        return 0;
        }

        int res = 0;
        for(int i = 0; i< n; i ++){
             if (val++ < 0)
        {
                PCB* pcb = blocked->get();
                pcb->status = READY;
                Scheduler::put(pcb);
                pcb->semVal = 1;
                res++;
        }
        }
        return res;
}

KernelSem::KernelSem(int init)
{

        blocked = new SleepQueue();
        val = init;
        System::semList->put(this);

}

KernelSem::~KernelSem()
{
        while (val < 0)
                signal();
        System::semList->remove(this);
        delete blocked;
}

