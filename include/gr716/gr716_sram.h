/*
 * GR716 SRAM configuration and setup
 *
 * Functions:
 *  1. gr716_sram0_clock_enable           - Enable clock for SRAM control unit 0
 *  2. gr716_sram0_clock_disable          - Enable disable for SRAM control unit 0
 *  3. gr716_sram0_write_data
 *  4. gr716_sram0_read_data 
 * 
*/

#include <bcc/bcc.h>

#ifndef __GR716_SRAM_H_
#define __GR716_SRAM_H_





/*
 * Enable clock for SRAM control unit 0
 *
 * return: ok
 * 
 */

int gr716_sram0_clock_enable(void);
/*
 * Disable clock for SRAM control unit 0
 *
 * return: ok
 * 
 */

int gr716_sram0_clock_disable(void);


/*
 * Write to memory location in SRAM control unit 0
 *
 * return: BCC_OK
 * 
 */

int gr716_sram0_write_data(int data, int offset);

/*
 * Read location in SRAM control unit 0
 *
 * return: read data
 * 
 */

int gr716_sram0_read_data(int offset);

#endif
