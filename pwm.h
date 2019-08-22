#define PWM0_BASE 0x80310000

#define CORE_CTRL_REG 0x0
#define PER_REG 0x20
#define COMP_REG 0x24
#define CTRL_REG 0x2C

#define CHANNEL_COUNT 7 //n-1

typedef struct 
{
    int period;
    int compare;
    int dead_bnd; 
    int ctrl;
} PWM_reg_t;



typedef struct {
    int core_ctrl;
    int scal_rld_reg;
    int intrpt_pnd_reg;
    int cap_reg1;
    int cap_reg2;
    int reserved0;
    int reserver1;
    int reserved2;
    PWM_reg_t channel[CHANNEL_COUNT];
} PWM_t;

volatile PWM_t* const pwm0 = (PWM_t*) PWM0_BASE;