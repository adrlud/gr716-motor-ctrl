/*
 * GR716 PLL, Clock and frequency setup
 *
 * - This file contains functions to setup and configure following clocks:
 *    - PLL mode and source clock
*    - System clock
*       -> possible to enable low power mode (switch system clock)
*    - SpaceWire clock
*    - MIL-1553B clock
*    - PWMx clock
 * 
*/

#include <bcc/bcc.h>

#ifndef __GR716_CLOCK_H_
#define __GR716_CLOCK_H_

/**** Clock Parameters and functions ****/

#define CLK_SOURCE_CLK   0x0 
#define CLK_SOURCE_SPW   0x1 
#define CLK_SOURCE_PLL   0x2 

#define SYS_MODE_NOM     0x0 
#define SYS_MODE_GEN     0x1 
#define SYS_MODE_SLEEP   0x2 

/*
 * System clock configuration
 *
 * source : Select source
 * div    : Div
 * duty   : Duty cycle
 *
 * return: BCC response
 *
 * Description:
 *
 * Mode #1: (Source = 0, Div = 0 and Duty = 0)
 *    - This mode bypasses the divider and uses the external clock pin as input 
 * 
 * Mode #2: (Source = X, Div = Y and Duty = 0)
 *   - This mode divides the clock source with 2^Y and selects as system clock
 *   - Y can be in the range from 1 to 31
 * 
 * Mode #3: (Source = X, Div = Y and Duty = Z)
 *    - This mode divides the clock source with Y and selects as system clock.
 *    - Clock duty cycle is set by 'Duty' in number of system clocks
 *    - Y can be in the range from 2 to 31 and must be at least 1 greater than X
 *    - Z can be in the range from 1 to 30 
 * 
 */
static uint32_t gr716_sysclk(uint32_t source, uint32_t div, uint32_t duty)
{
   struct pll_apb {
      volatile unsigned int  pll_cfg;
      volatile unsigned int  pll_sts;
      volatile unsigned int  pll_ref;
      volatile unsigned int  spw_ref;
      volatile unsigned int  mil_ref;
      volatile unsigned int  sys_ref;
      volatile unsigned int  sys_sel;
      volatile unsigned int  ctrl;
      volatile unsigned int  prot;
      volatile unsigned int  tctrl;
      volatile unsigned int  pwm0_ref;
      volatile unsigned int  pwm1_ref;
   };

    volatile struct pll_apb *pll_base = (struct pll_apb *) (PLL_BASE);

    if (source < CLK_SOURCE_CLK) {
       return BCC_FAIL;
    } else if (source > CLK_SOURCE_PLL) {
       return BCC_FAIL;
    } else if ((div != 0) & (duty != 0) & (duty <= div)) {
       return BCC_FAIL;
    } else {
       pll_base->sys_ref = ((duty & 0xFF) << 16) | ((source & 0x3) << 8) | ((div & 0xFF) << 0);

       // Select system ref clock
       if ((source == CLK_SOURCE_CLK) & (div == 0)) {
         pll_base->sys_sel = 0;
       } else {
         pll_base->sys_sel = 1;
       }

       return BCC_OK;
    } 

    return BCC_OK;
}

/*
 * SpaceWire clock configuration
 *
 * source : Select source
 * div    : Div
 * duty   : Duty cycle
 *
 * return: BCC response
 * 
 * Description:
 *
 * Mode #1: (Source = 0, Div = 0 and Duty = 0)
 *    - This mode bypasses the divider and uses the external clock pin as input 
 * 
 * Mode #2: (Source = X, Div = Y and Duty = 0)
 *   - This mode divides the clock source with 2^Y and selects as system clock
 *   - Y can be in the range from 1 to 31
 * 
 * Mode #3: (Source = X, Div = Y and Duty = Z)
 *    - This mode divides the clock source with Y and selects as system clock.
 *    - Clock duty cycle is set by 'Duty' in number of system clocks
 *    - Y can be in the range from 2 to 31 and must be at least 1 greater than X
 *    - Z can be in the range from 1 to 30 
 * 
 */

#define SPWCLK_SOURCE_CLK   0x0 
#define SPWCLK_SOURCE_PLL   0x1

static uint32_t gr716_spwclk(uint32_t source, uint32_t div, uint32_t duty)
{
   struct pll_apb {
      volatile unsigned int  pll_cfg;
      volatile unsigned int  pll_sts;
      volatile unsigned int  pll_ref;
      volatile unsigned int  spw_ref;
      volatile unsigned int  mil_ref;
      volatile unsigned int  sys_ref;
      volatile unsigned int  sys_sel;
      volatile unsigned int  ctrl;
      volatile unsigned int  prot;
      volatile unsigned int  tctrl;
      volatile unsigned int  pwm0_ref;
      volatile unsigned int  pwm1_ref;
   };

    volatile struct  pll_apb *pll_base = (struct pll_apb *) (PLL_BASE);

    if (source < SPWCLK_SOURCE_CLK) {
       return BCC_FAIL;
    } else if (source > SPWCLK_SOURCE_PLL) {
       return BCC_FAIL;
    } else if ((div != 0) & (duty != 0) & (duty <= div)) {
       return BCC_FAIL;
    } else {
       pll_base->spw_ref = ((duty & 0xFF) << 16) | ((source & 0x3) << 8) | ((div & 0xFF) << 0);
       return BCC_OK;
    } 

    return BCC_OK;
}

/*
 * MIL-1553B clock configuration
 *
 * source : Select source
 * div    : Div
 * duty   : Duty cycle
 *
 * return: BCC response
 * 
 * Description:
 *
 * Mode #1: (Source = 0, Div = 0 and Duty = 0)
 *    - This mode bypasses the divider and uses the external clock pin as input 
 * 
 * Mode #2: (Source = X, Div = Y and Duty = 0)
 *   - This mode divides the clock source with 2^Y and selects as system clock
 *   - Y can be in the range from 1 to 31
 * 
 * Mode #3: (Source = X, Div = Y and Duty = Z)
 *    - This mode divides the clock source with Y and selects as system clock.
 *    - Clock duty cycle is set by 'Duty' in number of system clocks
 *    - Y can be in the range from 2 to 31 and must be at least 1 greater than X
 *    - Z can be in the range from 1 to 30 
 * 
 */

#define MILCLK_SOURCE_CLK   0x0 
#define MILCLK_SOURCE_MIL   0x1 
#define MILCLK_SOURCE_SPW   0x2 
#define MILCLK_SOURCE_PLL   0x3 

static uint32_t gr716_milclk(uint32_t source, uint32_t div, uint32_t duty)
{
   struct pll_apb {
      volatile unsigned int  pll_cfg;
      volatile unsigned int  pll_sts;
      volatile unsigned int  pll_ref;
      volatile unsigned int  spw_ref;
      volatile unsigned int  mil_ref;
      volatile unsigned int  sys_ref;
      volatile unsigned int  sys_sel;
      volatile unsigned int  ctrl;
      volatile unsigned int  prot;
      volatile unsigned int  tctrl;
      volatile unsigned int  pwm0_ref;
      volatile unsigned int  pwm1_ref;
   };

    volatile struct  pll_apb *pll_base = (struct pll_apb *) (PLL_BASE);

    if (source < MILCLK_SOURCE_CLK) {
       return BCC_FAIL;
    } else if (source > MILCLK_SOURCE_PLL) {
       return BCC_FAIL;
    } else if ((div != 0) & (duty != 0) & (duty <= div)) {
       return BCC_FAIL;
    } else {
       pll_base->mil_ref = ((duty & 0xFF) << 16) | ((source & 0x3) << 8) | ((div & 0xFF) << 0);
       return BCC_OK;
    } 

    return BCC_OK;
}

/*
 * PWM0 clock configuration
 *
 * source : Select source
 * div    : Div
 * duty   : Duty cycle
 * div2   : Div2
 *
 * return: BCC response
 * 
 * Description:
 *
 * Mode #1: (Source = 0, Div = 0, Div2 = 0 and Duty = 0)
 *    - This mode bypasses the divider and uses the external clock pin as input 
 * 
 * Mode #2: (Source = X, Div = Y, Div2 = 0 and Duty = 0)
 *   - This mode divides the clock source with 2^Y and selects as system clock
 *   - Y can be in the range from 1 to 31
 * 
 * Mode #3: (Source = X, Div = Y, Div2 = 0 and Duty = Z)
 *    - This mode divides the clock source with Y and selects as system clock.
 *    - Clock duty cycle is set by 'Duty' in number of system clocks
 *    - Y can be in the range from 2 to 31 and must be at least 1 greater than X
 *    - Z can be in the range from 1 to 30 
 * 
 *  Mode #4: (Source = 3, Div = 0, Div2 = 1 and Duty = 0)
 *    - This mode generates a 200 MHz to the PWM
 * 
 */

#define PWMCLK_SOURCE_CLK    0x0 
#define PWMCLK_SOURCE_SPW    0x1 
#define PWMCLK_SOURCE_GPIO   0x2 
#define PWMCLK_SOURCE_PLL    0x3 

static uint32_t gr716_pwm0clk(uint32_t source, uint32_t div, uint32_t duty, uint32_t div2)
{
   struct pll_apb {
      volatile unsigned int  pll_cfg;
      volatile unsigned int  pll_sts;
      volatile unsigned int  pll_ref;
      volatile unsigned int  spw_ref;
      volatile unsigned int  mil_ref;
      volatile unsigned int  sys_ref;
      volatile unsigned int  sys_sel;
      volatile unsigned int  ctrl;
      volatile unsigned int  prot;
      volatile unsigned int  tctrl;
      volatile unsigned int  pwm0_ref;
      volatile unsigned int  pwm1_ref;
   };

    volatile struct pll_apb *pll_base = (struct pll_apb *) (PLL_BASE);

    if (source < PWMCLK_SOURCE_CLK) {
       return BCC_FAIL;
    } else if (source > PWMCLK_SOURCE_PLL) {
       return BCC_FAIL;
    } else if ((div != 0) & (duty != 0) & (duty <= div)) {
       return BCC_FAIL;
    } else {
       pll_base->pwm0_ref = ((div2 & 0x1) << 24) | ((duty & 0xFF) << 16) | ((source & 0x3) << 8) | ((div & 0xFF) << 0);
       return BCC_OK;
    } 

    return BCC_OK;
}

/*
 * PWM1 clock configuration
 *
 * source : Select source
 * div    : Div
 * duty   : Duty cycle
 * div2   : Div2
 *
 * return: BCC response
 * 
 * Description:
 *
 * Mode #1: (Source = 0, Div = 0, Div2 = 0 and Duty = 0)
 *    - This mode bypasses the divider and uses the external clock pin as input 
 * 
 * Mode #2: (Source = X, Div = Y, Div2 = 0 and Duty = 0)
 *   - This mode divides the clock source with 2^Y and selects as system clock
 *   - Y can be in the range from 1 to 31
 * 
 * Mode #3: (Source = X, Div = Y, Div2 = 0 and Duty = Z)
 *    - This mode divides the clock source with Y and selects as system clock.
 *    - Clock duty cycle is set by 'Duty' in number of system clocks
 *    - Y can be in the range from 2 to 31 and must be at least 1 greater than X
 *    - Z can be in the range from 1 to 30 
 * 
 *  Mode #4: (Source = 3, Div = 0, Div2 = 1 and Duty = 0)
 *    - This mode generates a 200 MHz to the PWM
 * 
 */
static uint32_t gr716_pwm1clk(uint32_t source, uint32_t div, uint32_t duty, uint32_t div2)
{
   struct pll_apb {
      volatile unsigned int  pll_cfg;
      volatile unsigned int  pll_sts;
      volatile unsigned int  pll_ref;
      volatile unsigned int  spw_ref;
      volatile unsigned int  mil_ref;
      volatile unsigned int  sys_ref;
      volatile unsigned int  sys_sel;
      volatile unsigned int  ctrl;
      volatile unsigned int  prot;
      volatile unsigned int  tctrl;
      volatile unsigned int  pwm0_ref;
      volatile unsigned int  pwm1_ref;
   };

    volatile struct  pll_apb *pll_base = (struct pll_apb *) (PLL_BASE);

    if (source < PWMCLK_SOURCE_CLK) {
       return BCC_FAIL;
    } else if (source > PWMCLK_SOURCE_PLL) {
       return BCC_FAIL;
    } else if ((div != 0) & (duty != 0) & (duty <= div)) {
       return BCC_FAIL;
    } else {
       pll_base->pwm1_ref = ((div2 & 0x1) << 24) | ((duty & 0xFF) << 16) | ((source & 0x3) << 8) | ((div & 0xFF) << 0);
       return BCC_OK;
    } 

    return BCC_OK;
}

/*
 * PLL configuration
 *
 * ref    : Select source
 * cfg    : PLL input source
 * pd     : PLL Power down
 *
 * return: BCC response
 * 
 * Description:
 * 
 *  Mode #1: (PD= 1, ref = X and cfg = Y)
 *   - This mode power down the PLL
 *
 *  Mode #2: (PD= 0, ref = X and cfg = Y)
 *   - This mode power on the PLL
 *   - Select the external input pin with 'ref'
 *   - The PLL must be configure the correct input frequency with 'cfg'
 *
 */

#define PLL_POWER_DOWN    0x1 
#define PLL_POWER_ENABLE  0x0 

#define PLL_FREQ_50MHZ    0x0 
#define PLL_FREQ_25MHZ    0x1
#define PLL_FREQ_20MHZ    0x2 
#define PLL_FREQ_12MHZ    0x3 
#define PLL_FREQ_10MHZ    0x4 
#define PLL_FREQ_5MHZ     0x5 

#define PLL_REF_SYS_CLK   0x0 
#define PLL_REF_SPW_CLK   0x1 

static uint32_t gr716_pll_config(uint32_t ref, uint32_t cfg, uint32_t pd)
{
   struct pll_apb {
      volatile unsigned int  pll_cfg;
      volatile unsigned int  pll_sts;
      volatile unsigned int  pll_ref;
      volatile unsigned int  spw_ref;
      volatile unsigned int  mil_ref;
      volatile unsigned int  sys_ref;
      volatile unsigned int  sys_sel;
      volatile unsigned int  ctrl;
      volatile unsigned int  prot;
      volatile unsigned int  tctrl;
      volatile unsigned int  pwm0_ref;
      volatile unsigned int  pwm1_ref;
   };

    volatile struct  pll_apb *pll_base = (struct pll_apb *) (PLL_BASE);

    if (CLK_SOURCE_SPW < ref ) {
       return BCC_FAIL;
    } else if (PLL_FREQ_5MHZ < cfg) {
       return BCC_FAIL;
    } else {
       pll_base->pll_cfg = (((pd & 0x1) << 31) | ((cfg & 0x7) << 0));
       pll_base->pll_ref = ((ref & 0x3) << 8);
       return BCC_OK;
    } 
}

/*
 * Clock test configuration
 *
 * mode    : Enable Test clock output
 *
 * return: BCC response
 * 
 * Description:
 * 
 *  Mode #1: (mode= 0)
 *   - Normal mode
 * 
  *  Mode #1: (mode= 1)
 *   - Production mode / Clock output mode
 *   - Enable clocks on GPIO:
 *       PWM1 -> GPIO59
 *       PWM0 -> GPIO60
 *       MIL  -> GPIO61
 *       SPW  -> GPIO62
 *       CLK  -> GPIO63
 * 
 */

#define PLL_TEST_CLOCK_DISABLE 0x0 
#define PLL_TEST_CLOCK_ENABLE  0x1 

static uint32_t pll_test_clock_enable(uint32_t mode)
{
   struct pll_apb {
      volatile unsigned int  pll_cfg;
      volatile unsigned int  pll_sts;
      volatile unsigned int  pll_ref;
      volatile unsigned int  spw_ref;
      volatile unsigned int  mil_ref;
      volatile unsigned int  sys_ref;
      volatile unsigned int  sys_sel;
      volatile unsigned int  ctrl;
      volatile unsigned int  prot;
      volatile unsigned int  tctrl;
      volatile unsigned int  pwm0_ref;
      volatile unsigned int  pwm1_ref;
   };

    volatile struct  pll_apb *pll_base = (struct pll_apb *) (PLL_BASE);

       pll_base->tctrl = (mode & 0x1);
       return BCC_OK;

}

#endif
