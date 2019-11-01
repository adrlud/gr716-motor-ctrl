
#include <gr716/gr716.h>

uint32_t gr716_adc_channel_enable(uint32_t aunit,
                                        uint32_t channel, uint32_t mode, uint32_t inputmode, 
                                        uint32_t oversamp, uint32_t events,
                                        uint32_t trigger, uint32_t source, uint32_t irqen, 
                                        uint32_t bypass, uint32_t gain, 
                                        uint32_t rate, uint32_t srate, uint32_t freq)
{
  /* ADC Init */
  volatile struct gradc_apb *adc0_base = (struct gradc_apb *) (ADC0_BASE + (aunit * 0x1000));


  unsigned int scaler;
  scaler = (freq / (rate*20));
  

  // Workout Sequence divisor
  unsigned int divisor;
  divisor = ((srate+1) / scaler);


  // Error checks
  if (rate > 300000)  {
    return BCC_FAIL;  
  } else if ((inputmode == ADC_INMODE_SINGLE) & ((gain > ADC_GAIN_0db) | (bypass != ADC_BYPASS_ENABLE))) {
   
    return BCC_FAIL;
  } else if (mode > ADC_MODE_SEQ_CONT) {
    
    return BCC_FAIL;
  } else {

    // Setup Pre-Amplifier
    adc0_base->pacfg   = REGSET(adc0_base->pacfg, PAG, gain);            // Set Gain
    adc0_base->pacfg   = REGSET(adc0_base->pacfg, PAB, bypass);          // Set bypass

    // Setup ADC0 (and analog mux)
    adc0_base->acfg   = REGSET(adc0_base->acfg, AM,  inputmode);         // Single ended mode select
    adc0_base->acfg   = REGSET(adc0_base->acfg, CS,  channel);           // Select channel
    adc0_base->acfg   = REGSET(adc0_base->acfg, AL,  0x0);               // Disable low and high range check
    adc0_base->acfg   = REGSET(adc0_base->acfg, AH,  0x0);     
    adc0_base->acfg   = REGSET(adc0_base->acfg, AS,  0x0);               // Disable conversion start when ADC during setup
    adc0_base->acfg   = REGSET(adc0_base->acfg, AC,  scaler);            // Set scaler
    adc0_base->acfg   = REGSET(adc0_base->acfg, AEN, 0x1);               // Enable (Power-On) ADC

    // Enable oversampling
    adc0_base->asampc = REGSET(adc0_base->asampc, AOC, oversamp);        // number consecutive samples
    adc0_base->asampc = REGSET(adc0_base->asampc, AE, events);           // number of events
    
    // Sequencer
    if (mode == ADC_MODE_SINGLE) {
        adc0_base->aseqc  = REGSET(adc0_base->aseqc, SE, 0);             // Disable sequencer
        adc0_base->aseqc  = REGSET(adc0_base->aseqc, SC, 0);                          
    } else if (mode == ADC_MODE_SEQ) {
        adc0_base->aseqc  = REGSET(adc0_base->aseqc, SE, 1);             // Enable sequencer
        adc0_base->aseqc  = REGSET(adc0_base->aseqc, SC, 0);             // Enable sequencer only once...
    } else {
        adc0_base->aseqc  = REGSET(adc0_base->aseqc, SE, 1);             // Enable sequencer
        adc0_base->aseqc  = REGSET(adc0_base->aseqc, SC, 1);             // Enable sequencer cont   
    } 
    adc0_base->aseqc  = REGSET(adc0_base->aseqc, SQ, trigger);           
    adc0_base->aseqc  = REGSET(adc0_base->aseqc, SD, divisor);            
    if (irqen == ADC_IRQ_AUTO) {
        adc0_base->aseqc  = REGSET(adc0_base->aseqc, ACC, 0x1);          // Auto clear for DMA Trigger 
    } else {
        adc0_base->aseqc  = REGSET(adc0_base->aseqc, ACC, 0x0);          // NO Auto clear 
    }

    // Select sync source
    adc0_base->async  = source;                                          
    
    // Enable interrupt
    if ((irqen == ADC_IRQ_AUTO) | (irqen == ADC_IRQ_ENABLE)) {
     adc0_base->amask = REGSET(adc0_base->amask,ME, 1);
     adc0_base->amask = REGSET(adc0_base->amask,ML, 0);
     adc0_base->amask = REGSET(adc0_base->amask,MH, 0);
     if (mode != ADC_MODE_SINGLE) {
      adc0_base->amask = REGSET(adc0_base->amask,MS, 1);
     } else {
      adc0_base->amask = REGSET(adc0_base->amask,MS, 0);
     }
    }

    // Enable ADC 0
    adc0_base->acfg   = REGSET(adc0_base->acfg, AS, ADC_ENABLE); 
    return BCC_OK;
  }

}

/*
 * Remap ADC Channel Interrupt
 *
 * aunit         : Select ADC unit {[0 - 7]}
 * 
 */

uint32_t gr716_adc_int_map_set(uint32_t aunit, uint32_t airq)
{
  int ret;
  if (aunit == 0) {
    ret = bcc_int_map_set(28,airq);
  } else if (aunit == 1) {
    ret = bcc_int_map_set(29,airq); 
  } else if (aunit == 2) {
    ret = bcc_int_map_set(30,airq); 
  } else if (aunit == 3) {
    ret = bcc_int_map_set(31,airq); 
  } else if (aunit == 4) {
    ret = bcc_int_map_set(32,airq); 
  } else if (aunit == 5) {
    ret = bcc_int_map_set(33,airq); 
  } else if (aunit == 6) {
    ret = bcc_int_map_set(34,airq); 
  } else if (aunit == 7) {
    ret = bcc_int_map_set(35,airq); 
  } else {
    //printf("Wrong ADC unit number. No interrupt remmaping \n");
    ret =  BCC_FAIL; /* Failure */
  }
  return ret;
};

/*
 * Get ADC Channel Data
 *
 * aunit         : Select ADC unit {[0 - 7]}
 *
 * return: DATA
 * 
 */
        
uint32_t gr716_adc_channel_val(uint32_t aunit)
{

  /* ADC Init */
  volatile struct gradc_apb *adc0_base = (struct gradc_apb *) (ADC0_BASE + (aunit * 0x1000));

  // Retrun sample value ADC 0
  if (aunit == 0) {
   return (adc0_base->asq0 & 0x7FFFF);
  } else if (aunit == 4) {
    return (adc0_base->asq0 & 0x7FFFF); 
  } else {
    return (adc0_base->asq0 & 0x7FFFF);
  }
  

}

/*
 * Enable ADC Channel Clock enable
 *
 * aunit         : Select ADC unit {[0 - 7]}
 */
        

uint32_t gr716_adc_clk_enable(uint32_t aunit)
{

  // Pointers to clock gate block
  struct  gckcfg_apb *gckcfgbase1 = (struct gckcfg_apb *) (GRCLKGATE1_BASE);
    
  if (aunit == 0) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC0, CG_UNLOCK);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRADC0, CG_ENABLE);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRADC0, CG_RELEASE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC0, CG_LOCK); 
  }

  if (aunit == 1) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC1, CG_UNLOCK);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRADC1, CG_ENABLE);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRADC1, CG_RELEASE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC1, CG_LOCK); 
  }

  if (aunit == 2) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC2, CG_UNLOCK);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRADC2, CG_ENABLE);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRADC2, CG_RELEASE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC2, CG_LOCK); 
  }

  if (aunit == 3) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC3, CG_UNLOCK);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRADC3, CG_ENABLE);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRADC3, CG_RELEASE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC3, CG_LOCK); 
  }

  if (aunit == 4) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC4, CG_UNLOCK);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRADC4, CG_ENABLE);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRADC4, CG_RELEASE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC4, CG_LOCK); 
  }

  if (aunit == 5) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC5, CG_UNLOCK);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRADC5, CG_ENABLE);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRADC5, CG_RELEASE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC5, CG_LOCK); 
  }

  if (aunit == 6) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC6, CG_UNLOCK);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRADC6, CG_ENABLE);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRADC6, CG_RELEASE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC6, CG_LOCK); 
  }

  if (aunit == 7) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC7, CG_UNLOCK);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRADC7, CG_ENABLE);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRADC7, CG_RELEASE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC7, CG_LOCK); 
  }

  return BCC_OK;

}

/*
 * Disable ADC Channel
 *
 * aunit         : Select ADC unit {[0 - 7]}
 */

uint32_t gr716_adc_channel_disable(uint32_t aunit)
{
  // GRADC configuration registers
  struct gradc_apb {
    volatile unsigned int  acfg;               
  };

  /* ADC Init */
  volatile struct gradc_apb *adc0_base = (struct gradc_apb *) (ADC0_BASE + (aunit * 0x1000));

  // Disable  ADC 0
  adc0_base->acfg   = REGSET(adc0_base->acfg, AEN, 0x0);
  adc0_base->acfg   = REGSET(adc0_base->acfg, AS,  0x0); 

  return BCC_OK;

}

/*
 * Clock disable ADC Channel
 *
 * aunit         : Select ADC unit [0 - 7]
 */

uint32_t gr716_adc_clk_disable(uint32_t aunit)
{

  // Pointers to clock gate block
  struct  gckcfg_apb *gckcfgbase1 = (struct gckcfg_apb *) (GRCLKGATE1_BASE);

 if (aunit == 0) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC0, CG_UNLOCK);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRADC0, CG_RESET);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRADC0, CG_DISABLE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC0, CG_LOCK); 
  }

  if (aunit == 1) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC1, CG_UNLOCK);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRADC1, CG_RESET);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRADC1, CG_DISABLE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC1, CG_LOCK); 
  }

  if (aunit == 2) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC2, CG_UNLOCK);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRADC2, CG_RESET);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRADC2, CG_DISABLE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC2, CG_LOCK); 
  }

  if (aunit == 3) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC3, CG_UNLOCK);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRADC3, CG_RESET);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRADC3, CG_DISABLE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC3, CG_LOCK); 
  }

  if (aunit == 4) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC4, CG_UNLOCK);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRADC4, CG_RESET);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRADC4, CG_DISABLE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC4, CG_LOCK); 
  }

  if (aunit == 5) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC5, CG_UNLOCK);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRADC5, CG_RESET);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRADC5, CG_DISABLE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC5, CG_LOCK); 
  }

  if (aunit == 6) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC6, CG_UNLOCK);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRADC6, CG_RESET);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRADC6, CG_DISABLE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC6, CG_LOCK); 
  }

  if (aunit == 7) {  
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC7, CG_UNLOCK);
    gckcfgbase1->reset   = REGSET(gckcfgbase1->reset ,  CG_GRADC7, CG_RESET);
    gckcfgbase1->clocken = REGSET(gckcfgbase1->clocken, CG_GRADC7, CG_DISABLE);
    gckcfgbase1->unlock  = REGSET(gckcfgbase1->unlock,  CG_GRADC7, CG_LOCK); 
  }

  return BCC_OK;

}

/*
 * Clear IRQ ADC Channel
 *
 * aunit         : Select ADC unit {[0 - 7]}
 *
 * 
 */

uint32_t gr716_adc_clear_irq(uint32_t aunit)
{

  /* ADC Init */
  volatile struct gradc_apb *adc0_base = (struct gradc_apb *) (ADC0_BASE + (aunit * 0x1000));

  //Clear all irq bits AINT IS IH IL IE
  adc0_base->aint   = REGSET(adc0_base->aint, IE, 0x0);
  adc0_base->aint   = REGSET(adc0_base->aint, IL, 0x0);
  adc0_base->aint   = REGSET(adc0_base->aint, IH, 0x0);
  adc0_base->aint   = REGSET(adc0_base->aint, IS, 0x0);
 
  return BCC_OK;

}