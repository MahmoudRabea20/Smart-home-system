
/******************************************************************************************************
 ******************************************************************************************************
 ******************************** AUTHOR  : Mahmoud Rabea  ********************************************
 ******************************** MICRO   : STM32F401CCU6  ********************************************
 ******************************** LAYER   : HAL            ********************************************
 ******************************** DRIVER  : Keypad_Driver  ********************************************
 ******************************** File    : program File   ********************************************
 ******************************** Date    : 6/9/2023       ********************************************
 ******************************** Version : 1.0            ********************************************
 ******************************************************************************************************
 ******************************************************************************************************/

#include "BIT_MATHS.h"
#include "STD_TYPES.h"

#include "GPIO_interface.h"
#include "SYSTICK_interface.h"

#include "Keypad_private.h"
#include "Keypad_configuration.h"
#include "Keypad_interface.h"

/* Argument   : Nothing
 * Return     : Error State (enum)
 * Operation  : To initialize the Keypad
 * */

ES_t HKeypad_enuInit()
{
	ES_t Local_enuErrorState = ES_NOK;

	u8 Local_Au8KeypadPins[8] = {KEYPAD_R0_PIN,KEYPAD_R1_PIN,KEYPAD_R2_PIN,KEYPAD_R3_PIN,KEYPAD_C0_PIN,KEYPAD_C1_PIN,KEYPAD_C2_PIN,KEYPAD_C3_PIN};


	for(u8 Local_u8Iterator1 = 0 ; Local_u8Iterator1 < 4 ; Local_u8Iterator1++)
	{
		MGPIO_enuSetPinDirectionMode(KEYPAD_GRP,Local_Au8KeypadPins[Local_u8Iterator1],MGPIO_INPUT);
		MGPIO_enuSetPinPullingMode(KEYPAD_GRP,Local_Au8KeypadPins[Local_u8Iterator1],MGPIO_PULL_UP);
	}

	for(u8 Local_u8Iterator = 4 ; Local_u8Iterator < 8 ; Local_u8Iterator++)
	{
		MGPIO_enuSetPinDirectionMode(KEYPAD_GRP,Local_Au8KeypadPins[Local_u8Iterator],MGPIO_OUTPUT);
		MGPIO_enuSetOutputSpeed(KEYPAD_GRP,Local_Au8KeypadPins[Local_u8Iterator],MGPIO_LOW_SPEED);
		MGPIO_enuSetOutputType(KEYPAD_GRP,Local_Au8KeypadPins[Local_u8Iterator],MGPIO_PUSH_PULL);
	}

	for(u8 Local_u8Iterator = 4 ; Local_u8Iterator < 8 ; Local_u8Iterator++)
	{
		MGPIO_enuSetPinValue(KEYPAD_GRP,Local_Au8KeypadPins[Local_u8Iterator],MGPIO_HIGH_OUTPUT);
	}

	for(u8 Local_u8Iterator = 0 ; Local_u8Iterator < 4 ; Local_u8Iterator++)
	{
		MGPIO_enuSetPinValue(KEYPAD_GRP,Local_Au8KeypadPins[Local_u8Iterator],MGPIO_HIGH_OUTPUT);
	}



	return Local_enuErrorState;
}

/* Argument   : Address to pass to it the pressed key
 * Return     : Error State (enum)
 * Operation  : To get the pressed key
 * */

ES_t HKeypad_enuGetPressedKey( u8* Copy_pu8PressedKey)
{
	ES_t Local_enuErrorState = ES_NOK;
	u8 Local_u8RowIter;
	u8 Local_u8ColumnIter;
	u8 Local_u8PinValue;
	*Copy_pu8PressedKey = Keypad_NOT_PREESED;
	u8 Local_Au8RowsPin[KEYPAD_u8ROWS_NUMBER] = {KEYPAD_R0_PIN,KEYPAD_R1_PIN,KEYPAD_R2_PIN,KEYPAD_R3_PIN};
	u8 Local_Au8ColumnsPin[KEYPAD_u8COLUMNS_NUMBER] = {KEYPAD_C0_PIN,KEYPAD_C1_PIN,KEYPAD_C2_PIN,KEYPAD_C3_PIN};
	u8 Local_Au8ArrayOfValue[KEYPAD_u8ROWS_NUMBER][KEYPAD_u8COLUMNS_NUMBER] = KEYPAD_Au8KEYS_VALUES ;

	MSYSTICK_enuInit();

	for(Local_u8ColumnIter = 0 ; Local_u8ColumnIter < KEYPAD_u8COLUMNS_NUMBER ; Local_u8ColumnIter++ )
	{
		/*  set column to zero*/
		MGPIO_enuSetPinValue(KEYPAD_GRP, Local_Au8ColumnsPin[Local_u8ColumnIter] , MGPIO_LOW_OUTPUT);

		for(Local_u8RowIter = 0 ; Local_u8RowIter < KEYPAD_u8ROWS_NUMBER ; Local_u8RowIter++)
		{
			MGPIO_enuGetPinValue(KEYPAD_GRP , Local_Au8RowsPin[Local_u8RowIter], &Local_u8PinValue );

			if( Local_u8PinValue == MGPIO_LOW_OUTPUT )
			{
				MSYSTICK_voidDelayMsec(10); // for debouncing
				MGPIO_enuGetPinValue(KEYPAD_GRP , Local_Au8RowsPin[Local_u8RowIter],&Local_u8PinValue);
				if( Local_u8PinValue == MGPIO_LOW_OUTPUT )
				{

					*Copy_pu8PressedKey = Local_Au8ArrayOfValue[Local_u8RowIter][Local_u8ColumnIter];
					//to prevent the holding press ( pooling or busy waiting )
					while(Local_u8PinValue == MGPIO_LOW_OUTPUT )
					{
						MGPIO_enuGetPinValue(KEYPAD_GRP , Local_Au8RowsPin[Local_u8RowIter] ,&Local_u8PinValue );
					}

					return ES_OK;
				}
			}

		}


		MGPIO_enuSetPinValue(KEYPAD_GRP, Local_Au8ColumnsPin[Local_u8ColumnIter] , MGPIO_HIGH_OUTPUT);
	}


	return Local_enuErrorState;
}
