#include "semqueue.h"
#include "pcb.h"
#include "schedule.h"


void SleepQueue::put(PCB* pcb, Time time)
{
	if (pcb)
	{
		int inf = (time == 0);
		Elem* elem = new Elem(pcb, time, inf);

		Elem* cur = first;
		Elem* prev = 0;

		while (cur != 0 && cur->time <= elem->time)
		{
			elem->time = elem->time - cur->time;
			prev = cur;
			cur = cur->next;
		}

		if (cur != 0)
		{
			elem->next = cur;
			cur->time = cur->time - elem->time;
		}

		if (prev)
			prev->next = elem;
		else
			first = elem;
	}
}

PCB* SleepQueue::get()
{
	PCB* pcb = 0;
	if (first)
	{
		Elem* old = first;
		first = first->next;
		if (old->inf == 0 && old->time > 0)
		{
			Elem* cur = first;
			while (cur != 0 && cur->inf != 0)
			{
				cur = cur->next;
			}

			if (cur != 0)
			{
				cur->time = cur->time + old->time;
			}
		}
		pcb = old->pcb;
		delete old;
	}
	return pcb;
}

SleepQueue::SleepQueue()
{
	first = 0;
}

SleepQueue::~SleepQueue()
{
	Elem* e = 0;
	while (first)
	{
		e = first;
		first = first->next;
		delete e;
	}
}

int SleepQueue::update()
{
	int count = 0;
	Elem* prev = 0;
	Elem* cur = first;

	while (cur && cur->inf != 0)
	{
		prev = cur;
		cur = cur->next;
	}

	if (cur)
	{
		
		if (cur->time > 0)
		{
			--cur->time;
		}

		while (cur->time == 0)
		{
			PCB* pcb = cur->pcb;

			count++;
			pcb->status = READY;
			Scheduler::put(pcb);
			pcb->semVal = 0;

			if (prev == 0)
				first = cur->next;
			else
				prev->next = cur->next;
			Elem* next = cur->next;
			delete cur;
			cur = next;

			while (cur && cur->inf != 0)
			{
				prev = cur;
				cur = cur->next;
			}

			if (cur == 0)
				break;
		}
	}

	return count;
}


void SemList::put(KernelSem* sem)
{
	if (sem)
	{
		Elem* elem = new Elem(sem);
		elem->next = first;
		first = elem;
	}
}

void SemList::remove(KernelSem* sem)
{
	if (sem)
	{
		Elem* prev = 0;
		Elem* cur = first;

		while (cur && cur->sem != sem)
		{
			prev = cur;
			cur = cur->next;
		}

		if (cur)
		{
			if (prev)
				prev->next = cur->next;
			else
				first = cur->next;
		}
	}
}

SemList::SemList()
{
	first = 0;
}

SemList::~SemList()
{
	Elem* e = 0;
	while (first)
	{
		e = first;
		first = first->next;
		delete e;
	}
}


