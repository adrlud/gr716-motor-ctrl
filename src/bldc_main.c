#include <gr716/gr716.h>
#include <bldc/bldc.h>


int duty;
int dutyChanged;
int main(){
    BLDC_start_motor();
    while (1){
      
        if (dutyChanged != duty){
            dutyChanged = duty;
            gr716_pwm0_comp_update( 1, duty, 0);
            gr716_pwm0_comp_update( 3, duty, 0);
            gr716_pwm0_comp_update( 5, duty, 0);
        }
    }
}
