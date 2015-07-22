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



void setup(void)
{
  sbi(DEFAULTDDR, TASKAPIN);
  sbi(DEFAULTDDR, TASKBPIN);
  sbi(DEFAULTDDR, TASKCPIN);
  sbi(DEFAULTDDR, TASKDPIN);
  sbi(DEFAULTDDR, TASKEPIN);
  setTracepoint(1);
}

u08 ja = 0, jc=0;

TASK(A,64)
{

	for(ja=0;ja < 100;ja++)
	{
      for(jc=0;jc<100;jc++)
      {
       		sbi(DEFAULTPORT, TASKAPIN);
				cbi(DEFAULTPORT, TASKAPIN);
      }

  	}
  	setTracepoint(2);
  	ENDTASK(A);
}

u08 jb = 0;
u08 ji;

TASK(B,64)
{

	for(jb=0;jb<2;jb++)
	{
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

u32 ua;
TASK(C,64)
{

	for(ua=0;ua<100000;ua+=100)
	{
	   sbi(DEFAULTPORT, TASKCPIN);
		cbi(DEFAULTPORT, TASKCPIN);
	}
	if(ua==100000)
		setTracepoint(5);
	
	ENDTASK(C);
}

u08 xa;
u16 xb;
TASK(D,64)
{

	for(xa=0;xa<10;xa++)
	{
		for(xb=0;xb<1000;xb++)
		{
	   	sbi(DEFAULTPORT, TASKDPIN);
			cbi(DEFAULTPORT, TASKDPIN);
		}
	}
	ENDTASK(D);
}

//----- Begin Code ------------------------------------------------------------

#define TASK_AMOUNT 2
TASK *taskset[] = {&taskobj_A, &taskobj_B};
TASK *taskset2[] = {&taskobj_C, &taskobj_D};

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
	assertEquals(ja, 100);
   assertEquals(jb,2);
   assertEquals(jc,100);
   checkTracepoint(2);
}

TEST(taskset2Test)
{
   checkTracepoint(5);
   assertEquals(ua, 100000);
   assertEquals(xa, 10);
   assertEquals(xb, 1000);
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
   assertEquals(0,ja);
   assertEquals(0,jb);
	setup();
	checkTracepoint(1);

   SCHEDULER(taskset, TASK_AMOUNT);
   RUN(taskset1Test);

   SCHEDULER(taskset2, TASK_AMOUNT);

   RUN(taskset2Test);
	suiteend();	
	
	do{
	  nop();
	} while(1);
	return 0;
}





































































