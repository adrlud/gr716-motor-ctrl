#include <gr716/gr716.h>

uint32_t gr716_pinfunc(int pin, int mode)
{

      
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
 * Enable Direction and Mode function per pin
 *
 * pin  : Select pin [0 - 63]
 * mode : Select mode
 * 
 */

uint32_t gr716_pinmode(uint32_t pin, uint32_t iomode, uint32_t mode)
{
      
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