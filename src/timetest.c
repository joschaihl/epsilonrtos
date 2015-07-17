#include "kernel.h"

#define DEFAULTPORT PORTB
#define DEFAULTDDR DDRB
#define TASKAPIN PB0
#define TASKBPIN PB1
#define TASKCPIN PB2
#define TASKDPIN PB3
#define TASKEPIN PB4



void setup(void)
{
  sbi(DEFAULTDDR, TASKAPIN);
  sbi(DEFAULTDDR, TASKBPIN);
  sbi(DEFAULTDDR, TASKCPIN);
  sbi(DEFAULTDDR, TASKDPIN);
  sbi(DEFAULTDDR, TASKEPIN);
}

u32 a;
TASK(A,32)
{
	for(a=0;a < 100000;a++)
	{
		sbi(DEFAULTPORT, TASKAPIN);
		cbi(DEFAULTPORT, TASKAPIN);
  	}
  	ENDTASK(A);
}

u08 b;
TASK(B,32)
{
   u08 i;
	for(b=0;b<2;b++)
	{
	   for(i=0; i < 100; i++)
	   {
			sbi(DEFAULTPORT, TASKBPIN);
			cbi(DEFAULTPORT, TASKBPIN);
		}
		sleep(20000);
  	}
  	ENDTASK(B);
}


//----- Begin Code ------------------------------------------------------------

#define TASK_AMOUNT 2
TASK *taskset[] = {&taskobj_A, &taskobj_B/*, &taskobj_C, &taskobj_D*/};

int main(void)
{

   INIT_RTOS();

	setup();
   	sbi(DEFAULTPORT, TASKDPIN);
	cbi(DEFAULTPORT, TASKDPIN);

	startRRScheduler(taskset, TASK_AMOUNT);
	
	while(1)
	{
		sbi(DEFAULTPORT, TASKDPIN);
		cbi(DEFAULTPORT, TASKDPIN);
	}
	//return 0;
}












































