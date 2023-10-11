#ifndef H_PCBLIST_H_
#define H_PCBLIST_H_

class PCB;
typedef int ID;

class PCBlist{
	struct Elem{
		PCB* pcb;
		Elem* next;
		Elem(PCB* pcbb){
			pcb = pcbb;
			next = 0;
		}
	};

	int num;
	Elem *first;
	void delPCBlst(){
		while(first){
			Elem *old = first;
			first = first->next;
			delete old;
		}
		num = 0;
	}
public:
	PCBlist() { first = 0; num = 0; }
	int size() const { return num; }

	PCBlist& put(PCB *pcbb){
		Elem *n = new Elem(pcbb);
		if (!first) first = n;
		n->next = first;
		first = n;
		num++;
		return *this;
	}
	PCB* get(){
		if (!first) return 0;
		Elem* temp=first; first=first->next;
		PCB* pcb =temp->pcb;
		delete temp;
		num--;
		return pcb;

	}
	PCB* getByID(ID id){
		Elem *temp = 0;
		temp=first;
		        while (temp){
		                if (id == temp->pcb->id){
		                        PCB* pcbb =temp->pcb;
		                        return pcbb;

		                }
		                else {
		                	 temp=temp->next;
		                }

		        }
		        return 0;
	}

	~PCBlist() { delPCBlst(); }







};



#endif /* H_PCBLIST_H_ */
