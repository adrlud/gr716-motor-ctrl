

#include "interrupt.h"


void interrupt_handler(void *ptr, int nbr){
    
    
    int irq_pin = gr716_gpio_find_irq_pin();
    gr716_gpio_toggle_edge(irq_pin);

}

