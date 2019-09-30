#include "pwm.h"
#include <drv/regs/grgpio.h>
#include <stdio.h>
#include <stdint.h>



volatile  MUX_t * MUX_gpio = (MUX_t *) 0x8000d000;

volatile struct grgpio_regs *gpio0 = (void*) 0x8030C000;

void PWM_GPIO_setup(){
    
}

void PWM_reset(volatile PWM_t *pwm, int pwm_channel){
    
    pwm->channel[pwm_channel].ctrl = 0x0;
    pwm->channel[pwm_channel].ctrl = 0x1;
}



void PWM_set_duty_cycle(volatile PWM_t *pwm,int pwm_channel, double duty_cycle){
    if (duty_cycle < 0 || duty_cycle > 100){
        printf("Error duty_cycle invalid");
        return;
    }
    pwm_channel /= 2;
    double quote = duty_cycle / 100;
    pwm->channel[pwm_channel].compare = pwm->channel[pwm_channel].period * quote;
    PWM_reset(pwm, pwm_channel);
}


void PWM_init(volatile PWM_t *pwm, int pwm_channel, int period){

    // enable:ar PWM generatorn
    pwm->core_ctrl |= 0x1;


    //Fungerar bara upp till PWM2
    
    if (pwm_channel == 0)
        MUX_gpio->gpio0to1 |= 0xA;
    
    if (pwm_channel == 2)
        MUX_gpio->gpio2to3 |= 0xA;

    pwm_channel /= 2;

    pwm->scal_rld_reg = 0xFFFF;
    pwm->scal_rld_reg = 0x31;
    
    //Reset period och compare register
    pwm->channel[pwm_channel].period = 0;
    pwm->channel[pwm_channel].compare = 0x0;
    
    pwm->channel[pwm_channel].period = period; 
    pwm->channel[pwm_channel].compare = period/2;
    PWM_reset(pwm, pwm_channel);
}

void PWM_enable(volatile PWM_t *pwm, int pwm_channel){
    pwm->channel[pwm_channel].ctrl = 0x1;
}

void PWM_disable(volatile PWM_t *pwm, int pwm_channel){
    pwm->channel[pwm_channel].ctrl = 0x0;
}

void PWM_deadband(volatile PWM_t *pwm, int pwm_channel, unsigned char compare){
    pwm->channel[pwm_channel].dead_bnd = compare;
    if(compare == 0)
        pwm->channel[pwm_channel].ctrl &= ~(1 << 21);
    else
        pwm->channel[pwm_channel].ctrl |= 1 << 21;
    
}



int main(){
    
    PWM_init(pwm0, 0, 100);
    PWM_init(pwm0, 2, 100);

    PWM_set_duty_cycle(pwm0, 0, 11);
    PWM_set_duty_cycle(pwm0, 2, 93);

}