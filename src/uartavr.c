/**
 *  @file uartavr.c
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

#include "uartavr.h"

#include <util/setbaud.h>
#include <stdlib.h>

/*
void uart_init(void)
{
   UBRRH = UBRRH_VALUE;
   UBRRL = UBRRL_VALUE;
   // evtl. verkuerzt falls Register aufeinanderfolgen (vgl. Datenblatt)
   //   UBRR = UBRR_VALUE;

#if USE_2X
   // U2X-Modus erforderlich
   UCSRA |= (1 << U2X);
#else
   // U2X-Modus nicht erforderlich
   UCSRA &= ~(1 << U2X);
#endif

   // hier weitere Initialisierungen (TX und/oder RX aktivieren, Modus setzen
}  */


/* UART-Init Bsp. ATmega16 */

void uart_init(void)
{
  UBRRH = UBRR_VAL >> 8;
  UBRRL = UBRR_VAL & 0xFF;

  UCSRB |= (1<<TXEN);  // UART TX einschalten
  UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);  // Asynchron 8N1
}

/* ATmega16 */
int uart_putc(unsigned char c)
{
    while (!(UCSRA & (1<<UDRE)))  /* warten bis Senden moeglich */
    {
    }

    UDR = c;                      /* sende Zeichen */
    return 0;
}


/* puts ist unabhaengig vom Controllertyp */
void uart_puts (char *s)
{
    while (*s)
    {   /* so lange *s != '\0' also ungleich dem "String-Endezeichen(Terminator)" */
        uart_putc(*s);
        s++;
    }
}

void uart_putd(int intvalue)
{
    char strbuf[11];
    itoa(intvalue, strbuf, 10);
    uart_puts(strbuf);
}

void uart_puts_p(const char *str){
	while(pgm_read_byte(str) != '\0'){
		uart_putc(pgm_read_byte(str++));
	}
}



