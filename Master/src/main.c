
#include "STD_TYPES.h"
#include "BIT_MATHS.h"

#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "NVIC_interface.h"
#include "EXTI_interface.h"
#include "SYSTICK_interface.h"
#include "UART_interface.h"
#include "LCD_interface.h"
#include "Keypad_interface.h"

#define TOGGLE_LAMP1             1
#define TOGGLE_LAMP2             2
#define TOGGLE_LAMP3             3
#define TOGGLE_FAN1              4
#define TOGGLE_FAN2              5
#define TOGGLE_FAN3              6
#define TOGGLE_TV                7
#define TURN_ON_AIRCONDITIONER   8
#define TURN_OFF_AIRCONDITIONER  9


#define OFF              0
#define ON               1

u8 Global_u8ASCounter = 0 ;
u8 Global_u8AChCounter = 0 ;
u8 Global_u8GSCounter = 0 ;
u8 Global_u8GChCounter = 0 ;
u8 Global_Au8AdminSetPassword[4];
u8 Global_Au8AdminCheckedPassword[4];
u8 Global_Au8GuestSetPassword[4];
u8 Global_Au8GuestCheckedPassword[4];

Bolean App_u8CheckPassword(u8 Copy_Au8SetPassword[],u8 Copy_Au8CheckedPassword[],u8 Copy_u8Counter1,u8 Copy_u8Counter2 );

int main()
{


	u8 Local_u8PressedValue = Keypad_NOT_PREESED ;
	u8 Local_u8AdminTriesCounts = 3 ;
	u8 Local_u8GuestTriesCounts = 3 ;
	u8 Local_u8AtAdmin = 0;
	u8 Local_u8AtGuest = 0;
	u8 Local_u8AtAirCond = 0 ;
	u8 Local_u8LampOneStatus = 0;
	u8 Local_u8LampTwoStatus = 0;
	u8 Local_u8LampThreeStatus = 0;
	u8 Local_u8FanOneStatus = 0;
	u8 Local_u8FanTwoStatus = 0;
	u8 Local_u8FanThreeStatus = 0;
	u8 Local_u8AirConStatus = 0;
	u8 Local_u8TVStatus = 0 ;
	u8 Local_Au8TemperatureValue[2] ;
	u8 Local_u8TemCounter = 0 ;
	u32 Local_u32ReadigValue=0 ;

	MRCC_voidInit();
	MRCC_enuEnablePeripheral(RCC_AHB1_BUS,RCC_AHB1ENR_GPIOA);
	MRCC_enuEnablePeripheral(RCC_APB2_BUS,RCC_APB2ENR_ADC1);
	MGPIO_enuSetPinDirectionMode(MGPIO_PORTA,MGPIO_PIN0,MGPIO_ANALOG);
	MRCC_enuEnablePeripheral(RCC_AHB1_BUS,RCC_AHB1ENR_GPIOB);
	MRCC_enuEnablePeripheral(RCC_APB1_BUS,RCC_APB1ENR_USART2);
	MRCC_enuEnablePeripheral(RCC_APB2_BUS,RCC_APB2ENR_ADC1);
	MGPIO_enuSetPinDirectionMode(MGPIO_PORTA,MGPIO_PIN0,MGPIO_ANALOG);
	MGPIO_enuSetPinDirectionMode(MGPIO_PORTA,MGPIO_PIN2,MGPIO_AF);
	MGPIO_enuSetPinDirectionMode(MGPIO_PORTA,MGPIO_PIN3,MGPIO_AF);
	MGPIO_enuSelectAlternateFunctionPin(MGPIO_PORTA, MGPIO_PIN2,MGPIO_AF7);
	MGPIO_enuSelectAlternateFunctionPin(MGPIO_PORTA, MGPIO_PIN3,MGPIO_AF7);
	MGPIO_enuSetPinDirectionMode(MGPIO_PORTA,MGPIO_PIN1,MGPIO_OUTPUT);
	MGPIO_enuSetOutputSpeed(MGPIO_PORTA,MGPIO_PIN1,MGPIO_LOW_SPEED);
	MGPIO_enuSetOutputType(MGPIO_PORTA,MGPIO_PIN1,MGPIO_PUSH_PULL);
	HLCD_enuInit();
	MUART_voidInit();
	HKeypad_enuInit();
	ADC_voidInit();
	HLCD_enuWriteString("Welcome to Smart");
	HLCD_enuGoToXYPosition(0,1);
	HLCD_enuWriteString("Home System ");
	MSYSTICK_voidDelayMsec(1000);
	HLCD_voidClear();
	HLCD_enuWriteString("Set Admin pass");
	HLCD_enuGoToXYPosition(0,1);

	/***************************** Set Admin Password *****************************************/

	while(1)
	{
		do
		{
			HKeypad_enuGetPressedKey(&Local_u8PressedValue);

		}
		while( Local_u8PressedValue == Keypad_NOT_PREESED);

		if(Local_u8PressedValue == 'C')
		{
			HLCD_voidClear();
			HLCD_enuWriteString("Password saved");
			MSYSTICK_voidDelayMsec(1000);
			HLCD_voidClear();
			break;
		}
		else if(Local_u8PressedValue == '-')
		{
			Global_u8ASCounter--;
			HLCD_voidDeleteCharacter(1);
		}
		else
		{
			HLCD_enuWriteIntegerNumber(Local_u8PressedValue);
			MSYSTICK_voidDelayMsec(20);
			HLCD_enuGoToXYPosition(Global_u8ASCounter,1);
			HLCD_enuWriteData('*');
			Global_Au8AdminSetPassword[Global_u8ASCounter] = Local_u8PressedValue ;
			Global_u8ASCounter ++;
		}
	}

	/******************************************************************************************/

	/***************************** Set Guest Password *****************************************/
	HLCD_enuWriteString("Set Guest pass");
	HLCD_enuGoToXYPosition(0,1);

	while(1)
	{
		do
		{
			HKeypad_enuGetPressedKey(&Local_u8PressedValue);

		}
		while( Local_u8PressedValue == Keypad_NOT_PREESED);

		if(Local_u8PressedValue == 'C')
		{
			HLCD_voidClear();
			HLCD_enuWriteString("Password saved");
			MSYSTICK_voidDelayMsec(1000);
			HLCD_voidClear();
			break;
		}
		else if(Local_u8PressedValue == '-')
		{
			Global_u8GSCounter--;
			HLCD_voidDeleteCharacter(1);
		}
		else
		{
			HLCD_enuWriteIntegerNumber(Local_u8PressedValue);
			MSYSTICK_voidDelayMsec(20);
			HLCD_enuGoToXYPosition(Global_u8GSCounter,1);
			HLCD_enuWriteData('*');
			Global_Au8GuestSetPassword[Global_u8GSCounter] = Local_u8PressedValue ;
			Global_u8GSCounter ++;
		}
	}

	/******************************************************************************************/

	/********************************** The main loop of project ******************************/

	while(1)
	{
		/********************************** Select Mode ******************************/
		HLCD_enuWriteString("Select Mode: ");
		HLCD_enuGoToXYPosition(0,1);
		HLCD_enuWriteString("0:Admin  1:Guest ");


		do
		{
			HKeypad_enuGetPressedKey(&Local_u8PressedValue);
		}
		while( Local_u8PressedValue == Keypad_NOT_PREESED);

		HLCD_enuGoToXYPosition(13,0);
		HLCD_enuWriteIntegerNumber(Local_u8PressedValue);
		MSYSTICK_voidDelayMsec(500);
		/**************************Select Admin Mode ******************************************/
		if( Local_u8PressedValue == 0 )
		{
			while(1)
			{
				/********************************** Check Admin Password ******************************/

				if(Local_u8AtAdmin == 0)
				{
					HLCD_voidClear();
					HLCD_enuWriteString("Check Admin Pass");
					HLCD_enuGoToXYPosition(0,1);
					Local_u8AtAdmin = 1;
				}

				do
				{
					HKeypad_enuGetPressedKey(&Local_u8PressedValue);
				}
				while( Local_u8PressedValue == Keypad_NOT_PREESED);

				if(Local_u8PressedValue == 'C')
				{
					if(App_u8CheckPassword(Global_Au8AdminSetPassword,Global_Au8AdminCheckedPassword,Global_u8ASCounter,Global_u8AChCounter))
					{
						do
						{
							/********************************** Select a room ******************************/

							HLCD_voidClear();
							HLCD_enuWriteString("1:Room1  2:Room2");
							HLCD_enuGoToXYPosition(0,1);
							HLCD_enuWriteString("3:Recep. 4:Air CON.");

							do
							{
								HKeypad_enuGetPressedKey(&Local_u8PressedValue);
							}
							while( Local_u8PressedValue == Keypad_NOT_PREESED);

							/********************************** Select room 1 ******************************/
							if(Local_u8PressedValue == 1)
							{
								do
								{
									HLCD_voidClear();
									HLCD_enuWriteString("1:Lamp  2:Fan");
									HLCD_enuGoToXYPosition(0,1);
									HLCD_enuWriteString("3:RET");
									do
									{
										HKeypad_enuGetPressedKey(&Local_u8PressedValue);
									}
									while( Local_u8PressedValue == Keypad_NOT_PREESED);

									/********************************** Select the lamp of room 1 ******************************/
									if(Local_u8PressedValue == 1)
									{
										do
										{
											HLCD_voidClear();
											HLCD_enuWriteString("Lamp1 Status:");
											if(Local_u8LampOneStatus == OFF)
											{
												HLCD_enuWriteString("OFF");
											}
											else
											{
												HLCD_enuWriteString("ON");
											}
											HLCD_enuGoToXYPosition(0,1);
											HLCD_enuWriteString("1:Tog Lamp 2:RET");
											do
											{
												HKeypad_enuGetPressedKey(&Local_u8PressedValue);
											}
											while( Local_u8PressedValue == Keypad_NOT_PREESED);

											if( Local_u8PressedValue == 1)
											{
												MUART_voidSendCharacter(TOGGLE_LAMP1);
												Local_u8LampOneStatus ^= 1;
											}

											/********************************** Return To Room1 ******************************/
											else if( Local_u8PressedValue == 2)
											{
												break;
											}
											else
											{/*Do Nothing*/}
										}while(1);
									}

									/********************************** Select the fan of room 1 ******************************/

									else if(Local_u8PressedValue == 2)
									{
										do
										{
											HLCD_voidClear();
											HLCD_enuWriteString("Fan1 Status:");
											if(Local_u8FanOneStatus == OFF)
											{
												HLCD_enuWriteString("OFF");
											}
											else
											{
												HLCD_enuWriteString("ON");
											}
											HLCD_enuGoToXYPosition(0,1);
											HLCD_enuWriteString("1:Tog Fan 2:RET");
											do
											{
												HKeypad_enuGetPressedKey(&Local_u8PressedValue);
											}
											while( Local_u8PressedValue == Keypad_NOT_PREESED);

											if( Local_u8PressedValue == 2)
											{
												break;
											}
											else if( Local_u8PressedValue == 1)
											{
												MUART_voidSendCharacter(TOGGLE_FAN1);
												Local_u8FanOneStatus ^= 1;
											}
											else
											{/*Do Nothing*/}
										}while(1);
									}

									/********************************** Return To Room1 ******************************/
									else if(Local_u8PressedValue == 3)
									{
										break;
									}
									else
									{/*Do Nothing*/}
								}while(1);

							}
							/********************************** Select room 2 ******************************/

							else if(Local_u8PressedValue == 2)
							{
								do
								{
									HLCD_voidClear();
									HLCD_enuWriteString("1:Lamp  2:Fan");
									HLCD_enuGoToXYPosition(0,1);
									HLCD_enuWriteString("3:TV     4:RET");
									do
									{
										HKeypad_enuGetPressedKey(&Local_u8PressedValue);
									}
									while( Local_u8PressedValue == Keypad_NOT_PREESED);

									/********************************** Select the lamp of room 2 ******************************/

									if(Local_u8PressedValue == 1)
									{
										do
										{
											HLCD_voidClear();
											HLCD_enuWriteString("Lamp2 Status:");
											if(Local_u8LampTwoStatus == OFF)
											{
												HLCD_enuWriteString("OFF");
											}
											else
											{
												HLCD_enuWriteString("ON");
											}
											HLCD_enuGoToXYPosition(0,1);
											HLCD_enuWriteString("1:Tog Lamp 2:RET");
											do
											{
												HKeypad_enuGetPressedKey(&Local_u8PressedValue);
											}
											while( Local_u8PressedValue == Keypad_NOT_PREESED);

											if( Local_u8PressedValue == 2)
											{
												break;
											}
											else if( Local_u8PressedValue == 1)
											{
												MUART_voidSendCharacter(TOGGLE_LAMP2);
												Local_u8LampTwoStatus ^= 1;
											}
											else
											{/*Do Nothing*/}
										}while(1);
									}

									/********************************** Select the fan of room 2 ******************************/

									else if(Local_u8PressedValue == 2)
									{
										do
										{
											HLCD_voidClear();
											HLCD_enuWriteString("Fan2 Status:");
											if(Local_u8FanTwoStatus == OFF)
											{
												HLCD_enuWriteString("OFF");
											}
											else
											{
												HLCD_enuWriteString("ON");
											}
											HLCD_enuGoToXYPosition(0,1);
											HLCD_enuWriteString("1:Tog Fan 2:RET");
											do
											{
												HKeypad_enuGetPressedKey(&Local_u8PressedValue);
											}
											while( Local_u8PressedValue == Keypad_NOT_PREESED);

											if( Local_u8PressedValue == 2)
											{
												break;
											}
											else if( Local_u8PressedValue == 1)
											{
												MUART_voidSendCharacter(TOGGLE_FAN2);
												Local_u8FanTwoStatus ^= 1;
											}
											else
											{/*Do Nothing*/}
										}while(1);
									}

									/********************************** Select the TV of room 2 ******************************/
									else if(Local_u8PressedValue == 3)
									{
										do
										{
											HLCD_voidClear();
											HLCD_enuWriteString("TV Status:");
											if(Local_u8TVStatus == OFF)
											{
												HLCD_enuWriteString("OFF");
											}
											else
											{
												HLCD_enuWriteString("ON");
											}
											HLCD_enuGoToXYPosition(0,1);
											HLCD_enuWriteString("1:Tog TV 2:RET");
											do
											{
												HKeypad_enuGetPressedKey(&Local_u8PressedValue);
											}
											while( Local_u8PressedValue == Keypad_NOT_PREESED);

											if( Local_u8PressedValue == 2)
											{
												break;
											}
											else if( Local_u8PressedValue == 1)
											{
												MUART_voidSendCharacter(TOGGLE_TV);
												Local_u8TVStatus ^= 1;
											}
											else
											{/*Do Nothing*/}
										}while(1);

									}

									/********************************** Return To Room3 ******************************/
									else if(Local_u8PressedValue == 4)
									{
										break;
									}
									else
									{/*Do Nothing*/}

								}while(1);
							}

							/********************************** Select The reception ******************************/

							else if(Local_u8PressedValue == 3)
							{
								do
								{
									HLCD_voidClear();
									HLCD_enuWriteString("1:Lamp  2:Fan");
									HLCD_enuGoToXYPosition(0,1);
									HLCD_enuWriteString("3:RET");
									do
									{
										HKeypad_enuGetPressedKey(&Local_u8PressedValue);
									}
									while( Local_u8PressedValue == Keypad_NOT_PREESED);

									/********************************** Select the lamp of reception ******************************/
									if(Local_u8PressedValue == 1)
									{
										do
										{
											HLCD_voidClear();
											HLCD_enuWriteString("Lamp3 Status:");
											if(Local_u8LampThreeStatus == OFF)
											{
												HLCD_enuWriteString("OFF");
											}
											else
											{
												HLCD_enuWriteString("ON");
											}
											HLCD_enuGoToXYPosition(0,1);
											HLCD_enuWriteString("1:Tog Lamp 2:RET");
											do
											{
												HKeypad_enuGetPressedKey(&Local_u8PressedValue);
											}
											while( Local_u8PressedValue == Keypad_NOT_PREESED);

											if( Local_u8PressedValue == 2)
											{
												break;
											}
											else if( Local_u8PressedValue == 1)
											{
												MUART_voidSendCharacter(TOGGLE_LAMP3);
												Local_u8LampThreeStatus ^= 1;
											}
										}while(1);
									}

									/********************************** Select the fan reception ******************************/
									else if(Local_u8PressedValue == 2)
									{
										do
										{
											HLCD_voidClear();
											HLCD_enuWriteString("Fan3 Status:");
											if(Local_u8FanThreeStatus == OFF)
											{
												HLCD_enuWriteString("OFF");
											}
											else
											{
												HLCD_enuWriteString("ON");
											}
											HLCD_enuGoToXYPosition(0,1);
											HLCD_enuWriteString("1:Tog Fan 2:RET");
											do
											{
												HKeypad_enuGetPressedKey(&Local_u8PressedValue);
											}
											while( Local_u8PressedValue == Keypad_NOT_PREESED);

											if( Local_u8PressedValue == 1)
											{
												MUART_voidSendCharacter(TOGGLE_FAN3);
												Local_u8FanThreeStatus ^= 1;
											}
											else if( Local_u8PressedValue == 2)
											{
												break;
											}
										}while(1);
									}

									/********************************** Return To ROOMS ******************************/
									else if(Local_u8PressedValue == 3)
									{
										break;
									}
									else
									{/*Do Nothing*/}

								}while(1);
							}

							else if(Local_u8PressedValue == 4)
							{
								do
								{
									HLCD_voidClear();
									HLCD_enuWriteString("Air C Status:");
									if(Local_u8AirConStatus == OFF)
									{
										HLCD_enuWriteString("OFF");
									}
									else if(Local_u8AirConStatus == ON)
									{
										HLCD_enuWriteString("ON");
									}
									HLCD_enuGoToXYPosition(0,1);
									HLCD_enuWriteString("1:ON 2:OFF 3:RET");
									do
									{
										HKeypad_enuGetPressedKey(&Local_u8PressedValue);
									}
									while( Local_u8PressedValue == Keypad_NOT_PREESED);

									if(Local_u8PressedValue == 1)
									{
										do
										{
											if(Local_u8AtAirCond == 0)
											{
												HLCD_voidClear();
												HLCD_enuWriteString("Set temperature");
												HLCD_enuGoToXYPosition(4,1);
												HLCD_enuWriteData('C');
												HLCD_enuGoToXYPosition(0,1);
												Local_u8AtAirCond = 1;
											}
											do
											{
												HKeypad_enuGetPressedKey(&Local_u8PressedValue);
											}
											while( Local_u8PressedValue == Keypad_NOT_PREESED);
											if(Local_u8PressedValue == 'C')
											{
												HLCD_voidClear();
												HLCD_enuWriteString("Temperature sent");
												MSYSTICK_voidDelayMsec(500);
												break;
											}
											else
											{
												HLCD_enuWriteIntegerNumber(Local_u8PressedValue);
												MSYSTICK_voidDelayMsec(2000);
												Local_Au8TemperatureValue[Local_u8TemCounter] = Local_u8PressedValue ;
												Local_u8TemCounter ++;
											}

										}while(1);

									}
									else if( Local_u8PressedValue == 2)
									{
										MUART_voidSendCharacter(TURN_OFF_AIRCONDITIONER);
										Local_u8AirConStatus = OFF;
									}
									else if( Local_u8PressedValue == 3)
									{
										break;
									}
								}while(1);

								if(((Local_Au8TemperatureValue[0] * 10) + Local_Au8TemperatureValue[1] ) < 25)
								{
									MUART_voidSendCharacter(TURN_ON_AIRCONDITIONER);
									Local_u8AirConStatus = ON;
								}
							}
							else
							{/*Do Nothing*/}

						}while(1);
					}
					else
					{
						HLCD_voidClear();
						Local_u8AdminTriesCounts--;
						Global_u8AChCounter = 0;
						HLCD_enuWriteString("Wrong Password ");
						HLCD_enuGoToXYPosition(0,1);
						HLCD_enuWriteString("Tries left : ");
						HLCD_enuWriteIntegerNumber(Local_u8AdminTriesCounts);
						MSYSTICK_voidDelayMsec(1000);
						Local_u8AtAdmin = 0;
						if(Local_u8AdminTriesCounts == 0)
						{
							HLCD_voidClear();
							MGPIO_enuSetPinValue(MGPIO_PORTA,MGPIO_PIN1,MGPIO_HIGH_OUTPUT);
							HLCD_enuWriteString("Thief");
							MSYSTICK_voidDelayMsec(1000);
							while(1);
						}
					}

				}
				else if(Local_u8PressedValue == '-')
				{
					Global_u8AChCounter--;
					HLCD_voidDeleteCharacter(1);
				}
				else
				{
					HLCD_enuWriteIntegerNumber(Local_u8PressedValue);
					MSYSTICK_voidDelayMsec(20);
					HLCD_enuGoToXYPosition(Global_u8AChCounter,1);
					HLCD_enuWriteData('*');
					Global_Au8AdminCheckedPassword[Global_u8AChCounter] = Local_u8PressedValue ;
					Global_u8AChCounter ++;
				}

			}
		}

		/**************************** Select Guest Mode ********************************************/

		if( Local_u8PressedValue == 1 )
		{
			while(1)
			{
				/********************************** Check Guest Password ******************************/

				if(Local_u8AtGuest == 0)
				{
					HLCD_voidClear();
					HLCD_enuWriteString("Check Guest Pass");
					HLCD_enuGoToXYPosition(0,1);
					Local_u8AtGuest = 1;
				}

				do
				{
					HKeypad_enuGetPressedKey(&Local_u8PressedValue);
				}
				while( Local_u8PressedValue == Keypad_NOT_PREESED);

				if(Local_u8PressedValue == 'C')
				{
					if(App_u8CheckPassword(Global_Au8GuestSetPassword,Global_Au8GuestCheckedPassword,Global_u8GSCounter,Global_u8GChCounter))
					{
						do
						{
							/********************************** Select a room ******************************/

							HLCD_voidClear();
							HLCD_enuWriteString("1:Room1 ");
							HLCD_enuGoToXYPosition(0,1);
							HLCD_enuWriteString("2:Reception ");

							do
							{
								HKeypad_enuGetPressedKey(&Local_u8PressedValue);
							}
							while( Local_u8PressedValue == Keypad_NOT_PREESED);

							/********************************** Select room 1 ******************************/
							if(Local_u8PressedValue == 1)
							{
								do
								{
									HLCD_voidClear();
									HLCD_enuWriteString("1:Lamp  2:Fan");
									HLCD_enuGoToXYPosition(0,1);
									HLCD_enuWriteString("3:RET");
									do
									{
										HKeypad_enuGetPressedKey(&Local_u8PressedValue);
									}
									while( Local_u8PressedValue == Keypad_NOT_PREESED);

									/********************************** Select the lamp of room 1 ******************************/
									if(Local_u8PressedValue == 1)
									{
										do
										{
											HLCD_voidClear();
											HLCD_enuWriteString("Lamp1 Status:");
											if(Local_u8LampOneStatus == OFF)
											{
												HLCD_enuWriteString("OFF");
											}
											else
											{
												HLCD_enuWriteString("ON");
											}
											HLCD_enuGoToXYPosition(0,1);
											HLCD_enuWriteString("1:Tog Lamp 2:RET");
											do
											{
												HKeypad_enuGetPressedKey(&Local_u8PressedValue);
											}
											while( Local_u8PressedValue == Keypad_NOT_PREESED);

											if( Local_u8PressedValue == 1)
											{
												MUART_voidSendCharacter(TOGGLE_LAMP1);
												Local_u8LampOneStatus ^= 1;
											}

											/********************************** Return To Room1 ******************************/
											else if( Local_u8PressedValue == 2)
											{
												break;
											}
											else
											{/*Do Nothing*/}
										}while(1);
									}

									/********************************** Select the fan of room 1 ******************************/

									else if(Local_u8PressedValue == 2)
									{
										do
										{
											HLCD_voidClear();
											HLCD_enuWriteString("Fan1 Status:");
											if(Local_u8FanOneStatus == OFF)
											{
												HLCD_enuWriteString("OFF");
											}
											else
											{
												HLCD_enuWriteString("ON");
											}
											HLCD_enuGoToXYPosition(0,1);
											HLCD_enuWriteString("1:Tog Fan 2:RET");
											do
											{
												HKeypad_enuGetPressedKey(&Local_u8PressedValue);
											}
											while( Local_u8PressedValue == Keypad_NOT_PREESED);

											if( Local_u8PressedValue == 2)
											{
												break;
											}
											else if( Local_u8PressedValue == 1)
											{
												MUART_voidSendCharacter(TOGGLE_FAN1);
												Local_u8FanOneStatus ^= 1;
											}
											else
											{/*Do Nothing*/}
										}while(1);
									}

									/********************************** Return To Room1 ******************************/
									else if(Local_u8PressedValue == 3)
									{
										break;
									}
									else
									{/*Do Nothing*/}
								}while(1);

							}

							/********************************** Select The reception ******************************/

							else if(Local_u8PressedValue == 2)
							{
								do
								{
									HLCD_voidClear();
									HLCD_enuWriteString("1:Lamp  2:Fan");
									HLCD_enuGoToXYPosition(0,1);
									HLCD_enuWriteString("3:RET");
									do
									{
										HKeypad_enuGetPressedKey(&Local_u8PressedValue);
									}
									while( Local_u8PressedValue == Keypad_NOT_PREESED);

									/********************************** Select the lamp of reception ******************************/
									if(Local_u8PressedValue == 1)
									{
										do
										{
											HLCD_voidClear();
											HLCD_enuWriteString("Lamp3 Status:");
											if(Local_u8LampThreeStatus == OFF)
											{
												HLCD_enuWriteString("OFF");
											}
											else
											{
												HLCD_enuWriteString("ON");
											}
											HLCD_enuGoToXYPosition(0,1);
											HLCD_enuWriteString("1:Tog Lamp 2:RET");
											do
											{
												HKeypad_enuGetPressedKey(&Local_u8PressedValue);
											}
											while( Local_u8PressedValue == Keypad_NOT_PREESED);

											if( Local_u8PressedValue == 2)
											{
												break;
											}
											else if( Local_u8PressedValue == 1)
											{
												MUART_voidSendCharacter(TOGGLE_LAMP3);
												Local_u8LampThreeStatus ^= 1;
											}
										}while(1);
									}

									/********************************** Select the fan of reception ******************************/
									else if(Local_u8PressedValue == 2)
									{
										do
										{
											HLCD_voidClear();
											HLCD_enuWriteString("Fan3 Status:");
											if(Local_u8FanThreeStatus == OFF)
											{
												HLCD_enuWriteString("OFF");
											}
											else
											{
												HLCD_enuWriteString("ON");
											}
											HLCD_enuGoToXYPosition(0,1);
											HLCD_enuWriteString("1:Tog Fan 2:RET");
											do
											{
												HKeypad_enuGetPressedKey(&Local_u8PressedValue);
											}
											while( Local_u8PressedValue == Keypad_NOT_PREESED);

											if( Local_u8PressedValue == 1)
											{
												MUART_voidSendCharacter(TOGGLE_FAN3);
												Local_u8FanThreeStatus ^= 1;
											}
											/********************************** Return To the reception ******************************/

											else if( Local_u8PressedValue == 2)
											{
												break;
											}
										}while(1);
									}

									/********************************** Return To ROOMS ******************************/
									else if(Local_u8PressedValue == 3)
									{
										break;
									}
									else
									{/*Do Nothing*/}

								}while(1);
							}
							else
							{/*Do Nothing*/}

						}while(1);
					}
					else
					{
						HLCD_voidClear();
						Local_u8GuestTriesCounts--;
						Global_u8GChCounter = 0;
						HLCD_enuWriteString("Wrong Password ");
						HLCD_enuGoToXYPosition(0,1);
						HLCD_enuWriteString("Tries left : ");
						HLCD_enuWriteIntegerNumber(Local_u8GuestTriesCounts);
						MSYSTICK_voidDelayMsec(1000);
						Local_u8AtGuest = 0;
						if(Local_u8GuestTriesCounts == 0)
						{
							HLCD_voidClear();
							MGPIO_enuSetPinValue(MGPIO_PORTA,MGPIO_PIN1,MGPIO_HIGH_OUTPUT);
							HLCD_enuWriteString("Thief");
							MSYSTICK_voidDelayMsec(1000);
							while(1);
						}
					}

				}
				else if(Local_u8PressedValue == '-')
				{
					Global_u8GChCounter--;
					HLCD_voidDeleteCharacter(1);
				}
				else
				{
					HLCD_enuWriteIntegerNumber(Local_u8PressedValue);
					MSYSTICK_voidDelayMsec(20);
					HLCD_enuGoToXYPosition(Global_u8GChCounter,1);
					HLCD_enuWriteData('*');
					Global_Au8GuestCheckedPassword[Global_u8GChCounter] = Local_u8PressedValue ;
					Global_u8GChCounter ++;
				}

			}
		}


	}


}



Bolean App_u8CheckPassword(u8 Copy_Au8SetPassword[],u8 Copy_Au8CheckedPassword[],u8 Copy_u8SetCounter,u8 Copy_u8ChechedCounter )
{
	if(Copy_u8SetCounter == Copy_u8ChechedCounter)
	{
		for(u8 Loacl_u8Iterator = 0 ; Loacl_u8Iterator < Copy_u8SetCounter ; Loacl_u8Iterator++)
		{
			if( Copy_Au8SetPassword[Loacl_u8Iterator] != Copy_Au8CheckedPassword[Loacl_u8Iterator])
			{
				return FALSE ;
			}
		}

		return TRUE ;

	}
	else
	{
		return FALSE;
	}

}


