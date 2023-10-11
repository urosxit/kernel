#ifndef H_IVTENTRY_H_
#define H_IVTENTRY_H_

#include "system.h"
class KernelEv;
typedef unsigned char IVTNo;


class IVTEntry
{
public:
	IVTNo ivtNo;
	KernelEv* ev;
	pInterrupt intrNew;
	pInterrupt intrOld;
	int flagForOld;
	void callEv();
	void callOld();
	~IVTEntry();
	IVTEntry(IVTNo ivtNo, int flagOld, pInterrupt intrNew);
	
};


#endif /* H_IVTENTRY_H_ */
