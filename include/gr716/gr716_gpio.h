/*
 * GR716 GPIO configuration and setup
 *
 * This file contains functions for GPIO
 *  - gr716_gpio_write          - Set GPIO output value
 *  - gr716_gpio_read           - Set GPIO read value
 *  - gr716_gpio_find_irq_pin   - Find pin that caused an intterrupt
 *  - gr716_gpio_config         - Configure GPIO
 *  - gr716_gpio_toggle_edge    - Shift polarity for edge interrupts
*/

#include <bcc/bcc.h>

#ifndef __GR716_GPIO_H_
#define __GR716_GPIO_H_



struct grgpio_apb {
    volatile unsigned int  data;         
    volatile unsigned int  output;       
    volatile unsigned int  direction;    
    volatile unsigned int  irq_mask;         
    volatile unsigned int  polarity;
    volatile unsigned int  edge;            
    volatile unsigned int  capability;
    volatile unsigned int  irq_map[7];
    volatile unsigned int  irq_avalible;
    volatile unsigned int  irq_flag;
    volatile unsigned int  input_enable;
};
      
/*
 * Output GPIO function per pin
 *  
 * Arguments:
 * pin    : Select pin [0 - 63]
 * others : 0 or 1
 * 
 * 
 */

uint32_t gr716_gpio_write(uint32_t pin, uint32_t value);

uint32_t gr716_gpio_read(uint32_t pin);

/* gr716_gpio_find_irq_pin
 * Works for only GPIO1 for now 
 * Finds wich pin caused an interrupt
 * Return: pin [32-63]
 *  
 */

uint32_t gr716_gpio_find_irq_pin();

uint32_t gr716_gpio_config(uint32_t pin, uint32_t direction, uint32_t mask, uint32_t polarity, uint32_t edge, uint32_t input);

uint32_t gr716_gpio_toggle_edge(uint32_t pin);

#endif
