/*
 * GR716 IO configuration and setup
 *
 * This file contains functions to configure GPIO and LVDS:
 *  - GPIO pin mode (per pin and table mode)
 *     1. gr716_pinfunc - Configure pin function
 *     2. gr716_tabfunc - Configure GPIO using table (tcl-script)
 *     3. gr716_pinmode - Configure pin mode
 *  - LVDS pin mode
 *     1. gr716_lvds_func - Configure LVDS function
 *  - Pull-dow resistor functions
 *     1. gr716_pulldown_enable_all - enables pull-down on all GPIOs
 *     2- gr716_pulldown_disable_adc - disable pull-down on all ADC channels
 * 
 * 
*/

#include <bcc/bcc.h>

#ifndef __GR716_IO_H_
#define __GR716_IO_H_

/**** IO Parameters and functions ****/

#define IO_MODE_GPIO      0x0 
#define IO_MODE_APBUART   0x1 
#define IO_MODE_MEM       0x2 
#define IO_MODE_PW        0x3 
#define IO_MODE_1553      0x4  
#define IO_MODE_CAN       0x5  
#define IO_MODE_I2C       0x6 
#define IO_MODE_SPI       0x7  
#define IO_MODE_ADC       0x8  
#define IO_MODE_DAC       0x8  
#define IO_MODE_ADCDAC    0x9  
#define IO_MODE_PWM       0xA  
#define IO_MODE_SPW       0xB  
#define IO_MODE_SPI4S     0xB  
#define IO_MODE_AHBUART   0xC 
#define IO_MODE_TDP       0xD 

#define IO_MODE_NONE      0xFF 

/*
 * Enable function per pin
 *
 * pin  : Select pin [0 - 63]
 * mode : Select mode
 *
 * return: BCC response
 * 
 * Todo: Add error checking
 * 
 */
static uint32_t gr716_pinfunc(int pin, int mode)
{
       
   struct sys_cfg_io_apb {
      volatile unsigned int  gpio0;
      volatile unsigned int  gpio1;
      volatile unsigned int  gpio2;
      volatile unsigned int  gpio3;
      volatile unsigned int  gpio4;
      volatile unsigned int  gpio5;
      volatile unsigned int  gpio6;
      volatile unsigned int  gpio7;
      volatile unsigned int  pullup0;
      volatile unsigned int  pullup1;
      volatile unsigned int  pulldown0;
      volatile unsigned int  pulldown1;
      volatile unsigned int  lvds;
      volatile unsigned int  prot;
      volatile unsigned int  eirq;
      volatile unsigned int  estat;
   };
      
   struct  sys_cfg_io_apb *sys_cfg_io_base = (struct sys_cfg_io_apb *) (SYS_CFG_IO_BASE);

    if (pin < 0) {
       return BCC_FAIL;
    } else if (pin > 63) {
       return BCC_FAIL;
    } else if (((mode == IO_MODE_ADC) | (mode == IO_MODE_DAC)) & ((pin < 37) | (pin > 48))) {
        return BCC_FAIL;
    } else {
       if (pin < 8) {
            sys_cfg_io_base->gpio0 = REGSETIO(sys_cfg_io_base->gpio0, (pin % 8) , mode);
       } else if (pin < 16) {
            sys_cfg_io_base->gpio1 = REGSETIO(sys_cfg_io_base->gpio1, (pin % 8) , mode);
       } else if (pin < 24) {
            sys_cfg_io_base->gpio2 = REGSETIO(sys_cfg_io_base->gpio2, (pin % 8) , mode);
       } else if (pin < 32) {
            sys_cfg_io_base->gpio3 = REGSETIO(sys_cfg_io_base->gpio3, (pin % 8) , mode);
       } else if (pin < 40) {
            sys_cfg_io_base->gpio4 = REGSETIO(sys_cfg_io_base->gpio4, (pin % 8) , mode);
       } else if (pin < 48) {
            sys_cfg_io_base->gpio5 = REGSETIO(sys_cfg_io_base->gpio5, (pin % 8) , mode);
       } else if (pin < 56) {
            sys_cfg_io_base->gpio6 = REGSETIO(sys_cfg_io_base->gpio6, (pin % 8) , mode);
       } else {
            sys_cfg_io_base->gpio7 = REGSETIO(sys_cfg_io_base->gpio7, (pin % 8) , mode);
       }
    
       return BCC_OK;
    }   
}

/*
 * Enable function per pin
 *
 * tab  : Select pin mode table
 *
 * return: BCC response
 * 
 * Todo: Add error checking
 * 
 */
static uint32_t gr716_tabfunc(uint32_t tab[8])
{
    struct sys_cfg_io_apb {
      volatile unsigned int  gpio0;
      volatile unsigned int  gpio1;
      volatile unsigned int  gpio2;
      volatile unsigned int  gpio3;
      volatile unsigned int  gpio4;
      volatile unsigned int  gpio5;
      volatile unsigned int  gpio6;
      volatile unsigned int  gpio7;
      volatile unsigned int  pullup0;
      volatile unsigned int  pullup1;
      volatile unsigned int  pulldown0;
      volatile unsigned int  pulldown1;
      volatile unsigned int  lvds;
      volatile unsigned int  prot;
      volatile unsigned int  eirq;
      volatile unsigned int  estat;
   };
      
   volatile struct  sys_cfg_io_apb *sys_cfg_io_base = (struct sys_cfg_io_apb *) (SYS_CFG_IO_BASE);

    sys_cfg_io_base->gpio0 = tab[0];
    sys_cfg_io_base->gpio1 = tab[1];
    sys_cfg_io_base->gpio2 = tab[2];
    sys_cfg_io_base->gpio3 = tab[3];
    sys_cfg_io_base->gpio4 = tab[4];
    sys_cfg_io_base->gpio5 = tab[5];
    sys_cfg_io_base->gpio6 = tab[6];
    sys_cfg_io_base->gpio7 = tab[7];
    
    return BCC_OK;
}

/*
 * Enable LVDS function
 *
 * func : Select LVDS mode
 *
 * return: BCC response
 * 
 * Todo: Add error checking
 * 
 */

#define LVDS_MODE_SPW       0x0 
#define LVDS_MODE_SPI4S     0x1 
#define LVDS_MODE_SPIM      0x2 
#define LVDS_MODE_SPIS      0x3 
#define LVDS_DISABLE        0x8 

#define LVDS_TX0_BIT   0
#define LVDS_TX0_MASK  0xF
#define LVDS_TX1_BIT   4
#define LVDS_TX1_MASK  0xF
#define LVDS_TX2_BIT   8
#define LVDS_TX2_MASK  0xF

#define LVDS_RX0_BIT   12
#define LVDS_RX0_MASK  0xF
#define LVDS_RX1_BIT   16
#define LVDS_RX1_MASK  0xF
#define LVDS_RX2_BIT   20
#define LVDS_RX2_MASK  0xF

static uint32_t gr716_lvds_func(uint32_t iofunc)
{
       
   struct sys_cfg_io_apb {
      volatile unsigned int  gpio0;
      volatile unsigned int  gpio1;
      volatile unsigned int  gpio2;
      volatile unsigned int  gpio3;
      volatile unsigned int  gpio4;
      volatile unsigned int  gpio5;
      volatile unsigned int  gpio6;
      volatile unsigned int  gpio7;
      volatile unsigned int  pullup0;
      volatile unsigned int  pullup1;
      volatile unsigned int  pulldown0;
      volatile unsigned int  pulldown1;
      volatile unsigned int  lvds;
      volatile unsigned int  prot;
      volatile unsigned int  eirq;
      volatile unsigned int  estat;
   };
      
   volatile struct  sys_cfg_io_apb *sys_cfg_io_base = (struct sys_cfg_io_apb *) (SYS_CFG_IO_BASE);

    if (iofunc < LVDS_MODE_SPW) {
       return BCC_FAIL;
    } else if ((iofunc > LVDS_MODE_SPIS) & (LVDS_DISABLE != LVDS_DISABLE)) {
       return BCC_FAIL;
    } else {
       if (iofunc == LVDS_DISABLE) {
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_RX0, LVDS_DISABLE);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_RX1, LVDS_DISABLE);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_RX2, LVDS_DISABLE);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_TX0, LVDS_DISABLE);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_TX1, LVDS_DISABLE);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_TX2, LVDS_DISABLE);
       } else if (iofunc == LVDS_MODE_SPIM) {
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_RX0, LVDS_MODE_SPIM);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_RX1, LVDS_DISABLE);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_RX2, LVDS_DISABLE);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_TX0, LVDS_MODE_SPIM);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_TX1, LVDS_MODE_SPIM);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_TX2, LVDS_MODE_SPIM);
       } else if (iofunc == LVDS_MODE_SPIS) {
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_RX0, LVDS_MODE_SPIS);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_RX1, LVDS_MODE_SPIS);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_RX2, LVDS_MODE_SPIS);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_TX0, LVDS_DISABLE);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_TX1, LVDS_DISABLE);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_TX2, LVDS_MODE_SPIS);
       } else if (iofunc == LVDS_MODE_SPI4S) {
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_RX0, LVDS_MODE_SPI4S);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_RX1, LVDS_MODE_SPI4S);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_RX2, LVDS_MODE_SPI4S);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_TX0, LVDS_DISABLE);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_TX1, LVDS_DISABLE);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_TX2, LVDS_MODE_SPI4S);
       } else if (iofunc == LVDS_MODE_SPW) {
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_RX0, LVDS_MODE_SPW);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_RX1, LVDS_MODE_SPW);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_RX2, LVDS_DISABLE);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_TX0, LVDS_MODE_SPW);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_TX1, LVDS_MODE_SPW);
            sys_cfg_io_base->lvds = REGSET(sys_cfg_io_base->lvds,LVDS_TX2, LVDS_DISABLE);
       } else {
            return BCC_FAIL;
       }
    
       return BCC_OK;
    }   
}

/*
 * Enable Direction and Mode function per pin
 *
 * pin  : Select pin [0 - 63]
 * mode : Select mode
 *
 * return: BCC response
 * 
 * Todo: Add error checking
 * 
 */

#define IO_MODE_INPUT     0x0 
#define IO_MODE_OUTPUT    0x1 
#define IO_MODE_PULLUP    0x2 
#define IO_MODE_PULLDOWN  0x3 

static uint32_t gr716_pinmode(uint32_t pin, uint32_t iomode, uint32_t mode)
{
       
   struct sys_cfg_io_apb {
      volatile unsigned int  gpio0;
      volatile unsigned int  gpio1;
      volatile unsigned int  gpio2;
      volatile unsigned int  gpio3;
      volatile unsigned int  gpio4;
      volatile unsigned int  gpio5;
      volatile unsigned int  gpio6;
      volatile unsigned int  gpio7;
      volatile unsigned int  pullup0;
      volatile unsigned int  pullup1;
      volatile unsigned int  pulldown0;
      volatile unsigned int  pulldown1;
      volatile unsigned int  lvds;
      volatile unsigned int  prot;
      volatile unsigned int  eirq;
      volatile unsigned int  estat;
   };

  struct grgpio_apb {
  volatile unsigned int  data;         // 0x00       I/O Port Data Register
  volatile unsigned int  output;       // 0x04       I/O Port Output Register
  volatile unsigned int  direction;    // 0x08       I/O Port Direction Register 
  volatile unsigned int  mask;         // 0x0C       I/O Port interrupt mask Register 
  };
      
   volatile struct  sys_cfg_io_apb *sys_cfg_io_base = (struct sys_cfg_io_apb *) (SYS_CFG_IO_BASE);

   struct grgpio_apb *gpiobase0 = (struct grgpio_apb *) GPIO0_BASE;
   struct grgpio_apb *gpiobase1 = (struct grgpio_apb *) GPIO1_BASE;

    if (pin < 0) {
       return BCC_FAIL;
    } else if (pin > 63) {
       return BCC_FAIL;
    } else {
       if (pin < 32) {
           if (iomode == IO_MODE_INPUT) {
              sys_cfg_io_base->pullup0   = REGCLRIOMODE(sys_cfg_io_base->pullup0, (pin % 32)); 
              sys_cfg_io_base->pulldown0 = REGCLRIOMODE(sys_cfg_io_base->pulldown0, (pin % 32)); 
              gpiobase0->direction       = REGCLRIOMODE(gpiobase0->direction, (pin % 32)); 
           } else if (iomode == IO_MODE_OUTPUT) {
              sys_cfg_io_base->pullup0   = REGCLRIOMODE(sys_cfg_io_base->pullup0, (pin % 32)); 
              sys_cfg_io_base->pulldown0 = REGCLRIOMODE(sys_cfg_io_base->pulldown0, (pin % 32)); 
              if (mode == IO_MODE_GPIO) {
                gpiobase0->direction       = REGSETIOMODE(gpiobase0->direction, (pin % 32), 0x1);               
              } else {
                gpiobase0->direction       = REGCLRIOMODE(gpiobase0->direction, (pin % 32));
              }
           } else if (iomode == IO_MODE_PULLUP) {
              sys_cfg_io_base->pulldown0 = REGCLRIOMODE(sys_cfg_io_base->pulldown0, (pin % 32)); 
              sys_cfg_io_base->pullup0   = REGSETIOMODE(sys_cfg_io_base->pullup0, (pin % 32), 0x1);
              gpiobase0->direction       = REGCLRIOMODE(gpiobase0->direction, (pin % 32));
           } else if (iomode == IO_MODE_PULLDOWN) {
              sys_cfg_io_base->pullup0   = REGCLRIOMODE(sys_cfg_io_base->pullup0, (pin % 32)); 
              sys_cfg_io_base->pulldown0 = REGSETIOMODE(sys_cfg_io_base->pulldown0, (pin % 32), 0x1);
              gpiobase0->direction       = REGCLRIOMODE(gpiobase0->direction, (pin % 32));
           } else {
               return BCC_FAIL;
           }
       } else {
           if (iomode == IO_MODE_INPUT) {
              sys_cfg_io_base->pullup1   = REGCLRIOMODE(sys_cfg_io_base->pullup1, (pin % 32)); 
              sys_cfg_io_base->pulldown1 = REGCLRIOMODE(sys_cfg_io_base->pulldown1, (pin % 32)); 
              gpiobase1->direction       = REGCLRIOMODE(gpiobase1->direction, (pin % 32));
           } else if (iomode == IO_MODE_OUTPUT) {
              sys_cfg_io_base->pullup1   = REGCLRIOMODE(sys_cfg_io_base->pullup1, (pin % 32)); 
              sys_cfg_io_base->pulldown1 = REGCLRIOMODE(sys_cfg_io_base->pulldown1, (pin % 32)); 
              if (mode == IO_MODE_GPIO) {
                gpiobase1->direction       = REGSETIOMODE(gpiobase1->direction, (pin % 32), 0x1);               
              } else {
                gpiobase1->direction       = REGCLRIOMODE(gpiobase1->direction, (pin % 32));
              }
           } else if (iomode == IO_MODE_PULLUP) {
              sys_cfg_io_base->pulldown1 = REGCLRIOMODE(sys_cfg_io_base->pulldown1, (pin % 32)); 
              sys_cfg_io_base->pullup1   = REGSETIOMODE(sys_cfg_io_base->pullup1, (pin % 32), 0x1);
              gpiobase1->direction       = REGCLRIOMODE(gpiobase1->direction, (pin % 32));
           } else if (iomode == IO_MODE_PULLDOWN) {
              sys_cfg_io_base->pullup1   = REGCLRIOMODE(sys_cfg_io_base->pullup1, (pin % 32)); 
              sys_cfg_io_base->pulldown1 = REGSETIOMODE(sys_cfg_io_base->pulldown1, (pin % 32), 0x1);
              gpiobase1->direction       = REGCLRIOMODE(gpiobase1->direction, (pin % 32));
           } else {
               return BCC_FAIL;
           }
       }
    
       return BCC_OK;
    }   
}

/*
 * Enable pull-down resistor on all GPIOs 
 *
 * input: void
 *
 * return: BCC response
 * 
 * Todo: Add error checking
 * 
 */
#define IO_PULLUP_ENABLE_ALL    0xFFFFFFFF 

static uint32_t gr716_pulldown_enable_all(void)
{
    struct sys_cfg_io_apb {
      volatile unsigned int  gpio0;
      volatile unsigned int  gpio1;
      volatile unsigned int  gpio2;
      volatile unsigned int  gpio3;
      volatile unsigned int  gpio4;
      volatile unsigned int  gpio5;
      volatile unsigned int  gpio6;
      volatile unsigned int  gpio7;
      volatile unsigned int  pullup0;
      volatile unsigned int  pullup1;
      volatile unsigned int  pulldown0;
      volatile unsigned int  pulldown1;
      volatile unsigned int  lvds;
      volatile unsigned int  prot;
      volatile unsigned int  eirq;
      volatile unsigned int  estat;
   };
      
   volatile struct  sys_cfg_io_apb *sys_cfg_io_base = (struct sys_cfg_io_apb *) (SYS_CFG_IO_BASE);

    sys_cfg_io_base->pulldown0 = IO_PULLUP_ENABLE_ALL;
    sys_cfg_io_base->pulldown1 = IO_PULLUP_ENABLE_ALL;
    
    return BCC_OK;
}

/*
 * Disable pull-down resistor on all adc input channels
 *
 * input: void
 *
 * return: BCC response
 * 
 * Todo: Add error checking
 * 
 */

#define ADC_CHANNEL_0   0x5 
#define ADC_CHANNEL_1   0x6
#define ADC_CHANNEL_2   0x7
#define ADC_CHANNEL_3   0x8
#define ADC_CHANNEL_4   0x9
#define ADC_CHANNEL_5   0xA
#define ADC_CHANNEL_6   0xB
#define ADC_CHANNEL_7   0xC
static uint32_t gr716_pulldown_disable_adc(void)
{
    struct sys_cfg_io_apb {
      volatile unsigned int  gpio0;
      volatile unsigned int  gpio1;
      volatile unsigned int  gpio2;
      volatile unsigned int  gpio3;
      volatile unsigned int  gpio4;
      volatile unsigned int  gpio5;
      volatile unsigned int  gpio6;
      volatile unsigned int  gpio7;
      volatile unsigned int  pullup0;
      volatile unsigned int  pullup1;
      volatile unsigned int  pulldown0;
      volatile unsigned int  pulldown1;
      volatile unsigned int  lvds;
      volatile unsigned int  prot;
      volatile unsigned int  eirq;
      volatile unsigned int  estat;
   };
      
   volatile struct  sys_cfg_io_apb *sys_cfg_io_base = (struct sys_cfg_io_apb *) (SYS_CFG_IO_BASE);
    
    sys_cfg_io_base->pulldown1 = REGCLRIOMODE(sys_cfg_io_base->pulldown1, ADC_CHANNEL_0); 
    sys_cfg_io_base->pulldown1 = REGCLRIOMODE(sys_cfg_io_base->pulldown1, ADC_CHANNEL_1); 
    sys_cfg_io_base->pulldown1 = REGCLRIOMODE(sys_cfg_io_base->pulldown1, ADC_CHANNEL_2); 
    sys_cfg_io_base->pulldown1 = REGCLRIOMODE(sys_cfg_io_base->pulldown1, ADC_CHANNEL_3); 
    sys_cfg_io_base->pulldown1 = REGCLRIOMODE(sys_cfg_io_base->pulldown1, ADC_CHANNEL_4); 
    sys_cfg_io_base->pulldown1 = REGCLRIOMODE(sys_cfg_io_base->pulldown1, ADC_CHANNEL_5); 
    sys_cfg_io_base->pulldown1 = REGCLRIOMODE(sys_cfg_io_base->pulldown1, ADC_CHANNEL_6); 
    sys_cfg_io_base->pulldown1 = REGCLRIOMODE(sys_cfg_io_base->pulldown1, ADC_CHANNEL_7); 
    
    
    return BCC_OK;
}

#endif
