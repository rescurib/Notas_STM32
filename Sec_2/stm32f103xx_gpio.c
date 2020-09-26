/*
 * stm32f103xx_gpio.c
 *
 *  Created on: Sep 20, 2020
 *      Author: Rodolfo
 */

#include "stm32f103xx_gpio.h"

void GPIO_Pin_Init(GPIO_Handle *Conf)
{
	uint32_t temp,md;

	//(Reference Manual (RM0008), Sec. 9.2.2, pags. 171 - 172)
	//(Reference Manual (RM0008), Table 20, pag. 161

	if(Conf->pinConfig.pinNumber<8)
	{
	    // Establecer modo
		md = Conf->pinConfig.pinMode;
		temp = 0x0F<<(4*Conf->pinConfig.pinNumber); // Máscara de borrado
		Conf->pgpiox->CRL &= ~temp; // Borrar segmento del registro
		temp = md<<(4*Conf->pinConfig.pinNumber); // Máscara de configuración
		Conf->pgpiox->CRL |= temp; // Escribir en segmento del registro

		//Establecer tipo
		md = Conf->pinConfig.pinType;
		temp = md<<(4*(Conf->pinConfig.pinNumber)+2); // Máscara de configuración
		Conf->pgpiox->CRL |= temp; // Escribir en segmento del registro
	}
	else
	{
		// Establecer modo
		md = Conf->pinConfig.pinMode;
		temp = 0x0F<<(4*Conf->pinConfig.pinNumber); // Máscara de borrado
		Conf->pgpiox->CRH &= ~temp; // Borrar segmento del registro
		temp = md<<(4*Conf->pinConfig.pinNumber); // Máscara de configuración
		Conf->pgpiox->CRH |= temp; // Escribir en segmento del registro

		//Establecer tipo
		md = Conf->pinConfig.pinType;
	    temp = md<<(4*(Conf->pinConfig.pinNumber)+2); // Máscara de configuración
		    Conf->pgpiox->CRH |= temp; // Escribir en segmento del registro
	}

	//Configuración de Pull-Up/Downs
	if(Conf->pinConfig.pull != PULL_NONE)
	{
		temp = 1<<(Conf->pinConfig.pinNumber);
		Conf->pgpiox->ODR &= ~temp;
		temp = (Conf->pinConfig.pull)<<(Conf->pinConfig.pinNumber);
		Conf->pgpiox->ODR |= temp;
	}
}

void GPIO_WritePin(GPIO_RegDef *Port,uint8_t pin_num,uint8_t value)
{
	if(value==1)
		Port->ODR |=  (1<<pin_num);
	else
		Port->ODR &= ~(1<<pin_num);
}

void GPIO_TogglePin(GPIO_RegDef *Port,uint8_t pin_num)
{
	Port->ODR ^= 1<<pin_num;
}

uint8_t GPIO_ReadPin(GPIO_RegDef* Port,uint8_t pin_num)
{
	uint8_t temp;
	temp = (uint8_t)((Port->IDR)>>pin_num) & 0x0001;
	return temp;
}

uint16_t GPIO_ReadPort(GPIO_RegDef* Port)
{
	return (uint16_t)Port->IDR;
}


