#include <bcc/bcc.h>

#include <gr716/gr716.h>
#include <bldc/bldc.h>
#include <drv/timer.h>
#include <drv/spi.h>


#define TEST_ADC_TRANS 4
#define TEST_ADC_NBR   0
#define TEST_ADC_IRQ 7

int testcntr,i;
static volatile unsigned int adcdata0[TEST_ADC_TRANS+1]; 
static volatile unsigned int adcdata0_status[TEST_ADC_TRANS+1]; 

const int WATCHDOG_SUB = 6;
int timer0_ret;
int timer1_ret;
struct timer_priv *timer0_device;
struct timer_priv *timer1_device;
void *timer0_wdsub;
void *timer0_sub;
void *timer1_sub;

int gr716_adc_timers_enable(void)   {

  /* Register drivers */
  timer_autoinit();

  timer0_ret = timer_dev_count();
  //printf("%d TIMER units present\n", timer0_ret);
  if (timer0_ret == 0) {
    //printf("Timer Init Error - No TIMER units found \n");
    return -1; /* Failure */
  }

  timer0_device = timer_open(0);
  if (NULL == timer0_device) {
    return -1; /* Failure */
  }
  timer1_device = timer_open(1);
  if (NULL == timer1_device) {
    return -1; /* Failure */
  }

  /* Open watchdog */
  timer0_wdsub = timer_sub_open(timer0_device, WATCHDOG_SUB);

  /* Kick the watchdog */
  timer_kick(timer0_wdsub);

  /* Temporarily disable watchdog. */
  timer_stop(timer0_wdsub);

  /* Timer Unit #1 Init */
  // Setup Timer1 counter 0 and 1
  //   - Set reload to a very slow tick for test purpose only
  timer_set_scaler(timer1_device,0xFFFF);
  timer_set_scaler_reload(timer1_device,0x0500);
  timer1_sub = timer_sub_open(timer1_device, 0);
  timer_set_reload(timer1_sub, 0xffff);
  timer_set_ctrl(timer1_sub, GPTIMER_CTRL_LD | GPTIMER_CTRL_RS | GPTIMER_CTRL_EN);
  timer1_sub = timer_sub_open(timer1_device, 1);
  timer_set_reload(timer1_sub, 0xffff);
  timer_set_ctrl(timer1_sub, GPTIMER_CTRL_LD | GPTIMER_CTRL_RS | GPTIMER_CTRL_EN);

  /* Enable Timer Tick */
  bcc_timer_tick_init();

  return 0;

}

void event_test_adc0(void *ptr, int nbr)   {
 
 // Store data in memory
 adcdata0[testcntr] = gr716_adc_channel_val(TEST_ADC_NBR);

 // Update test counter
 testcntr = testcntr + 1;
}

int main(){
    BLDC_start_motor();
    

  /* Report start */
  printf("Start ADC test \n");

  /* Clear test counter */
  testcntr = 0;

  /* Clear ADC store (default values) */
  for ( i = 0; i < TEST_ADC_TRANS; i++ ) {
    adcdata0[i] = 0;
  }

  /* Init IRQ, Timers, ADC and PWM */
  int ret_adc;
  ret_adc = adc_test_init();
  if (ret_adc != 0) {
   gr716_adc_channel_disable(TEST_ADC_NBR);
   return -1; /* Failure */
  }

  printf("wait.... \n");
  gr716_wait_cycles(10000);

 gr716_adc_timers_enable();



  /* Enable traps and set PIL to Zero to catch all interrupts in test*/
  void *ictx0;
  int ret;

  /* Dynamic remapping of ADCn IRQ from n -> TEST_ADC_IRQ */
  ret = gr716_adc_int_map_set(TEST_ADC_NBR,TEST_ADC_IRQ);

  ictx0 = bcc_isr_register(TEST_ADC_IRQ, event_test_adc0, NULL);
  if ((ret != BCC_OK) | (ictx0 == NULL)) {
   return -1; /* Failure */
  }
  bcc_int_unmask(TEST_ADC_IRQ);

  /* Print ADC Samples */
  for ( i = 0; i < TEST_ADC_TRANS; i++ ) {
    printf("[%i] = %i \n",i,adcdata0[i]);
  }

  /* Report end of test and go to sleep */
  printf("End of ADC test \n");
  gr716_adc_clk_disable(TEST_ADC_NBR);
  gr716_adc_channel_disable(TEST_ADC_NBR);
  


    
    /* The controll algoritm for the motor is completly interrupt based */
    while (1);
      
  
}
