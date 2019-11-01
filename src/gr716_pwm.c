#include <gr716/gr716.h>
#include <bldc/bldc.h>

/* PWM Core control register */
#define CEN_BIT   0     // PWM Core enable
#define CEN_MASK  0x1
#define DIS_BIT   1 
#define DIS_MASK  0x1   // Select Enable or Disable mode
#define NOUP_BIT  12
#define NOUP_MASK 0xFF
#define PEN_BIT   20     // Enable/Disable of PWMs
#define PEN_MASK  0xFF

/* PWM SCALER register */
#define PRELOAD_BIT   0 
#define PRELOAD_MASK  0xFFFF

/* PWM Interrupt pending register */
#define PIRQ_BIT   0 
#define PIRQ_MASK  0xFF

/* PWM Period register */
#define PER_BIT   0 
#define PER_MASK  0xFFFF

/* PWM Compare register */
#define COMP1_BIT   0 
#define COMP1_MASK  0xFFFF
#define COMP2_BIT   16 
#define COMP2_MASK  0xFFFF

/* PWM Dead Band register */
#define DBCOMP_BIT   0 
#define DBCOMP_MASK  0xFFFF

/* PWM Core control register */
#define PWMEN_BIT       0      // PWM enable/disable bit. 0b0 = PWM is disabled. 0b1 = PWM is enabled. 
#define PWMEN_MASK      0x1
#define POL_BIT         1      // PWM polarity select bit. 0b0 = PWM is active low, 0b1 = PWM is active high
#define POL_MASK        0x1
#define PAIR_BIT        2      // PWM pair bit. If this bit is set to 0b1 a complement output for this PWM will be generated, creating a PWM pair instead of a single PWM. 
#define PAIR_MASK       0x1
#define FIX_BIT         3      // PWM fix value select bits. 
#define FIX_MASK        0x7
#define METH_BIT        6      // PWM generation method select bit
#define METH_MASK       0x1
#define PAIRZ_BIT       7      // when pair and par_zero are set the complementary output is driven to 0
#define PAIRZ_MASK      0x1
#define DCEN_BIT        8      // Dual compare mode enable
#define DCEN_MASK       0x1
#define WEN_BIT         9      // Waveform PWM enable
#define WEN_MASK        0x1
#define SCALERSEL_BIT   10     //  Scaler select bits
#define SCALERSEL_MASK  0x7
#define IRQEN_BIT       13     // Interrupt enable/disable bit. 0b0 = Interrupt is disabled. 0b1 = Interrupt is enabled
#define IRQEN_MASK      0x1
#define IRQT_BIT        14     // Interrupt type. 0b0 = Generate interrupt on PWM period match. 0b1 = Generate interrupt on PWM compare match.
#define IRQT_MASK       0x1
#define IRQSCALER_BIT   15     // Interrupt scaler
#define IRQSCALER_MASK  0x3F
#define DBEN_BIT        21     // Dead band enable.
#define DBEN_MASK       0x1
#define DSCALER_BIT     22     // Dead band scaler.
#define DSCALER_MASK    0xF
#define FLIP_BIT        26     // Output flip bit
#define FLIP_MASK       0x1
#define COMP2EN_BIT     27     // Enable 2 compare points
#define COMP2EN_MASK    0x1
#define IDLE_BIT        28     // Idle Sync enable 
#define IDLE_MASK       0x1
#define TICKCFG_BIT     30     // Configiuration of trigger events 01b = Comapre point 1 10b = compare point2 
#define TICKCFG_MASK    0x3


uint32_t gr716_pwm0_config(uint32_t nbr,
                                  uint32_t mode,  uint32_t meth,     uint32_t trigger, uint32_t scaler,
                                  uint32_t irqen, uint32_t iscaler,  uint32_t pair,    uint32_t polarity,
                                  uint32_t flip,  uint32_t deadband, uint32_t dbscaler,
                                  uint32_t period,
                                  uint32_t comp1, uint32_t comp2,
                                  uint32_t dcompx)
{

  /* PWM Unit: a bit ugly but does the job */
  volatile struct grpwm_apb *pwmbase0 = (struct grpwm_apb *) (GRPWM0_BASE + (nbr * 0x10));

  // Always disable
  pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   PWMEN,   0x0);

  pwmbase0->period0 = REGSET(pwmbase0->period0,   PER,     period);

  pwmbase0->pcomp0   = REGSET(pwmbase0->pcomp0,   COMP1,   comp1);
  pwmbase0->pcomp0   = REGSET(pwmbase0->pcomp0,   COMP2,   comp2);

  pwmbase0->pdead0   = REGSET(pwmbase0->pdead0,   DBCOMP,  dcompx);


  pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   IRQT,    0x1); 
  pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   IRQEN,   0x1); 
  pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   PAIR,    0x1); 
  pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   COMP2EN, 0x1); 
  pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   TICKCFG, 0x1); 

  pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   POL,    polarity); 

  if (pair == PWM_PAIR_ZERO) {
    pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   PAIR,     1);
    pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   PAIRZ,    1);
  } else {
    pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   PAIR,     pair);
    pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   PAIRZ,    0);
  }

  pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   METH,    meth); 

  if (mode == PWM_MODE_ONECOMP) {
    pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   DCEN,    0); 
    pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   COMP2EN, 0); 
  } else if (mode == PWM_MODE_DUALCOMP) {
    pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   DCEN,    1); 
    pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   COMP2EN, 0); 
  } else {
    pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   DCEN,    0); 
    pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   COMP2EN, 1); 
  }

  if (irqen == PWM_IRQ_NONE) {
    pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   IRQEN,   0); 
    pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   IRQT,    0); 
  } else if (irqen == PWM_IRQ_ENABLE) {
    pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   IRQEN,   1); 
    pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   IRQT,    0); 
  } else {
    pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   IRQEN,   1); 
    pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   IRQT,    1); 
  }

  pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   DBEN,   deadband);

  pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   IRQSCALER,   iscaler);
  pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   DSCALER,     dbscaler);
  pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   SCALERSEL,   scaler);

  pwmbase0->pctrl0   = REGSET(pwmbase0->pctrl0,   TICKCFG,      trigger); 

  return BCC_OK;
}

/*
 * PWM0 Update
 * 
 */

uint32_t gr716_pwm0_comp_update(uint32_t nbr, uint32_t comp1, uint32_t comp2)
{

  /* PWM Unit: a bit ugly but does the job */
  volatile struct grpwm_apb *pwmbase0 = (struct grpwm_apb *) (GRPWM0_BASE + (nbr * 0x10));
  
    pwmbase0->pcomp0   = REGSET(pwmbase0->pcomp0,   COMP1,   comp1);
    pwmbase0->pcomp0   = REGSET(pwmbase0->pcomp0,   COMP2,   comp2);

    return BCC_OK;

}

/*
 * PWM0 Init
 * 
 */

uint32_t gr716_pwm0_init(uint32_t scaler)
{

  /* PWM0 Unit */
  volatile struct grpwm_apb *pwmbase0 = (struct grpwm_apb *) GRPWM0_BASE;

  // Core 
  pwmbase0->ctrl = REGSET(pwmbase0->ctrl, CEN, 0x0); // Disable Core at start

  // Scaler
  pwmbase0->scaler = REGSET(pwmbase0->scaler, PRELOAD, scaler); // Fast scaler i.e. 0

  // Interrupt pending
  pwmbase0->ipend = 0xFFFFFFFF;
  //pwmbase0->ipend = REGSET(pwmbase0->ipend, PIRQ, 0xFFFFFFFF); // Clear all pending interrupts

  return BCC_OK;

}

/*
 * PWM0 Global enable
 * 
 */

uint32_t gr716_pwm0_global_enable(uint32_t mask)
{

  /* PWM0 Unit */
  volatile struct grpwm_apb *pwmbase0 = (struct grpwm_apb *) GRPWM0_BASE;

  // Enable All PWMs
  //pwmbase0->ctrl = REGCLR(pwmbase0->ctrl, DIS);
  pwmbase0->ctrl = REGSET(pwmbase0->ctrl, CEN, 0x1);  // Enable Core at start
  pwmbase0->ctrl = REGSET(pwmbase0->ctrl, PEN, mask); // Enable PWM0 to PWM7

  return BCC_OK;

}

uint32_t gr716_pwm0_global_disable(uint32_t mask)
{

  /* PWM0 Unit */
  volatile struct grpwm_apb *pwmbase0 = (struct grpwm_apb *) GRPWM0_BASE;
  
  //pwmbase0->ctrl = REGCLR(pwmbase0->ctrl, PEN);
  pwmbase0->ctrl = REGSET(pwmbase0->ctrl, DIS, 0x1);
  pwmbase0->ctrl = REGSET(pwmbase0->ctrl, PEN, mask); // disable PWM0 to PWM7

  return BCC_OK;
}

/*
 * PWM0 enable
 * 
 */

uint32_t gr716_pwm0_enable(uint32_t nbr)
{

  /* PWM Unit: a bit ugly but does the job */
  volatile struct grpwm_apb *pwmbase0 = (struct grpwm_apb *) (GRPWM0_BASE + (nbr * 0x10));

  // Always disable
  pwmbase0->pctrl0 = REGSET(pwmbase0->pctrl0,   PWMEN,   0x1);

  return BCC_OK;

}

/*
 * PWM0 disable
 * 
 */

uint32_t gr716_pwm0_disable(uint32_t nbr)
{

  /* PWM0 Unit */
  volatile struct grpwm_apb *pwmbase0 = (struct grpwm_apb *) (GRPWM0_BASE + (nbr * 0x10));

  // Always disable
  pwmbase0->pctrl0 = REGSET(pwmbase0->pctrl0,   PWMEN, 0x0);

  return BCC_OK;

}

/*
 * PWM0 Clock enable
 *
 */

uint32_t gr716_pwm0_clk_enable(void)
{
  // Pointer to clock gate block
  struct  gckcfg_apb *gckcfgbase0 = (struct gckcfg_apb *) (GRCLKGATE0_BASE);
    
  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_GRPWM0, CG_UNLOCK);
  gckcfgbase0->clocken = REGSET(gckcfgbase0->clocken, CG_GRPWM0, CG_ENABLE);
  gckcfgbase0->reset   = REGSET(gckcfgbase0->reset ,  CG_GRPWM0, CG_RELEASE);
  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_GRPWM0, CG_LOCK); 

  return BCC_OK;

}

/*
 * PWM0 clock disable
 *
 */

uint32_t gr716_pwm0_clk_disable(void)
{
  // Pointers t clock gate block
  struct  gckcfg_apb *gckcfgbase0 = (struct gckcfg_apb *) (GRCLKGATE0_BASE);

  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_GRPWM0, CG_UNLOCK);
  gckcfgbase0->reset   = REGSET(gckcfgbase0->reset ,  CG_GRPWM0, CG_RESET);
  gckcfgbase0->clocken = REGSET(gckcfgbase0->clocken, CG_GRPWM0, CG_DISABLE);
  gckcfgbase0->unlock  = REGSET(gckcfgbase0->unlock,  CG_GRPWM0, CG_LOCK); 

  return BCC_OK;

}