/*
 * GR716 CAN configuration and setup
 *
 * Functions:
 *  1. gr716_can0_clk_enable      - Enable CAN0 interface
 *  2. gr716_can0_clk_disable     - Disable CAN0 interface
 * 
*/

#include <bcc/bcc.h>

#ifndef __GR716_CAN_H_
#define __GR716_CAN_H_

/*
 * CAN0 Clock enable
 *
 *
 * return: OK
 * 
 */

static uint32_t gr716_can0_clk_enable(void)
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
    
  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_CAN0, CG_UNLOCK);
  gckcfgbase0->clocken = REGSET(gckcfgbase0->clocken, CG_CAN0, CG_ENABLE);
  gckcfgbase0->reset   = REGSET(gckcfgbase0->reset ,  CG_CAN0, CG_RELEASE);
  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_CAN0, CG_LOCK); 

  return BCC_OK;

}

/*
 * CAN0 clock disable
 *
 *
 * return: BCC response
 * 
 */

static uint32_t gr716_can0_clk_disable(void)
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

  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_CAN0, CG_UNLOCK);
  gckcfgbase0->reset   = REGSET(gckcfgbase0->reset ,  CG_CAN0, CG_RESET);
  gckcfgbase0->clocken = REGSET(gckcfgbase0->clocken, CG_CAN0, CG_DISABLE);
  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_CAN0, CG_LOCK); 

  return BCC_OK;

}

#endif
