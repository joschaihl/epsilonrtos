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





