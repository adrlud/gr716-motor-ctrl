#include "pwm.h"


void PWN_init(volatile PWM_t *pwm/*, int pwm_id*/){
    pwm->core_ctrl |= 0x1;
    pwm->per |= 0x1000;
    pwm->comp |= 0x500;
    pwm->ctrl_reg |= 0x1;
}



int main(){
    PWN_init(pwm0);
}