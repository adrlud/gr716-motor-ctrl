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

typedef struct {
    char gpio0to1;
    char gpio2to3;
    char gpio4to5;
    char gpio6to7;
    char gpio8to9;
    char gpio10to11;
    char gpio12to13;
    char gpio14to15;
    char gpio16to17;
    char gpio18to19;
    char gpio20to21;
    char gpio22to23;
    char gpio24to25;
    char gpio26to27;
    char gpio28to29;
    char gpio30to31;
    char gpio32to33;
    char gpio34to35;
    char gpio36to37;
    

} MUX_t;


//typedef struct GPIO_mux_ {};

volatile PWM_t* const pwm0 = (PWM_t*) PWM0_BASE;

void PWM_enable(volatile PWM_t *pwm, int pwm_channel);
void PWM_disable(volatile PWM_t *pwm, int pwm_channel);
void PWM_deadband(volatile PWM_t *pwm, int pwm_channel, unsigned char compare);


