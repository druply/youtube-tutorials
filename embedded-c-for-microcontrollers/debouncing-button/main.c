
#include <stdint.h>
#include "hw_port.h"
#include "gpio.h"
#include "clock.h"

#define SW1  0u
#define SW2  4u


#define READ_SW(x)  READ_PIN(GPIO_PORTF_DATA_R, x)

/**
 * main.c
 */
int main(void)
{

    /*
     * Initialization steps include:
     *  1.- Initialize clock
     *  2.- Initialize gpio
     */

    clock_config_T clock_config;

    clock_config.mode = rcc1;
    clock_config.frequency = Bus80MHz;
    clock_config.osc_source = SYSCTL_RCC2_OSCSRC2_MO;
    clock_config.crystal = SYSCTL_RCC_XTAL_16MHZ;

    clockConfig(&clock_config);

    int ctr;
    int flag_button_pressed;

    //configuration for switch
    SYSCTL_RCGCGPIO_R |= PORTF_CLOCK;  // activate port F
    configPinAsInput(GPIO_PORTF_BASE, PIN(SW1) | PIN(SW2));

   ctr = 0;
   flag_button_pressed = 0;

   while(1) {

       if(READ_SW(SW2) == 0) {
           ctr++;
       }
       else {
           ctr = 0;
       }

       if (ctr > 100) {
           flag_button_pressed = 1;
       }
   }




	return 0;
}
