#include <gr716/gr716.h>

int gr716_spi0_clock_enable(void)
{


  struct  gckcfg_apb *gckcfgbase0 = (struct gckcfg_apb *) (GRCLKGATE0_BASE);
  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_SPICTRL0, CG_UNLOCK);
  gckcfgbase0->clocken = REGSET(gckcfgbase0->clocken, CG_SPICTRL0, CG_ENABLE);
  gckcfgbase0->reset   = REGSET(gckcfgbase0->reset ,  CG_SPICTRL0, CG_RELEASE);
  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_SPICTRL0, CG_LOCK); 
  return 0;
}

/*
 * Set slave select for SPI control unit 0
 * 
 */

int gr716_spi0_slave_select(uint32_t mask)
{

  // Pointers to Clock gate and IO configuration registers
  struct  spictrl_apb *spictrlbase0 = (struct spictrl_apb *) (SPICTRL0_BASE);
  /* Slave select is active-low */
  spictrlbase0->slvsel = ~mask;
  return 0;
}

/*
 * Set Auto slave select for SPI control unit 0
 * 
 */

int gr716_spi0_automatic_slave_select(uint32_t mask)
{
  // Pointers to Clock gate and IO configuration registers
  struct  spictrl_apb *spictrlbase0 = (struct spictrl_apb *) (SPICTRL0_BASE);

  /* Slave select is active-low */
  spictrlbase0->aslvsel = ~mask;

  spictrlbase0->mode   = REGSET(spictrlbase0->mode, SPI_ASEL    , 1);
  spictrlbase0->mode   = REGSET(spictrlbase0->mode, SPI_ASELDEL , 0);
  spictrlbase0->mode   = REGSET(spictrlbase0->mode, SPI_IGSEL   , 0);

  return 0;
}

/*
 * Wait for TIP low
 *
 * return: ok
 * 
 */

int gr716_wait_for_tip_low(void)
{

  // Pointers to Clock gate and IO configuration registers
  struct  spictrl_apb *spictrlbase0 = (struct spictrl_apb *) (SPICTRL0_BASE);
  int event;
  event = spictrlbase0->event & 0x80000000;
  do {
   // Check status  
   event = spictrlbase0->event & 0x80000000;
  } while (event!=0);

  return 0;
}

/*
 * Wait for TIP high
 *
 * return: ok
 * 
 */

int gr716_wait_for_tip_high(void)
{


  // Pointers to Clock gate and IO configuration registers
  struct  spictrl_apb *spictrlbase0 = (struct spictrl_apb *) (SPICTRL0_BASE);
  int event;
  event = spictrlbase0->event & 0x80000000;
  do {
   // Check status  
   event = spictrlbase0->event & 0x80000000;
  } while (event==0);

  return 0;
}

/*
 * Ignore SPISEL input( Mainly when acting as master)
 *
 * return: 0
 * 
 */
int gr716_spi0_ignore_spi_select()
{
  // Pointers to Clock gate and IO configuration registers
  struct  spictrl_apb *spictrlbase0 = (struct spictrl_apb *) (SPICTRL0_BASE);

  /* ignore spi sel(GR716 is master) */
  spictrlbase0->mode   = REGSET(spictrlbase0->mode, SPI_IGSEL   , 1);

  return 0;
}