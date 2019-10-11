
/*
 * GR716 register address and mapping
 *
 *   - This file contains address to internal functions in GR716
 *   - Macros for setting and clearing bits are used in GR716 functions
 *     Functions require '_mask' and ''_bit' filed
*/

#include <bcc/bcc.h>

#ifndef __GR716_REG_H_
#define __GR716_REG_H_

// Marcos for setting and clearing bits in registers
#define REGCLR(reg,fld) (reg&~((fld##_MASK)<<(fld##_BIT)))
#define REGSET(reg,fld,val) (REGCLR(reg,fld) | (((val)&(fld##_MASK))<<fld##_BIT))

#define REGCLRIO(reg,nbr) (reg&~(0xF<<(4*nbr)))
#define REGSETIO(reg,nbr,val) (REGCLRIO(reg,nbr) | (((val)&0xF)<<(4*nbr)))

#define REGCLRIOMODE(reg,nbr) (reg&~(0x1<<(nbr)))
#define REGSETIOMODE(reg,nbr,val) (REGCLRIOMODE(reg,nbr) | (((val)&0x1)<<(nbr)))

// System AHB Base address
#define AHBROM_BASE       0x00000000
#define PROM_BASE         0x01000000
#define SPIMCTRL0_BASE    0x02000000
#define SPIMCTRL1_BASE    0x04000000
#define DLRAM_BASE        0x30000000
#define ILRAM_BASE        0x31000000
#define SRAM_BASE         0x40000000
#define NVRAM_BASE        0x50000000

// APB0  Base address
#define APB0_BASE         0x80000000
#define FTMCTRL_BASE      0x80000000
#define DLRAMC_BASE       0x80001000
#define IRQMP_BASE        0x80002000
#define GPTIMER0_BASE     0x80003000
#define GPTIMER1_BASE     0x80004000
#define MEMPROTSYS_BASE   0x80005000
#define GRCLKGATE0_BASE   0x80006000
#define GRCLKGATE1_BASE   0x80007000
#define SYS_CFG_BOOT_BASE 0x80008000
#define L3STAT_BASE       0x80009000
#define AHBSTAT0_BASE     0x8000A000
#define ILRAMC_BASE       0x8000B000
#define GRSPWTDP_BASE     0x8000C000
#define SYS_CFG_IO_BASE   0x8000D000
#define SYS_CFG_CONF_BASE 0x8000E000
#define AHBUART_BASE      0x8000F000

// APB1 Base address
#define APB1_BASE         0x80100000
#define GRSPW_BASE        0x80100000
#define GR1553B_BASE      0x80101000
#define GRCAN0_BASE       0x80102000
#define GRCAN1_BASE       0x80103000
#define SPI2AHB_BASE      0x80104000
#define I2C2AHB_BASE      0x80105000
#define GRDMAC0_BASE      0x80106000
#define GRDMAC1_BASE      0x80107000
#define GRDMAC2_BASE      0x80108000
#define GRDMAC3_BASE      0x80109000
#define MEMPROTDMA_BASE   0x8010A000
#define BANDGAP_BASE      0x8010B000
#define BO_BASE           0x8010C000
#define PLL_BASE          0x8010D000
#define GRPWRX_BASE       0x8010E000
#define GRPWTX_BASE       0x8010F000

// APB2 Base address
#define APB3_BASE         0x80300000
#define APBUART0_BASE     0x80300000
#define APBUART1_BASE     0x80301000
#define APBUART2_BASE     0x80302000
#define APBUART3_BASE     0x80303000
#define APBUART4_BASE     0x80304000
#define APBUART5_BASE     0x80305000
#define AHBSTAT1_BASE     0x80306000
#define FTMCTRL_INT_BASE  0x80307000
#define GRADCDAC_BASE     0x80308000
#define SPICTRL0_BASE     0x80309000
#define SPICTRL1_BASE     0x8030A000
#define GPIO0_BASE        0x8030C000
#define GPIO0_SEQ1_BASE   0x8030C100
#define GPIO0_SEQ2_BASE   0x8030C120
#define GPIO0_SEQ3_BASE   0x8030C140
#define GPIO0_SEQ4_BASE   0x8030C160
#define GPIO0_SEQ_OFFSET  0x8030C180
#define GPIO1_BASE        0x8030D000
#define GPIO1_SEQ1_BASE   0x8030D100
#define GPIO1_SEQ2_BASE   0x8030D120
#define GPIO1_SEQ3_BASE   0x8030D140
#define GPIO1_SEQ4_BASE   0x8030D160
#define GPIO1_SEQ_OFFSET  0x8030D180
#define I2CMST0_BASE      0x8030E000
#define I2CMST1_BASE      0x8030F000
#define GRPWM0_BASE       0x80310000

// APB3 Base address
#define APB4_BASE         0x80400000
#define ADC0_BASE         0x80400000
#define ADC1_BASE         0x80401000
#define ADC2_BASE         0x80402000
#define ADC3_BASE         0x80403000
#define ADC4_BASE         0x80404000
#define ADC5_BASE         0x80405000
#define ADC6_BASE         0x80406000
#define ADC7_BASE         0x80407000
#define DAC0_BASE         0x80408000
#define DAC1_BASE         0x80409000
#define DAC2_BASE         0x8040A000
#define DAC3_BASE         0x8040B000
#define I2CSLV0_BASE      0x8040C000
#define I2CSLV1_BASE      0x8040D000
#define GRPWM1_BASE       0x80410000

#define CG_LOCK         0
#define CG_UNLOCK       1
#define CG_DISABLE      0
#define CG_ENABLE       1
#define CG_RELEASE      0
#define CG_RESET        1

// Clock Enable bits
#define CG_SPI2AHB_BIT      0
#define CG_I2C2AHB_BIT      1
#define CG_GRPWRX_BIT       2
#define CG_GRPWTX_BIT       3
#define CG_FTMCTRL_BIT      4
#define CG_SPIMCTRL0_BIT    5
#define CG_SPIMCTRL1_BIT    6
#define CG_SPICTRL0_BIT     7
#define CG_SPICTRL1_BIT     8
#define CG_I2CMST0_BIT      9
#define CG_I2CMST1_BIT      10
#define CG_I2CSLV0_BIT      11
#define CG_I2CSLV1_BIT      12
#define CG_GRADCDAC_BIT     13
#define CG_GRPWM0_BIT       14
#define CG_GRPWM1_BIT       15
#define CG_UART0_BIT        16
#define CG_UART1_BIT        17
#define CG_UART2_BIT        18
#define CG_UART3_BIT        19
#define CG_UART4_BIT        20
#define CG_UART5_BIT        21
#define CG_UART6_BIT        22
#define CG_UART7_BIT        23
#define CG_L3STAT_BIT       24 
#define CG_AUART_BIT        25
#define CG_MEMPROT_BIT      26
#define CG_ASUP_BIT         27
#define CG_GRSPWTDP_BIT     28
#define CG_GRSPI4S_BIT      29
#define CG_FTMCTRL_INT_BIT  30

#define CG_SPI2AHB_MASK     1
#define CG_I2C2AHB_MASK     1
#define CG_GRPWRX_MASK      1
#define CG_GRPWTX_MASK      1
#define CG_FTMCTRL_MASK     1
#define CG_SPIMCTRL0_MASK   1
#define CG_SPIMCTRL1_MASK   1
#define CG_SPICTRL0_MASK    1
#define CG_SPICTRL1_MASK    1
#define CG_I2CMST0_MASK     1
#define CG_I2CMST1_MASK     1
#define CG_I2CSLV0_MASK     1
#define CG_I2CSLV1_MASK     1
#define CG_GRADCDAC_MASK    1
#define CG_GRPWM0_MASK      1
#define CG_GRPWM1_MASK      1
#define CG_UART0_MASK       1
#define CG_UART1_MASK       1
#define CG_UART2_MASK       1
#define CG_UART3_MASK       1
#define CG_UART4_MASK       1
#define CG_UART5_MASK       1
#define CG_UART6_MASK       1
#define CG_UART7_MASK       1
#define CG_L3STAT_MASK      1 
#define CG_AUART_MASK       1
#define CG_MEMPROT_MASK     1
#define CG_ASUP_MASK        1
#define CG_GRSPWTDP_MASK    1
#define CG_GRSPI4S_MASK     1
#define CG_FTMCTRL_INT_MASK 1      

// Clock Enable bits
#define CG_GRDMA0_BIT      0
#define CG_GRDMA1_BIT      1
#define CG_GRDMA2_BIT      2
#define CG_GRDMA3_BIT      3
#define CG_1553_BIT        4
#define CG_CAN0_BIT        5
#define CG_CAN1_BIT        6
#define CG_SPW_BIT         7
#define CG_GRDAC0_BIT      8
#define CG_GRDAC1_BIT      9
#define CG_GRDAC2_BIT      10
#define CG_GRDAC3_BIT      11
#define CG_GRADC0_BIT      12
#define CG_GRADC1_BIT      13
#define CG_GRADC2_BIT      14
#define CG_GRADC3_BIT      15
#define CG_GRADC4_BIT      16
#define CG_GRADC5_BIT      17
#define CG_GRADC6_BIT      18
#define CG_GRADC7_BIT      19
#define CG_GSEQ0_BIT       20
#define CG_GSEQ1_BIT       21

#define CG_GRDMA0_MASK     1
#define CG_GRDMA1_MASK     1
#define CG_GRDMA2_MASK     1
#define CG_GRDMA3_MASK     1
#define CG_1553_MASK       1
#define CG_CAN0_MASK       1
#define CG_CAN1_MASK       1
#define CG_SPW_MASK        1
#define CG_GRDAC0_MASK     1
#define CG_GRDAC1_MASK     1
#define CG_GRDAC2_MASK     1
#define CG_GRDAC3_MASK     1
#define CG_GRADC0_MASK     1
#define CG_GRADC1_MASK     1
#define CG_GRADC2_MASK     1
#define CG_GRADC3_MASK     1
#define CG_GRADC4_MASK     1
#define CG_GRADC5_MASK     1
#define CG_GRADC6_MASK     1
#define CG_GRADC7_MASK     1
#define CG_GSEQ0__MASK     1
#define CG_GSEQ1__MASK     1
#define CG_GSEQ0_MASK      1
#define CG_GSEQ1_MASK      1

// IRQ
#define GRDMAC0_IRQ   6
#define GPTIMER0_IRQ  9
#define GPTIMER1_IRQ  53
#define I2CMST0_PIRQ  50
#define MEMSCRUB_IRQ  63
#define AHBSTAT1_IRQ  63

// Trap call numbers
#define INSTRUCTION_ACCESS_EXCEPTION  0x01
#define WINDOW_OVERFLOW               0x05
#define WINDOW_UNDERFLOW              0x06
#define DATA_ACCESS_EXCEPTION         0x09
#define DATA_STORE_ERROR              0x2B

/* gpio configuration */
#define GPIO_DEFAULT  0x0
#define ANALOG_ENABLE 0x8

/* gpio0 register */
#define GP0_BIT         0
#define GP0_MASK     0x0F
#define GP1_BIT         4
#define GP1_MASK     0x0F
#define GP2_BIT         8
#define GP2_MASK     0x0F
#define GP3_BIT        12
#define GP3_MASK     0x0F
#define GP4_BIT        16
#define GP4_MASK     0x0F
#define GP5_BIT        20
#define GP5_MASK     0x0F
#define GP6_BIT        24
#define GP6_MASK     0x0F
#define GP7_BIT        28
#define GP7_MASK     0x0F

/* gpio1 register */
#define GP8_BIT         0
#define GP8_MASK     0x0F
#define GP9_BIT         4
#define GP9_MASK     0x0F
#define GP10_BIT        8
#define GP10_MASK    0x0F
#define GP11_BIT       12
#define GP11_MASK    0x0F
#define GP12_BIT       16
#define GP12_MASK    0x0F
#define GP13_BIT       20
#define GP13_MASK    0x0F
#define GP14_BIT       24
#define GP14_MASK    0x0F
#define GP15_BIT       28
#define GP15_MASK    0x0F

/* gpio2 register */
#define GP16_BIT        0
#define GP16_MASK    0x0F
#define GP17_BIT        4
#define GP17_MASK    0x0F
#define GP18_BIT        8
#define GP18_MASK    0x0F
#define GP19_BIT       12
#define GP19_MASK    0x0F
#define GP20_BIT       16
#define GP20_MASK    0x0F
#define GP21_BIT       20
#define GP21_MASK    0x0F
#define GP22_BIT       24
#define GP22_MASK    0x0F
#define GP23_BIT       28
#define GP23_MASK    0x0F

/* gpio3 register */
#define GP24_BIT        0
#define GP24_MASK    0x0F
#define GP25_BIT        4
#define GP25_MASK    0x0F
#define GP26_BIT        8
#define GP26_MASK    0x0F
#define GP27_BIT       12
#define GP27_MASK    0x0F
#define GP28_BIT       16
#define GP28_MASK    0x0F
#define GP29_BIT       20
#define GP29_MASK    0x0F
#define GP30_BIT       24
#define GP30_MASK    0x0F
#define GP31_BIT       28
#define GP31_MASK    0x0F

/* gpio4 register */
#define GP32_BIT        0
#define GP32_MASK    0x0F
#define GP33_BIT        4
#define GP33_MASK    0x0F
#define GP34_BIT        8
#define GP34_MASK    0x0F
#define GP35_BIT       12
#define GP35_MASK    0x0F
#define GP36_BIT       16
#define GP36_MASK    0x0F
#define GP37_BIT       20
#define GP37_MASK    0x0F
#define GP38_BIT       24
#define GP38_MASK    0x0F
#define GP39_BIT       28
#define GP39_MASK    0x0F

/* gpio5 register */
#define GP40_BIT        0
#define GP40_MASK    0x0F
#define GP41_BIT        4
#define GP41_MASK    0x0F
#define GP42_BIT        8
#define GP42_MASK    0x0F
#define GP43_BIT       12
#define GP43_MASK    0x0F
#define GP44_BIT       16
#define GP44_MASK    0x0F
#define GP45_BIT       20
#define GP45_MASK    0x0F
#define GP46_BIT       24
#define GP46_MASK    0x0F
#define GP47_BIT       28
#define GP47_MASK    0x0F

/* gpio6 register */
#define GP48_BIT        0
#define GP48_MASK    0x0F
#define GP49_BIT        4
#define GP49_MASK    0x0F
#define GP50_BIT        8
#define GP50_MASK    0x0F
#define GP51_BIT       12
#define GP51_MASK    0x0F
#define GP52_BIT       16
#define GP52_MASK    0x0F
#define GP53_BIT       20
#define GP53_MASK    0x0F
#define GP54_BIT       24
#define GP54_MASK    0x0F
#define GP55_BIT       28
#define GP55_MASK    0x0F

/* gpio6 register */
#define GP56_BIT        0
#define GP56_MASK    0x0F
#define GP57_BIT        4
#define GP57_MASK    0x0F
#define GP58_BIT        8
#define GP58_MASK    0x0F
#define GP59_BIT       12
#define GP59_MASK    0x0F
#define GP60_BIT       16
#define GP60_MASK    0x0F
#define GP61_BIT       20
#define GP61_MASK    0x0F
#define GP62_BIT       24
#define GP62_MASK    0x0F
#define GP63_BIT       28
#define GP63_MASK    0x0F

/**** Clock Parameters and functions ****/

#define CLK_SOURCE_CLK   0x0 
#define CLK_SOURCE_SPW   0x1 
#define CLK_SOURCE_PLL   0x2 

#define SYS_MODE_NOM     0x0 
#define SYS_MODE_GEN     0x1 
#define SYS_MODE_SLEEP   0x2 

#endif