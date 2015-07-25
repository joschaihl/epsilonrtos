/**
 *  @file hal.h
 *  @brief Hardware Abstraktions Schicht für epsilon RTOS,
 *  	   um von mikrocontrollerspezifischen Funktionen
 *  	   zu abstrahieren.
 *  @author Joscha Ihl vision.josh@gmail.com
 *  @version 0.1
 *
 *  Projekt     : EpsilonRTOS
 *
 *  This code is distributed under the GNU Public License
 *  which can be found at http://www.gnu.org/licenses/gpl.txt
 */

#ifndef HAL_H_
#define HAL_H_
#include "global.h"

#ifdef MCU_AVR
#include "halavr.h"
#endif

#endif /* HAL_H_ */



