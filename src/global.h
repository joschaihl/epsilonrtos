
//*****************************************************************************
//
// File Name	: 'global.h'
// Title		: AVR project global include
// Author		: Pascal Stang
// Created		: 7/12/2001
// Revised		: 9/30/2002
// Version		: 1.1
// Target MCU	: Atmel AVR series
// Editor Tabs	: 4
//
//	Description : This include file is designed to contain items useful to all
//					code files and projects.
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************

#ifndef GLOBAL_H
#define GLOBAL_H

// global AVRLIB types definitions
#include "libtypes.h"


// CPU clock speed
//#define F_CPU        16000000                         // 16MHz processor
//#define F_CPU        14745000                         // 14.745MHz processor
#define F_CPU        8000000                            // 8MHz processor
//#define F_CPU        7372800                          // 7.37MHz processor
//#define F_CPU        4000000                          // 4MHz processor
//#define F_CPU        3686400                          // 3.69MHz processor

//#define UNITTEST_TESTS
#define RTOS_TESTS

#define CYCLES_PER_US ((F_CPU+500000)/1000000) 	// cpu cycles per microsecond

#define USE_TERMINAL
// Baudrate
//#define BAUD 9600
#define BAUD 250000

// Berechnungen
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))     // Reale Baudrate
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD) // Fehler in Promille, 1000 = kein Fehler.

#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
  #error Systematischer Fehler der Baudrate grösser 1% und damit zu hoch!
#endif

#endif






