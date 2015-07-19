/*
 * test.c
 *
 *  Created on: 18.07.2015
 *      Author: joscha
 */

#include "test.h"
#include "libtypes.h"

u08 errors = 0;
u08 runs = 0;
u08 expected_runs = 0;
u08 gerrors = 0;
u08 gruns = 0;
u08 tracepoint = 0;


void suite(void)
{
		  errors = 0;
		  gerrors = 0;
		  runs = 0;
		  gruns = 0;
		  expected_runs = 0;
		  uart_puts_p(PSTR("---===### Testsuite ###===---\n"));
}

void suiteend(void)
{
		  gerrors += errors;
		  gruns += runs;
		  uart_puts_p(PSTR("---===#### RESULTS ####===---\nErrors="));
		  uart_putd(gerrors);
		  uart_puts_p(PSTR("\nExpected "));
		  uart_putd(expected_runs);
		  uart_puts_p(PSTR(" runs of "));
		  uart_putd(gruns);
		  uart_puts_p(PSTR("\n----- Finished Testsuite ----\n"));
}

void checkTracepoint(u08 ptracepoint)
{
	expected_runs++;
	if(errors==0)
	{
		runs++;
  		uart_puts_p(PSTR("Checking Tracepoint "));
   	uart_putd(tracepoint);
   	uart_puts_p(PSTR("... "));	
		if(tracepoint==ptracepoint)
		{
			uart_puts_p(PSTR("OK\n"));
		}
		else
		{
			errors++;
			uart_puts_p(PSTR("Failure\n"));
		}
	}
}

void assertion(const char *file, int line, int expected, int current, COMPARE_OPERATION compare_operator)
{
   BOOL result = 0;
	expected_runs++;
	if(errors==0) {
		 runs++;
		 uart_puts_p(PSTR(" * "));
		 uart_puts_p(file);
		 uart_putc(':');
       uart_putd(line);

       switch(compare_operator) {
          case LOWER_THAN:
             uart_puts_p(PSTR(" assertLower("));
             if(expected<current)
             	result = 1;
             break;
          case LOWER_EQUAL_THAN:
          	 uart_puts_p(PSTR(" assertLowerEqual("));
             if(expected<=current)
               result = 1;
             break;
          case EQUALS:
             uart_puts_p(PSTR(" assertEquals("));
             if(expected==current)
               result = 1;
             break;
          case GREATER_EQUAL_THAN:
          	 uart_puts_p(PSTR(" assertGreaterEqual("));
             if(expected>=current)
               result = 1;
             break;
          case GREATER_THAN:
             uart_puts_p(PSTR(" assertGreater("));
             if(expected>current)
               result = 1;
		 }
		
		
       uart_putd(expected);
       uart_puts_p(PSTR(","));
       uart_putd(current);
       uart_puts_p(PSTR(")... "));
       if(result)
       {
       	uart_puts_p(PSTR("OK\n"));      	
       }
       else
       {
        	   uart_puts_p(PSTR("Failure\n"));
           errors++;
       	    uart_puts_p(PSTR("Tests aborted because of "));
           uart_putd(errors);
           uart_puts_p(PSTR(" ERRORS\n"));
       }
   }
}






