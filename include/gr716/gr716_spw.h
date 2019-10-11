/*
 * GR716 SpaceWire configuration and setup
 *
 * Functions:
 *  1. gr716_spw_clk_enable      - Enable SPW interface
 *  2. gr716_spw_clk_disable     - Disable SPW interface
 * 
*/

#include <bcc/bcc.h>

#ifndef __GR716_SPW_H_
#define __GR716_SPW_H_

/*
 * SPW Clock enable
 *
 *
 * return: OK
 * 
 */

static uint32_t gr716_spw_clk_enable(void)
{

  // Clock gate and IO configuration registers
  struct gckcfg_apb {
   volatile unsigned int  unlock;
   volatile unsigned int  clocken;
   volatile unsigned int  reset;
   volatile unsigned int  override;
  };

  // Pointers to clock gate block
  struct  gckcfg_apb *gckcfgbase0 = (struct gckcfg_apb *) (GRCLKGATE0_BASE);
    
  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_SPW, CG_UNLOCK);
  gckcfgbase0->clocken = REGSET(gckcfgbase0->clocken, CG_SPW, CG_ENABLE);
  gckcfgbase0->reset   = REGSET(gckcfgbase0->reset ,  CG_SPW, CG_RELEASE);
  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_SPW, CG_LOCK); 

  return BCC_OK;

}

/*
 * SPW clock disable
 *
 *
 * return: BCC response
 * 
 */

static uint32_t gr716_spw_clk_disable(void)
{

  // Clock gate and IO configuration registers
  struct gckcfg_apb {
   volatile unsigned int  unlock;
   volatile unsigned int  clocken;
   volatile unsigned int  reset;
   volatile unsigned int  override;
  };

  // Pointers to clock gate block
  struct  gckcfg_apb *gckcfgbase0 = (struct gckcfg_apb *) (GRCLKGATE0_BASE);

  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_SPW, CG_UNLOCK);
  gckcfgbase0->reset   = REGSET(gckcfgbase0->reset ,  CG_SPW, CG_RESET);
  gckcfgbase0->clocken = REGSET(gckcfgbase0->clocken, CG_SPW, CG_DISABLE);
  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_SPW, CG_LOCK); 

  return BCC_OK;

}

#endif
