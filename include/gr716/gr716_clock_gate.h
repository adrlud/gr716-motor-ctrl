#ifndef __GR716_CLOCK_GATE_H_
#define __GR716_CLOCK_GATE_H_

/*
 *  Clock gate register
 * 
 */ 

struct gckcfg_apb {
    volatile unsigned int  unlock;
    volatile unsigned int  clocken;
    volatile unsigned int  reset;
    volatile unsigned int  override;
};

#endif