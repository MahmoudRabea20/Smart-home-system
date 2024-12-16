
/******************************************************************************************************
 ******************************************************************************************************
 ******************************** AUTHOR  : Mahmoud Rabea *********************************************
 ******************************** MICRO   : STM32F401CCU6 *********************************************
 ******************************** LAYER   : MCAL          *********************************************
 ******************************** DRIVER  : NVIC_Driver   *********************************************
 ******************************** File    : program File  *********************************************
 ******************************** Date    : 30/8/2023     *********************************************
 ******************************** Version : 1.0           *********************************************
 ******************************************************************************************************
 ******************************************************************************************************/


#include "BIT_MATHS.h"
#include "STD_TYPES.h"

#include "NVIC_private.h"
#include "NVIC_configuration.h"
#include "NVIC_interface.h"

u32 Global_u32GroupMode = 0;

/* Argument  : Id of peripheral interrupt
 * Return    : Error State (Enum)
 * Operation : To enable peripheral interrupt
 * */

ES_t MNVIC_enuEnableInterrupt(u8 Copy_u8InterruptId)
{
	ES_t Local_enuErrorState = ES_NOK;
	u8 Local_u8RegisterNumber = 0 ;
	u8 Local_u8BitNumber = 0 ;

	if(Copy_u8InterruptId <= MNVIC_INTERRUPTS_NUMBER )
	{
		Local_u8RegisterNumber = Copy_u8InterruptId / MNVIC_REGISTER_BITS ;  /*Divide by register bits to get bit number */
		Local_u8BitNumber = Copy_u8InterruptId % MNVIC_REGISTER_BITS ;            /*Divide by register bits to get bit number */
		NVIC->NVIC_ISER[Local_u8RegisterNumber] |= MNVIC_BIT_MASK << Local_u8BitNumber ;

		Local_enuErrorState = ES_OK;
	}
	else
	{
		/* Do Nothing */
		return Local_enuErrorState;

	}

	return Local_enuErrorState;

}

/* Argument  : Id of peripheral interrupt
 * Return    : Error State (Enum)
 * Operation : To disable peripheral interrupt
 * */

ES_t MNVIC_enuDisableInterrupt(u8 Copy_u8InterruptId)
{
	ES_t Local_enuErrorState = ES_NOK;
	u8 Local_u8RegisterNumber = 0 ;
	u8 Local_u8BitNumber = 0 ;

	if(Copy_u8InterruptId <= MNVIC_INTERRUPTS_NUMBER )
	{
		Local_u8RegisterNumber = Copy_u8InterruptId / MNVIC_REGISTER_BITS ; /*Divide by register bits to get register number */
		Local_u8BitNumber = Copy_u8InterruptId % MNVIC_REGISTER_BITS ;      /*Divide by register bits to get bit number */
		NVIC->NVIC_ICER[Local_u8RegisterNumber] |= MNVIC_BIT_MASK << Local_u8BitNumber ;

		Local_enuErrorState = ES_OK;
	}
	else
	{
		/* Do Nothing */
		return Local_enuErrorState;

	}

	return Local_enuErrorState;

}

/* Argument  : Id of peripheral interrupt
 * Return    : Error State (Enum)
 * Operation : To set pending interrupt by software
 * */

ES_t MNVIC_enuSetPendingInterrupt(u8 Copy_u8InterruptId)
{
	ES_t Local_enuErrorState = ES_NOK;
	u8 Local_u8RegisterNumber = 0 ;
	u8 Local_u8BitNumber = 0 ;

	if(Copy_u8InterruptId <= MNVIC_INTERRUPTS_NUMBER )
	{
		Local_u8RegisterNumber = Copy_u8InterruptId / MNVIC_REGISTER_BITS ; /*Divide by register bits to get register number */
		Local_u8BitNumber = Copy_u8InterruptId % MNVIC_REGISTER_BITS ;      /*Divide by register bits to get bit number */
		NVIC->NVIC_ISPR[Local_u8RegisterNumber] |= MNVIC_BIT_MASK << Local_u8BitNumber ;

		Local_enuErrorState = ES_OK;
	}
	else
	{
		/* Do Nothing */
		return Local_enuErrorState;

	}

	return Local_enuErrorState;

}

/* Argument  : Id of peripheral interrupt
 * Return    : Error State (Enum)
 * Operation : To clear pending interrupt by software
 * */

ES_t MNVIC_enuClearPendingInterrupt(u8 Copy_u8InterruptId)
{
	ES_t Local_enuErrorState = ES_NOK;
	u8 Local_u8RegisterNumber = 0 ;
	u8 Local_u8BitNumber = 0 ;

	if(Copy_u8InterruptId <= MNVIC_INTERRUPTS_NUMBER )
	{
		Local_u8RegisterNumber = Copy_u8InterruptId / MNVIC_REGISTER_BITS ; /*Divide by register bits to get register number */
		Local_u8BitNumber = Copy_u8InterruptId % MNVIC_REGISTER_BITS ;      /*Divide by register bits to get bit number */
		NVIC->NVIC_ICPR[Local_u8RegisterNumber] |= MNVIC_BIT_MASK << Local_u8BitNumber ;

		Local_enuErrorState = ES_OK;
	}
	else
	{
		/* Do Nothing */
		return Local_enuErrorState;

	}

	return Local_enuErrorState;

}

/* Argument  : Mode of group
 * Return    : Error State (Enum)
 * Operation : To select the group mode of priority
 * */

ES_t MNVIC_enuSetGroupMode(Group_T Copy_enuGroupMode)
{
	ES_t Local_enuErrorState = ES_NOK ;
	u32 Local_u32AIRCRValue = 0 ;

	if(( Copy_enuGroupMode <= NVIC_0_GRP_16_SUBGRP ) && ( Copy_enuGroupMode >= NVIC_16_GRP_0_SUBGRP ))
	{
		Global_u32GroupMode = Copy_enuGroupMode ;      /*To convert the 8-bit variable to 32-bit and use it later */
		AIRCR &= 0x0000f8ff ;  /*To clear the required bits */
		Local_u32AIRCRValue = (( MNVIC_VECTKEY ) | ( Copy_enuGroupMode << MNVIC_BIT_PRIGRP )) ;
		AIRCR |= Local_u32AIRCRValue;

		Local_enuErrorState = ES_OK ;
	}
	else
	{
		/* Do Nothing */
		return Local_enuErrorState;
	}
	return Local_enuErrorState;
}

/*
 * Argument : Id of peripheral interrupt , Group priority number , Group priority number
 * Return : Error State (Enum)
 * Function : to set the priority of the groups and the subgroups
 *
 * */

ES_t MNVIC_enuSetPriority(u8 Copy_u8InterruptId,u8 Copy_u8GroupPriorityNumber,u8 Copy_u8SubgroupPriorityNumber )
{
	ES_t Local_enuErrorState = ES_OK;

	switch(Global_u32GroupMode)
	{
	case NVIC_16_GRP_0_SUBGRP :
		NVIC->NVIC_IPR[Copy_u8InterruptId] = Copy_u8GroupPriorityNumber << MNVIC_BIT_FOUR ;
		break;
	case NVIC_8_GRP_2_SUBGRP :
		NVIC->NVIC_IPR[Copy_u8InterruptId] = ((Copy_u8GroupPriorityNumber << MNVIC_BIT_FIVE ) | (Copy_u8SubgroupPriorityNumber << MNVIC_BIT_FOUR));
		break;
	case NVIC_4_GRP_4_SUBGRP :
		NVIC->NVIC_IPR[Copy_u8InterruptId] = ((Copy_u8GroupPriorityNumber << MNVIC_BIT_SIX ) | (Copy_u8SubgroupPriorityNumber << MNVIC_BIT_FOUR));

		break;
	case NVIC_2_GRP_8_SUBGRP :
		NVIC->NVIC_IPR[Copy_u8InterruptId] = ((Copy_u8GroupPriorityNumber << MNVIC_BIT_SEVEN ) | (Copy_u8SubgroupPriorityNumber << MNVIC_BIT_FOUR));

		break;
	case NVIC_0_GRP_16_SUBGRP :
		NVIC->NVIC_IPR[Copy_u8InterruptId] = Copy_u8SubgroupPriorityNumber << MNVIC_BIT_FOUR ;

		break;
	default :
		Local_enuErrorState = ES_NOK ;
		break;
	}

	return Local_enuErrorState;
}
