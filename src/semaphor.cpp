#include "semaphor.h"
#include "kernelse.h"
#include "system.h"

Semaphore::Semaphore (int init)
{
#ifndef BCC_BLOCK_IGNORE
        lock
#endif
        myImpl = new KernelSem(init);
#ifndef BCC_BLOCK_IGNORE
        unlock
#endif
}

Semaphore::~Semaphore ()
{
#ifndef BCC_BLOCK_IGNORE
        lock
#endif
        delete myImpl;
#ifndef BCC_BLOCK_IGNORE
        unlock
#endif
}


int Semaphore::wait(Time maxTimeToWait)
{
#ifndef BCC_BLOCK_IGNORE
        lock
#endif

        int res = myImpl->wait(maxTimeToWait);
#ifndef BCC_BLOCK_IGNORE
        unlock
#endif
        return res;
}

int Semaphore::signal(int n)
{
#ifndef BCC_BLOCK_IGNORE
        lock
#endif
        int res = myImpl->signal(n);
#ifndef BCC_BLOCK_IGNORE
        unlock
#endif
return res;
}

int Semaphore::val () const {
#ifndef BCC_BLOCK_IGNORE
        lock
#endif
        int res = myImpl->val;
#ifndef BCC_BLOCK_IGNORE
        unlock
#endif
        return res;
}

