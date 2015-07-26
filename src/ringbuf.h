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
  u08 buffer[RINGBUFFER_SIZE];
  volatile u16 head;
  volatile u16 tail;
} RINGBUFFER;



u08 ringbufferWrite(u08 data);
u08 ringbufferRead(u08 *byte);
/* u08 ringbufferFindPeak(void); */

#endif /* RINGBUF_H_ */





