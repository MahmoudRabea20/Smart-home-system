
/******************************************************************************************************
 ******************************************************************************************************
 ******************************** AUTHOR  : Mahmoud Rabea *********************************************
 ******************************** MICRO   : STM32F401CCU6 *********************************************
 ******************************** LAYER   : MCAL          *********************************************
 ******************************** DRIVER  : EXTI_Driver   *********************************************
 ******************************** File    : private File  *********************************************
 ******************************** Date    : 2/9/2023      *********************************************
 ******************************** Version : 1.0           *********************************************
 ******************************************************************************************************
 ******************************************************************************************************/

#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

typedef struct
{
	volatile u32 EXTI_IMR         ;
	volatile u32 EXTI_EMR         ;
	volatile u32 EXTI_RTSR        ;
	volatile u32 EXTI_FTSR        ;
	volatile u32 EXTI_SWIER       ;
	volatile u32 EXTI_PR          ;

}EXTI_T;

typedef struct
{
	volatile u32 SYSCFG_EXTICR1   ;
	volatile u32 SYSCFG_EXTICR2   ;
	volatile u32 SYSCFG_EXTICR3   ;
	volatile u32 SYSCFG_EXTICR4   ;

}SYSCFG_T;

#define EXTI_BASE_ADDRESS         0x40013C00
#define EXTI                      ((volatile EXTI_T*)EXTI_BASE_ADDRESS)
#define SYSCFG_BASE_ADDRESS       0x40013808
#define SYSCFG                    ((volatile SYSCFG_T*)SYSCFG_BASE_ADDRESS)

#define EXTI_PORT_BITS            4
#define EXTI_FACTOR4              4
#define EXTI_FACTOR8              8
#define EXTI_FACTOR12             12
#define EXTI_FOUR_BIT_MASK        15
#define EXTI_ONE_BIT_MASK         1

#endif /* EXTI_PRIVATE_H_ */
