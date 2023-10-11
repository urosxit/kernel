#ifndef SYSTEM_H_
#define SYSTEM_H_

#define lock asm pushf; asm cli;
#define unlock asm popf;

class PCB;
class SemList;
class EmptyThread;
class IVTEntry;
typedef unsigned char IVTNo;
typedef unsigned int Time;
typedef void interrupt (*pInterrupt)();

class Thread;
class SemList;
class PCBlist;

class System
{
public:
	static void dispatch();
	static void interrupt _dispatch();
	static PCB* running;
	static void initStack(PCB* pcb);
	static void wrapper();
	static void interrupt timer();
	static pInterrupt replaceInterrupt(IVTNo ivtNo, pInterrupt newInterrupt);
	static pInterrupt oldTimer;
	static Time timeRunning;
	static EmptyThread* emptyThread;
	static IVTEntry* entries[];
	
	static Thread* mainThread;
	static SemList* semList;
	static PCBlist* listPCB;
};


#endif /* SYSTEM_H_ */
