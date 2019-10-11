#include "../include/gr716.h" 

int gr716_wait_cycles(uint32_t wait_event)
{
  int event;
  event = 0;
  do {
   // Wait  
   event = event + 1;
  } while (event < wait_event);

  return 0;
}

/* This function waits "duration x 10 microseconds". */
void gr716_sleep_10ms(uint32_t duration)
{
        uint32_t t0;
        uint32_t tdiff;
        t0 = bcc_timer_get_us();
        do {
                uint32_t t1;
                //bcc_power_down();
                t1 = bcc_timer_get_us();
                tdiff = t1 - t0;
        } while (tdiff <= duration);
}