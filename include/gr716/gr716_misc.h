/*
 * GR716 Misc functions
 *
 * Functions:
 *  1. gr716_wait_cycles           - Wait using counter (CPU in active mode)
 *  2. gr716_sleep_10ms            - Wait using GPTIMER (CPU in sleep mode)
 * 
*/
#include <bcc/bcc.h>

#ifndef __GR716_MISC_H_
#define __GR716_MISC_H_

/* This function waits specified number of itterations. */
int gr716_wait_cycles(uint32_t wait_event);

/* This function waits "duration x 10 microseconds". */
void gr716_sleep_10ms(uint32_t duration);

#endif
