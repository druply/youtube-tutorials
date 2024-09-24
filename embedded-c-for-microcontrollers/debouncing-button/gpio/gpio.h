/*
 * gpio.h
 *
 *  Created on: Aug 30, 2024
 *      Author: rortega
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

#include "tm4c123gh6pm.h"
#include <stdint.h>

#define  PIN(x)     (1u<<x)

#define PORTF_CLOCK     (PIN(5))
#define PORTE_CLOCK     (PIN(4))
#define PORTD_CLOCK     (PIN(3))
#define PORTC_CLOCK     (PIN(2))
#define PORTB_CLOCK     (PIN(1))
#define PORTA_CLOCK     (PIN(0))


// PORT F operations
#define     SET_PORTF_PIN(x)            GPIO_PORTF_DATA_R|=PIN(x)
#define     CLEAR_PORTF_PIN(x)          GPIO_PORTF_DATA_R&=~PIN(x)
#define     TOGGLE_PORTF_PIN(x)         GPIO_PORTF_DATA_R^=PIN(x)
#define     READ_PORTF_PIN(x)           (GPIO_PORTF_DATA_R&(PIN(x)))&&(PIN(x))

// PORT E operations
#define     SET_PORTE_PIN(x)            GPIO_PORTE_DATA_R|=(1<<x)
#define     CLEAR_PORTE_PIN(x)          GPIO_PORTE_DATA_R&=~(1<<x)
#define     TOGGLE_PORTE_PIN(x)         GPIO_PORTE_DATA_R^=(1<<x)
#define     READ_PORTE_PIN(x)           (GPIO_PORTE_DATA_R&(1<<x))&&(1<<x)

// PORT D operations
#define     SET_PORTD_PIN(x)            GPIO_PORTD_DATA_R|=(1<<x)
#define     CLEAR_PORTD_PIN(x)          GPIO_PORTD_DATA_R&=~(1<<x)
#define     TOGGLE_PORTD_PIN(x)         GPIO_PORTD_DATA_R^=(1<<x)
#define     READ_PORTD_PIN(x)           (GPIO_PORTD_DATA_R&(1<<x))&&(1<<x)

// PORT C operations
#define     SET_PORTC_PIN(x)            GPIO_PORTC_DATA_R|=(1<<x)
#define     CLEAR_PORTC_PIN(x)          GPIO_PORTC_DATA_R&=~(1<<x)
#define     TOGGLE_PORTC_PIN(x)         GPIO_PORTC_DATA_R^=(1<<x)
#define     READ_PORTC_PIN(x)           (GPIO_PORTC_DATA_R&(1<<x))&&(1<<x)

// PORT B operations
#define     SET_PORTB_PIN(x)            GPIO_PORTB_DATA_R|=(1<<x)
#define     CLEAR_PORTB_PIN(x)          GPIO_PORTB_DATA_R&=~(1<<x)
#define     TOGGLE_PORTB_PIN(x)         GPIO_PORTB_DATA_R^=(1<<x)
#define     READ_PORTB_PIN(x)           (GPIO_PORTB_DATA_R&(1<<x))&&(1<<x)

// PORT A operations
#define     SET_PORTA_PIN(x)            GPIO_PORTA_DATA_R|=(1<<x)
#define     CLEAR_PORTA_PIN(x)          GPIO_PORTA_DATA_R&=~(1<<x)
#define     TOGGLE_PORTA_PIN(x)         GPIO_PORTA_DATA_R^=(1<<x)
#define     READ_PORTA_PIN(x)           (GPIO_PORTA_DATA_R&(1<<x))&&(1<<x)


#define     SET_PIN(reg,x)            (reg|=PIN(x))
#define     CLEAR_PIN(reg,x)          (reg&=~PIN(x))
#define     TOGGLE_PIN(reg,x)         (reg^=PIN(x))
#define     READ_PIN(reg,x)           ((reg&PIN(x))&&PIN(x))

#define     WRITE_PIN(reg,pin,val)     ((val==0x01)?SET_PIN(reg,pin):CLEAR_PIN(reg,pin))


//*****************************************************************************
//
// Values that can be passed to GPIOPadConfigSet as the ui32Strength parameter,
// and returned by GPIOPadConfigGet in the *pui32Strength parameter.
//
//*****************************************************************************
#define GPIO_STRENGTH_2MA       0x00000001  // 2mA drive strength
#define GPIO_STRENGTH_4MA       0x00000002  // 4mA drive strength
#define GPIO_STRENGTH_6MA       0x00000065  // 6mA drive strength
#define GPIO_STRENGTH_8MA       0x00000066  // 8mA drive strength
#define GPIO_STRENGTH_8MA_SC    0x0000006E  // 8mA drive with slew rate control
#define GPIO_STRENGTH_10MA      0x00000075  // 10mA drive strength
#define GPIO_STRENGTH_12MA      0x00000077  // 12mA drive strength


//*****************************************************************************
//
// Values that can be passed to GPIOPadConfigSet as the ui32PadType parameter,
// and returned by GPIOPadConfigGet in the *pui32PadType parameter.
//
//*****************************************************************************
#define GPIO_PIN_TYPE_STD       0x00000008  // Push-pull
#define GPIO_PIN_TYPE_STD_WPU   0x0000000A  // Push-pull with weak pull-up
#define GPIO_PIN_TYPE_STD_WPD   0x0000000C  // Push-pull with weak pull-down
#define GPIO_PIN_TYPE_OD        0x00000009  // Open-drain
#define GPIO_PIN_TYPE_ANALOG    0x00000000  // Analog comparator
#define GPIO_PIN_TYPE_WAKE_HIGH 0x00000208  // Hibernate wake, high
#define GPIO_PIN_TYPE_WAKE_LOW  0x00000108  // Hibernate wake, low


enum mode_E {
    as_input = 0,
    as_output,
    as_interrupt
};

enum port_E {
    portA = 0,
    portB,
    portC,
    portD,
    portE,
    portF

};

struct gpio_S {
    uint8_t pin;
    enum port_E port;
    enum mode_E mode;
    uint32_t *reg;
};

typedef struct gpio_S gpio_config_T;
typedef enum mode_E pin_mode_T;

void gpioInit(void);
void configPinAsOutput(uint32_t reg, uint8_t pins);
void configPinAsInput(uint32_t reg, uint8_t pins) ;

void EdgeCounter_Init(void);

#endif /* GPIO_GPIO_H_ */
