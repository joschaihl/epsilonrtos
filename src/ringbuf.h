/**
 * @file ringbuf.h
 * @brief BESCHREIBUNG
 * @date 23.07.2015 12:40:28
 * @author Joscha Ihl <vision.josh@gmail.com>
 * @version 0.1
 *
 * Projekt: epsilonRTOS
 *
 *  This code is distributed under the GNU Public License
 *  which can be found at http://www.gnu.org/licenses/gpl.txt
 */

#ifndef RINGBUF_H_
#define RINGBUF_H_

#include "global.h"

/**
 *
 */
typedef struct
{
  unsigned char buffer[RINGBUFFER_SIZE];
  volatile unsigned int head;
  volatile unsigned int tail;
} RINGBUFFER;

// Initialize all elements in one shot
RINGBUFFER ringbuffer = { {0}, 0, 0 };

#endif /* RINGBUF_H_ */
