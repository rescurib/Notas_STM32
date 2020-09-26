/*
 * stm32f103xx_gpio.h
 *
 *  Created on: Sep 20, 2020
 *      Author: Rodolfo
 */

#ifndef STM32F103XX_GPIO_H_
#define STM32F103XX_GPIO_H_

#include <stdint.h>

//---------------- Puertos ------------------
// Direcciones. (Reference Manual (RM0008), Table 3, pag. 51)
#define PORTA_BASE			0x40010800U
#define PORTB_BASE			0x40010C00U
#define PORTC_BASE			0x40011000U
#define PORTD_BASE			0x40011400U
#define PORTE_BASE			0x40011800U

#define AFIO_BASE 0x40010000U

// Estructura de registros GPIO
// (Reference Manual (RM0008), Sec. 9.2, pag. 171)
typedef struct
{
	volatile uint32_t CRL; //Configuration Register Low  (pag. 171)
	volatile uint32_t CRH; //Configuration Register High (pag. 172)
	volatile uint32_t IDR; //Input Data Register (pag. 172)
	volatile uint32_t ODR; //Output Data Register (pag. 173)
	volatile uint32_t BSRR;//Bit Set/Reset Register(pag. 173)
	volatile uint32_t BRR; //Bit Reset Register (pag. 174)
	volatile uint32_t LCKR;//Configuration Lock Register (pag. 174)
}GPIO_RegDef;

#define GPIOA (GPIO_RegDef*) PORTA_BASE
#define GPIOB (GPIO_RegDef*) PORTB_BASE
#define GPIOC (GPIO_RegDef*) PORTC_BASE
#define GPIOD (GPIO_RegDef*) PORTD_BASE
#define GPIOE (GPIO_RegDef*) PORTE_BASE

//Estructura de registros AFIO
//(Table 60, pag.195)
typedef struct
{
	volatile uint32_t EVCR;      //Event Control Register (pag. 183)
	volatile uint32_t MAPR;      //AF remap and debug register (pag. 184)
	volatile uint32_t EXTICR[4]; //External Interrupt Control Reg. (pag. 191)
	volatile uint32_t MAPR2;     //AF remap and debug register 2 (pag. 193)
}AFIO_RegDef;

#define AFIO ((AFIO_RegDef*) AFIO_BASE)

// Manejadores de configuración

typedef struct
{
	volatile uint8_t pinNumber;   //Número de pin
	volatile uint8_t pinMode;     //Modo de pin (entrada o salida)
 	volatile uint8_t pinType;     //Tipo de salida
	volatile uint8_t pull;        //Pull up/down
	volatile uint8_t altFuncMode; //Modo de función alterna
}GPIO_PinConfig;

typedef struct
{
	volatile GPIO_RegDef    *pgpiox;    // Dirección base del puerto
	volatile GPIO_PinConfig  pinConfig; // Configuración de pin

}GPIO_Handle;

// Macros auxiliares
#define SET   1
#define RESET 0

//(Reference Manual (RM0008), Sec. 9.2.2, pags. 171 - 172)
#define MODE_IN        0x00
#define MODE_OUT_10MHZ 0x01
#define MODE_OUT_2MH   0x02
#define MODE_OUT_50MHZ 0x03

#define MODE_ANALOG     0
#define MODE_FLOATING   1
#define MODE_PULL       2

#define PULL_DOWN 0
#define PULL_UP   1
#define PULL_NONE 2

#define PUSH_PULL      0
#define OPEN_DRAIN     1
#define ALT_PUSH_PULL  2
#define ALT_OPEN_DRAIN 3

//---------------- Funciones -----------------------
void GPIO_Pin_Init(GPIO_Handle *Conf);
uint8_t  GPIO_ReadPin(GPIO_RegDef *Port,uint8_t pin_num);
uint16_t GPIO_ReadPort(GPIO_RegDef *Port);
void GPIO_WritePin(GPIO_RegDef *Port,uint8_t pin_num,uint8_t value);
void GPIO_TogglePin(GPIO_RegDef *Port,uint8_t pin_num);
void GPIO_WritePort(GPIO_RegDef *Port,uint16_t value);
uint8_t GPIO_ReadPin(GPIO_RegDef *Port, uint8_t pin_num);
uint16_t GPIO_ReadPort(GPIO_RegDef *Port);

#endif /* STM32F103XX_GPIO_H_ */
