#ifndef __GR716_IRQTS_H_
#define __GR716_IRQTS_H_

#include <gr716/gr716.h>


#define TSS1_BIT   26
#define TSS1_MASK  0x1
#define TSISEL_BIT 0
#define TSISEL_MASK 0b11111

#define TSCON_BASE 0x80002104

//configure timestamp register
 int gr716_int_timestamp_config(uint32_t interrupt_line);

 int gr716_int_timestamp_acc_assertion();


#endif