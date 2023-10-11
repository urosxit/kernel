#include "kernelev.h"
#include "system.h"
#include "pcb.h"
#include "kernelse.h"
#include "ivtentry.h"


void KernelEv::signal()
{
        if (sem->val < 1)
        {
                sem->signal();
        }
}

void KernelEv::wait()
{
        if (pcb != System::running)
        {
                return;
        }

        sem->wait(0);
}

KernelEv::KernelEv(IVTNo ivtNo)
{
        pcb = System::running;
        this->ivtNo = ivtNo;


        entry = System::entries[ivtNo];
        if (entry != 0)
        {
                
                if (entry->ev == 0)
                {
                        
                        entry->ev = this;
                }
        }
        sem = new KernelSem(0);
}

KernelEv::~KernelEv()
{
        
        if (entry != 0)
        {

                if (entry->ev == this)
                {
                        
                        entry->ev = 0;
                }
        }
        if (sem->val < 0)
                signal();
        delete sem;
}

