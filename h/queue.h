#ifndef H_QUEUE_H_
#define H_QUEUE_H_

class PCB;

class Queue
{
public:
	struct Elem
	{
		Elem(PCB* pcb) { this->pcb = pcb; next = 0; }
		PCB* pcb;
		Elem* next;
	};
	Elem *first, *last;
	void put(PCB* pcb);
	PCB* get();
	Queue();
	~Queue();
};


#endif /* H_QUEUE_H_ */
