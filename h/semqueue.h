#ifndef H_SEMQUEUE_H_
#define H_SEMQUEUE_H_


class PCB;
class KernelSem;
typedef unsigned int Time;

class SleepQueue
{
public:
	struct Elem
	{
		Elem(PCB* pcb, Time time, int inf) { this->pcb = pcb; this->time = time; this->inf = inf; next = 0; }
		PCB* pcb;
		Time time;
		int inf;
		Elem* next;
	};
	Elem *first;
	void put(PCB* pcb, Time time);
	PCB* get();
	SleepQueue();
	~SleepQueue();
	int update();
};

class SemList
{
public:
	struct Elem
	{
		Elem(KernelSem* sem) { this->sem = sem; next = 0; }
		KernelSem* sem;
		Elem* next;
	};
	Elem *first;
	void put(KernelSem* sem);
	void remove(KernelSem* sem);
	SemList();
	~SemList();
};


#endif /* H_SEMQUEUE_H_ */
