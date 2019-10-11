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
 * return: BCC response
 * 
 * Todo: Add error checking
 * 
 */


uint32_t gr716_gpio_write(uint32_t pin, uint32_t value);

int gr716_gpio_read(uint32_t pin);

/* Adrians funktion */

int gr716_gpio_find_irq_pin();

uint32_t gr716_gpio_config(uint32_t pin, uint32_t direction, uint32_t mask, uint32_t polarity, uint32_t edge);

int gr716_gpio_toggle_edge(int pin);

#endif
