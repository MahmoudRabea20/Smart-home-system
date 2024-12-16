
/******************************************************************************************************
 ******************************************************************************************************
 ******************************** AUTHOR  : Mahmoud Rabea  ********************************************
 ******************************** MICRO   : STM32F401CCU6  ********************************************
 ******************************** LAYER   : MCAL           ********************************************
 ******************************** DRIVER  : UART_Driver    ********************************************
 ******************************** File    : interface File ********************************************
 ******************************** Date    : 4/9/2023       ********************************************
 ******************************** Version : 1.0            ********************************************
 ******************************************************************************************************
 ******************************************************************************************************/

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void MUART_voidInit(void);

void MUART_voidSendCharacter(u16 Copy_u16TransmittedCharacter);

u16 MUART_u16ReceiveCharacter(void);

ES_t MUART_enuSendString(const char* Copy_pchString);


#endif /* UART_INTERFACE_H_ */
