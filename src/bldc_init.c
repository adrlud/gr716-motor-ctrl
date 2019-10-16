#include <bldc/bldc.h>
#include <gr716/gr716.h>
#include <stdio.h>




/*PWM IO */

int pwm0_out_nbrs[] = {49, 51, 53, 55, 57, 59};
/*Global config*/
#define PWM0_GSCALER 0x31

#define PWM_CHANNEL_COUNT 6

/*PWM channel config*/
#define PWM0_NBR           0                          // Select PWM output [0 - 7]
#define PWM1_NBR           1                          // Select PWM output [0 - 7]
#define PWM2_NBR           2                          // Select PWM output [0 - 7]
#define PWM3_NBR           3                          // Select PWM output [0 - 7]
#define PWM4_NBR           4                          // Select PWM output [0 - 7]
#define PWM5_NBR           5                          // Select PWM output [0 - 7]
#define PWM0_MODE          PWM_MODE_ONECOMP           // Select PWM mode {OneCompMode, DualCompMode, ExtCompMode}
#define PWM0_METH          PWM_MODE_ASYMMETRIC        // Select Asymmetric or symmetric method {Asymmetric, Symmetric}
#define PWM0_PAIR          PWM_PAIR_NONE              // Pair mode {none, enable, zero}
#define PWM0_POLARITY      PWM_POLARITY_LOW          // Select polarity {low, high}
#define PWM3_POLARITY      PWM_POLARITY_LOW          // Select polarity {low, high}
#define PWM0_FLIP          PWM_FLIP_NONE              // Output flip bit {none, flip}
#define PWM0_DEADBAND      PWM_DEAD_NONE              // Enable deadband {none, deadband}
#define PWM0_TRIGGER       PWM_TRIGGER_NONE           // Select trigger mode {none, enable}
#define PWM0_IRQEN         PWM_IRQ_NONE               // Generate interrupt  {none, enable, comp}
#define PWM0_SCALER        0                          // Set clock scaler scaler [0 - 7]
#define PWM0_ISCALER       0                          // Set interrupt scaler scaler [0 - 7]
#define PWM0_DSCALER       0                          // Set deadband scaler [0 - 7]
#define PWM0_PERIOD        100 //0xffff                     // PWM period register [0 - 0xFFFF]
#define PWM0_COMP1         0 //0x1fff                     // COMP1 dead band compare register [0 - 0xFFFF]
#define PWM3_COMP1         0                           // comp1 low polarity = unmodulasted pwm 
#define PWM0_COMP2         0x0                        // COMP2 dead band compare register [0 - 0xFFFF]
#define PWM0_DBCOMP        0x0                        // PWM dead band compare register [0 - 0xFF]

/* GPIO config*/
#define GPIO_DIR 0x0
#define GPIO_IRQ 0x1
#define GPIO_POL 0x0
#define GPIO_EDGE 0x1 



#define U_LOW 0
#define U_HIGH 1
#define V_LOW 2
#define V_HIGH 3
#define W_LOW 4
#define W_HIGH 5

unsigned int comm_state;



void commutate(){

    //unsigned char hall = ((gr716_gpio_read(40)<<0) | (gr716_gpio_read(41)<<1) | (gr716_gpio_read(42)<<2));
    
    /*if(0){

        switch (hall)
            {
            case (0b00000010):
                comm_state = 1;
                break;
            case (0b00000011):
                comm_state = 2;
                break;
            case (0b00000001):
                comm_state = 3;
                break;
            case (0b00000101):
                comm_state = 4;
                break;
            case (0b00000100):
                comm_state = 5;
                break;
            case (0b00000110):
                comm_state = 6;
                break;
            default:
                //omm_state++;
                break;
            }

    }*/
   


    switch(comm_state){

        case 1:
            gr716_pwm0_disable(W_HIGH);
            gr716_pwm0_enable(U_HIGH);
        break;
        case 2:
            gr716_pwm0_disable(V_LOW);
            gr716_pwm0_enable(W_LOW);
        break;
        case 3:
            gr716_pwm0_disable(U_HIGH);
            gr716_pwm0_enable(V_HIGH);
        break;
        case 4:
            gr716_pwm0_disable(W_LOW);
            gr716_pwm0_enable(U_LOW);
        break; 
        case 5:
            gr716_pwm0_disable(V_HIGH);
            gr716_pwm0_enable(W_HIGH);
        break;
        case 6:
            gr716_pwm0_disable(U_LOW);
            gr716_pwm0_enable(V_LOW); 
            comm_state = 0;
        break;

        default:
            for(int i = 0; i<6; i++)
                gr716_pwm0_disable(i);
        break;       
    }
    comm_state++;
}



void PWM_init(){
    

    /*Enable PWM clockgate*/

    if (gr716_pwm0_clk_enable() != 0){
        printf("Failed to enable pwm0 clockgate");
        return;
    }
    
    
    /*Setup PWM generator*/
    gr716_pwm0_init(PWM0_GSCALER);
    /*Setup each PWM channel*/
     gr716_pwm0_config( PWM0_NBR,
                        PWM0_MODE, PWM0_METH, PWM0_TRIGGER, PWM0_SCALER, 
                        PWM0_IRQEN, PWM0_ISCALER, PWM0_PAIR, PWM0_POLARITY,
                        PWM0_FLIP, PWM0_DEADBAND, PWM0_DSCALER, 
                        PWM0_PERIOD,  
                        PWM3_COMP1, PWM0_COMP2,   
                        PWM0_DBCOMP);
    
    gr716_pwm0_config(  PWM1_NBR,
                        PWM0_MODE, PWM0_METH, PWM0_TRIGGER, PWM0_SCALER, 
                        PWM0_IRQEN, PWM0_ISCALER, PWM0_PAIR, PWM0_POLARITY,
                        PWM0_FLIP, PWM0_DEADBAND, PWM0_DSCALER, 
                        PWM0_PERIOD,  
                        PWM0_COMP1, PWM0_COMP2,   
                        PWM0_DBCOMP);

    gr716_pwm0_config(  PWM2_NBR,
                        PWM0_MODE, PWM0_METH, PWM0_TRIGGER, PWM0_SCALER, 
                        PWM0_IRQEN, PWM0_ISCALER, PWM0_PAIR, PWM0_POLARITY,
                        PWM0_FLIP, PWM0_DEADBAND, PWM0_DSCALER, 
                        PWM0_PERIOD,  
                        PWM3_COMP1, PWM0_COMP2,   
                        PWM0_DBCOMP);
    
    gr716_pwm0_config(  PWM3_NBR,
                        PWM0_MODE, PWM0_METH, PWM0_TRIGGER, PWM0_SCALER, 
                        PWM0_IRQEN, PWM0_ISCALER, PWM0_PAIR, PWM0_POLARITY,
                        PWM0_FLIP, PWM0_DEADBAND, PWM0_DSCALER, 
                        PWM0_PERIOD,  
                        PWM0_COMP1, PWM0_COMP2,   
                        PWM0_DBCOMP);
    
    gr716_pwm0_config(  PWM4_NBR,
                        PWM0_MODE, PWM0_METH, PWM0_TRIGGER, PWM0_SCALER, 
                        PWM0_IRQEN, PWM0_ISCALER, PWM0_PAIR, PWM0_POLARITY,
                        PWM0_FLIP, PWM0_DEADBAND, PWM0_DSCALER, 
                        PWM0_PERIOD,  
                        PWM0_COMP1, PWM0_COMP2,   
                        PWM0_DBCOMP);
    
    gr716_pwm0_config(  PWM5_NBR,
                        PWM0_MODE, PWM0_METH, PWM0_TRIGGER, PWM0_SCALER, 
                        PWM0_IRQEN, PWM0_ISCALER, PWM0_PAIR, PWM0_POLARITY,
                        PWM0_FLIP, PWM0_DEADBAND, PWM0_DSCALER, 
                        PWM0_PERIOD,  
                        PWM0_COMP1, PWM0_COMP2,   
                        PWM0_DBCOMP);
    
    gr716_pwm0_global_enable(0);
    for(int i = 0; i<6; i++){

        gr716_pwm0_enable(i);
        gr716_sleep_10ms(10000);
        gr716_pwm0_disable(i);
    }
    gr716_pwm0_global_enable(0);
    
}

void GPIO_init(){

    //läs in hall sensorer för att ställa in polaritet på flank
    int hall_a;
    int hall_b;
    int hall_c;

    if (gr716_gpio_read(40))
        hall_a = 0;
    else
        hall_a = 1;
        
    if (gr716_gpio_read(41))
        hall_b = 0;
    else
        hall_b = 1;

    if (gr716_gpio_read(42))
        hall_c = 0;
    else
        hall_c = 1;



    gr716_gpio_config(40,GPIO_DIR, GPIO_IRQ, hall_a, GPIO_EDGE,1);
    gr716_gpio_config(41,GPIO_DIR, GPIO_IRQ, hall_b, GPIO_EDGE,1);
    gr716_gpio_config(42,GPIO_DIR, GPIO_IRQ, hall_c, GPIO_EDGE,1);


    
    unsigned char hall = ((gr716_gpio_read(40)<<0) | (gr716_gpio_read(41)<<1) | (gr716_gpio_read(42)<<2));
    
    switch (hall)
    {
    case (0b00000010):
        comm_state = 1;
        break;
    case (0b00000011):
        comm_state = 2;
        break;
    case (0b00000001):
        comm_state = 3;
        break;
    case (0b00000101):
        comm_state = 4;
        break;
    case (0b00000100):
        comm_state = 5;
        break;
    case (0b00000110):
        comm_state = 6;
        break;
    default:
        //comm_state++;
        break;
    }
 
    bcc_int_map_set(38, 18); 
    bcc_isr_register(18, interrupt_handler, NULL);
    bcc_int_unmask(18);
}

void BLDC_init(){
  int ret_gpio;
    for(int i = 0; i < PWM_CHANNEL_COUNT; i++){
       ret_gpio = gr716_pinfunc(pwm0_out_nbrs[i], IO_MODE_PWM);
       ret_gpio = gr716_pinmode(pwm0_out_nbrs[i], IO_MODE_OUTPUT, IO_MODE_PWM);
    }

    commutate();
    
}


int main(){
    
    
    PWM_init();
    GPIO_init();
    BLDC_init();
    
    
    for(int i = 0; i < 12; i++){
        commutate();
        gr716_sleep_10ms(100000-(i*5000));
    }
    
    while(1);
   
   
  
    
  


}