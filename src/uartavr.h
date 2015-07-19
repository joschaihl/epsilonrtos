/**
 *  @file uartavr.h
 *  @brief Einfaches UART für Testing- und Debugging Ausgaben bei epsilonRTOS.
 *  	   Implementierungsbeispiele von mikrocontroller.net.
 *  @author Joscha Ihl vision.josh@gmail.com
 *  @version 0.1
 *  @date 18.07.2015
 *
 *  Projekt     : EpsilonRTOS
 *
 *  This code is distributed under the GNU Public License
 *  which can be found at http://www.gnu.org/licenses/gpl.txt
 */

#ifndef UART_H
#define UART_H

#include <avr/pgmspace.h>
#include "global.h"
void uart_init(void);
int uart_putc(unsigned char c);
void uart_puts (char *s);
void uart_puts_p(const char *str);
void uart_putd(int value);

#endif // UART_H





