/*
 * GR716 GPIO configuration and setup
 *
 * This file contains functions for GPIO
 *  - gr716_gpio_write  - Set GPIO output value
 *  - gr716_gpio_read   - Set GPIO read value
 * 
*/

#include <bcc/bcc.h>

#ifndef __GR716_GPIO_H_
#define __GR716_GPIO_H_

/*
 * Output GPIO function per pin
 *
 * pin   : Select pin [0 - 63]
 * value : 0 or 1
 *
 * 
 */

struct grgpio_apb {
    volatile unsigned int  data;         // 0x00       I/O Port Data Register
    volatile unsigned int  output;       // 0x04       I/O Port Output Register
    volatile unsigned int  direction;    // 0x08       I/O Port Direction Register 
    volatile unsigned int  mask;         // 0x0C       I/O Port interrupt mask Register 
};

uint32_t gr716_gpio_write(uint32_t pin, uint32_t value);

int gr716_gpio_read(uint32_t pin);

int gr716_gpio_find_irq_pin();

uint32_t gr716_gpio_config(uint32_t pin, uint32_t direction, uint32_t mask, uint32_t polarity, uint32_t edge, uint32_t input);

int gr716_gpio_toggle_edge(int pin);

#endif
