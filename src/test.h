/*
 * test.h
 *
 *  Created on: 18.07.2015
 *      Author: joscha
 */

#ifndef TEST_H_
#define TEST_H_
#include "hal.h"

extern u08 errors;
extern u08 runs;
extern u08 expected_runs;
extern u08 gerrors;
extern u08 gruns;
extern u08 tracepoint;

void suite(void);		
void suiteend(void);

#define setTracepoint(TRACEPOINT) \
	tracepoint=TRACEPOINT
	
void checkTracepoint(u08 ptracepoint);	



typedef enum {LOWER_THAN = 0, LOWER_EQUAL_THAN = 1,
	EQUALS = 2, GREATER_EQUAL_THAN = 3, GREATER_THAN = 4} COMPARE_OPERATION;

void assertion(const char *file, int line, int expected, int current, COMPARE_OPERATION compare_operator);

#define assertLower(EXPECTED,CURRENT) \
		  assertion(PSTR(__FILE__), __LINE__, EXPECTED, CURRENT, LOWER_THAN);

#define assertLowerEqual(EXPECTED,CURRENT) \
		  assertion(PSTR(__FILE__), __LINE__, EXPECTED, CURRENT, LOWER_EQUAL_THAN);
		
#define assertEquals(EXPECTED,CURRENT) \
		  assertion(PSTR(__FILE__), __LINE__, EXPECTED, CURRENT, EQUALS);
		
#define assertGreaterEqual(EXPECTED,CURRENT) \
		  assertion(PSTR(__FILE__), __LINE__, EXPECTED, CURRENT, GREATER_EQUAL_THAN);		

#define assertGreater(EXPECTED,CURRENT) \
		  assertion(PSTR(__FILE__), __LINE__, EXPECTED, CURRENT, GREATER_THAN);

#define TEST(NAME) \
		  void test_ ## NAME(void); \
		  void test_ ## NAME(void)


#define RUN(NAME) \
		  	uart_puts_p(PSTR(" * Running Test ")); \
		  	uart_puts_p(PSTR(#NAME "\n")); \
		  	gerrors += errors; \
		  	gruns += runs; \
		  	errors = 0; \
		  	runs = 0; \
		  	test_ ## NAME();



#endif /* TEST_H_ */










