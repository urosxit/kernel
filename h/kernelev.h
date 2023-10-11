#ifndef H_KERNELEV_H_
#define H_KERNELEV_H_

class PCB;
typedef unsigned char IVTNo;
class IVTEntry;
class KernelSem;

class KernelEv
{
public:
	IVTNo ivtNo;
	PCB* pcb;
	IVTEntry* entry;
	KernelSem* sem;
	void signal();
	void wait();
	KernelEv(IVTNo ivtNo);
	~KernelEv();
};


#endif /* H_KERNELEV_H_ */
