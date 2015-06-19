/*
 * kernel.h
 *
 *  Created on: 24.04.2015
 *      Author: joscha
 */

#ifndef KERNEL_H_
#define KERNEL_H_

#include "global.h"		// include our global settings
#include "hal.h"

typedef void (*TASK_FUNC)(void);

typedef enum {TASK_UNINITIALIZED, TASK_RUNNING,
	TASK_PAUSE, TASK_FINISHED} TASK_STATE;

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
	TASK taskobj_ ## NAME = {task_ ## NAME, (u16) &task_ ## NAME, taskstack_ ## NAME, \
	 (u16) taskstack_ ## NAME + SIZE, SIZE + MINIMUM_TASK_STACKSIZE, TASK_UNINITIALIZED}; \
	void task_ ## NAME(void)
	
#define ENDTASK(NAME) \
	taskobj_ ## NAME.taskState = TASK_FINISHED; \
	while(1) { \
		nop(); \
	} \
	return;
	
#define DEFINE_TASKSET(TASKSETNAME, TASK, ...)

#endif /* KERNEL_H_ */




















