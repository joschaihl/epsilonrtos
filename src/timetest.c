/**
 *  @file timetest.c
 *  @brief Mini-Test-Suite für epsilonRTOS.
 *  @author Joscha Ihl vision.josh@gmail.com
 *  @version 0.1
 *  @date 18.07.2015
 *
 *  Projekt     : EpsilonRTOS
 *
 *  This code is distributed under the GNU Public License
 *  which can be found at http://www.gnu.org/licenses/gpl.txt
 */

#include "kernel.h"
#include "test.h"
#include <stdlib.h>

#define DEFAULTPORT PORTB
#define DEFAULTDDR DDRB
#define TASKAPIN PB0
#define TASKBPIN PB1
#define TASKCPIN PB2
#define TASKDPIN PB3
#define TASKEPIN PB4
#define ANALOGPORT PORTC
#define ANALOGDDR  DDRC
#define DEFAULTADC PC0



void setup(void)
{
  sbi(DEFAULTDDR, TASKAPIN);
  sbi(DEFAULTDDR, TASKBPIN);
  sbi(DEFAULTDDR, TASKCPIN);
  sbi(DEFAULTDDR, TASKDPIN);
  sbi(DEFAULTDDR, TASKEPIN);
  setTracepoint(1);
}



u08 ja = 0;
void task_a_func(void)
{
   u16 jc=0;
	for(ja=0;ja < 5;ja++)
	{
      for(jc=0;jc<1000;jc++)
      {
       		sbi(DEFAULTPORT, TASKAPIN);
				cbi(DEFAULTPORT, TASKAPIN);
      }
      PUTSP("A ");
  	}
  	PUTSP("\n");
  	setTracepoint(2);
}

TASK(A,128)
{
   task_a_func();
  	ENDTASK(A);
}

u08 jb = 0;
u08 ji;

TASK(B,128)
{

	for(jb=0;jb<3;jb++)
	{
		PUTSP("B ");
	   for(ji=0; ji < 100; ji++)
	   {
			sbi(DEFAULTPORT, TASKBPIN);
			cbi(DEFAULTPORT, TASKBPIN);
		}
		sleep(10);
  	}
  	setTracepoint(3);
  	ENDTASK(B);
}


TASK(C,64)
{
   u32 ua;
	for(ua=0;ua<100000;ua+=100)
	{
	   sbi(DEFAULTPORT, TASKCPIN);
		cbi(DEFAULTPORT, TASKCPIN);
	}
	if(ua==100000)
		setTracepoint(5);
	
	ENDTASK(C);
}

u08 xc;

volatile u08 pwmfreq = 0;

TASK(D,64)
{
   u16 xd;
   enableADC0();
	for(xc=0;xc<10;xc++)
	{
		for(xd=0;xd<1000;xd++)
		{
			pwmfreq = readADC();
		}
	}
	ENDTASK(D);
}



void task_e_func(void)
{
   u16 i;
	enablePWM();
	for(i=0;i<10000;i++)
	{
		setPWM1val(pwmfreq);
	}
	
	disablePWM();	
}

TASK(E,64)
{
   task_e_func();

	ENDTASK(E);
}

//----- Begin Code ------------------------------------------------------------

#define TASK_AMOUNT 2
TASK *taskset[] = {&taskobj_A, &taskobj_B};
TASK *taskset2[] = {&taskobj_C, &taskobj_D, &taskobj_E};

#ifdef UNITTEST_TESTS
TEST(assertionsFailure)
{
   checkTracepoint(0);
	assertEquals(0,0);
	setTracepoint(1);
	checkTracepoint(1);
	assertEquals(0,-1);
	setTracepoint(2);
	assertEquals(10000,10000);
	setTracepoint(3);
}

TEST(assertionsFailure2)
{
	setTracepoint(4);
	assertLower(0,0);
   setTracepoint(5);
}

TEST(assertionsNoFailure)
{
   setTracepoint(6);
	assertLower(-1, 0);
	assertLower(0, 1);
	assertLowerEqual(-1, 0);
	assertLowerEqual(0, 1);
	assertLowerEqual(-1, -1);
	assertEquals(10000, 10000);
	assertGreaterEqual(10000, 10000);
	assertGreaterEqual(10001, 10000);
	assertGreater(0, -1);
	assertGreater(1, 0);
	setTracepoint(7);
	
}

TEST(tracepointFailure)
{
   checkTracepoint(0);
}
#endif

TEST(taskset1Test)
{
  	assertEquals(ja, 5);
  //	assertEquals(jc, 1000);
   assertEquals(jb,3);
   assertEquals(ji,100);
   checkTracepoint(2);
}

TEST(taskset2Test)
{
   checkTracepoint(5);
   //assertEquals(ua, 100000);
 //  assertEquals(xc, 10);
 //  assertEquals(xd, 1000);
}

int main(void)
{
   INIT_RTOS();

#ifdef UNITTEST_TESTS	
	suite();
	RUN(assertionsFailure);
	checkTracepoint(1);
	RUN(tracepointFailure);
	RUN(assertionsFailure2);
	checkTracepoint(4);
	RUN(assertionsNoFailure);
	checkTracepoint(7);
	suiteend();
#endif

   suite();
	setup();
	checkTracepoint(1);

   SCHEDULER(taskset, TASK_AMOUNT);
   RUN(taskset1Test);

   SCHEDULER(taskset2, 3);
   RUN(taskset2Test);
	suiteend();	
	
	do{
	  nop();
	} while(1);
	return 0;
}














































































