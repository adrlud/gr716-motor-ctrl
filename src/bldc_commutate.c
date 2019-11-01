#include <bldc/bldc.h>
#include <gr716/gr716.h>


void commutate(){
    
    unsigned char hall = ((gr716_gpio_read(40)<<0) | (gr716_gpio_read(41)<<1) | (gr716_gpio_read(42)<<2));

    switch(hall){
    
        case 0b000000010:
            gr716_pwm0_disable(W_HIGH);
            gr716_pwm0_enable(U_HIGH);
        break;
        case 0b00000011:
            gr716_pwm0_enable(V_LOW);
            gr716_pwm0_disable(U_LOW);
        break;
        case 0b00000001:
            gr716_pwm0_disable(V_HIGH);
            gr716_pwm0_enable(W_HIGH);
        break;
        case 0b00000101:
            gr716_pwm0_enable(U_LOW);
            gr716_pwm0_disable(W_LOW);
        break; 
        case 0b00000100:
            gr716_pwm0_disable(U_HIGH);
            gr716_pwm0_enable(V_HIGH);
            
        break;
        case 0b00000110:
            gr716_pwm0_enable(W_LOW);
            gr716_pwm0_disable(V_LOW);
        break;

        default:
            for(int i = 0; i<6; i++)
                gr716_pwm0_disable(i);
        break;       
    }
}