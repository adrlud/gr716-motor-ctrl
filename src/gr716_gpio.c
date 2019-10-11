#include "../include/gr716_gpio.h"
#include "../include/gr716_reg.h"

uint32_t gr716_gpio_write(uint32_t pin, uint32_t value)
{

  struct grgpio_apb {
  volatile unsigned int  data;         // 0x00       I/O Port Data Register
  volatile unsigned int  output;       // 0x04       I/O Port Output Register
  volatile unsigned int  direction;    // 0x08       I/O Port Direction Register 
  volatile unsigned int  mask;         // 0x0C       I/O Port interrupt mask Register 
  };
      

   struct grgpio_apb *gpiobase0 = (struct grgpio_apb *) GPIO0_BASE;
   struct grgpio_apb *gpiobase1 = (struct grgpio_apb *) GPIO1_BASE;

    if (pin < 0) {
       return BCC_FAIL;
    } else if (pin > 63) {
       return BCC_FAIL;
    } else {
       if (pin < 32) {
          gpiobase0->output       = REGSETIOMODE(gpiobase0->output, (pin % 32),value);
       } else {
          gpiobase1->output       = REGSETIOMODE(gpiobase1->output, (pin % 32),value);
       }
    
       return BCC_OK;
    }   
}

int gr716_gpio_read(uint32_t pin)
{

  struct grgpio_apb {
  volatile unsigned int  data;         // 0x00       I/O Port Data Register
  volatile unsigned int  output;       // 0x04       I/O Port Output Register
  volatile unsigned int  direction;    // 0x08       I/O Port Direction Register 
  volatile unsigned int  mask;         // 0x0C       I/O Port interrupt mask Register
  };
      

   struct grgpio_apb *gpiobase0 = (struct grgpio_apb *) GPIO0_BASE;
   struct grgpio_apb *gpiobase1 = (struct grgpio_apb *) GPIO1_BASE;

    if (pin < 0) {
       return BCC_FAIL;
    } else if (pin > 63) {
       return BCC_FAIL;
    } else {
       if (pin < 32) {
          return ((gpiobase0->data & (1 << (pin % 32))) >> (pin % 32));
       } else {
          return ((gpiobase1->data & (1 << (pin % 32))) >> (pin % 32));
       }
    
    }   
}

/* Adrians funktion */

uint32_t gr716_gpio_config(uint32_t pin, uint32_t direction, uint32_t mask, uint32_t polarity, uint32_t edge)
{
   struct grgpio_apb {
   volatile unsigned int  data;         // 0x00       I/O Port Data Register
   volatile unsigned int  output;       // 0x04       I/O Port Output Register
   volatile unsigned int  direction;    // 0x08       I/O Port Direction Register 
   volatile unsigned int  irq_mask;         // 0x0C       I/O Port interrupt mask Register
   volatile unsigned int  polarity;
   volatile unsigned int  edge;            // 0x0C       I/O Port interrupt mask Register
   volatile unsigned int  capability;
   volatile unsigned int  irq_map[7];
   volatile unsigned int  irq_avalible;
   volatile unsigned int  irq_flag;
   volatile unsigned int  input_enable;
   };
      
      

   struct grgpio_apb *gpiobase0 = (struct grgpio_apb *) GPIO0_BASE;
   struct grgpio_apb *gpiobase1 = (struct grgpio_apb *) GPIO1_BASE;

    if (pin < 0) {
       return BCC_FAIL;
    } else if (pin > 63) {
       return BCC_FAIL;
    } else {
       if (pin < 32) {
          gpiobase0->direction       = REGSETIOMODE(gpiobase0->direction, (pin % 32),direction);
          gpiobase0->irq_mask        = REGSETIOMODE(gpiobase0->irq_mask, (pin % 32),mask);
          gpiobase0->polarity        = REGSETIOMODE(gpiobase0->polarity, (pin % 32),polarity);
          gpiobase0->edge            = REGSETIOMODE(gpiobase0->edge, (pin % 32),edge);
       } else {
          gpiobase1->direction       = REGSETIOMODE(gpiobase1->direction, (pin % 32),direction);
          gpiobase1->irq_mask        = REGSETIOMODE(gpiobase1->irq_mask, (pin % 32),mask);
          gpiobase1->polarity        = REGSETIOMODE(gpiobase1->polarity, (pin % 32),polarity);
          gpiobase1->edge            = REGSETIOMODE(gpiobase1->edge, (pin % 32),edge);
       }
    
       return BCC_OK;
    }   
}
/* Funktinen hittar vilken gpio pinne som har orsakat ett interrrupt */
 int gr716_gpio_find_irq_pin()
{

  struct grgpio_apb {
  volatile unsigned int  data;         // 0x00       I/O Port Data Register
  volatile unsigned int  output;       // 0x04       I/O Port Output Register
  volatile unsigned int  direction;    // 0x08       I/O Port Direction Register 
  volatile unsigned int  irq_mask;         // 0x0C       I/O Port interrupt mask Register
  volatile unsigned int  polarity;
  volatile unsigned int  edge;            // 0x0C       I/O Port interrupt mask Register
  volatile unsigned int  capability;
  volatile unsigned int  irq_map[7];
  volatile unsigned int  irq_avalible;
  volatile unsigned int  irq_flag;
  volatile unsigned int  input_enable;
  };
      

   struct grgpio_apb *gpiobase0 = (struct grgpio_apb *) GPIO0_BASE;
   struct grgpio_apb *gpiobase1 = (struct grgpio_apb *) GPIO1_BASE;

   for(int i = 0; i < 0; i++){
      if (gpiobase0->irq_flag & (1 << i)){
         //clear interrupt flag
         gpiobase0->irq_flag        = REGSETIOMODE(gpiobase0->irq_flag, i, 1);
         return i;
      } else if(gpiobase1->irq_flag & (1 << i))
      {  
         //clear interrupt flag
         gpiobase1->irq_flag        = REGSETIOMODE(gpiobase0->irq_flag, i, 1);
         return i+32;
      }
   }
   return BCC_OK;
}

int gr716_gpio_toggle_edge(int pin){
   
   struct grgpio_apb {
   volatile unsigned int  data;         // 0x00       I/O Port Data Register
   volatile unsigned int  output;       // 0x04       I/O Port Output Register
   volatile unsigned int  direction;    // 0x08       I/O Port Direction Register 
   volatile unsigned int  irq_mask;         // 0x0C       I/O Port interrupt mask Register
   volatile unsigned int  polarity;
   volatile unsigned int  edge;            // 0x0C       I/O Port interrupt mask Register
   volatile unsigned int  capability;
   volatile unsigned int  irq_map[7];
   volatile unsigned int  irq_avalible;
   volatile unsigned int  irq_flag;
   volatile unsigned int  input_enable;
   };
      
      

   struct grgpio_apb *gpiobase0 = (struct grgpio_apb *) GPIO0_BASE;
   struct grgpio_apb *gpiobase1 = (struct grgpio_apb *) GPIO1_BASE;
   
   if(pin < 0) {
      return BCC_FAIL;
   } else if(pin >63){
      return BCC_FAIL;
   } else {
      if(pin < 32){
         gpiobase0->edge ^= (1 << pin%32);
      }else {
         gpiobase1->edge ^= (1 << pin%32);
      }
       
   } 
   return BCC_OK;

}