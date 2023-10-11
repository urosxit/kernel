#include "pcb.h"
#include "system.h"
#include "semqueue.h"
#include "empty.h"
#include "pcblist.h"

int userMain(int argc, char* argv[]);

int main(int argc, char* argv[])
{

        System::listPCB = new PCBlist();
        System::semList = new SemList();

        
        System::timeRunning = 0;

        System::mainThread = new Thread();
        System::mainThread->myPCB->started = 1;
        System::running = System::mainThread->myPCB;
        
        System::emptyThread = new EmptyThread();
        System::emptyThread->start();

        

        System::oldTimer = System::replaceInterrupt(8, &System::timer);

        int result = userMain(argc, argv);

        System::replaceInterrupt(8, System::oldTimer);

        delete System::emptyThread;

        delete System::listPCB;
        delete System::semList;
        delete System::mainThread;

        return result;
}

