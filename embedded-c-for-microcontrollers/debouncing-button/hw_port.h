/*
 * hw_port.h
 *
 *  Created on: Sep 2, 2024
 *      Author: rortega
 */

#ifndef HW_PORT_H_
#define HW_PORT_H_

#define GPIO_PORTA_BASE         0x40004000  // GPIO Port A
#define GPIO_PORTB_BASE         0x40005000  // GPIO Port B
#define GPIO_PORTC_BASE         0x40006000  // GPIO Port C
#define GPIO_PORTD_BASE         0x40007000  // GPIO Port D
#define GPIO_PORTE_BASE         0x40024000  // GPIO Port E
#define GPIO_PORTF_BASE         0x40025000  // GPIO Port F

//*****************************************************************************
//
// The following are defines for the GPIO register offsets.
//
//*****************************************************************************
#define GPIO_O_DATA             0x00000000  // GPIO Data
#define GPIO_O_DIR              0x00000400  // GPIO Direction
#define GPIO_O_IS               0x00000404  // GPIO Interrupt Sense
#define GPIO_O_IBE              0x00000408  // GPIO Interrupt Both Edges
#define GPIO_O_IEV              0x0000040C  // GPIO Interrupt Event
#define GPIO_O_IM               0x00000410  // GPIO Interrupt Mask
#define GPIO_O_RIS              0x00000414  // GPIO Raw Interrupt Status
#define GPIO_O_MIS              0x00000418  // GPIO Masked Interrupt Status
#define GPIO_O_ICR              0x0000041C  // GPIO Interrupt Clear
#define GPIO_O_AFSEL            0x00000420  // GPIO Alternate Function Select
#define GPIO_O_DR2R             0x00000500  // GPIO 2-mA Drive Select
#define GPIO_O_DR4R             0x00000504  // GPIO 4-mA Drive Select
#define GPIO_O_DR8R             0x00000508  // GPIO 8-mA Drive Select
#define GPIO_O_ODR              0x0000050C  // GPIO Open Drain Select
#define GPIO_O_PUR              0x00000510  // GPIO Pull-Up Select
#define GPIO_O_PDR              0x00000514  // GPIO Pull-Down Select
#define GPIO_O_SLR              0x00000518  // GPIO Slew Rate Control Select
#define GPIO_O_DEN              0x0000051C  // GPIO Digital Enable
#define GPIO_O_LOCK             0x00000520  // GPIO Lock
#define GPIO_O_CR               0x00000524  // GPIO Commit
#define GPIO_O_AMSEL            0x00000528  // GPIO Analog Mode Select
#define GPIO_O_PCTL             0x0000052C  // GPIO Port Control
#define GPIO_O_ADCCTL           0x00000530  // GPIO ADC Control
#define GPIO_O_DMACTL           0x00000534  // GPIO DMA Control
#define GPIO_O_SI               0x00000538  // GPIO Select Interrupt
#define GPIO_O_DR12R            0x0000053C  // GPIO 12-mA Drive Select
#define GPIO_O_WAKEPEN          0x00000540  // GPIO Wake Pin Enable
#define GPIO_O_WAKELVL          0x00000544  // GPIO Wake Level
#define GPIO_O_WAKESTAT         0x00000548  // GPIO Wake Status
#define GPIO_O_PP               0x00000FC0  // GPIO Peripheral Property
#define GPIO_O_PC               0x00000FC4  // GPIO Peripheral Configuration


#define  HWREG(x)   (*((volatile uint32_t *)(x)))

#endif /* HW_PORT_H_ */
