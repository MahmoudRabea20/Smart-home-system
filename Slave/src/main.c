

#include "STD_TYPES.h"
#include "BIT_MATHS.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "UART_interface.h"

#define TOGGLE_LAMP1             1
#define TOGGLE_LAMP2             2
#define TOGGLE_LAMP3             3
#define TOGGLE_FAN1              4
#define TOGGLE_FAN2              5
#define TOGGLE_FAN3              6
#define TOGGLE_TV                7
#define TURN_ON_AIRCONDITIONER   8
#define TURN_OFF_AIRCONDITIONER  9


int main()
{
	u8 Local_u8Status = 0 ;

	MRCC_voidInit();
	MRCC_enuEnablePeripheral(RCC_AHB1_BUS,RCC_AHB1ENR_GPIOA);
	MRCC_enuEnablePeripheral(RCC_AHB1_BUS,RCC_AHB1ENR_GPIOB);
	MRCC_enuEnablePeripheral(RCC_APB1_BUS,RCC_APB1ENR_USART2);
	MGPIO_enuSetPinDirectionMode(MGPIO_PORTA,MGPIO_PIN2,MGPIO_AF);
	MGPIO_enuSetPinDirectionMode(MGPIO_PORTA,MGPIO_PIN3,MGPIO_AF);
	MGPIO_enuSelectAlternateFunctionPin(MGPIO_PORTA, MGPIO_PIN2,MGPIO_AF7);
	MGPIO_enuSelectAlternateFunctionPin(MGPIO_PORTA, MGPIO_PIN3,MGPIO_AF7);

	for(u8 Local_u8Iterator = 0; Local_u8Iterator < MGPIO_PIN8 ; Local_u8Iterator++ )
	{
		MGPIO_enuSetPinDirectionMode(MGPIO_PORTB,Local_u8Iterator,MGPIO_OUTPUT);
		MGPIO_enuSetOutputSpeed(MGPIO_PORTB,Local_u8Iterator,MGPIO_LOW_SPEED);
		MGPIO_enuSetOutputType(MGPIO_PORTB,Local_u8Iterator,MGPIO_PUSH_PULL);
	}

	MUART_voidInit();


	while(1)
	{
		Local_u8Status = MUART_u16ReceiveCharacter();

		if( Local_u8Status == TOGGLE_LAMP1 )
		{
			MGPIO_enuTogglePinValue(MGPIO_PORTB,MGPIO_PIN0);
		}
		else if(Local_u8Status == TOGGLE_LAMP2)
		{
			MGPIO_enuTogglePinValue(MGPIO_PORTB,MGPIO_PIN1);
		}
		else if(Local_u8Status == TOGGLE_LAMP3)
		{
			MGPIO_enuTogglePinValue(MGPIO_PORTB,MGPIO_PIN2);
		}
		else if( Local_u8Status == TOGGLE_FAN1 )
		{
			MGPIO_enuTogglePinValue(MGPIO_PORTB,MGPIO_PIN3);
		}
		else if(Local_u8Status == TOGGLE_FAN2)
		{
			MGPIO_enuTogglePinValue(MGPIO_PORTB,MGPIO_PIN4);
		}
		else if(Local_u8Status == TOGGLE_FAN3)
		{
			MGPIO_enuTogglePinValue(MGPIO_PORTB,MGPIO_PIN5);
		}
		else if( Local_u8Status == TOGGLE_TV )
		{
			MGPIO_enuTogglePinValue(MGPIO_PORTB,MGPIO_PIN7);
		}
		else if(Local_u8Status == TURN_ON_AIRCONDITIONER)
		{
			MGPIO_enuSetPinValue(MGPIO_PORTB,MGPIO_PIN6,MGPIO_HIGH_OUTPUT);
		}
		else if(Local_u8Status == TURN_OFF_AIRCONDITIONER)
		{
			MGPIO_enuSetPinValue(MGPIO_PORTB,MGPIO_PIN6,MGPIO_LOW_OUTPUT);
		}
		else
		{
			/*Do Nothing*/
		}

	}

}
