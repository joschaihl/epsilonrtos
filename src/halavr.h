/**
 *  @file halavr.h
 *  @brief Konkrete AVR-Implementierung für die Hardware-Abstraktions-Schicht
 *  	   für epsilonRTOS
 *  @author Joscha Ihl vision.josh@gmail.com
 *  @version 0.1
 *  @date 27.04.2015
 *
 *  Projekt     : EpsilonRTOS
 *
 *  This code is distributed under the GNU Public License
 *  which can be found at http://www.gnu.org/licenses/gpl.txt
 */

#ifndef HALAVR_H_
#define HALAVR_H_

#include <avr/io.h>			// include I/O definitions (port names, pin names, etc)
#include <avr/interrupt.h>	// include interrupt support
#include <avr/pgmspace.h>
#include "libdefs.h"
#include "global.h"
#include "uartavr.h"

#define INIT_STACK() \
	SP = RAMEND \
	
#ifdef USE_TERMINAL
#define INIT_TERM() \
	uart_init(); \

#define PUTC(UC) \
	uart_putc(UC); \

#define PUTS(C) \
	uart_puts(C); \

#define PUTSP(CP) \
	uart_puts_p(PSTR(CP)); \
		
#else
#define INIT_TERM()

#define PUTC(UC)

#define PUTS(C)

#define PUTSP(CP)

#endif


#define CLEAR_REGISTERS() \
  asm volatile ("clr    r0"); \
  asm volatile ("clr    r1"); \
  asm volatile ("clr    r2"); \
  asm volatile ("clr    r3"); \
  asm volatile ("clr    r4"); \
  asm volatile ("clr    r5"); \
  asm volatile ("clr    r6");\
  asm volatile ("clr    r7");\
  asm volatile ("clr    r8");\
  asm volatile ("clr    r9");\
  asm volatile ("clr    r10");\
  asm volatile ("clr    r11");\
  asm volatile ("clr    r12");\
  asm volatile ("clr    r13");\
  asm volatile ("clr    r14");\
  asm volatile ("clr    r15");\
  asm volatile ("clr    r16");\
  asm volatile ("clr    r17");\
  asm volatile ("clr    r18");\
  asm volatile ("clr    r19");\
  asm volatile ("clr    r20");\
  asm volatile ("clr    r21");\
  asm volatile ("clr    r22");\
  asm volatile ("clr    r23");\
  asm volatile ("clr    r24");\
  asm volatile ("clr    r25");\
  asm volatile ("clr    r26");\
  asm volatile ("clr    r27");\
  asm volatile ("clr    r28");\
  asm volatile ("clr    r29");\
  asm volatile ("clr		r30");\
  asm volatile ("clr		r31");\


#define INIT_RTOS() \
	INIT_STACK(); \
	CLEAR_REGISTERS(); \
	INIT_TERM(); \


#define set_stackpointer(STACKPOINTER) SP = STACKPOINTER
#define get_stackpointer() SP
	
#define nop() \
   asm volatile ("nop"); \

#define WORKING_REGISTERS 32
#define FUNCTION_WIDTH 2
#define MINIMUM_TASK_STACKSIZE WORKING_REGISTERS + FUNCTION_WIDTH

#define save_registers() \
  asm volatile ("push    r0"); \
  asm volatile ("push    r1"); \
  asm volatile ("push    r2"); \
  asm volatile ("push    r3"); \
  asm volatile ("push    r4"); \
  asm volatile ("push    r5"); \
  asm volatile ("push    r6");\
  asm volatile ("push    r7");\
  asm volatile ("push    r8");\
  asm volatile ("push    r9");\
  asm volatile ("push    r10");\
  asm volatile ("push    r11");\
  asm volatile ("push    r12");\
  asm volatile ("push    r13");\
  asm volatile ("push    r14");\
  asm volatile ("push    r15");\
  asm volatile ("push    r16");\
  asm volatile ("push    r17");\
  asm volatile ("push    r18");\
  asm volatile ("push    r19");\
  asm volatile ("push    r20");\
  asm volatile ("push    r21");\
  asm volatile ("push    r22");\
  asm volatile ("push    r23");\
  asm volatile ("push    r24");\
  asm volatile ("push    r25");\
  asm volatile ("push    r26");\
  asm volatile ("push    r27");\
  asm volatile ("push    r28");\
  asm volatile ("push    r29");\
  asm volatile ("push    r30");\
  asm volatile ("push    r31");\

#define load_registers() \
  asm volatile ("pop    r31");\
  asm volatile ("pop    r30");\
  asm volatile ("pop    r29");\
  asm volatile ("pop    r28");\
  asm volatile ("pop    r27");\
  asm volatile ("pop    r26");\
  asm volatile ("pop    r25");\
  asm volatile ("pop    r24");\
  asm volatile ("pop     r23");\
  asm volatile ("pop     r22");\
  asm volatile ("pop     r21");\
  asm volatile ("pop     r20");\
  asm volatile ("pop     r19");\
  asm volatile ("pop     r18");\
  asm volatile ("pop     r17");\
  asm volatile ("pop     r16");\
  asm volatile ("pop     r15");\
  asm volatile ("pop     r14");\
  asm volatile ("pop     r13");\
  asm volatile ("pop     r12");\
  asm volatile ("pop     r11");\
  asm volatile ("pop     r10");\
  asm volatile ("pop     r9");\
  asm volatile ("pop     r8");\
  asm volatile ("pop     r7");\
  asm volatile ("pop     r6");\
  asm volatile ("pop     r5");\
  asm volatile ("pop     r4");\
  asm volatile ("pop     r3");\
  asm volatile ("pop     r2");\
  asm volatile ("pop     r1");\
  asm volatile ("pop     r0");\

#define return_interrupt() \
	asm volatile("reti");

#define TIMER_DELAY_US 250

#ifdef TCCR0A
#define TCCR TCCR0A
#endif

#ifdef TCCR0
#define TCCR TCCR0
#endif

#define initTimer() \
  TCCR = (1<<CS01); \
  TIMSK = (1<<TOIE0); /* TOIE0: Interrupt bei Timer Overflow */ \
  sei();

#define disableTimer() \
	TIMSK = 0;
	
/* #define SCHEDULER_TIMER() ISR(TIMER0_OVF0_vect,ISR_NAKED) */
#define SCHEDULER_TIMER() ISR(TIMER0_OVF_vect,ISR_NAKED)


#endif /* HALAVR_H_ */

















