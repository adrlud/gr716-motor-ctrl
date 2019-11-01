#ifndef __BLDC_H_
#define __BLDC_H_


#include "bldc_interrupt.h"
#include "bldc_commutate.h"
#include "bldc_init.h"

/* GPIO config*/
#define GPIO_DIR 0x0
#define GPIO_IRQ 0x1
#define GPIO_POL 0x0
#define GPIO_EDGE 0x1
#define GPIO_INPUT_ENABLE 0x1
#define GPIO_RISING 0x1
#define GPIO_FALLING 0x0

/* Hall sensor input pins*/
#define HALL_A 40
#define HALL_B 41
#define HALL_C 42

/* PWM channels*/
#define U_LOW 0
#define U_HIGH 1
#define V_LOW 2
#define V_HIGH 3
#define W_LOW 4
#define W_HIGH 5

#endif