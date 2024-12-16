
/******************************************************************************************************
 ******************************************************************************************************
 ******************************** AUTHOR  : Mahmoud Rabea *********************************************
 ******************************** MICRO   : STM32F401CCU6 *********************************************
 ******************************** LAYER   : MCAL          *********************************************
 ******************************** DRIVER  : NVIC_Driver   *********************************************
 ******************************** File    : interface File*********************************************
 ******************************** Date    : 30/8/2023     *********************************************
 ******************************** Version : 1.0           *********************************************
 ******************************************************************************************************
 ******************************************************************************************************/

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

/* Modes of Group of priority between groups and subgroups */

typedef enum
{
	NVIC_16_GRP_0_SUBGRP = 3,
	NVIC_8_GRP_2_SUBGRP,
	NVIC_4_GRP_4_SUBGRP,
	NVIC_2_GRP_8_SUBGRP,
	NVIC_0_GRP_16_SUBGRP
}Group_T;

/* Priority of Group and Sun Group */

typedef enum
{
	priority_0,
	priority_1,
	priority_2,
	priority_3,
	priority_4,
	priority_5,
	priority_6,
	priority_7,
	priority_8,
	priority_9,
	priority_10,
	priority_11,
	priority_12,
	priority_13,
	priority_14,
	priority_15
};

/* Copy_u8InterruptId : MNVIC_WWDG_POSITION_ID ----------> MNVIC_SPI4_POSITION_ID
 * */

ES_t MNVIC_enuEnableInterrupt(u8 Copy_u8InterruptId);

/* Copy_u8InterruptId : MNVIC_WWDG_POSITION_ID ----------> MNVIC_SPI4_POSITION_ID
 * */

ES_t MNVIC_enuDisableInterrupt(u8 Copy_u8InterruptId);

/* Copy_u8InterruptId : MNVIC_WWDG_POSITION_ID ----------> MNVIC_SPI4_POSITION_ID
 * */

ES_t MNVIC_enuSetPendingInterrupt(u8 Copy_u8InterruptId);

/* Copy_u8InterruptId : MNVIC_WWDG_POSITION_ID ----------> MNVIC_SPI4_POSITION_ID
 * */

ES_t MNVIC_enuClearPendingInterrupt(u8 Copy_u8InterruptId);

/* Copy_enuGroupMode : NVIC_16_GRP_0_SUBGRP
 *                     NVIC_8_GRP_2_SUBGRP
 *                     NVIC_4_GRP_4_SUBGRP
 *                     NVIC_2_GRP_8_SUBGRP
 *                     NVIC_0_GRP_16_SUBGRP
 * */

ES_t MNVIC_enuSetGroupMode(Group_T Copy_enuGroupMode);

/* Copy_u8InterruptId : MNVIC_WWDG_POSITION_ID ----------> MNVIC_SPI4_POSITION_ID
 * Copy_u8GroupId     : priority_0 ----------------------> priority_15
 * Copy_u8SubgroupId  : priority_0 ----------------------> priority_15
 * */

ES_t MNVIC_enuSetPriority(u8 Copy_u8InterruptId,u8 Copy_u8GroupPriorityNumber,u8 Copy_u8SubgroupPriorityNumber );


/* Positions of peripheral interrupt */
/* Set the position of peripheral interrupt when you need it */
#define MNVIC_WWDG_POSITION_ID                          0
#define MNVIC_EXTI16_PVD_POSITION_ID                    1
#define MNVIC_EXTI21_TAMP_STAMP_POSITION_ID             2
#define MNVIC_EXTI22_RTC_WKUP_POSITION_ID               3
#define MNVIC_FLASH_POSITION_ID                         4
#define MNVIC_RCC_POSITION_ID                           5
#define MNVIC_EXTI0_POSITION_ID                         6
#define MNVIC_EXTI1_POSITION_ID                         7
#define MNVIC_EXTI2_POSITION_ID                         8
#define MNVIC_EXTI3_POSITION_ID                         9
#define MNVIC_EXTI4_POSITION_ID                         10
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              0
#define MNVIC__POSITION_ID                              84
#define MNVIC_SPI4_POSITION_ID


#endif /* NVIC_INTERFACE_H_ */
