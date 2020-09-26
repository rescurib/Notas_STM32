/*
 * stm32f103xx_interrupts.c
 *
 *  Created on: 24 sep. 2020
 *      Author: Rodolfo
 */

#include "stm32f103xx_gpio.h"
#include "stm32f103xx_interrupts.h"

void enable_interrupt(uint8_t IRQNUM)
{
	//Indice:         IRQNUM/32 = IRQNUM>>32
	//Desplazamiento: IRQNUM % 32 = IRQNUM and 0x1F
	NVIC->ISER[((uint32_t)(IRQNUM) >> 5)] = (1 << ((uint32_t)(IRQNUM) & 0x1F));
}

void disable_interrupt(uint8_t IRQNUM)
{
	//Indice:         IRQNUM/32 = IRQNUM>>32
	//Desplazamiento: IRQNUM % 32 = IRQNUM and 0x1F
	NVIC->ICER[((uint32_t)(IRQNUM) >> 5)] = (1 << ((uint32_t)(IRQNUM) & 0x1F));
}

void EINT_Init(enum EXTI_t EXTIx,uint8_t EDGE,uint8_t PxINT)
{
   uint8_t rind = (EXTIx / 4);
   uint8_t shft = (EXTIx % 4);
   AFIO->EXTICR[rind] &= 0x00000;
   AFIO->EXTICR[rind] |= PxINT<<shft;

   if(EDGE == RISING || EDGE == RISING_FALLING)
   {
	   EXTI->RTSR |= 1<<EXTIx;
   }
   if(EDGE == FALLING || EDGE == RISING_FALLING)
   {
	   EXTI->FTSR |= 1<<EXTIx;
   }

}

void IRQ_Priority(uint8_t IRQNUM,uint8_t PR)
{
	// Table 42, 125: Solo los 4 bits más
	//  significativos de cada campo están
	//  emplementados:
	NVIC->IPR[IRQNUM] = PR<<4;
}
