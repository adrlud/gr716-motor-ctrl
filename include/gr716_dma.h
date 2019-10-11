/*
 * GR716 DMA configuration and setup
 *
 * Functions:
 *  1. gr716_dma0_clk_enable      - Enable DMA0 interface
 *  2. gr716_dma0_clk_disable     - Disable DMA0 interface
 * 
*/

#include <bcc/bcc.h>

#ifndef __GR716_DMA_H_
#define __GR716_DMA_H_

/*
 * DMA0 Clock enable
 *
 *
 * return: OK
 * 
 */

static uint32_t gr716_dma0_clk_enable(void)
{

  // Clock gate and IO configuration registers
  struct gckcfg_apb {
   volatile unsigned int  unlock;
   volatile unsigned int  clocken;
   volatile unsigned int  reset;
   volatile unsigned int  override;
  };

  // Pointers to clock gate block
  struct  gckcfg_apb *gckcfgbase1 = (struct gckcfg_apb *) (GRCLKGATE1_BASE);
    
  gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDMA1, CG_UNLOCK);
  gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRDMA1, CG_ENABLE);
  gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRDMA1, CG_RELEASE);
  gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDMA1, CG_LOCK); 

  return BCC_OK;

}

/*
 * DMA0 clock disable
 *
 *
 * return: BCC response
 * 
 */

static uint32_t gr716_dma0_clk_disable(void)
{

  // Clock gate and IO configuration registers
  struct gckcfg_apb {
   volatile unsigned int  unlock;
   volatile unsigned int  clocken;
   volatile unsigned int  reset;
   volatile unsigned int  override;
  };

  // Pointers to clock gate block
  struct  gckcfg_apb *gckcfgbase1 = (struct gckcfg_apb *) (GRCLKGATE1_BASE);

  gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDMA0, CG_UNLOCK);
  gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRDMA0, CG_RESET);
  gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRDMA0, CG_DISABLE);
  gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDMA0, CG_LOCK); 

  return BCC_OK;

}

#endif
