#include "empty.h"


EmptyThread::EmptyThread()
{
	pcb = myPCB;
}

void EmptyThread::run()
{
	while (1);
}

