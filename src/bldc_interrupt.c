

#include <bldc/bldc.h>
#include <gr716/gr716.h>
uint32_t volatile *timestamp_reg = (volatile uint32_t*)(0x80002108);
uint32_t timestamp_new;
uint32_t timestamp_old;
uint32_t timestamp_diff;
uint32_t counter;


void interrupt_handler(void *ptr, int nbr){
    commutate();
    int pin = gr716_gpio_find_irq_pin();
    
    gr716_gpio_toggle_edge(pin);

    
    timestamp_new = *timestamp_reg;
    if (timestamp_new > timestamp_old && ((counter % 24) == 0 )){
        timestamp_diff = timestamp_new - timestamp_old;
        timestamp_old = timestamp_new;
    }
    counter++;

    gr716_int_timestamp_acc_assertion();
}


