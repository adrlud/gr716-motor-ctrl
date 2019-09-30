
#include "pwm.h"

#define A 0
#define B 2
#define C 4
#define A_ 6
#define B_ 8
#define C_ 10


extern unsigned char comm_state; // input from hall-sensors

void commutate(){
    switch(comm_state){
        case 1:
            PWM_enable(pwm0, A);
            PWM_enable(pwm0, B_);
        break;
        case 2:
            
        
        break;
        case 3:
        
        break;
        
        case 4:
        break;
        case 5:
        break;
        case 6:
        break;
        default:
        break;
    }



} 