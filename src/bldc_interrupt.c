

#include <bldc/bldc.h>
#include <gr716/gr716.h>
void interrupt_handler(void *ptr, int nbr){
    
    gr716_int_timestamp_config(18);
    gr716_int_timestamp_acc_assertion();



    int pin = gr716_gpio_find_irq_pin();
    
    gr716_gpio_toggle_edge(pin);
    
 
    commutate();
}


