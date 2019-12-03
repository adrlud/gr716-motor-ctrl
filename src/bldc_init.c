#include <bldc/bldc.h>
#include <gr716/gr716.h>
#include <stdlib.h>
#include <bcc/bcc.h>
#include <bcc/regs/apbuart.h>
#include <bcc/bcc_param.h>


/*system clock 50 Mhz*/
const unsigned int __bsp_sysfreq = 50*1000*1000;

/*Global config*/
#define PWM0_GSCALER 0x31

#define PWM_CHANNEL_COUNT 6

/*PWM channel config*/
#define PWM0_NBR           0                          
#define PWM1_NBR           1                          
#define PWM2_NBR           2
#define PWM3_NBR           3             
#define PWM4_NBR           4                        
#define PWM5_NBR           5                        
#define PWM0_MODE          PWM_MODE_ONECOMP        
#define PWM0_METH          PWM_MODE_ASYMMETRIC       
#define PWM0_PAIR          PWM_PAIR_NONE            
#define PWM0_POLARITY      PWM_POLARITY_LOW        
#define PWM3_POLARITY      PWM_POLARITY_LOW       
#define PWM0_FLIP          PWM_FLIP_NONE    
#define PWM0_DEADBAND      PWM_DEAD_NONE            
#define PWM0_TRIGGER       PWM_TRIGGER_NONE          
#define PWM0_IRQEN         PWM_IRQ_NONE              
#define PWM0_SCALER        0                         
#define PWM0_ISCALER       0                          
#define PWM0_DSCALER       0                        
#define PWM0_PERIOD        100                         
#define PWM0_COMP1         40                    
#define PWM3_COMP1         0                           
#define PWM0_COMP2         0x0                      
#define PWM0_DBCOMP        0x0    

#define TEST_ADC_NBR            0                   // ADC unit [0 - 7] 
#define TEST_ADC_CHANNEL        0                   // Channel {[0-7], ADC_CHANNEL_TEMP, ADC_CHANNEL_VOLT}
#define TEST_ADC_MODE_SEQ_CONT  ADC_MODE_SEQ_CONT   // Mode (ADC_MODE_SINGLE,ADC_MODE_SEQ,ADC_MODE_SEQ_CONT)
#define TEST_ADC_INMODE_SINGLE  ADC_INMODE_SINGLE   // INput mode (ADC_INMODE_DIFF, ADC_INMODE_SINGLE)
#define TEST_ADC_SAMPLES        0                   // Use 0 consecutive samples
#define TEST_ADC_EVENTS         1                   // Over events...
#define TEST_ADC_TRIGGER_ENABLE ADC_TRIGGER_ENABLE  // Enable trigger (ADC_TRIGGER_ENABLE, ADC_TRIGGER_NONE)
#define TEST_ADC_TRIGGER_SOURCE ADC_TRIG_TIM1_CNT1  // Enable sync source from Timer1 counter 1 
#define TEST_ADC_IRQ_AUTO       ADC_IRQ_AUTO        // Enable IRQ (ADC_IRQ_NONE, ADC_IRQ_ENABLE, ADC_IRQ_AUTO)
#define TEST_ADC_BYPASS_ENABLE  ADC_BYPASS_ENABLE   // Bypass (ADC_BYPASS_NONE, ADC_BYPASS_ENABLE)
#define TEST_ADC_GAIN_0db       ADC_GAIN_0db        // Gain (ADC_GAIN_0db, ADC_GAIN_6db, ADC_GAIN_12db)
#define TEST_ADC_RATE_KHZ       200*1000            // Sample rate (1000Hz - 3000000Hz)
#define TEST_ADC_SEQ_RATE       1*1000              // Sequence (1 - 65535 Msps) rate if no sync source is selected
#define TEST_ADC_FREQ_KHZ       50*1000*1000        // System clock frequency (1Mhz - 50MHz)

/* Define number of sucessful ADC transfers to perform in test */
#define TEST_ADC_TRANS 4

/* Define ADC transfer interrupt in test */
#define TEST_ADC_IRQ 7

// Store of data in local RAM


/* Test Init */
int adc_test_init(){

  /* Enable and clear Brown Outs */
  //gr716_bo_enable_all();
  
  /* Enable Clocks */
  int ret_adc_clk;
  ret_adc_clk = gr716_adc_clk_enable(TEST_ADC_NBR);
  
  /* Setup IO MUX for selected ADC */
  // Enable:
  //   - ADC 0 -> Pin #37 (SYS.CFG.GP4.GP5)
  // ADC pin is related to external ADC channel and NOT ADC unit
  int adc_io_pin;
  int adc_io_diff_pin;
  adc_io_pin = 37 + TEST_ADC_CHANNEL;
  adc_io_diff_pin = 37 + TEST_ADC_CHANNEL + 1;
  int ret_io;
  ret_io = gr716_pinfunc(adc_io_pin,IO_MODE_ADC);
  if ((TEST_ADC_INMODE_SINGLE == ADC_INMODE_DIFF) && (ret_io == BCC_OK)) {
    ret_io = gr716_pinfunc(adc_io_diff_pin,IO_MODE_ADC);
  } else if ((TEST_ADC_INMODE_SINGLE == ADC_INMODE_DIFF) && (ret_io != BCC_OK)) {
    printf("Not able to to set diff pair inputs for ADC \n");
  }

  /* ADC Init */
  int ret_adc;
  ret_adc = gr716_adc_channel_enable(TEST_ADC_NBR,
                                     TEST_ADC_CHANNEL, TEST_ADC_MODE_SEQ_CONT, TEST_ADC_INMODE_SINGLE,
                                     TEST_ADC_SAMPLES, TEST_ADC_EVENTS,
                                     TEST_ADC_TRIGGER_ENABLE, TEST_ADC_TRIGGER_SOURCE, TEST_ADC_IRQ_AUTO,
                                     TEST_ADC_BYPASS_ENABLE, TEST_ADC_GAIN_0db,
                                     TEST_ADC_RATE_KHZ, TEST_ADC_SEQ_RATE, TEST_ADC_FREQ_KHZ);

  return (ret_adc | ret_io | ret_adc_clk);
}




void PWM_init(){
    /*Enable PWM clockgate*/

    if (gr716_pwm0_clk_enable() != 0){
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
                        PWM3_COMP1, PWM0_COMP2,   
                        PWM0_DBCOMP);
    
    gr716_pwm0_config(  PWM5_NBR,
                        PWM0_MODE, PWM0_METH, PWM0_TRIGGER, PWM0_SCALER, 
                        PWM0_IRQEN, PWM0_ISCALER, PWM0_PAIR, PWM0_POLARITY,
                        PWM0_FLIP, PWM0_DEADBAND, PWM0_DSCALER, 
                        PWM0_PERIOD,  
                        PWM0_COMP1, PWM0_COMP2,   
                        PWM0_DBCOMP);
    
    /*Make sure all pwm are reset with the new conigurations*/
    gr716_pwm0_global_enable(0);
    for(int i = 0; i<6; i++){

        gr716_pwm0_enable(i);
        gr716_sleep_10ms(10000);
        gr716_pwm0_disable(i);
    }
    gr716_pwm0_global_enable(0);
    
}

void GPIO_init(){
    /* Setup polarity on edge interrupt according to current state of hall to enable interrupt on change from the get go */
    /* The GPIO doesnt support interrupt on both rising and falling edge at the same time*/

    /*Configure hall sensors input pins to make them readable*/
    gr716_gpio_config(HALL_A, GPIO_DIR, GPIO_IRQ, GPIO_POL, GPIO_EDGE, GPIO_INPUT_ENABLE);
    gr716_gpio_config(HALL_B, GPIO_DIR, GPIO_IRQ, GPIO_POL, GPIO_EDGE, GPIO_INPUT_ENABLE);
    gr716_gpio_config(HALL_C, GPIO_DIR, GPIO_IRQ, GPIO_POL, GPIO_EDGE, GPIO_INPUT_ENABLE);

    int hall_a;
    int hall_b;
    int hall_c;

    /*Read hall sensors input*/
    if (gr716_gpio_read(HALL_A)) 
        hall_a = GPIO_FALLING;        /* If hall sensor is high, set interrupt to trigger on falling edge*/
    else
        hall_a = GPIO_RISING;         /* If hall sensor is low, set interrupt to trigger on rising edge*/
        
    if (gr716_gpio_read(HALL_B))
        hall_b = GPIO_FALLING;
    else
        hall_b = GPIO_RISING;

    if (gr716_gpio_read(HALL_C))
        hall_c = GPIO_FALLING;
    else
        hall_c = GPIO_RISING;

    /*Configure interrupt polarity again with the new values to the polarity bits*/
    gr716_gpio_config(HALL_A, GPIO_DIR, GPIO_IRQ, hall_a, GPIO_EDGE, GPIO_INPUT_ENABLE);
    gr716_gpio_config(HALL_B, GPIO_DIR, GPIO_IRQ, hall_b, GPIO_EDGE, GPIO_INPUT_ENABLE);
    gr716_gpio_config(HALL_C, GPIO_DIR, GPIO_IRQ, hall_c, GPIO_EDGE, GPIO_INPUT_ENABLE);


}

void interrupt_init(){
    /*Remap gpio1 interrupt vector*/
    bcc_int_map_set(38, 18);
    bcc_isr_register(18, interrupt_handler, NULL);
    bcc_int_unmask(18);
}

void BLDC_init(){
    
    /*PWM IO */
    /* pwm out nbrs shall contain the pwm output pins numbers*/
    int pwm0_out_nbrs[] = {49, 51, 53, 55, 57, 59};
    /*Set IO mux to PWM */
    for(int i = 0; i < PWM_CHANNEL_COUNT; i++){
       gr716_pinfunc(pwm0_out_nbrs[i], IO_MODE_PWM); /* pwm out nbrs shall contain the pwm output pins */
       gr716_pinmode(pwm0_out_nbrs[i], IO_MODE_OUTPUT, IO_MODE_PWM);
    }

    /* Read hall-sensors into one word*/
    unsigned char hall = ((gr716_gpio_read(40)<<0) | (gr716_gpio_read(41)<<1) | (gr716_gpio_read(42)<<2));
    
    /*Enable pwm accordingly to the phase*/
    switch (hall)
    {
    case (0b000000010):
        //comm_state = 1;
        gr716_pwm0_enable(V_LOW); 
        gr716_pwm0_enable(U_HIGH);
        break;
    case (0b00000011):
        //comm_state = 2;
        gr716_pwm0_enable(W_HIGH);
        gr716_pwm0_enable(V_LOW);
        break;
    case (0b00000001):
        //comm_state = 3;
        gr716_pwm0_enable(U_LOW);
        gr716_pwm0_enable(W_HIGH);
        break;
    case (0b00000101):
        //comm_state = 4;
        gr716_pwm0_enable(V_HIGH);
        gr716_pwm0_enable(U_LOW);
        break;
    case (0b00000100):
       // comm_state = 5;
        gr716_pwm0_enable(V_HIGH);
        gr716_pwm0_enable(W_LOW);
        break;
    case (0b00000110):
       // comm_state = 6;
        gr716_pwm0_enable(U_HIGH);
        gr716_pwm0_enable(W_LOW);
        break;
    default:
        break;
    
    }

}

void ADC_init(){
    /* TODO: Initilize for zero crossing detection */
}

void TIMER_init(){
    /* TODO: initilize for sending an irq after half of a phase time */
}



void BLDC_start_motor(){
    gr716_int_timestamp_config(18);
    PWM_init();
    GPIO_init();
    interrupt_init();
    BLDC_init();
    gr716_int_timestamp_config(18);
}

    
  
