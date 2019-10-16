

#include <bldc/bldc.h>

void interrupt_handler(void *ptr, int nbr){
    
   //int plevel =  bcc_int_disable();
    
    //volatile unsigned int * iflag = (volatile int*) 0x8030D044;
    
    int pin = gr716_gpio_find_irq_pin();

    //printf("pin: %d\n", pin);
    
    gr716_gpio_toggle_edge(pin);
    
    //printf("%p\n", *iflag);

    //bcc_int_enable(plevel);
     
    commutate();
}


