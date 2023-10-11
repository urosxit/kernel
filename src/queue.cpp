#include "queue.h"

void Queue::put(PCB* pcb)
{
	if (pcb)
	{
		Elem* e = new Elem(pcb);
		if (last)
			last->next = e;
		else
			first = e;
		last = e;
	}
}

PCB* Queue::get()
{
	PCB* pcb = 0;
	if (first)
	{
		pcb = first->pcb;
		Elem* e = first;
		first = first->next;
		if (first == 0)
			last = 0;
		delete e;
	}
	return pcb;
}

Queue::Queue()
{
	first = last = 0;
}

Queue::~Queue()
{
	Elem* e = 0;
	while (first)
	{
		e = first;
		first = first->next;
		if (first == 0)
			last = 0;
		delete e;
	}
}

