/*
 * GR716 BrownOut configuration and setup
 *
* Functions:
 *  1. gr716_bo_enable_all      - Enable BrownOut
 *  2. gr716_bo_disable_all     - Disable BrownOut

 * 
*/

#include <bcc/bcc.h>

#ifndef __GR716_BO_H_
#define __GR716_BO_H_

/**** BO Parameters and functions ****/

#define BLI_BIT         18
#define BLC_BIT         15
#define BLA_BIT         12
#define BLD_BIT         9
#define BLB_BIT         6
#define BLL_BIT         3
#define BLP_BIT         0
#define BLI_MASK        0x7
#define BLC_MASK        0x7
#define BLA_MASK        0x7
#define BLD_MASK        0x7
#define BLB_MASK        0x7
#define BLL_MASK        0x7
#define BLP_MASK        0x7

#define BI_BIT          6 
#define BC_BIT          5 
#define BA_BIT          4 
#define BD_BIT          3 
#define BB_BIT          2 
#define BL_BIT          1 
#define BP_BIT          0
#define BI_MASK         0x1 
#define BC_MASK         0x1 
#define BA_MASK         0x1 
#define BD_MASK         0x1 
#define BB_MASK         0x1 
#define BL_MASK         0x1 
#define BP_MASK         0x1

#define TRM_BIT         0
#define TRM_MASK        0x7 

#define LDO_TRIM_0V     0x0
#define LDO_TRIM_22V    0x1
#define LDO_TRIM_44V    0x2
#define LDO_TRIM_66V    0x3
#define LDO_TRIM_m88V   0x4
#define LDO_TRIM_m66V   0x5
#define LDO_TRIM_m44V   0x6
#define LDO_TRIM_m22V   0x7

static uint32_t gr716_bo_enable_all(void)
{

  // Clock gate and IO configuration registers
  struct bo_apb {
   volatile unsigned int  cfg;
   volatile unsigned int  sts;
   volatile unsigned int  irq;
   volatile unsigned int  msk;
   volatile unsigned int  ldotrim;
   volatile unsigned int  vdel;
   volatile unsigned int  vpd;
   volatile unsigned int  unused;
   volatile unsigned int  xen;
   volatile unsigned int  bdi;
  };

  // Reset Generation, LDO trim and Brownout Detection registers
  struct gckcfg_apb {
   volatile unsigned int  unlock;
   volatile unsigned int  clocken;
   volatile unsigned int  reset;
   volatile unsigned int  override;
  };

  // Pointers to Clock gate and IO configuration registers
  struct  bo_apb *bobase0 = (struct bo_apb *) (BO_BASE);

  // Pointers to clock gate block
  struct  gckcfg_apb *gckcfgbase0 = (struct gckcfg_apb *) (GRCLKGATE0_BASE);

  // Enable BO control register clock
  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_ASUP, CG_UNLOCK);
  gckcfgbase0->clocken = REGSET(gckcfgbase0->clocken, CG_ASUP, CG_ENABLE);
  gckcfgbase0->reset   = REGSET(gckcfgbase0->reset,   CG_ASUP, CG_RELEASE);
  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_ASUP, CG_LOCK);  

  // Powerdown Brown Detectors
  bobase0->vpd  = REGSET(bobase0->vpd,  BI, 1);
  bobase0->vpd  = REGSET(bobase0->vpd,  BL, 1); 
  bobase0->vpd  = REGSET(bobase0->vpd,  BB, 1);
  bobase0->vpd  = REGSET(bobase0->vpd,  BD, 1); 
  bobase0->vpd  = REGSET(bobase0->vpd,  BA, 1); 
  bobase0->vpd  = REGSET(bobase0->vpd,  BC, 1); 
  bobase0->vpd  = REGSET(bobase0->vpd,  BI, 1);

  int event;
  event = 0;
  do {
   // Wait  
   event = event + 1;
  } while (event < 1000);

  // Re-enable Brown Detectors
  bobase0->vpd  = REGSET(bobase0->vpd,  BI, 0);
  bobase0->vpd  = REGSET(bobase0->vpd,  BL, 0); 
  bobase0->vpd  = REGSET(bobase0->vpd,  BB, 0);
  bobase0->vpd  = REGSET(bobase0->vpd,  BD, 0); 
  bobase0->vpd  = REGSET(bobase0->vpd,  BA, 0); 
  bobase0->vpd  = REGSET(bobase0->vpd,  BC, 0); 
  bobase0->vpd  = REGSET(bobase0->vpd,  BI, 0);

  // Check Status register
  if ((bobase0->sts & 0xFF) == 0) {
     return BCC_OK;
  } else {
     //printf("Brownout Detection status register error \n");
     return BCC_FAIL;
  }

}

static uint32_t gr716_bo_disable_all(void)
{

  // Clock gate and IO configuration registers
  struct bo_apb {
   volatile unsigned int  cfg;
   volatile unsigned int  sts;
   volatile unsigned int  irq;
   volatile unsigned int  msk;
   volatile unsigned int  ldotrim;
   volatile unsigned int  vdel;
   volatile unsigned int  vpd;
   volatile unsigned int  unused;
   volatile unsigned int  xen;
   volatile unsigned int  bdi;
  };

  // Reset Generation, LDO trim and Brownout Detection registers
  struct gckcfg_apb {
   volatile unsigned int  unlock;
   volatile unsigned int  clocken;
   volatile unsigned int  reset;
   volatile unsigned int  override;
  };

  // Pointers to Clock gate and IO configuration registers
  struct  bo_apb *bobase0 = (struct bo_apb *) (BO_BASE);

  // Pointers to clock gate block
  struct  gckcfg_apb *gckcfgbase0 = (struct gckcfg_apb *) (GRCLKGATE0_BASE);

  // Enable BO control register clock
  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_ASUP, CG_UNLOCK);
  gckcfgbase0->clocken = REGSET(gckcfgbase0->clocken, CG_ASUP, CG_ENABLE);
  gckcfgbase0->reset   = REGSET(gckcfgbase0->reset,   CG_ASUP, CG_RELEASE);

  // Powerdown Brown Detectors
  bobase0->vpd  = REGSET(bobase0->vpd,  BI, 1);
  bobase0->vpd  = REGSET(bobase0->vpd,  BL, 1); 
  bobase0->vpd  = REGSET(bobase0->vpd,  BB, 1);
  bobase0->vpd  = REGSET(bobase0->vpd,  BD, 1); 
  bobase0->vpd  = REGSET(bobase0->vpd,  BA, 1); 
  bobase0->vpd  = REGSET(bobase0->vpd,  BC, 1); 
  bobase0->vpd  = REGSET(bobase0->vpd,  BI, 1);

  // Disable BO control register clock
  gckcfgbase0->reset   = REGSET(gckcfgbase0->reset,   CG_ASUP, CG_RESET);
  gckcfgbase0->clocken = REGSET(gckcfgbase0->clocken, CG_ASUP, CG_DISABLE);
  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_ASUP, CG_LOCK); 

  return BCC_OK;
}

#endif
