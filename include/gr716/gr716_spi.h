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


#define SPI_ASEL_BIT      14
#define SPI_ASEL_MASK     0x1
#define SPI_ASELDEL_BIT   5
#define SPI_ASELDEL_MASK  0x1
#define SPI_IGSEL_BIT     2
#define SPI_IGSEL_MASK    0x1

  // Clock gate and IO configuration registers
  struct spictrl_apb {
    volatile unsigned int  cap0;
    volatile unsigned int  unused4;
    volatile unsigned int  unused8;
    volatile unsigned int  unusedC;
    volatile unsigned int  unused10;
    volatile unsigned int  unused14;
    volatile unsigned int  unused18;
    volatile unsigned int  unused1C;
    volatile unsigned int  mode;
    volatile unsigned int  event;
    volatile unsigned int  mask;
    volatile unsigned int  cmd;
    volatile unsigned int  tx;
    volatile unsigned int  rx;
    volatile unsigned int  slvsel;
    volatile unsigned int  aslvsel;
  };

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
