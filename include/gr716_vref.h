/*
 * GR716 VREF configuration and setup
 *
 * Functions:
 *  1. gr716_enable_vref_buf      - Enable VREFBUF
 *  2. gr716_disable_vref_buf     - Disable VREFBUF
 * 
*/

#include <bcc/bcc.h>

#ifndef __GR716_VREF_H_
#define __GR716_VREF_H_

/*
 * Enable VREFBUF
 *
 * return: BCC response
 * 
 */

#define VREFEN_BIT   20
#define VREFEN_MASK  0x1

static uint32_t gr716_enable_vref_buf(void)
{

  /*  Interrupt test configuration register */
  struct scfg_apb {
    volatile unsigned int  scfg;    
  };

  /* DAC Init */
  volatile struct scfg_apb *scfg_base = (struct scfg_apb *) SYS_CFG_CONF_BASE;

  // Enable VREFBUF
  scfg_base->scfg   = REGSET(scfg_base->scfg, VREFEN, 0x1);

  return BCC_OK;

}

/*
 * Disable VREFBUF
 *
 * return: BCC response
 * 
 */

#define VREFEN_BIT   20
#define VREFEN_MASK  0x1

static uint32_t gr716_disable_vref_buf(void)
{

  /*  Interrupt test configuration register */
  struct scfg_apb {
    volatile unsigned int  scfg;    
  };

  /* DAC Init */
  volatile struct scfg_apb *scfg_base = (struct scfg_apb *) SYS_CFG_CONF_BASE;

  // Enable VREFBUF
  scfg_base->scfg   = REGSET(scfg_base->scfg, VREFEN, 0);

  return BCC_OK;

}

#endif
