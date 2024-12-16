
/******************************************************************************************************
 ******************************************************************************************************
 ******************************** AUTHOR  : Mahmoud Rabea *********************************************
 ******************************** MICRO   : STM32F401CCU6 *********************************************
 ******************************** LAYER   : MCAL          *********************************************
 ******************************** DRIVER  : NVIC_Driver   *********************************************
 ******************************** File    : private File  *********************************************
 ******************************** Date    : 30/8/2023     *********************************************
 ******************************** Version : 1.0           *********************************************
 ******************************************************************************************************
 ******************************************************************************************************/

#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_


typedef struct{
	volatile u32 NVIC_ISER[8]        ;
	volatile u32 Reserved0[24]       ;
	volatile u32 NVIC_ICER[8]        ;
	volatile u32 Reserved1[24]       ;
	volatile u32 NVIC_ISPR[8]        ;
	volatile u32 Reserved2[24]       ;
	volatile u32 NVIC_ICPR[8]        ;
	volatile u32 Reserved3[24]       ;
	volatile u32 NVIC_IAPR[8]        ;
	volatile u32 Reserved4[56]       ;
	volatile u8 NVIC_IPR[240]        ;     /* Byte accessible*/
	volatile u32 Reserved5[580]      ;
	volatile u32 NVIC_STIR           ;
}NVIC_T;

#define NVIC_BASE_ADDRESS            0xE000E100

#define NVIC                         ((volatile NVIC_T*)NVIC_BASE_ADDRESS)
#define AIRCR                        *((volatile u32*)0xE000ED0C)

#define MNVIC_INTERRUPTS_NUMBER      239
#define MNVIC_REGISTER_BITS          32
#define MNVIC_BIT_MASK               1
#define MNVIC_VECTKEY                0x05FA0000
#define MNVIC_BIT_SIXTEEN            16
#define MNVIC_BIT_PRIGRP             8
#define MNVIC_BIT_FOUR               4
#define MNVIC_BIT_FIVE               5
#define MNVIC_BIT_SIX                6
#define MNVIC_BIT_SEVEN              7


#endif /* NVIC_PRIVATE_H_ */
