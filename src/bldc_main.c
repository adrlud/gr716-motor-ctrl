#include <gr716/gr716.h>
#include <bldc/bldc.h>


int main(){
    BLDC_start_motor();
    
    /* The controll algoritm for the motor is completly interrupt based */
    while (1);
      
  
}
