#include "System.h"
#include "ucunit.h"

#include "kernel.h"

#define DEFAULTPORT PORTB
#define DEFAULTDDR DDRB
#define TASKAPIN PB0
#define TASKBPIN PB1
#define TASKCPIN PB2
#define TASKDPIN PB3
#define TASKEPIN PB4


static void Test_BasicChecksDemo(void)
{
    char * s = NULL;
    int a = 0;
    int b = 0;
    int c = 0;

    UCUNIT_TestcaseBegin("DEMO:Simple Checks");
    UCUNIT_CheckIsEqual( 0, a ); /* Pass*/
    UCUNIT_CheckIsEqual( 0, b ); /* Pass */
    UCUNIT_CheckIsEqual( 0, c ); /* Pass */

    UCUNIT_CheckIsEqual( 0, (1-1) ); /* Pass */
    UCUNIT_CheckIsEqual( 0, (-1+1) ); /* Pass */
    UCUNIT_CheckIsEqual( -1, (-2+1) ); /* Pass */

    UCUNIT_CheckIsNull(s); /* Pass */
    UCUNIT_TestcaseEnd();
}

static void Test_PointersDemo(void)
{
    char * s = NULL;

    UCUNIT_TestcaseBegin("DEMO:Checking pointers");

    UCUNIT_CheckIsNull(s); /* Pass */

    /* Empty string has a 0 byte/word as end of string */
    s = "";

    UCUNIT_CheckIsNotNull(s); /* Pass */
    UCUNIT_Check( (*s)=='\00' , "No end-of-string found","s" ); /* Pass */

    /* Check if first character of string "Hello World!\n" is a 'H' */
    s = "Hello World!\n";
    UCUNIT_CheckIsNotNull(s); /* Pass */
    UCUNIT_Check( (*s)=='H' , "String starts not with 'H'","s" ); /* Pass */

    UCUNIT_TestcaseEnd(); /* Pass */
}

static void Test_ChecklistDemo(void)
{
    int a = 0;
    int b = 0;
    int c = 0;

    UCUNIT_TestcaseBegin("DEMO:Checklists");

    /* Check if calculation works */
    a = 10;
    b = -20;
    c = a + b;

    UCUNIT_ChecklistBegin(UCUNIT_ACTION_WARNING);
    UCUNIT_CheckIsEqual( -10, c ); /* Pass */
    UCUNIT_CheckIsInRange(a,0,10); /* Pass */
    UCUNIT_CheckIsInRange(a,11,20); /* Fail */
    UCUNIT_CheckIsInRange(a,0,9); /* Fail */
    UCUNIT_ChecklistEnd();

    UCUNIT_TestcaseEnd(); /* Fail */
}

static void Test_BitChecksDemo(void)
{
    UCUNIT_TestcaseBegin("DEMO:Checking Bits");

    UCUNIT_CheckIsBitSet(0x0001, 0); /* Pass */
    UCUNIT_CheckIsBitSet(0x0000, 0); /* Fail */
    UCUNIT_CheckIsBitSet(0x0002, 1); /* Pass */
    UCUNIT_CheckIsBitSet(0x0000, 6); /* Fail */
    UCUNIT_CheckIsBitSet(0xFFFF, 6); /* Pass */

    UCUNIT_CheckIsBitClear(0x0001, 0); /* Fail */
    UCUNIT_CheckIsBitClear(0x0001, 1); /* Pass */

    UCUNIT_TestcaseEnd(); /* Fail */
}

static void Test_CheckTracepointsDemo(void)
{

    int found = FALSE;
    int i = 0;
    unsigned short a = 0;

    UCUNIT_TestcaseBegin("DEMO:Tracepoints");

    a = 0x1234;
    UCUNIT_ResetTracepointCoverage();
    UCUNIT_Tracepoint(0); /* Pass */
    UCUNIT_CheckIs8Bit(a); /* Fail */
    UCUNIT_CheckIs16Bit(a); /* Pass */
    UCUNIT_CheckIs32Bit(a); /* Pass */
    UCUNIT_Tracepoint(1); /* Pass */

    UCUNIT_CheckTracepointCoverage(0); /* Pass */
    UCUNIT_CheckTracepointCoverage(1); /* Pass */

    UCUNIT_ResetTracepointCoverage();
    for (i = 0; (i < 50) && (!found); i++)
    {
        if (i == 25)
        {
            UCUNIT_Tracepoint(0); /* Never executed */
            break;
        }

        if (i == 10)
        {
            UCUNIT_Tracepoint(1); /* Executed */
            found = TRUE;
        }

        if (i == 15)
        {
            UCUNIT_Tracepoint(2); /* Never executed */
            found = TRUE;
        }
    }

    UCUNIT_CheckTracepointCoverage(0); /* Fail  */
    UCUNIT_CheckTracepointCoverage(1); /* Pass */
    UCUNIT_CheckTracepointCoverage(2); /* Fail */

    UCUNIT_TestcaseEnd(); /* Fail */
}

void Testsuite_RunTests(void)
{
    Test_BasicChecksDemo();
    Test_PointersDemo();
    Test_ChecklistDemo();
    Test_BitChecksDemo();
    Test_CheckTracepointsDemo();

    UCUNIT_WriteSummary();
}


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
    UCUNIT_Init();
    UCUNIT_WriteString("\n**************************************");
    UCUNIT_WriteString("\nName:     ");
    UCUNIT_WriteString("uCUnit demo application");
    UCUNIT_WriteString("\nCompiled: ");
    UCUNIT_WriteString(__DATE__);
    UCUNIT_WriteString("\nTime:     ");
    UCUNIT_WriteString(__TIME__);
    UCUNIT_WriteString("\nVersion:  ");
    UCUNIT_WriteString(UCUNIT_VERSION);
    UCUNIT_WriteString("\n**************************************");
    Testsuite_RunTests();
    UCUNIT_Shutdown();

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














































