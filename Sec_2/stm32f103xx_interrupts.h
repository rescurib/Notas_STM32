/*
 * stm32f103xx_interrupts.h
 *
 *  Created on: 24 sep. 2020
 *      Author: Rodolfo
 */

#ifndef STM32F103XX_INTERRUPTS_H_
#define STM32F103XX_INTERRUPTS_H_

#define ENABLE 1
#define DISABLE 0

//------ Controlador de interupciones externas --------
// Direcciones. (Reference Manual (RM0008), Table 3, pag. 51)
#define EXTI_BASE 0x40010400U

//(Reference Manual (RM0008), Sec. 10.3.7, pag. 214)
typedef struct
{
	volatile uint32_t IMR;   // Interrupt Mask Register (pag. 211)
	volatile uint32_t EMR;   // Event Mask Register (pag. 211)
	volatile uint32_t RTSR;  // Rising Trig. Selection Reg. (pag. 212)
	volatile uint32_t FTSR;  // Falling Trig. Selection Reg. (pag. 212)
	volatile uint32_t SWIER; // Software Interrupt Event Reg.(pag. 213)
	volatile uint32_t PR;    // Pending Register (pag. 213)
}EXTI_RegDef;

#define EXTI ((EXTI_RegDef*) EXTI_BASE)

#define RISING           4 // Interrupción flanco de subida
#define FALLING          5 // Interripcion flanco de bajada
#define RISING_FALLING   6 // Interrupcion ambos flancos

//(RM0008, Figure 21, pag. 210)
//(RM0008,pags. 191-192)
#define PA_PIN 0
#define PB_PIN 1
#define PC_PIN 2
#define PD_PIN 3
#define PE_PIN 4

enum EXTI_t {EXTI0,EXTI1,EXTI2,EXTI3,
	         EXTI4,EXTI5,EXTI6,EXTI7,
			 EXTI8,EXTI9,EXTI10,EXTI11,
			 EXTI12,EXTI13,EXTI14,EXTI15};

#define EXTI0_IRQNUM 6

// ------------ Mapa de registros NVIC -------------
//Cortex-M3 Programming Manual (PM0056), Tabla 44, pag. 128
//Cortex-M3 Technical Reference Manual, Table 6-1, pag. 63
#define NVIC_BASE       ((uint32_t) 0xE000E100)
typedef struct
{
	uint32_t   ISER[8];     /* Offset: 0x000 - 0x01C PM0056, pag. 120 */
	uint32_t  RES0[24];     /* Offset: 0x020 - 0x07C */
	uint32_t   ICER[8];     /* Offset: 0x080 - 0x09C */
	uint32_t  RES1[24];     /* Offset: 0x0A0 - 0x0FC */
	uint32_t   ISPR[8];     /* Offset: 0x100 - 0x11C */
	uint32_t  RES2[24];     /* Offset: 0x120 - 0x17C */
	uint32_t   ICPR[8];     /* Offset: 0x180 - 0x19C */
	uint32_t  RES3[24];     /* Offset: 0x1A0 - 0x1FC */
	uint32_t   IABR[8];     /* Offset: 0x200 - 0x21C */
	uint32_t  RES4[56];     /* Offset: 0x220 - 0x2FC */
	uint8_t   IPR[240];     /* Offset: 0x300 - 0x3EC */
	uint32_t RES5[644];     /* Offset: 0x3F0 - 0xEFC */
	uint32_t      STIR;     /* Offset:         0xF00 */
} NVIC_RegDef;

#define NVIC  ((NVIC_RegDef*) NVIC_BASE)

//--------------------- Funciones ------------------
void EINT_Init(enum EXTI_t EXTIx,uint8_t EDGE,uint8_t PxINT);
void enable_interrupt(uint8_t IRQNUM);
void disable_interrupt(uint8_t IRQNUM);
void IRQ_Priority(uint8_t IRQNUM,uint8_t PR);
//--------------------------------------------------

#endif /* STM32F103XX_INTERRUPTS_H_ */
