/*
 * GR716 ADC configuration and setup
 *
 * Functions:
 *  1. gr716_adc_channel_enable  - Enable ADC Channel
 *  2. gr716_adc_int_map_set     - Remap ADC Channel Interrupt
 *  3. gr716_adc_channel_val     - Get ADC Channel Data
 *  4. gr716_adc_clk_enable      - Enable ADC Channel Clock enable
 *  5. gr716_adc_channel_disable - Disable ADC Channel
 *  6. gr716_adc_clk_disable     - Clock disable ADC Channel
 *  7. gr716_adc_clear_irq       - Clear IRQ ADC Channel
*/

#include <bcc/bcc.h>

#ifndef __GR716_ADC_H_
#define __GR716_ADC_H_

/**** ADC Parameters and functions ****/

#define ADC_ENABLE 1
#define ADC_DISABLE 0

/* ADC configiuration register */
#define AM_BIT   0
#define AM_MASK  0x1
//#define AR_BIT   1
//#define AR_MASK  0x1
#define CS_BIT   2
#define CS_MASK  0xF
#define AL_BIT   7
#define AL_MASK  0x1
#define AH_BIT   8
#define AH_MASK  0x1
#define PS_BIT   8
#define PS_MASK  0x1F

#define AS_BIT   14
#define AS_MASK  0x1
#define AEN_BIT  15
#define AEN_MASK 0x1
#define AC_BIT   16
#define AC_MASK  0xFFFF

/* ADC sampling control register */
#define AOC_BIT  0
#define AOC_MASK 0xFFFF
#define AE_BIT   16
#define AE_MASK  0x3

/* ADC sequence control register */
#define SD_BIT   0
#define SD_MASK  0xFFFF
#define SP_BIT   16
#define SP_MASK  0x7
#define ACC_BIT  27
#define ACC_MASK 0x1
#define SC_BIT   28
#define SC_MASK  0x1
#define SE_BIT   29
#define SE_MASK  0x1
#define SI_BIT   30
#define SI_MASK  0x1
#define SQ_BIT   31
#define SQ_MASK  0x1

/* ADC sequence sync register */
#define S0_BIT   0
#define S0_MASK  0x1
#define S1_BIT   1
#define S1_MASK  0x1
#define S2_BIT   2
#define S2_MASK  0x1

/* ADC status register */
#define AD_BIT   0
#define AD_MASK  0x7FFFF
#define AES_BIT  31
#define AES_MASK 0x1

/* ADC interrupt register */
#define IE_BIT   0
#define IE_MASK  0x1
#define IL_BIT   1
#define IL_MASK  0x1
#define IH_BIT   2
#define IH_MASK  0x1
#define IS_BIT   3
#define IS_MASK  0x1

/* ADC mask register */
#define ME_BIT   0
#define ME_MASK  0x1
#define ML_BIT   1
#define ML_MASK  0x1
#define MH_BIT   2
#define MH_MASK  0x1
#define MS_BIT   3
#define MS_MASK  0x1

/* Pre-Amplifier and MUX configiuration register */
#define PAG_BIT   0
#define PAG_MASK  0x3
#define PAB_BIT   2
#define PAB_MASK  0x1
#define PAH_BIT  3
#define PAH_MASK 0x1
#define PAL_BIT  4
#define PAL_MASK 0x1

/* ADC High level detection register */
#define AHT_BIT   0
#define AHT_MASK  0x7FFFF

/* ADC Low level detection register */
#define ALT_BIT   0
#define ALT_MASK  0x7FFFF

/* ADC sequence register */
#define AD_BIT   0
#define AD_MASK  0x7FFFF

/*
 * Enable ADC Channel
 *
 * aunit         : Select ADC unit {[0 - 7]}
 * channel       : Select channel {[0 - 7], temp, voltage}
 * mode          : Select sampling mode {single, seq, seq_cont}
 * inputmode     : Select mode {single, diff}
 * oversamp      : Select number of samples [0 - 65535]
 * events        : Select number of sequential events [0 - 4]
 * trigger       : Select trigger mode {none, enable}
 * source        : Select trigger source [0 - 47]
 * irqen         : generate interrupt  {none, enable, auto}
 * zero          : amplifer autozeroing {none, enable}
 * bypass        : amplifer bypass {none, enable}
 * gain          : amplifer bypass {0, 6, 12} db
 * rate          : Set ADC sample rate [1*1000 Hz - 600*1000 Hz]
 * srate         : Sequence rate [0 - 65535] Msps
 * freq          : System frequency [0 - 50*1000*1000 Hz]
 *
 * return: BCC response
 * 
 * Modes: 
 * 1. single     - TBD.  
 * 
 * 2. seq        - TBD. 
 * 
 * 3. seq_cont   - TBD. 
 * 
 */

#define ADC_CHANNEL_TEMP     0x8
#define ADC_CHANNEL_VOLT     0x8

#define ADC_MODE_SINGLE      0x0
#define ADC_MODE_SEQ         0x1
#define ADC_MODE_SEQ_CONT    0x2

#define ADC_INMODE_DIFF      0x0
#define ADC_INMODE_SINGLE    0x1

#define ADC_TRIGGER_NONE     0x0
#define ADC_TRIGGER_ENABLE   0x1

#define ADC_IRQ_NONE         0x0
#define ADC_IRQ_ENABLE       0x1
#define ADC_IRQ_AUTO         0x2

#define ADC_BYPASS_NONE      0x0
#define ADC_BYPASS_ENABLE    0x1

#define ADC_GAIN_0db         0x0
#define ADC_GAIN_6db         0x1
#define ADC_GAIN_12db        0x2

// Define trigger source
// See Datasheet for source description
#define ADC_TRIG_TIM0_CNT0   0
#define ADC_TRIG_TIM0_CNT1   1
#define ADC_TRIG_TIM0_CNT2   2
#define ADC_TRIG_TIM0_CNT3   3
#define ADC_TRIG_TIM0_CNT4   4
#define ADC_TRIG_TIM0_CNT5   5
#define ADC_TRIG_TIM0_CNT6   6
#define ADC_TRIG_TIM0_CNT7   7
#define ADC_TRIG_TIM1_CNT0   8
#define ADC_TRIG_TIM1_CNT1   9
#define ADC_TRIG_TIM1_CNT2   10
#define ADC_TRIG_TIM1_CNT3   11
#define ADC_TRIG_TIM1_CNT4   12
#define ADC_TRIG_TIM1_CNT5   13
#define ADC_TRIG_TIM1_CNT6   14
#define ADC_TRIG_TIM1_CNT7   15
#define ADC_TRIG_GPIO0       16
#define ADC_TRIG_GPIO1       17
#define ADC_TRIG_GPIO2       18
#define ADC_TRIG_GPIO3       19
#define ADC_TRIG_GPIO4       20
#define ADC_TRIG_GPIO5       21
#define ADC_TRIG_GPIO6       22
#define ADC_TRIG_GPIO7       23
#define ADC_TRIG_GPIO56      24
#define ADC_TRIG_GPIO57      25
#define ADC_TRIG_GPIO58      26
#define ADC_TRIG_GPIO59      27
#define ADC_TRIG_GPIO60      28
#define ADC_TRIG_GPIO61      29
#define ADC_TRIG_GPIO62      30
#define ADC_TRIG_GPIO63      31
#define ADC_TRIG_PWMO_TICK0  32
#define ADC_TRIG_PWMO_TICK1  33
#define ADC_TRIG_PWMO_TICK2  34
#define ADC_TRIG_PWMO_TICK3  35
#define ADC_TRIG_PWMO_TICK4  36
#define ADC_TRIG_PWMO_TICK5  37
#define ADC_TRIG_PWMO_TICK6  38
#define ADC_TRIG_PWMO_TICK7  39
#define ADC_TRIG_PWM1_TICK0  40
#define ADC_TRIG_PWM1_TICK1  41
#define ADC_TRIG_PWM1_TICK2  42
#define ADC_TRIG_PWM1_TICK3  43
#define ADC_TRIG_PWM1_TICK4  44
#define ADC_TRIG_PWM1_TICK5  45
#define ADC_TRIG_PWM1_TICK6  46
#define ADC_TRIG_PWM1_TICK7  47

static uint32_t gr716_adc_channel_enable(uint32_t aunit,
                                        uint32_t channel, uint32_t mode, uint32_t inputmode, 
                                        uint32_t oversamp, uint32_t events,
                                        uint32_t trigger, uint32_t source, uint32_t irqen, 
                                        uint32_t bypass, uint32_t gain, 
                                        uint32_t rate, uint32_t srate, uint32_t freq)
{

  // GRADC configuration registers
  struct gradc_apb {
    volatile unsigned int  acfg;    
    volatile unsigned int  asampc;       
    volatile unsigned int  aseqc;       
    volatile unsigned int  async;       
    volatile unsigned int  asts;       
    volatile unsigned int  aint;       
    volatile unsigned int  amask;       
    volatile unsigned int  pacfg;       
    volatile unsigned int  ahlvl;       
    volatile unsigned int  allvl;       
    volatile unsigned int  dummy0;       
    volatile unsigned int  asq0;       
    volatile unsigned int  asq1;       
    volatile unsigned int  asq2;       
    volatile unsigned int  asq3;            
  };

  /* ADC Init */
  volatile struct gradc_apb *adc0_base = (struct gradc_apb *) (ADC0_BASE + (aunit * 0x1000));

  // Workout scaler value i.e. ADC frequency for wanted sample rate
  unsigned int scaler;
  scaler = (freq / (rate*20));
  //printf("scaler : %d  \n", scaler); 

  // Workout Sequence divisor
  unsigned int divisor;
  divisor = ((srate+1) / scaler);
  //printf("divisor : %d  \n", divisor); 

  // Error checks....
  if (rate > 300000)  {
    //printf("Fail mode: Do not run to fast due to power and performance degradation \n");
    return BCC_FAIL;  
  } else if ((inputmode == ADC_INMODE_SINGLE) & ((gain > ADC_GAIN_0db) | (bypass != ADC_BYPASS_ENABLE))) {
    //printf("Fail mode: Do not use gain or amplifier in single ended mode \n");
    return BCC_FAIL;
  } else if (mode > ADC_MODE_SEQ_CONT) {
    //printf("Fail mode: Mode does not exist \n");
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
    adc0_base->aseqc  = REGSET(adc0_base->aseqc, SQ, trigger);           // Enable sequence synchronization enable
    adc0_base->aseqc  = REGSET(adc0_base->aseqc, SD, divisor);           // Sample rate if no sync source is selected
    if (irqen == ADC_IRQ_AUTO) {
        adc0_base->aseqc  = REGSET(adc0_base->aseqc, ACC, 0x1);          // Auto clear for DMA Trigger 
    } else {
        adc0_base->aseqc  = REGSET(adc0_base->aseqc, ACC, 0x0);          // NO Auto clear 
    }

    // Select sync source
    adc0_base->async  = source;                                          // Enable sync source from Timer0 counter 1
    
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
 * return: OK or NOK
 * 
 */

static uint32_t gr716_adc_int_map_set(uint32_t aunit, uint32_t airq)
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

static uint32_t gr716_adc_channel_val(uint32_t aunit)
{
  // GRADC configuration registers
  struct gradc_apb {
    volatile unsigned int  acfg;    
    volatile unsigned int  asampc;       
    volatile unsigned int  aseqc;       
    volatile unsigned int  async;       
    volatile unsigned int  asts;       
    volatile unsigned int  aint;       
    volatile unsigned int  amask;       
    volatile unsigned int  pacfg;       
    volatile unsigned int  ahlvl;       
    volatile unsigned int  allvl;       
    volatile unsigned int  dummy0;       
    volatile unsigned int  asq0;       
    volatile unsigned int  asq1;       
    volatile unsigned int  asq2;       
    volatile unsigned int  asq3;                         
  };

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
 *
 * return: DATA
 * 
 */

static uint32_t gr716_adc_clk_enable(uint32_t aunit)
{

  // Clock gate and IO configuration registers
  struct gckcfg_apb {
   volatile unsigned int  unlock;
   volatile unsigned int  clocken;
   volatile unsigned int  reset;
   volatile unsigned int  override;
  };

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
 *
 * return: BCC response
 * 
 */

static uint32_t gr716_adc_channel_disable(uint32_t aunit)
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
 * aunit         : Select ADC unit {[0 - 7]}
 *
 * return: BCC response
 * 
 */

static uint32_t gr716_adc_clk_disable(uint32_t aunit)
{

  // Clock gate and IO configuration registers
  struct gckcfg_apb {
   volatile unsigned int  unlock;
   volatile unsigned int  clocken;
   volatile unsigned int  reset;
   volatile unsigned int  override;
  };

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
 * return: BCC response
 * 
 * TODO : Specify which IRQ to be cleared
 * 
 */

static uint32_t gr716_adc_clear_irq(uint32_t aunit)
{
// GRADC configuration registers
  struct gradc_apb {
    volatile unsigned int  acfg;    
    volatile unsigned int  asampc;       
    volatile unsigned int  aseqc;       
    volatile unsigned int  async;       
    volatile unsigned int  asts;       
    volatile unsigned int  aint;       
    volatile unsigned int  amask;       
    volatile unsigned int  pacfg;       
    volatile unsigned int  ahlvl;       
    volatile unsigned int  allvl;       
    volatile unsigned int  dummy0;       
    volatile unsigned int  asq0;       
    volatile unsigned int  asq1;       
    volatile unsigned int  asq2;       
    volatile unsigned int  asq3;            
  };

  /* ADC Init */
  volatile struct gradc_apb *adc0_base = (struct gradc_apb *) (ADC0_BASE + (aunit * 0x1000));

  //Clear all irq bits AINT IS IH IL IE
  adc0_base->aint   = REGSET(adc0_base->aint, IE, 0x0);
  adc0_base->aint   = REGSET(adc0_base->aint, IL, 0x0);
  adc0_base->aint   = REGSET(adc0_base->aint, IH, 0x0);
  adc0_base->aint   = REGSET(adc0_base->aint, IS, 0x0);
 
  return BCC_OK;

}

#endif
