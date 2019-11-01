#include <gr716/gr716.h>
#include <stdio.h>
uint32_t gr716_gpio_write(uint32_t pin, uint32_t value)
{
   struct grgpio_apb *gpiobase0 = (struct grgpio_apb *) GPIO0_BASE;
   struct grgpio_apb *gpiobase1 = (struct grgpio_apb *) GPIO1_BASE;

    if (pin < 0) {
       return BCC_FAIL;
    } else if (pin > 63) {
       return BCC_FAIL;
    } else {
       if (pin < 32) {
          gpiobase0->output = REGSETIOMODE(gpiobase0->output, (pin % 32),value);
       } else {
          gpiobase1->output = REGSETIOMODE(gpiobase1->output, (pin % 32),value);
       }
    
       return BCC_OK;
    }   
}

uint32_t gr716_gpio_read(uint32_t pin){
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


uint32_t gr716_gpio_config(uint32_t pin, uint32_t direction, uint32_t mask, uint32_t polarity, uint32_t edge, uint32_t input){
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
          gpiobase0->input_enable    = REGSETIOMODE(gpiobase0->input_enable, (pin % 32), input);
       } else {
          gpiobase1->direction       = REGSETIOMODE(gpiobase1->direction, (pin % 32),direction);
          gpiobase1->irq_mask        = REGSETIOMODE(gpiobase1->irq_mask, (pin % 32),mask);
          gpiobase1->polarity        = REGSETIOMODE(gpiobase1->polarity, (pin % 32),polarity);
          gpiobase1->edge            = REGSETIOMODE(gpiobase1->edge, (pin % 32),edge);
          gpiobase1->input_enable    = REGSETIOMODE(gpiobase1->input_enable, (pin % 32),input);
       }
    
       return BCC_OK;
    }   
}
/* Find pin who caused uint32_terrupt*/
 uint32_t gr716_gpio_find_irq_pin(){
                                                       /*Raw pinter to interrupt*/          
   volatile uint32_t * iflag = (volatile uint32_t*) 0x8030D044; 
   for(int i = 0; i < 32; i++){
      //if uint32_terrupt bit = 1 the pin caused interrupt 
      if (*iflag & (1 << i)){
         //clear uint32_terrupt flag
         *iflag = REGSETIOMODE(*iflag, i, 1); /* bit is cleared by writing 1 to it, write of 0 have no effect */
         return i+32; /* This is becouse GPIO1 (pin 32-63) is used, delete +32 for use with GPIO0 
                       * GPIO0 is not initilized in this program
                       * The state of GPIO0 uint32_terrupt flag register is unknown                       
                       */
      }
   } 
   return BCC_FAIL;
 }

/*
 * This function change polarity for the edge interupt.
 * i.e the gpio request an uint32_terrupt on either low to high flank or high to low flank.
 * If interrupt on both flanks is wanated, call this function after an uint32_terrupt to change flank. 
 */ 

uint32_t gr716_gpio_toggle_edge(uint32_t pin){
   struct grgpio_apb *gpiobase0 = (struct grgpio_apb *) GPIO0_BASE;
   struct grgpio_apb *gpiobase1 = (struct grgpio_apb *) GPIO1_BASE;
   
   if(pin < 0) {
      return BCC_FAIL;
   } else if(pin >63){
      return BCC_FAIL;
   } else {
      if(pin < 32){
         gpiobase0->polarity ^= (1 << pin%32);
      }else {
         gpiobase1->polarity ^= (1 << pin%32);
      }
   } 
   return BCC_OK;

}