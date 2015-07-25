/**
 * @file ringbuf.c
 * @brief BESCHREIBUNG
 * @date 23.07.2015 12:40:06
 * @author Joscha Ihl <vision.josh@gmail.com>
 * @version 0.1
 *
 * Projekt: epsilonRTOS
 *
 *  This code is distributed under the GNU Public License
 *  which can be found at http://www.gnu.org/licenses/gpl.txt
 */

#include "ringbuf.h"

// Initialize all elements in one shot
RINGBUFFER ringbuffer = { {0}, 0, 0 };

u08 ringbufferWrite(u08 data)
{
  u08 result = 0;
  unsigned int next = (unsigned int)(ringbuffer.head + 1) % RINGBUFFER_SIZE;
  if (next != ringbuffer.tail)
  {
	  ringbuffer.buffer[ringbuffer.head] = data;
	  ringbuffer.head = next;
	  result = 1;
  }
  return (result);
}

u08 ringbufferRead(u08 *byte)
{
  u08 result = 0;
  // if the head isn't ahead of the tail, we don't have any characters
  if (ringbuffer.head == ringbuffer.tail) {
	  *byte = 0;        // quit with an error
  }
  else {

    *byte = ringbuffer.buffer[ringbuffer.tail];
    ringbuffer.tail = (unsigned int)(ringbuffer.tail + 1) % RINGBUFFER_SIZE;
    result = 1;
  }

  return(result);
}

u08 ringbufferFindPeak(void)
{
    u08 i;
    for(i=0;i<RINGBUFFER_SIZE;i++)
    {

	 }
}


