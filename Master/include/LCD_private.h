
/******************************************************************************************************
 ******************************************************************************************************
 ******************************** AUTHOR  : Mahmoud Rabea  ********************************************
 ******************************** MICRO   : STM32F401CCU6  ********************************************
 ******************************** LAYER   : HAL            ********************************************
 ******************************** DRIVER  : LCD_Driver     ********************************************
 ******************************** File    : private File   ********************************************
 ******************************** Date    : 6/9/2023       ********************************************
 ******************************** Version : 1.0            ********************************************
 ******************************************************************************************************
 ******************************************************************************************************/

#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_



#define LCD_EIGHT_BIT               8
#define LCD_FOUR_BIT                4
#define LCD_BIT_MASK                1
#define LCD_u8BLOCKBYTES            8

static void HLCD_voidSendHalfDataPort(u8 Copy_u8Data);
static void HLCD_voidSendEnablePulse();


#endif /* LCD_PRIVATE_H_ */
