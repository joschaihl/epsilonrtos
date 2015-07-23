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

void ringbufferStore(unsigned char data)
{
  unsigned int next = (unsigned int)(ringbuffer.head + 1) % RINGBUFFER_SIZE;
  if (next != ringbuffer.tail)
  {
	  ringbuffer.buffer[ringbuffer.head] = data;
	  ringbuffer.head = next;
  }
}

char ringbufferRead(void)
{
  char result;
  // if the head isn't ahead of the tail, we don't have any characters
  if (ringbuffer.head == ringbuffer.tail) {
	  result = -1;        // quit with an error
  }
  else {
    result = ringbuffer.buffer[ringbuffer.tail];
    ringbuffer.tail = (unsigned int)(ringbuffer.tail + 1) % RINGBUFFER_SIZE;
  }

  return(result);
}

