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

/**
 * @brief Scheduler Datenstruktur mit der Menge und Anzahl von Tasks,
 * sowie den aktuellen Task der abgearbeitet werden soll
 * und der Stackpointer der zuletzt vor dem Scheduling gesetzt war.
 */
typedef struct {
	TASK **tasks;
	u08 current_task;
	u08 tasks_length;
	u16 stackPointer;
} SCHEDULER;


/* @brief Datenstruktur um Uhrzeit zu speichern, so dass Funktionen wie sleep() m�glich sind. */
typedef struct {
   u08 hours;
   u08 minutes;
   u08 seconds;
   u16 ms;
   u16 us;
} TIME;

/* @brief Aktuelle Uhrzeit */
TIME currentTime = {0, 0, 0, 0, 0};

SCHEDULER currentScheduler;

/**
 * @brief Einen Task initialisieren: Setze den Programmz�hler des Tasks auf die Taskfunktion,
 * Setze den Stackpointer des jeweiligen Tasks auf den Anfangswert,
 * Initialisiere den Speicher im Stack auf 0, speichere ganz oben
 * auf dem Stack den Programmzähler der Task-Prozedur und setze den Zustand des Tasks
 * auf TASK_RUNNING.
 * @param task Der Task der initialisiert werden soll.
 */
void initTask(TASK *task)
{

   u08 i, pc_high, pc_low;
   u16 sp;
	
	// Set programm Counter
	task->programmCounter = (u16) task->taskFunction;
	
	// Set Stackpointer
	sp = task->stackPointer;
	sp = task->stackSize;
 	
   sp = task->stackSize;
   sp -= MINIMUM_TASK_STACKSIZE;
   sp += (u16) task->stack;
	task->stackPointer = sp;
	//task->stackPointer = (u16) &task->stack;
	//task->stackPointer += task->stackSize;
	
	// Set pause
	task->pause_ms = 0;
	
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

void sleep(u32 pause_ms)
{
	TASK *task;
	BOOL pause = 0;
	task = currentScheduler.tasks[currentScheduler.current_task];
	//if(task->taskState == TASK_RUNNING)
	//{
	  // cli();
		task->pause_ms = pause_ms;
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
      	if(task->pause_ms <= TIMER_DELAY_MS)
      	{
      		task->pause_ms = 0;
      		task->taskState = TASK_RUNNING;
      	}
      	else
      	{
      		task->pause_ms -= TIMER_DELAY_MS;
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

/**
 * @brief Starte einen präemptiven Round-Robin-Scheduler mit einer
 * gegebenen Menge von Tests.
 * @param tasks Liste der Tasks die abgearbeitet werden sollen.
 * @param tasks_length Anzahl der Tasks in der Liste.
 */
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
   //if((currentTime.us+TIMER_DELAY_US)==1000)
   //{
   	if((currentTime.ms+TIMER_DELAY_MS)==1000)
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
   	currentTime.ms = (currentTime.ms+TIMER_DELAY_MS) % 1000;
   //}
   //currentTime.us = (currentTime.us+TIMER_DELAY_US) % 1000;
}

/**
 * @brief Timer Funktion für den Round-Robin-Scheduler.
 * Hier werden zuerst die Register
 * des vorhergehenden Tasks auf dessen Stack gesichert,
 * der Stackpointer des Tasks gesichert,
 * die Systemzeit erhöht und Pausenlängen dekrementiert
 * und anschließend wird vom nächsten abzuarbeitenden Task
 * die Register aus dem Stack geladen und der Stackpointer
 * des Tasks gesetzt.
 */
SCHEDULER_TIMER()
{
	// Testen ob nicht alle Tasks beendet worden sind
	// falls ja:
	//if(!allTasksFinished())
	//{
   	save_registers();
   	if(allTasksFinished())
		{
		 	disableTimer();
		 	set_stackpointer(currentScheduler.stackPointer);
		 	return_interrupt();
		}
	
		TASK *task;
		task = currentScheduler.tasks[currentScheduler.current_task];

	// Stackpointer vom letzten task sichern
		task->stackPointer = get_stackpointer();
		incrementTime();
		decrementPause();


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








































