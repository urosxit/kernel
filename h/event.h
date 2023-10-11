#ifndef H_EVENT_H_
#define H_EVENT_H_

#include "ivtentry.h"

typedef unsigned char IVTNo;

class KernelEv;

class Event {
public:
	Event (IVTNo ivtNo);
	~Event ();
	void wait ();
protected:
	friend class KernelEv;
	void signal(); // can call KernelEv
private:
	KernelEv* myImpl;
};

#define PREPAREENTRY(num,oldflag)\
void interrupt intrNew##num();\
IVTEntry entry##num(num, oldflag, &intrNew##num);\
void interrupt intrNew##num()\
{\
	entry##num.callOld();\
	entry##num.callEv();\
	dispatch();\
}

#endif /* H_EVENT_H_ */
