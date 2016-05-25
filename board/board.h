/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for the STMicroelectronics STM3210C-EVAL evaluation board.
 */

//#define GPIOD_LED1              7
//#define GPIOD_LED2              13
//#define GPIOD_LED3              3
//#define GPIOD_LED4              4

/*
 * Board identifier.
 */
#define BOARD_SK_MSTM32F107
#define BOARD_NAME              "SK-MSTM32F107"

/*
 * Board frequencies.
 */
#define STM32_LSECLK            32768
#define STM32_HSECLK            25000000

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define STM32F10X_CL
//#define STM32F107xC

/*
 * IO pins assignments.
 */
#define GPIOA_PA0	              0
#define GPIOA_PA1			          1
#define GPIOA_PA2	              2
#define GPIOA_PA3	              3
#define GPIOA_SPI_NSS           4
#define GPIOA_SPI_SCK           5
#define GPIOA_SPI_MISO          6
#define GPIOA_SPI_MOSI          7
#define GPIOA_PA8	              8
#define GPIOA_VBUS_FS           9
#define GPIOA_OTG_FS_ID         10
#define GPIOA_OTG_FS_DM         11
#define GPIOA_OTG_FS_DP         12
#define GPIOA_SWDIO             13
#define GPIOA_SWCLK             14
#define GPIOA_PA15              15

#define GPIOB_PB0	              0
#define GPIOB_PB1	              1
#define GPIOB_PB2               2
#define GPIOB_SWO               3
#define GPIOB_PB4               4
#define GPIOB_PB5               5
#define GPIOB_PB6               6
#define GPIOB_PB7               7
#define GPIOB_CAN_RX            8
#define GPIOB_CAN_TX            9
#define GPIOB_PB10       				10
#define GPIOB_PB11       				11
#define GPIOB_PB12              12
#define GPIOB_PB13              13
#define GPIOB_PB14			        14
#define GPIOB_PB15			        15

#define GPIOC_LED_STATUS1       0
#define GPIOC_PC1               1
#define GPIOC_SWITCH_USER       2
#define GPIOC_PC3               3
#define GPIOC_PC4               4
#define GPIOC_PC5               5
#define GPIOC_PC6               6
#define GPIOC_PC7               7
#define GPIOC_PC8               8
#define GPIOC_PC9               9
#define GPIOC_PC10              10
#define GPIOC_PC11              11
#define GPIOC_PC12              12
#define GPIOC_PC13              13
#define GPIOC_PC14              14
#define GPIOC_PC15              15

#define GPIOD_CAN_RX            0
#define GPIOD_CAN_TX            1
#define GPIOD_PD2               2
#define GPIOD_PD3               3
#define GPIOD_PD4               4
#define GPIOD_U_TX              5
#define GPIOD_U_RX              6
#define GPIOD_PD7               7
#define GPIOD_PD8               8
#define GPIOD_PD9               9
#define GPIOD_PD10              10
#define GPIOD_PD11              11
#define GPIOD_PD12              12
#define GPIOD_PD13              13
#define GPIOD_PD14              14
#define GPIOD_PD15              15

#define SBIT(n)     (1<<(n))

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 *
 * The digits have the following meaning:
 *   0 - Analog input.
 *   1 - Push Pull output 10MHz.
 *   2 - Push Pull output 2MHz.
 *   3 - Push Pull output 50MHz.
 *   4 - Digital input.
 *   5 - Open Drain output 10MHz.
 *   6 - Open Drain output 2MHz.
 *   7 - Open Drain output 50MHz.
 *   8 - Digital input with PullUp or PullDown resistor depending on ODR.
 *   9 - Alternate Push Pull output 10MHz.
 *   A - Alternate Push Pull output 2MHz.
 *   B - Alternate Push Pull output 50MHz.
 *   C - Reserved.
 *   D - Alternate Open Drain output 10MHz.
 *   E - Alternate Open Drain output 2MHz.
 *   F - Alternate Open Drain output 50MHz.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_ANALOG_INPUT(n)         ((uint64_t)0<<(4*n))
#define PIN_DIG_INPUT_FLOATING(n)   ((uint64_t)4<<(4*n))
#define PIN_DIG_INPUT_PUPD(n)       ((uint64_t)8<<(4*n))
#define PIN_OUTPUT_PUSHPULL_10M(n)  ((uint64_t)1<<(4*n))
#define PIN_OUTPUT_PUSHPULL_50M(n)  ((uint64_t)3<<(4*n))
#define PIN_OUTPUT_PUSHPULL_2M(n)   ((uint64_t)2<<(4*n))
#define PIN_OUTPUT_OPENDRAIN_10M(n) ((uint64_t)5<<(4*n))
#define PIN_OUTPUT_OPENDRAIN_2M(n)  ((uint64_t)6<<(4*n))
#define PIN_OUTPUT_OPENDRAIN_50M(n) ((uint64_t)7<<(4*n))
#define PIN_OUT_ALTERNATE_PUSHPULL_10M(n)   ((uint64_t)0x9<<(4*n))
#define PIN_OUT_ALTERNATE_PUSHPULL_2M(n)    ((uint64_t)0xA<<(4*n))
#define PIN_OUT_ALTERNATE_PUSHPULL_50M(n)   ((uint64_t)0xB<<(4*n))
#define PIN_OUT_ALTERNATE_OPENDRAIN_10M(n)  ((uint64_t)0xD<<(4*n))
#define PIN_OUT_ALTERNATE_OPENDRAIN_2M(n)   ((uint64_t)0xE<<(4*n))
#define PIN_OUT_ALTERNATE_OPENDRAIN_50M(n)  ((uint64_t)0xF<<(4*n))
#define PIN_SETUP_MASK(n)                   ((uint64_t)0xF<<(4*n))   

/*
 * Port A setup.
 * Everything input with pull-up except:
 * PA2  - Alternate output          (GPIOA_USART_TX).
 * PA3  - Normal input              (GPIOA_USART_RX).
 * PA5  - Push Pull output          (GPIOA_LED_GREEN).
 * PA13 - Pull-up input             (GPIOA_SWDIO).
 * PA14 - Pull-down input           (GPIOA_SWCLK).
 */
#define VAL_GPIOACR            (                                      \
                                PIN_DIG_INPUT_FLOATING(GPIOA_PA0)  |  \
                                PIN_DIG_INPUT_FLOATING(GPIOA_PA1)  |  \
                                PIN_DIG_INPUT_FLOATING(GPIOA_PA2)  |  \
                                PIN_DIG_INPUT_FLOATING(GPIOA_PA3)  |  \
                                PIN_OUTPUT_PUSHPULL_10M(GPIOA_SPI_NSS)          |  \
                                PIN_OUT_ALTERNATE_PUSHPULL_10M(GPIOA_SPI_MOSI)  |  \
                                PIN_OUT_ALTERNATE_PUSHPULL_10M(GPIOA_SPI_SCK)   |  \
                                PIN_DIG_INPUT_FLOATING(GPIOA_SPI_MISO)          |  \
                                PIN_DIG_INPUT_FLOATING(GPIOA_PA8)     |  \
                                PIN_DIG_INPUT_PUPD(GPIOA_VBUS_FS)     |  \
                                PIN_DIG_INPUT_PUPD(GPIOA_OTG_FS_ID)   |  \
                                PIN_OUT_ALTERNATE_PUSHPULL_50M(GPIOA_OTG_FS_DM)   |   \
                                PIN_OUT_ALTERNATE_PUSHPULL_50M(GPIOA_OTG_FS_DP)   |   \
                                PIN_DIG_INPUT_PUPD(GPIOA_SWDIO) |   \
                                PIN_DIG_INPUT_PUPD(GPIOA_SWCLK) |   \
                                PIN_DIG_INPUT_PUPD(GPIOA_PA15)      \
                                )
#define VAL_GPIOACRL            ((uint32_t)VAL_GPIOACR)      /*  PA7...PA0 */
#define VAL_GPIOACRH            (VAL_GPIOACR >> 32)            /* PA15...PA8 */
/** Port output data register (GPIOx_ODR) (x=A..G)
    Bits 15:0
    ODRy: Port output data (y= 0 .. 15)
    These bits can be read and written by software and can be accessed in Word mode only.
 @note 
    For atomic bit set/reset, the ODR bits can be individually set and cleared by writing to
    the GPIOx_BSRR register (x = A .. G). */
#define VAL_GPIOAODR            (                      \
                                /*SBIT( GPIOA_USB_DM    ) |*/ \
                                /*SBIT( GPIOA_USB_DP    ) |*/ \
                                SBIT( GPIOA_SPI_NSS     ) |   \
                                SBIT( GPIOA_SWDIO     ) | \
                                SBIT( GPIOA_PA15      )   \
                                )

/*
 * Port B setup.
 * Everything input with pull-up except:
 * PB3  - Pull-up input             (GPIOA_SWO).
 */
#define VAL_GPIOBCR             (              \
                                PIN_DIG_INPUT_FLOATING(GPIOB_PB0  )  |  \
                                PIN_DIG_INPUT_FLOATING(GPIOB_PB1  )  |  \
                                PIN_DIG_INPUT_PUPD(GPIOB_PB2 )  |  \
                                PIN_DIG_INPUT_PUPD(GPIOB_SWO )  |  \
                                PIN_DIG_INPUT_PUPD(GPIOB_PB4 )  |  \
                                PIN_DIG_INPUT_PUPD(GPIOB_PB5 )  |  \
                                PIN_DIG_INPUT_PUPD(GPIOB_PB6 )  |  \
                                PIN_DIG_INPUT_PUPD(GPIOB_PB7 )  |  \
                                PIN_DIG_INPUT_FLOATING(GPIOB_CAN_RX)    |  \
                                PIN_DIG_INPUT_FLOATING(GPIOB_CAN_TX)    |  \
                                PIN_DIG_INPUT_PUPD(GPIOB_PB10)    |  \
                                PIN_DIG_INPUT_PUPD(GPIOB_PB11)    |  \
                                PIN_DIG_INPUT_PUPD(GPIOB_PB12)          |  \
                                PIN_DIG_INPUT_PUPD(GPIOB_PB13)          |  \
                                PIN_DIG_INPUT_FLOATING(GPIOB_PB14) |  \
                                PIN_DIG_INPUT_FLOATING(GPIOB_PB15)  \
                                )                                       
#define VAL_GPIOBCRL            ((uint32_t)VAL_GPIOBCR) /*  PB7...PB0 */
#define VAL_GPIOBCRH            (VAL_GPIOBCR >> 32)      /* PB15...PB8 */
/** Port output data register (GPIOx_ODR) (x=A..G)
    Bits 15:0
    ODRy: Port output data (y= 0 .. 15)
    These bits can be read and written by software and can be accessed in Word mode only.
 @note 
    For atomic bit set/reset, the ODR bits can be individually set and cleared by writing to
    the GPIOx_BSRR register (x = A .. G). */
#define VAL_GPIOBODR            0xFFFFFFFF

/*
 * Port C setup.
 * Everything input with pull-up except:
 * PC13 - Normal input              (GPIOC_BUTTON).
 */
#define VAL_GPIOCCR             (               \
                                 PIN_OUTPUT_PUSHPULL_2M(GPIOC_LED_STATUS1)     |    \
                                 PIN_DIG_INPUT_PUPD(GPIOC_PC1)          |    \
                                 PIN_DIG_INPUT_PUPD(GPIOC_SWITCH_USER)  |    \
                                 PIN_DIG_INPUT_FLOATING(GPIOC_PC3) |    \
                                 PIN_DIG_INPUT_FLOATING(GPIOC_PC4) |    \
                                 PIN_DIG_INPUT_FLOATING(GPIOC_PC5) |    \
                                 PIN_DIG_INPUT_FLOATING(GPIOC_PC6) |    \
                                 PIN_DIG_INPUT_FLOATING(GPIOC_PC7) |    \
                                 PIN_DIG_INPUT_PUPD(GPIOC_PC8)     |    \
                                 PIN_DIG_INPUT_PUPD(GPIOC_PC9)     |    \
                                 PIN_DIG_INPUT_FLOATING(GPIOC_PC10) | \
                                 PIN_DIG_INPUT_FLOATING(GPIOC_PC11)        | \
                                 PIN_DIG_INPUT_FLOATING(GPIOC_PC12)      | \
                                 PIN_DIG_INPUT_PUPD(GPIOC_PC13)               | \
                                 PIN_DIG_INPUT_FLOATING(GPIOC_PC14)           | \
                                 PIN_DIG_INPUT_FLOATING(GPIOC_PC15)             \
                                )                                             
#define VAL_GPIOCCRL            ((uint32_t)VAL_GPIOCCR)   /*  PC7...PC0 */    
#define VAL_GPIOCCRH            (VAL_GPIOCCR >> 32)        /* PC15...PC8 */    
/** Port output data register (GPIOx_ODR) (x=A..G)
    Bits 15:0
    ODRy: Port output data (y= 0 .. 15)
    These bits can be read and written by software and can be accessed in Word mode only.
 @note 
    For atomic bit set/reset, the ODR bits can be individually set and cleared by writing to
    the GPIOx_BSRR register (x = A .. G). */
#define VAL_GPIOCODR            0xFFFFFFFF

/*
 * Port D setup.
 * Everything input with pull-up except:
 * PD0  - Normal input              (GPIOD_OSC_IN).
 * PD1  - Normal input              (GPIOD_OSC_OUT).
 */
#define VAL_GPIODCR             (                 \
                                PIN_DIG_INPUT_FLOATING(GPIOD_CAN_RX)  |   \
                                PIN_DIG_INPUT_FLOATING(GPIOD_CAN_TX)  |   \
                                PIN_DIG_INPUT_PUPD(GPIOD_PD2)         |   \
                                PIN_DIG_INPUT_PUPD(GPIOD_PD3)         |   \
                                PIN_DIG_INPUT_PUPD(GPIOD_PD4)         |   \
                                PIN_DIG_INPUT_PUPD(GPIOD_U_RX)        |   \
                                PIN_OUT_ALTERNATE_PUSHPULL_2M(GPIOD_U_TX) |   \
                                PIN_DIG_INPUT_PUPD(GPIOD_PD7)         |   \
                                PIN_DIG_INPUT_PUPD(GPIOD_PD8)         |   \
                                PIN_DIG_INPUT_PUPD(GPIOD_PD9)         |   \
                                PIN_DIG_INPUT_PUPD(GPIOD_PD10)        |   \
                                PIN_DIG_INPUT_PUPD(GPIOD_PD11)        |   \
                                PIN_DIG_INPUT_PUPD(GPIOD_PD12)        |   \
                                PIN_DIG_INPUT_PUPD(GPIOD_PD13)        |   \
                                PIN_DIG_INPUT_PUPD(GPIOD_PD14)        |   \
                                PIN_DIG_INPUT_PUPD(GPIOD_PD15)            \
                                )

#define VAL_GPIODCRL            ((uint32_t)VAL_GPIODCR)      /*  PD7...PD0 */
#define VAL_GPIODCRH            (VAL_GPIODCR >> 32)          /* PD15...PD8 */
#define VAL_GPIODODR            0xFFFFFFFF

/*
 * Port E setup.
 * Everything input with pull-up except:
 */
#define VAL_GPIOECRL            0x88888888      /*  PE7...PE0 */
#define VAL_GPIOECRH            0x88888888      /* PE15...PE8 */
#define VAL_GPIOEODR            0xFFFFFFFF



#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
