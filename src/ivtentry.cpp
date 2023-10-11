#include "ivtentry.h"
#include "system.h"
#include "kernelev.h"

void IVTEntry::callEv()
{
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	if (ev != 0)
	{
		ev->signal();
	}
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}

void IVTEntry::callOld()
{
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	if (intrOld != 0 && flagForOld != 0)
	{
		(*intrOld)();
	}
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}

IVTEntry::IVTEntry(IVTNo ivtNo, int flagOld, pInterrupt intrNew)
{
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	this->intrNew = intrNew;
	this->ivtNo = ivtNo;
	this->flagForOld = flagOld;
	this->intrOld = System::replaceInterrupt(ivtNo, intrNew);
	this->ev = 0;
	System::entries[ivtNo] = this;
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}

IVTEntry::~IVTEntry()
{
#ifndef BCC_BLOCK_IGNORE
	lock
#endif
	System::entries[ivtNo] = 0;
	System::replaceInterrupt(ivtNo, intrOld);
	if (intrOld != 0)
		(*intrOld)();
#ifndef BCC_BLOCK_IGNORE
	unlock
#endif
}

