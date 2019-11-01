/*
 * GR716 IO configuration and setup
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
#define IO_MODE_INPUT     0x0 
#define IO_MODE_OUTPUT    0x1 
#define IO_MODE_PULLUP    0x2 
#define IO_MODE_PULLDOWN  0x3 





       
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

/* funktions headers */

uint32_t gr716_pinfunc(int pin, int mode);
uint32_t gr716_pinmode(uint32_t pin, uint32_t iomode, uint32_t mode);




#endif
