/*
 * GR716 SPI configuration and setup
 *
 * Functions:
 *  1. gr716_spi0_clock_enable           - Enable clock for SPI control unit 0
 *  2. gr716_spi0_slave_select           - Set slave select for SPI control unit 0
 *  3. gr716_spi0_automatic_slave_select - Set Auto slave select for SPI control unit 0
 *  3. gr716_wait_for_tip_low            - Wait for TIP low
 *  4. gr716_wait_for_tip_high           - Wait for TIP High
 * 
*/

#include <bcc/bcc.h>

#ifndef __GR716_SPI_H_
#define __GR716_SPI_H_

/*
 * Enable clock for SPI control unit 0
 *
 * return: ok
 * 
 */

int gr716_spi0_clock_enable(void);

/*
 * Set slave select for SPI control unit 0
 *
 * return: ok
 * 
 */

int gr716_spi0_slave_select(uint32_t mask);

/*
 * Set Auto slave select for SPI control unit 0
 *
 * return: ok
 * 
 */

int gr716_spi0_automatic_slave_select(uint32_t mask);

/*
 * Wait for TIP low
 *
 * return: ok
 * 
 */

int gr716_wait_for_tip_low(void);
/*
 * Wait for TIP high
 *
 * return: ok
 * 
 */

int gr716_wait_for_tip_high(void);


/*
 * Ignore SPISEL input( Mainly when acting as master)
 *
 * return: 0
 * 
 */
int gr716_spi0_ignore_spi_select();


#endif
