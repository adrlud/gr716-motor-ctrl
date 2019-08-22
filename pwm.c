#include "pwm.h"
 

// 
void PWN_init(volatile PWM_t *pwm, int pwm_channel){
    pwm->core_ctrl |= 0x1;
    
    
    pwm->channel[0].period |= 0x200; 
    pwm->channel[0].compare |= 0x100;
    pwm->channel[0].ctrl |= 0x1;
}



int main(){
    PWN_init(pwm0, 0);
}