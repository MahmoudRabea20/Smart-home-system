/**
 * *************************************************************************
 *  @file      ADC_program.c
 *  @author    Eslam Shahin (eslamshahin552000@gmail.com)
 *  @version   v1.0
 *  @date      05/08/2021
 *  @brief     This file have the implementation of
 *
 *
 *  @note      This program is distributed in the hope  that it
 * 	           will be useful,but WITHOUT ANY WARRANTY; without
 *	           even the implied warranty of  MERCHANTABILITY or
 *	           FITNESS FOR A PARTICULAR PURPOSE.
 *
 * *************************************************************************
 */

/******************************************************************************
* Includes
*******************************************************************************/
// Include libraries
#include "STD_TYPES.h"
#include "BIT_MATHS.h"

// Include files

#include "ADC_private.h"
#include "ADC_interface.h"


/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/


/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Static Function Prototypes
*******************************************************************************/
static void ADC_voidOn();
static void ADC_voidOff();
/******************************************************************************
* Function Definitions
*******************************************************************************/

/**
 * @fn
 * @brief
 * @param
 * @return
 * PRE-CONDITION
 * POST-CONDITION
 */
void ADC_voidInit(){

	/* Enable Clock  */
	//RCC_voidEnableClock(APB2,(9+ (ADC_Config->ADC_Num)));
	/* ADC On  */
	SET_BIT(ADC_1->CR2,0);
	/* Enable the single conversation mode  */
	CLEAR_BIT (ADC_1->CR1,1) ;
	/* Enable Scan mode  */
	CLEAR_BIT (ADC_1->CR1,8) ;
	/* Discontinuous mode on regular channels Disabled*/
	CLEAR_BIT(ADC_1->CR1,11);
	/* Data alignment */
	CLEAR_BIT(ADC_1->CR2,11);
	/* Single conversion mode */
	CLEAR_BIT(ADC_1->CR2,1);
}

u16 ADC_u16Read(u8 Channel)
{
	ADC_voidOn();
	ADC_voidOn();
	ADC_1->SQR3 &=0XFFFFFFF0; /* Clear channel */
	ADC_1->SQR3 |= Channel;
	/* Start conversion of regular channels */
	SET_BIT(ADC_1->CR2,22);
	/* Wait till end of operation flag is set */
	while (GET_BIT(ADC_1->SR,1)==0);
	u16 Result =(u16)ADC_1->DR;
	CLEAR_BIT(ADC_1->SR,1);
	CLEAR_BIT(ADC_1->SR,4);
	ADC_voidOff();
	return Result;
}
static void ADC_voidOn(void){
	/* Conversion starts when ADON bit is set for a second time by
	software after ADC_1 power-up time (tSTAB) */
	SET_BIT(ADC_1->CR2,0);
}

static void ADC_voidOff(void){
	CLEAR_BIT(ADC_1->CR2,0);
}

/*************** END OF FUNCTIONS *********************************************/
