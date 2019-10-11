#include "../include/gr716/gr716.h"

int gr716_sram0_clock_enable(void) {

 // Clock gate and IO configuration registers
  struct gckcfg_apb {
   volatile unsigned int  unlock;
   volatile unsigned int  clocken;
   volatile unsigned int  reset;
   volatile unsigned int  override;
  };

  struct  gckcfg_apb *gckcfgbase0 = (struct gckcfg_apb *) (GRCLKGATE0_BASE);

  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_FTMCTRL, CG_UNLOCK);
  gckcfgbase0->clocken = REGSET(gckcfgbase0->clocken, CG_FTMCTRL, CG_ENABLE);
  gckcfgbase0->reset   = REGSET(gckcfgbase0->reset ,  CG_FTMCTRL, CG_RELEASE);
  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_FTMCTRL, CG_LOCK); 

  return 0;
}

/*
 * Disable clock for SRAM control unit 0
 *
 * return: ok
 * 
 */

int gr716_sram0_clock_disable(void) {

 // Clock gate and IO configuration registers
  struct gckcfg_apb {
   volatile unsigned int  unlock;
   volatile unsigned int  clocken;
   volatile unsigned int  reset;
   volatile unsigned int  override;
  };

  struct  gckcfg_apb *gckcfgbase0 = (struct gckcfg_apb *) (GRCLKGATE0_BASE);

  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_FTMCTRL, CG_UNLOCK);
  gckcfgbase0->reset   = REGSET(gckcfgbase0->reset ,  CG_FTMCTRL, CG_RESET);
  gckcfgbase0->clocken = REGSET(gckcfgbase0->clocken, CG_FTMCTRL, CG_DISABLE);
  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_FTMCTRL, CG_LOCK); 
  
  return 0;

}

/*
 * Write to memory location in SRAM control unit 0
 *
 * return: BCC_OK
 * 
 */

int gr716_sram0_write_data(int data, int offset) {

  /* Addr Pointer */
  volatile int *srambase0 = (int *) (SRAM_BASE + offset);
  
  *srambase0 = data;

  return BCC_OK;
}

/*
 * Read location in SRAM control unit 0
 *
 * return: read data
 * 
 */

int gr716_sram0_read_data(int offset) {

  /* Addr Pointer */
  volatile int *srambase0 = (int *) (SRAM_BASE + offset);

  return (int) *srambase0;
}

