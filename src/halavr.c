/**
 *  @file halavr.c
 *  @brief Hardware Abstraktions Schicht für epsilon RTOS,
 *  	   um von mikrocontrollerspezifischen Funktionen
 *  	   zu abstrahieren.
 *  @author Joscha Ihl vision.josh@gmail.com
 *  @version 0.1
 *  @date 27.04.2015
 *
 *  Projekt     : EpsilonRTOS
 *
 *  This code is distributed under the GNU Public License
 *  which can be found at http://www.gnu.org/licenses/gpl.txt
 */
#include "halavr.h"
#include <stdint.h>
#include <avr/eeprom.h>

 /* Die Schleife dauert  4 * count + 3  Ticks */
/*void delayloop16 (unsigned int count)
{


    asm volatile ("1:"           "\n\t"
                  "sbiw %0,1"    "\n\t"
                  "brcc 1b"
                  : "+w" (count));
}*/

//void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
//{
	/* Wait for completion of previous write */
	//while(EECR & (1<<EEWE))
		;
	/* Set up address and data registers */
	//EEAR = uiAddress;
	//EEDR = ucData;
	/* Write logical one to EEMWE */
	//EECR |= (1<<EEMWE);
	/* Start eeprom write by setting EEWE */
	//EECR |= (1<<EEWE);
//}

//unsigned char EEPROM_read(unsigned int uiAddress)
//{
	/* Wait for completion of previous write */
	//while(EECR & (1<<EEWE))
	//;
	/* Set up address register */
	//EEAR = uiAddress;
	/* Start eeprom read by writing EERE */
	//EECR |= (1<<EERE);
	/* Return data from data register */
	//return EEDR;
//}





