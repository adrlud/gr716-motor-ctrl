#include <gr716/gr716_irqts.h>


int gr716_int_timestamp_config(uint32_t interrupt_line){
    volatile unsigned int *tscon = (unsigned volatile int * ) TSCON_BASE;
    *tscon = REGSET(*tscon, TSISEL, interrupt_line);
    
    return BCC_OK;
}


int gr716_int_timestamp_acc_assertion(){
    volatile unsigned int *tscon = (unsigned volatile int * ) TSCON_BASE;
    *tscon = REGSET(*tscon, TSS1, 1);

    return BCC_OK;
}