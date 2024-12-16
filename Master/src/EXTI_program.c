
/******************************************************************************************************
 ******************************************************************************************************
 ******************************** AUTHOR  : Mahmoud Rabea *********************************************
 ******************************** MICRO   : STM32F401CCU6 *********************************************
 ******************************** LAYER   : MCAL          *********************************************
 ******************************** DRIVER  : EXTI_Driver   *********************************************
 ******************************** File    : program File  *********************************************
 ******************************** Date    : 2/9/2023      *********************************************
 ******************************** Version : 1.0           *********************************************
 ******************************************************************************************************
 ******************************************************************************************************/

#include "BIT_MATHS.h"
#include "STD_TYPES.h"

#include "EXTI_private.h"
#include "EXTI_configuration.h"
#include "EXTI_interface.h"

static void (*EXTI0_Fun_Ptr)(void) = NULL;

/* Argument  : Port number , Line number
 * Return    : Error State (enum)
 * Operation : To configure the port number
 * */

ES_t MEXTI_enuSetInterruptPort(Port_T Copy_enuPortNumber,Line_T Copy_enuLineNumber)
{
	ES_t Local_enuErrorState = ES_OK;

	if((Copy_enuLineNumber <= EXTI_LINE3) && (Copy_enuLineNumber > EXTI_LINE0))
	{
		SYSCFG->SYSCFG_EXTICR1 &= ~((u16)EXTI_FOUR_BIT_MASK << (Copy_enuLineNumber * EXTI_PORT_BITS)) ;
		SYSCFG->SYSCFG_EXTICR1 |= ((u16)Copy_enuPortNumber << (Copy_enuLineNumber * EXTI_PORT_BITS)) ;
	}
	else if( (Copy_enuLineNumber <= EXTI_LINE7) && (Copy_enuLineNumber > EXTI_LINE3) )
	{
		SYSCFG->SYSCFG_EXTICR2 &= ~((u16)EXTI_FOUR_BIT_MASK << ((Copy_enuLineNumber % EXTI_FACTOR4) * EXTI_PORT_BITS)) ;
		SYSCFG->SYSCFG_EXTICR2 |= ((u16)Copy_enuPortNumber << ((Copy_enuLineNumber % EXTI_FACTOR4) * EXTI_PORT_BITS)) ;
	}
	else if((Copy_enuLineNumber <= EXTI_LINE11 ) && (Copy_enuLineNumber > EXTI_LINE7 ))
	{
		SYSCFG->SYSCFG_EXTICR3 &= ~((u16)EXTI_FOUR_BIT_MASK << ((Copy_enuLineNumber % EXTI_FACTOR8 ) * EXTI_PORT_BITS)) ;
		SYSCFG->SYSCFG_EXTICR3 |= ((u16)Copy_enuPortNumber << ((Copy_enuLineNumber % EXTI_FACTOR8 ) * EXTI_PORT_BITS)) ;
	}
	else if((Copy_enuLineNumber <= EXTI_LINE15 ) && (Copy_enuLineNumber > EXTI_LINE11 ))
	{
		SYSCFG->SYSCFG_EXTICR4 &= ~((u16)EXTI_FOUR_BIT_MASK << ((Copy_enuLineNumber % EXTI_FACTOR12 ) * EXTI_PORT_BITS)) ;
		SYSCFG->SYSCFG_EXTICR4 |= ((u16)Copy_enuPortNumber << ((Copy_enuLineNumber % EXTI_FACTOR12 ) * EXTI_PORT_BITS)) ;
	}
	else
	{
		/* Do Nothing */
		Local_enuErrorState = ES_NOK;
	}

	return Local_enuErrorState;
}

/* Argument    : Enabling State      ,      Line number
 * Return      : Error State (enum)
 * Operation   : To enable or disable interrupt
 * */

ES_t MEXTI_eunEnableDisableInterrupt(u8 Copy_u8EnablingState,Line_T Copy_enuLineNumber)
{
	ES_t Local_enuErrorState = ES_OK;

	if((Copy_enuLineNumber >= EXTI_LINE0 ) && (Copy_enuLineNumber <= EXTI_LINE15 ) )
	{
		EXTI->EXTI_IMR &= ~( EXTI_ONE_BIT_MASK << Copy_enuLineNumber );
		EXTI->EXTI_IMR |= ( Copy_u8EnablingState << Copy_enuLineNumber );
	}
	else
	{
		/* Do Nothing */
		Local_enuErrorState = ES_NOK;
	}

	return Local_enuErrorState;
}

/* Argument    : Enabling State      ,      Line number
 * Return      : Error State (enum)
 * Operation   : To enable or disable event
 * */

ES_t MEXTI_eunEnableDisableEvent(u8 Copy_u8EnablingState,Line_T Copy_enuLineNumber)
{
	ES_t Local_enuErrorState = ES_OK;

	if((Copy_enuLineNumber >= EXTI_LINE0 ) && (Copy_enuLineNumber <= EXTI_LINE15 ) )
	{
		EXTI->EXTI_EMR &= ~( EXTI_ONE_BIT_MASK << Copy_enuLineNumber );
		EXTI->EXTI_EMR |= ( Copy_u8EnablingState << Copy_enuLineNumber );
	}
	else
	{
		/* Do Nothing */
		Local_enuErrorState = ES_NOK;
	}

	return Local_enuErrorState;
}

/* Argument    : Trigger type      ,      Line number
 * Return      : Error State (enum)
 * Operation   : To select the trigger type
 * */

ES_t MEXTI_enuSelectTrigger(Trigger_T Copy_enuTriggerType ,Line_T Copy_enuLineNumber)
{
	ES_t Local_enuErrorState = ES_OK;

	switch(Copy_enuTriggerType)
	{
		case RISING_TRIGGER :
			SET_BIT(EXTI->EXTI_RTSR,Copy_enuLineNumber) ;
			CLEAR_BIT(EXTI->EXTI_FTSR,Copy_enuLineNumber) ;
			break;
		case FALLING_TRIGGER :
			SET_BIT(EXTI->EXTI_FTSR,Copy_enuLineNumber) ;
			CLEAR_BIT(EXTI->EXTI_RTSR,Copy_enuLineNumber) ;
			break;
		case ANY_CHANGE :
			SET_BIT(EXTI->EXTI_RTSR,Copy_enuLineNumber) ;
			SET_BIT(EXTI->EXTI_FTSR,Copy_enuLineNumber) ;
			break;
		default:
			Local_enuErrorState = ES_NOK;
			break;
	}

	return Local_enuErrorState;
}

/* Argument    : Line number
 * Return      : Error State (enum)
 * Operation   : To set software interrupt
 * */

ES_t MEXTI_enuSetSoftwareInterrupr(Line_T Copy_enuLineNumber)
{
	ES_t Local_enuErrorState = ES_OK;

	if((Copy_enuLineNumber >= EXTI_LINE0 ) && (Copy_enuLineNumber <= EXTI_LINE15 ) )
	{
		SET_BIT(EXTI->EXTI_SWIER,Copy_enuLineNumber);
	}
	else
	{
		/* Do Nothing */
		Local_enuErrorState = ES_NOK;
	}

	return Local_enuErrorState;
}

/* Argument    : Line number
 * Return      : Error State (enum)
 * Operation   : To set pending flag
 * */

ES_t MEXTI_enuSetPendingFlag(Line_T Copy_enuLineNumber)
{
	ES_t Local_enuErrorState = ES_OK;

	if((Copy_enuLineNumber >= EXTI_LINE0 ) && (Copy_enuLineNumber <= EXTI_LINE15 ) )
	{
		SET_BIT(EXTI->EXTI_PR,Copy_enuLineNumber);
	}
	else
	{
		/* Do Nothing */
		Local_enuErrorState = ES_NOK;
	}

	return Local_enuErrorState;
}

/* Argument    : pointer to function
 * Return      : Error State (enum)
 * Operation   : To call function existing in main
 * */

ES_t MEXTI0_enuCallBackFunction(void (*Copy_pvPtrToFun)(void))
{
	ES_t Local_enuErrorState = ES_NOK;

	if(Copy_pvPtrToFun != NULL)
	{
		EXTI0_Fun_Ptr = Copy_pvPtrToFun ;
	}
	else
	{
		/* Do Nothing */
		Local_enuErrorState = NULL_POINTER;
	}

	return Local_enuErrorState;
}

/* Argument : void
 * Return   : void
 * Function : To execute the Interrupt
 * */

void EXTI0_IRQHandler(void)
{
	EXTI0_Fun_Ptr();
}


