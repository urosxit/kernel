#ifndef H_KERNELSE_H_
#define H_KERNELSE_H_


class SleepQueue;
typedef unsigned int Time;

class KernelSem
{
public:
	int val;
	SleepQueue* blocked;
	int wait(Time maxTimeToWait);
	int signal(int n = 0);
	KernelSem(int init);
	~KernelSem();
};


#endif /* H_KERNELSE_H_ */
