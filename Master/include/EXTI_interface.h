
/******************************************************************************************************
 ******************************************************************************************************
 ******************************** AUTHOR  : Mahmoud Rabea *********************************************
 ******************************** MICRO   : STM32F401CCU6 *********************************************
 ******************************** LAYER   : MCAL          *********************************************
 ******************************** DRIVER  : EXTI_Driver   *********************************************
 ******************************** File    : interface File*********************************************
 ******************************** Date    : 2/9/2023      *********************************************
 ******************************** Version : 1.0           *********************************************
 ******************************************************************************************************
 ******************************************************************************************************/

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

/* Ports of external interrupts*/

typedef enum
{
	EXTI_PORTA,
	EXTI_PORTB,
	EXTI_PORTC,
	EXTI_PORTD,
	EXTI_PORTE,
	EXTI_PORTH = 7
}Port_T;

/* Lines of external interrupts*/

typedef enum
{
	EXTI_LINE0,
	EXTI_LINE1,
	EXTI_LINE2,
	EXTI_LINE3,
	EXTI_LINE4,
	EXTI_LINE5,
	EXTI_LINE6,
	EXTI_LINE7,
	EXTI_LINE8,
	EXTI_LINE9,
	EXTI_LINE10,
	EXTI_LINE11,
	EXTI_LINE12,
	EXTI_LINE13,
	EXTI_LINE14,
	EXTI_LINE15,
}Line_T;

/* Enable or disable interrupt */

typedef enum
{
	EXTI_DISABLE,
	EXTI_ENABLE
}Enabling_T;

/* Types of trigger*/

typedef enum
{
	RISING_TRIGGER,
	FALLING_TRIGGER,
	ANY_CHANGE
}Trigger_T;

/* Copy_enuPortNumber : EXTI_PORTA ------>EXTI_PORTE , EXTI_PORTH
 * Copy_enuLineNumber : EXTI_LINE0 ------> EXTI_LINE15
 * */

ES_t MEXTI_enuSetInterruptPort(Port_T Copy_enuPortNumber,Line_T Copy_enuLineNumber);

/* Copy_u8EnablingState : EXTI_DISABLE      ,      EXTI_ENABLE
 * Copy_u8LineNumber     : EXTI_LINE0 -------> EXTI_LINE15
 * */

ES_t MEXTI_eunEnableDisableInterrupt(u8 Copy_u8EnablingState,Line_T Copy_enuLineNumber);

/* Copy_u8EnablingState : EXTI_DISABLE      ,      EXTI_ENABLE
 * Copy_u8LineNumber    : EXTI_LINE0 -------> EXTI_LINE15
 * */

ES_t MEXTI_eunEnableDisableEvent(u8 Copy_u8EnablingState,Line_T Copy_enuLineNumber);

/* Copy_enuTriggerType : RISING_TRIGGER   ,   FALLING_TRIGGER   ,   ANY_CHANGE
 * Copy_enuLineNumber  : EXTI_LINE0 -------> EXTI_LINE15
 * */

ES_t MEXTI_enuSelectTrigger(Trigger_T Copy_enuTriggerType ,Line_T Copy_enuLineNumber);

/* Copy_enuLineNumber  : EXTI_LINE0 -------> EXTI_LINE15
 * */

ES_t MEXTI_enuSetSoftwareInterrupr(Line_T Copy_enuLineNumber);

/* Copy_enuLineNumber  : EXTI_LINE0 -------> EXTI_LINE15
 * */

ES_t MEXTI_enuSetPendingFlag(Line_T Copy_enuLineNumber);

/* Copy_pvPtrToFun : pointer to function
 * */

ES_t MEXTI0_enuCallBackFunction(void (*Copy_pvPtrToFun)(void));


#define EXTI_DISABLE                0
#define EXTI_ENABLE                 1

#endif /* EXTI_INTERFACE_H_ */
