/*
 * gpio.c
 *
 *  Created on: Aug 30, 2024
 *      Author: rortega
 */

#include "gpio.h"
#include "hw_port.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

void gpioInit(void) {

    SYSCTL_RCGCGPIO_R |= PORTF_CLOCK;  // activate port F
    GPIO_PORTF_DIR_R |= PIN(2);   // make PF2 out (built-in blue LED)
    GPIO_PORTF_AFSEL_R &= ~PIN(2);// disable alt funct on PF2
    GPIO_PORTF_DEN_R |= PIN(2);   // enable digital I/O on PF2
    GPIO_PORTF_AMSEL_R = 0;     // disable analog functionality on PF

    //configure for sw1
    //GPIO_PORTF_DIR_R &= ~PIN(4); // make PF4 input
    //GPIO_PORTF_AFSEL_R &= ~PIN(4);// disable alt funct on PF4
    //GPIO_PORTF_DEN_R |= PIN(4);   // enable digital I/O on PF4
    //GPIO_PORTF_PUR_R |= PIN(4); // neable pull up resistor

    //we must unlock manually the PORTF0, this is to ensure safety for protected pins.
    GPIO_PORTF_LOCK_R = 0x4C4F434B; // unlock the GPIOCR register
    GPIO_PORTF_CR_R |= PIN(0); // enable write rights to the PF0;

    //configure for sw2
    GPIO_PORTF_DIR_R &= ~PIN(0); // make PF0 input
    GPIO_PORTF_AFSEL_R &= ~PIN(0);// disable alt funct on PF0
    GPIO_PORTF_DEN_R |= PIN(0);   // enable digital I/O on PF0
    GPIO_PORTF_PUR_R |= PIN(0); // neable pull up resistor on PF0

}


static void configPad(uint32_t reg, uint8_t pins, uint32_t Strength, uint32_t pinType) {
    HWREG(reg + GPIO_O_AFSEL) &= ~pins;
    HWREG(reg + GPIO_O_DEN) |= pins;
    HWREG(reg + GPIO_O_AMSEL) &= ~pins;
}

static void configPinDir(uint32_t reg, uint8_t pins, pin_mode_T mode) {

    if (mode == as_output) {
      HWREG(reg + GPIO_O_DIR) |= pins;
    }
    else if (mode == as_input) {
      HWREG(reg + GPIO_O_DIR) &= ~pins;
    }

}

void configPinAsOutput(uint32_t reg, uint8_t pins) {


    configPinDir(reg, pins, as_output);
    configPad(reg,pins,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);


}

void configPinAsInput(uint32_t reg, uint8_t pins) {
    //SYSCTL_RCGCGPIO_R |= PORTF_CLOCK;  // activate port F

    configPinDir(reg, pins, as_input);
    configPad(reg,pins,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);

    HWREG(reg + GPIO_O_PUR) |= pins;
}

volatile uint32_t FallingEdges = 0;
void EdgeCounter_Init(void){

    //SYSCTL_RCGCGPIO_R |= 0x00000020; // (a) activate clock for port F
  FallingEdges = 0;             // (b) initialize counter
  GPIO_PORTF_DIR_R &= ~0x10;    // (c) make PF4 in (built-in button)
  GPIO_PORTF_AFSEL_R &= ~0x10;  //     disable alt funct on PF4
  GPIO_PORTF_DEN_R |= 0x10;     //     enable digital I/O on PF4
  GPIO_PORTF_PCTL_R &= ~0x000F0000; // configure PF4 as GPIO
  GPIO_PORTF_AMSEL_R = 0;       //     disable analog functionality on PF
  GPIO_PORTF_PUR_R |= 0x10;     //     enable weak pull-up on PF4

  //interrupt config
  GPIO_PORTF_IS_R &= ~0x10;     // (d) PF4 is edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x10;    //     PF4 is not both edges
  GPIO_PORTF_IEV_R &= ~0x10;    //     PF4 falling edge event
  GPIO_PORTF_ICR_R = 0x10;      // (e) clear flag4
  GPIO_PORTF_IM_R |= 0x10;      // (f) arm interrupt on PF4 *** No IME bit as mentioned in Book ***
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
  NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
  EnableInterrupts();           // (i) Clears the I bit
}


void GPIOPortF_Handler(void){
  GPIO_PORTF_ICR_R = 0x10;      // acknowledge flag4
  FallingEdges = FallingEdges + 1;
}
