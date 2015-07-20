/**
 *  @file kernel.c
 *  @brief Betriebssystemkern
 *  	   für epsilonRTOS
 *  @author Joscha Ihl vision.josh@gmail.com
 *  @version 0.1
 *
 *  Projekt     : EpsilonRTOS
 *  @date 27.04.2015
 *
 *  This code is distributed under the GNU Public License
 *  which can be found at http://www.gnu.org/licenses/gpl.txt
 */

#include "kernel.h"

typedef struct {
	TASK **tasks;
	u08 current_task;
	u08 tasks_length;
	u16 stackPointer;
} SCHEDULER;

typedef struct {
   u08 hours;
   u08 minutes;
   u08 seconds;
   u16 ms;
   u16 us;
} TIME;

TIME currentTime = {0, 0, 0, 0, 0};

SCHEDULER currentScheduler;


void initTask(TASK *task)
{
   u08 i, pc_high, pc_low;
	
	if(task->taskState == TASK_UNINITIALIZED)
	{
		 // Set Stack Address
       for(i = 0; i < (task->stackSize -2); i++)
       {
          task->stack[i] = 0;
       }
       pc_high = (task->programmCounter >> 8);
       pc_low =  0xff & task->programmCounter;
       i++;
       task->stack[i] = pc_high;
       i++;
       task->stack[i] = pc_low;
		 // Set Task Ready
		 task->taskState = TASK_RUNNING;		
	}
}

void sleep(u32 pause_us)
{
	TASK *task;
	BOOL pause = 0;
	task = currentScheduler.tasks[currentScheduler.current_task];
	//if(task->taskState == TASK_RUNNING)
	//{
	  // cli();
		task->pause_us = pause_us;
		task->taskState = TASK_PAUSE;
	//	sei();
		
		do
		{
			pause = (currentScheduler.tasks[currentScheduler.current_task]->taskState == TASK_PAUSE);
		} while(pause);
	//}
}

void decrementPause(void)
{
   u08 i;
   TASK *task;
	for(i = 0;	i < currentScheduler.tasks_length; i++)
	{
		task = currentScheduler.tasks[i];
		if(task->taskState == TASK_PAUSE)
		{
      	if(task->pause_us <= TIMER_DELAY_US)
      	{
      		task->pause_us = 0;
      		task->taskState = TASK_RUNNING;
      	}
      	else
      	{
      		task->pause_us -= TIMER_DELAY_US;
      	}
      }
	}
}

u08 allTasksFinished(void)
{
   u08 i;
   TASK *task;
   u08 result = 1;
	for(i = 0;	i < currentScheduler.tasks_length; i++)
	{
		task = currentScheduler.tasks[i];
		if(task->taskState != TASK_FINISHED)
		{
			result = 0;
			break;
		}
	}
	return (result);
}

void startRRScheduler(TASK **tasks, u08 tasks_length)
{
	currentScheduler.stackPointer = SP + 7;
   TASK *task;
	currentScheduler.current_task = 0;
	currentScheduler.tasks = tasks;
	currentScheduler.tasks_length = tasks_length;

	// Inititalize Tasks
	for(currentScheduler.current_task = 0;
			currentScheduler.current_task < currentScheduler.tasks_length;
			currentScheduler.current_task++)
	{
		task = currentScheduler.tasks[currentScheduler.current_task];
      initTask(task);
	}
	currentScheduler.current_task = 0;
   task = currentScheduler.tasks[0];
	initTimer();

	set_stackpointer(task->stackPointer + WORKING_REGISTERS);
	task->taskFunction();
}

void nextScheduleItem(void)
{
	if (currentScheduler.current_task < (currentScheduler.tasks_length -1))
	{
		currentScheduler.current_task++;
	}
	else
	{
		currentScheduler.current_task = 0;
	}
}

void incrementTime(void)
{
   if((currentTime.us+TIMER_DELAY_US)==1000)
   {
   	if((currentTime.ms+1)==1000)
   	{
   	   if((currentTime.seconds+1)==60)
   	   {
   	   	if((currentTime.minutes+1)==60)
   	   	{
   	   		currentTime.hours = (currentTime.hours+1) % 24;
   	   	}
   	   	currentTime.minutes = (currentTime.minutes+1) % 60;
   	   }
   	   currentTime.seconds = (currentTime.seconds+1) % 60;
   	}
   	currentTime.ms = (currentTime.ms+1) % 1000;
   }
   currentTime.us = (currentTime.us+TIMER_DELAY_US) % 1000;
}

SCHEDULER_TIMER()
{
	// Testen ob nicht alle Tasks beendet worden sind
	// falls ja:
	//if(!allTasksFinished())
	//{
   	save_registers();
		TASK *task;
		task = currentScheduler.tasks[currentScheduler.current_task];

	// Stackpointer vom letzten task sichern
		task->stackPointer = get_stackpointer();
		incrementTime();
		decrementPause();

		if(allTasksFinished())
		{
		 	set_stackpointer(currentScheduler.stackPointer);
		 	disableTimer();
		 	return_interrupt();
		}
	
		nextScheduleItem();
  		task = currentScheduler.tasks[currentScheduler.current_task];
		set_stackpointer(task->stackPointer);
		load_registers();
	/*}
	else
	{ // Kein Task mehr da
	 	// Stackpointer setzen
		set_stackpointer(currentScheduler.stackPointer);
		// Timer deaktivieren
		disableTimer();
	}  */
   return_interrupt();
}































