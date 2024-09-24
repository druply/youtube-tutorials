/*
 * clock.c
 *
 *  Created on: Aug 30, 2024
 *      Author: rortega
 */
#include "clock.h"

static void rccConfig(const clock_config_T *config) {
    // bypass PLL
    SYSCTL_RCC_R |= SYSCTL_RCC_BYPASS;
    // clear xtal parameters
    SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;
    // select 16mhz crystal
    SYSCTL_RCC_R  |= config->crystal;
    // clear oscillator parameter
    SYSCTL_RCC_R &= ~SYSCTL_RCC_OSCSRC_M;// clear oscillator source field
    // select main oscillator
    SYSCTL_RCC_R += config->osc_source;
    // enable PLL
    SYSCTL_RCC_R &= ~SYSCTL_RCC_PWRDN;
    // select frequency divider
    SYSCTL_RCC_R = (SYSCTL_RCC_R&~0x03800000) // clear system clock divider field
                      + (config->frequency<<22);      // set the parameter frequency
    // wait for the PLL to lock by polling PLLLRIS
    while((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS)==0){};
    // enable use of PLL by clearing bypass
    SYSCTL_RCC_R &= ~SYSCTL_RCC_BYPASS;

}

static void rcc2Config(const clock_config_T *config) {
    // 0) configure the system to use RCC2 for advanced features
    //    such as 400 MHz PLL and non-integer System Clock Divisor
    SYSCTL_RCC2_R |= SYSCTL_RCC2_USERCC2;
    // 1) bypass PLL while initializing
    SYSCTL_RCC2_R |= SYSCTL_RCC2_BYPASS2;
    // 2) select the crystal value and oscillator source
    SYSCTL_RCC_R &= ~SYSCTL_RCC_XTAL_M;   // clear XTAL field
    SYSCTL_RCC_R += config->crystal;// select crystal
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_OSCSRC2_M;// clear oscillator source field
    SYSCTL_RCC2_R += config->osc_source;// select oscillator source
    // 3) activate PLL by clearing PWRDN
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_PWRDN2;
    // 4) set the desired system divider and the system divider least significant bit

    //if(div400 == 1){
    //    SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;  // use 400 MHz PLL
    //}

    //else {
    //    SYSCTL_RCC2_R |= SYSCTL_RCC2_DIV400;  // use 400 MHz PLL
    //}



    SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~0x1FC00000) // clear system clock divider field
                    + (config->frequency<<22);      // configure for 80 MHz clock
    // 5) wait for the PLL to lock by polling PLLLRIS
    while((SYSCTL_RIS_R&SYSCTL_RIS_PLLLRIS)==0){};
    // 6) enable use of PLL by clearing BYPASS
    SYSCTL_RCC2_R &= ~SYSCTL_RCC2_BYPASS2;
}


void clockConfig(const clock_config_T *config) {

    void (*funcPtr[])(const clock_config_T *conf) = {rccConfig, rcc2Config};

    (*funcPtr[config->mode])(config);

}
void clock_set_mode(enum OperationalMode mode) {

    if (mode == run) {
     // enter run mode configuration
    }

    if (mode == sleep) {
     // enter sleep mode configuration
      __asm("    wfi\n"
                 "    bx      lr\n");
 }

 if (mode == deep_sleep) {
     // enter deep_sleep mode configuration
         //
         // Enable deep-sleep.
         //
         NVIC_SYS_CTRL_R |= NVIC_SYS_CTRL_SLEEPDEEP;

         //
         // Wait for an interrupt.
         //
         __asm("    wfi\n"
         "    bx      lr\n");

         //
         // Disable deep-sleep so that a future sleep works correctly.
         //
         NVIC_SYS_CTRL_R &= ~(NVIC_SYS_CTRL_SLEEPDEEP);
  }

  if (mode == hibernate) {
      // enter hibernate mode configuration
  }
}