#ifndef H_PCB_H_
#define H_PCB_H_

#include "thread.h"
class Queue;

enum PCBStatus { READY, BLOCKED, FINISHED };

class PCB
{
public:
	StackSize stackSize;
	Time timeSlice;
	int bp, ss, sp;
	int* stack;
	PCB(StackSize stackSize, Time timeSlice);
	~PCB();
	Queue* waitingToComplete;
	PCBStatus status;
	int started;
	int isNewThread() { return !started && status == READY; }
	Thread* thread;
	int semVal; // sta je vratio wait

	//id i posID
	int id;
	static int posID;
	
};


#endif /* H_PCB_H_ */
