/*
 * GR716 DAC configuration and setup
 *
 * Functions:
 *  1. gr716_dac_channel_enable  - Enable DAC Channel
 *  2. gr716_dac_channel_val     - Output DAC Data/Value
 *  3. gr716_dac_clear_irq       - Clear DAC interrupt
 *  4. gr716_dac_clk_enable      - Enable DAC UNIT Clock enable
 *  5. gr716_dac_channel_disable - Disable DAC Unit
 *  6. gr716_dac_clk_disable     - Disable DAC clock
 *  7. gr716_dac_disable_all     - Clear and Disable ALL DAC Units
 *  8. gr716_dac_int_map_set     - Remap DAC unit interrupt
 * 
*/

#include <bcc/bcc.h>

#ifndef __GR716_DAC_H_
#define __GR716_DAC_H_

/**** DAC Parameters and functions ****/

#define DAC_ENABLE 1
#define DAC_DISABLE 0

/* DAC configiuration register */
#define DDE_BIT   0
#define DDE_MASK  0x1
#define DDD_BIT   1
#define DDD_MASK  0x1
#define DDO_BIT   2
#define DDO_MASK  0x1
#define DDS_BIT   16
#define DDS_MASK  0xFFFF

/* DAC outregister register */
#define DDI_BIT   0
#define DDI_MASK  0xFFF

/* DAC sequence control register */
#define DSQ_BIT  31
#define DSQ_MASK 0x1

/* DAC sequence sync register */
#define DSYNC_BIT  0
#define DSYNC_MASK 0xF

/* DAC status register */
#define DWT_BIT   0
#define DWT_MASK  0x1

/* DAC interrupt register */
#define DEI_BIT   0
#define DEI_MASK  0x1

/* DAC mask register */
#define DEM_BIT   0
#define DEM_MASK  0x1

/*
 * Enable DAC Channel
 *
 * pin  : Select pin [0 - 63]
 *
 * return: BCC response
 * 
 * Todo: Add error checking
 * 
 */



/*
 * Enable DAC UNit
 *
 * aunit         : Select DAC unit {[0 - 3]}
 * mode          : Select DAC mode {normal, dem}
 * trigger       : Select trigger mode {none, enable}
 * source        : Select trigger source [0 - 47]
 * irqen         : generate interrupt  {none, enable, auto}
 * rate          : Set DAC sample rate [1*1000 Hz - 1000*1000 Hz]
 * freq          : System frequency [0 - 50*1000*1000 Hz]
 * val           : Default output value [0x0 - 0xFFF]
 * enable        : Output default value {none, enable}
 *
 * return: BCC response
 * 
 * Modes: 
 * 
 */

#define DAC_MODE_NOM         0x0
#define DAC_MODE_DEM         0x1

#define DAC_TRIGGER_NONE     0x0
#define DAC_TRIGGER_ENABLE   0x1

#define DAC_IRQ_NONE         0x0
#define DAC_IRQ_ENABLE       0x1

#define DAC_VAL_NONE         0x0
#define DAC_VAL_ENABLE       0x1

static uint32_t gr716_dac_channel_enable(uint32_t aunit,
                                         uint32_t mode, 
                                         uint32_t trigger, uint32_t source, uint32_t irqen,
                                         uint32_t rate, uint32_t freq,
                                         uint32_t val, uint32_t enable)
{
  /* DAC configiuration register */
  struct grdac_apb {
    volatile unsigned int  dcfg;    
    volatile unsigned int  dout;       
    volatile unsigned int  dseq;      
    volatile unsigned int  dsync;     
    volatile unsigned int  dstat;  
    volatile unsigned int  dint;  
    volatile unsigned int  dmask; 
  };

  // Workout scaler value i.e. ADC frequency for wanted sample rate
  unsigned int scaler;
  scaler = (freq / (2*rate));

  /* ADC Init */
  volatile struct grdac_apb *dacbase0 = (struct grdac_apb *) (DAC0_BASE + (aunit * 0x1000));
  
  // Config default DAC output
  // Setup DAC0 for single value output
  dacbase0->dcfg   = REGSET(dacbase0->dcfg, DDS, scaler);          // Set Scaler 
  dacbase0->dcfg   = REGSET(dacbase0->dcfg, DDD, mode);            // Without DEM mode  
  dacbase0->dseq   = REGSET(dacbase0->dseq, DSQ, trigger);         // Enable sync
  dacbase0->dsync  = source;                                       // Select timer 1 as trigger for new DAC update 
  dacbase0->dmask  = REGSET(dacbase0->dmask,DEM, irqen);           // Enable interrupt 
  dacbase0->dcfg   = REGSET(dacbase0->dcfg, DDO, enable);          // Output value from DAC  
  dacbase0->dout   = REGSET(dacbase0->dout, DDI, val);
  dacbase0->dcfg   = REGSET(dacbase0->dcfg, DDE, DAC_ENABLE);      // Enable DAC (Powerup DAC)
  return BCC_OK;

}

/*
 * Output DAC Data/Value
 *
 * aunit         : Select DAC unit {[0 - 3]}
 *
 * return: OK
 * 
 */

static uint32_t gr716_dac_channel_val(uint32_t aunit, uint32_t val)
{
  /* DAC configiuration register */
  struct grdac_apb {
    volatile unsigned int  dcfg;    
    volatile unsigned int  dout;       
    volatile unsigned int  dseq;      
    volatile unsigned int  dsync;     
    volatile unsigned int  dstat;  
    volatile unsigned int  dint;  
    volatile unsigned int  dmask; 
  };

  /* ADC Init */
  volatile struct grdac_apb *dac0_base = (struct grdac_apb *) (DAC0_BASE + (aunit * 0x1000));

  // Disable DAC Output
  dac0_base->dcfg   = REGSET(dac0_base->dcfg, DDO, 0x0);

  // Output new Value
  dac0_base->dout   = val;

  // Enable DAC Output
  dac0_base->dcfg   = REGSET(dac0_base->dcfg, DDO, 0x1);

  return BCC_OK;

}

/*
 * Clear DAC interrupt
 *
 * aunit         : Select DAC unit {[0 - 3]}
 *
 * return: OK
 * 
 */

static uint32_t gr716_dac_clear_irq(uint32_t aunit)
{
  /* DAC configiuration register */
  struct grdac_apb {
    volatile unsigned int  dcfg;    
    volatile unsigned int  dout;       
    volatile unsigned int  dseq;      
    volatile unsigned int  dsync;     
    volatile unsigned int  dstat;  
    volatile unsigned int  dint;  
    volatile unsigned int  dmask; 
  };

  /* ADC Init */
  volatile struct grdac_apb *dac0_base = (struct grdac_apb *) (DAC0_BASE + (aunit * 0x1000));

  // Clear DAC interrupt
  dac0_base->dint   = 0x1;

  return BCC_OK;

}

/*
 * Enable DAC UNIT Clock enable
 *
 * aunit         : Select DAC unit {[0 - 3]}
 *
 * return: OK
 * 
 */

static uint32_t gr716_dac_clk_enable(uint32_t aunit)
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
    
  if (aunit == 0) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDAC0, CG_UNLOCK);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRDAC0, CG_ENABLE);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRDAC0, CG_RELEASE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDAC0, CG_LOCK); 
  }

  if (aunit == 1) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDAC1, CG_UNLOCK);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRDAC1, CG_ENABLE);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRDAC1, CG_RELEASE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDAC1, CG_LOCK); 
  }

  if (aunit == 2) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDAC2, CG_UNLOCK);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRDAC2, CG_ENABLE);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRDAC2, CG_RELEASE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDAC2, CG_LOCK); 
  }

  if (aunit == 3) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDAC3, CG_UNLOCK);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRDAC3, CG_ENABLE);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRDAC3, CG_RELEASE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDAC3, CG_LOCK); 
  }

  return BCC_OK;

}

/*
 * Disable DAC Unit
 *
 * aunit         : Select DAC unit {[0 - 3]}
 *
 * return: BCC response
 * 
 */

static uint32_t gr716_dac_channel_disable(uint32_t aunit)
{

  /* DAC configiuration register */
  struct grdac_apb {
    volatile unsigned int  dcfg;    
    volatile unsigned int  dout;       
    volatile unsigned int  dseq;      
    volatile unsigned int  dsync;     
    volatile unsigned int  dstat;  
    volatile unsigned int  dint;  
    volatile unsigned int  dmask; 
  };

  /* DAC Init */
  volatile struct grdac_apb *dac0_base = (struct grdac_apb *) (DAC0_BASE + (aunit * 0x1000));

  // Disable DAC 0
  dac0_base->dcfg   = REGSET(dac0_base->dcfg, DDO, 0x0);
  dac0_base->dcfg   = REGSET(dac0_base->dcfg, DDE, 0x0); 

  return BCC_OK;

}

/*
 * Clock disable DAC Unit
 *
 * aunit         : Select DAC unit {[0 - 3]}
 *
 * return: BCC response
 * 
 */

static uint32_t gr716_dac_clk_disable(uint32_t aunit)
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

 if (aunit == 0) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDAC0, CG_UNLOCK);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRDAC0, CG_RESET);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRDAC0, CG_DISABLE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDAC0, CG_LOCK); 
  }

  if (aunit == 1) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDAC1, CG_UNLOCK);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRDAC1, CG_RESET);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRDAC1, CG_DISABLE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDAC1, CG_LOCK); 
  }

  if (aunit == 2) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDAC2, CG_UNLOCK);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRDAC2, CG_RESET);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRDAC2, CG_DISABLE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDAC2, CG_LOCK); 
  }

  if (aunit == 3) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDAC3, CG_UNLOCK);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRDAC3, CG_RESET);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRDAC3, CG_DISABLE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRDAC3, CG_LOCK); 
  }

  return BCC_OK;

}

/*
 * Clear and Disable ALL DAC Units
 *
 *
 * return: BCC response
 * 
 */

static uint32_t gr716_dac_disable_all(void)
{

  gr716_dac_clk_enable(0);
  gr716_dac_channel_disable(0);
  gr716_dac_clk_disable(0);

  gr716_dac_clk_enable(1);
  gr716_dac_channel_disable(1);
  gr716_dac_clk_disable(1);

  gr716_dac_clk_enable(2);
  gr716_dac_channel_disable(2);
  gr716_dac_clk_disable(2);

  gr716_dac_clk_enable(3);
  gr716_dac_channel_disable(3);
  gr716_dac_clk_disable(3);

  return BCC_OK;

}

/*
 * Remap DAC unit interrupt
 *
 *
 * return: BCC response
 * 
 */

static uint32_t gr716_dac_int_map_set(uint32_t aunit)
{
  int ret;
  if (aunit == 0) {
    ret = bcc_int_map_set(26,7);
  } else if (aunit == 1) {
    ret = bcc_int_map_set(27,7); 
  } else if (aunit == 2) {
    ret = bcc_int_map_set(36,7); 
  } else if (aunit == 3) {
    ret = bcc_int_map_set(37,7); 
  } else {
    //printf("Wrong DAC unit number. No interrupt remmaping \n");
    ret =  BCC_FAIL; /* Failure */
  }
  return ret;
};

#endif
