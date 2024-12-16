
/******************************************************************************************************
 ******************************************************************************************************
 ******************************** AUTHOR  : Mahmoud Rabea  ********************************************
 ******************************** MICRO   : STM32F401CCU6  ********************************************
 ******************************** LAYER   : MCAL           ********************************************
 ******************************** DRIVER  : SYSTICK_Driver ********************************************
 ******************************** File    : interface File ********************************************
 ******************************** Date    : 3/9/2023       ********************************************
 ******************************** Version : 1.0            ********************************************
 ******************************************************************************************************
 ******************************************************************************************************/

#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_

void MSYSTICK_enuInit(void);

void MSYSTICK_voidLoadValue(u32 Copy_32RequiredValue);

u32 MSYSTICK_u32GetRemainingCounts(void);

u32 MSYSTICK_u32GetElapsedCounts(void);

u8 MSYSTICK_u8ReadFlag(void);

void MSYSTICK_voidDelayMsec(u32 Copy_u32DelayValue);

void MSYSTICK_voidDelayUsec(u32 Copy_u32DelayValue);

ES_t MSYSTICK_voidCallBackFunction(void (*Copy_pvPtrToFun)(void));



#endif /* SYSTICK_INTERFACE_H_ */
