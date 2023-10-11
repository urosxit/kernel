#ifndef H_EMPTY_H_
#define H_EMPTY_H_


#include "thread.h"

class EmptyThread : public Thread
{
public:
	EmptyThread();
	PCB* getPCB() { return pcb; }
protected:
	void run();
private:
	PCB* pcb;
};


#endif /* H_EMPTY_H_ */
