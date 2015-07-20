/**
 *  @file kernel.h
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

#ifndef KERNEL_H_
#define KERNEL_H_

#include "global.h"		// include our global settings
#include "hal.h"

typedef void (*TASK_FUNC)(void);

typedef enum {TASK_UNINITIALIZED = 0, TASK_RUNNING = 1,
	TASK_PAUSE = 2, TASK_FINISHED = 3} TASK_STATE;

typedef struct {
	TASK_FUNC taskFunction;
	u16 programmCounter;
	u08 *stack;
	u16 stackPointer;
	u08 stackSize;
	u32 pause_us;
	TASK_STATE taskState;
} TASK;


void initTask(TASK *task);
void startRRScheduler(TASK **tasks, u08 tasks_length);
void sleep(u32 pause_us);

#define TASK(NAME,SIZE) \
	void task_ ## NAME(void); \
	u08 taskstack_ ## NAME[SIZE + MINIMUM_TASK_STACKSIZE] = "STACK"; \
	TASK taskobj_ ## NAME = { task_ ## NAME, (u16) &task_ ## NAME, taskstack_ ## NAME, \
	(u16) taskstack_ ## NAME + SIZE, \
	SIZE + MINIMUM_TASK_STACKSIZE, \
	0, \
	TASK_UNINITIALIZED}; \
	void task_ ## NAME(void)
	
#define ENDTASK(NAME) \
	taskobj_ ## NAME.taskState = TASK_FINISHED; \
	while(1) { \
		nop(); \
	} \
	return;
	
#define DEFINE_TASKSET(TASKSETNAME, TASK, ...)

#endif /* KERNEL_H_ */






















