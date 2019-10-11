/*
 * GR716 PWM configuration and setup
 *
 * Functions:
 *  1. gr716_pwm0_clk_enable      - Enable PWM0 interface
 *  2. gr716_pwm0_clk_disable     - Disable PWM0 interface
 *  3. gr716_pwm0_init            - Config PWM0 Unit
 *  4. gr716_pwm0_config          - Config PWM0 config
 *  5. gr716_pwm0_enable          - Enable PWM0 Output
 *  6. gr716_pwm0_comp_update     - Update PWM0 Compare values
 *  7. gr716_pwm0_disable         - Disable PWM0
 *  8. gr716_pwm0_global_enable   - Global PWM0 enbale
 *  9. gr716_pwm0_global_disable  - Global PWM1 disable
 * 
*/

#include <bcc/bcc.h>

#ifndef __GR716_PWM_H_
#define __GR716_PWM_H_

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
#define WEN_BIT         9      // Waveform PWM enable (Shall be removed!)
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

// PWM configuration registers
struct grpwm_apb {
   volatile unsigned int  ctrl;
   volatile unsigned int  scaler;
   volatile unsigned int  ipend;
   volatile unsigned int  cap1;
   volatile unsigned int  cap2;
   volatile unsigned int  wave;     // Not used for GR716!
   volatile unsigned int  r0;       // Not used for GR716!
   volatile unsigned int  r1;       // Not used for GR716!
   volatile unsigned int  period0;
   volatile unsigned int  pcomp0;
   volatile unsigned int  pdead0;
   volatile unsigned int  pctrl0;
   volatile unsigned int  period1;
   volatile unsigned int  pcomp1;
   volatile unsigned int  pdead1;
   volatile unsigned int  pctrl1;
   volatile unsigned int  period2;
   volatile unsigned int  pcomp2;
   volatile unsigned int  pdead2;
   volatile unsigned int  pctrl2;
   volatile unsigned int  period3;
   volatile unsigned int  pcomp3;
   volatile unsigned int  pdead3;
   volatile unsigned int  pctrl3;
   volatile unsigned int  period4;
   volatile unsigned int  pcomp4;
   volatile unsigned int  pdead4;
   volatile unsigned int  pctrl4;
   volatile unsigned int  period5;
   volatile unsigned int  pcomp5;
   volatile unsigned int  pdead5;
   volatile unsigned int  pctrl5;
};

/*
 * Config PWM0 Unit
 *
 * nbr           : Select PWM output [0 - 7]
 * mode          : Select PWM mode {OneCompMode, DualCompMode, ExtCompMode}
 * meth          : Select Asymmetric or symmetric method {Asymmetric, Symmetric}
 * trigger       : Select trigger mode {none, enable}
 * scaler        : Set clock scaler scaler [0 - 7]
 * irqen         : Generate interrupt  {none, enable, comp}
 * iscaler       : Set interrupt scaler scaler [0 - 7]
 * pair          : Pair mode {none, enable}
 * polarity      : Select polarity {low, high}
 * flip          : Output flip bit {none, flip}
 * deadband      : Enable deadband {none, deadband}
 * dscaler       : Set deadband scaler [0 - 7]
 * period        : PWM period register
 * comp1         : COMP1 dead band compare register
 * comp2         : COMP2 dead band compare register
 * dbcomp        : PWM dead band compare register
 *
 * return: BCC response
 * 
 * Modes: 
 * 
 */

#define PWM_MODE_ONECOMP      0x0
#define PWM_MODE_DUALCOMP     0x1
#define PWM_MODE_EXTCOMP      0x2

#define PWM_MODE_ASYMMETRIC   0x0
#define PWM_MODE_SYMMETRIC    0x1

#define PWM_TRIGGER_NONE      0x0
#define PWM_TRIGGER_ENABLE    0x1

#define PWM_IRQ_NONE          0x0
#define PWM_IRQ_ENABLE        0x1
#define PWM_IRQ_COMP          0x2

#define PWM_PAIR_NONE         0x0
#define PWM_PAIR_ENABLE       0x1
#define PWM_PAIR_ZERO         0x2

#define PWM_POLARITY_LOW      0x0
#define PWM_POLARITY_HIGH     0x1

#define PWM_FLIP_NONE         0x0
#define PWM_FLIP_ENABLE       0x1

#define PWM_DEAD_NONE         0x0
#define PWM_DEAD_ENABLE       0x1


uint32_t gr716_pwm0_config(uint32_t nbr,
                                  uint32_t mode,  uint32_t meth,     uint32_t trigger, uint32_t scaler,
                                  uint32_t irqen, uint32_t iscaler,  uint32_t pair,    uint32_t polarity,
                                  uint32_t flip,  uint32_t deadband, uint32_t dbscaler,
                                  uint32_t period,
                                  uint32_t comp1, uint32_t comp2,
                                  uint32_t dcompx);

/*
 * PWM0 Update
 *
 *
 * return: OK
 * 
 */

uint32_t gr716_pwm0_comp_update(uint32_t nbr, uint32_t comp1, uint32_t comp2);

/*
 * PWM0 Init
 *
 *
 * return: OK
 * 
 */

uint32_t gr716_pwm0_init(uint32_t scaler);

uint32_t gr716_pwm0_global_disable(uint32_t mask);

uint32_t gr716_pwm0_global_enable(uint32_t mask);

/*
 * PWM0 enable
 *
 *
 * return: OK
 * 
 */

uint32_t gr716_pwm0_enable(uint32_t nbr);

/*
 * PWM0 disable
 *
 *
 * return: OK
 * 
 */

uint32_t gr716_pwm0_disable(uint32_t nbr);

/*
 * PWM0 Clock enable
 *
 *
 * return: OK
 * 
 */

uint32_t gr716_pwm0_clk_enable(void);

/*
 * PWM0 clock disable
 *
 *
 * return: BCC response
 * 
 */

uint32_t gr716_pwm0_clk_disable(void);

#endif
