/**
 * ******************************************************************************
 * @file user_interface.h
 * @author Gump
 * @version V0.1
 * @date 2020-08-06
 * @brief 用户多程序选择交互头文件
 * 
 * ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USER_INTERFACE_H__
#define __USER_INTERFACE_H__ 

/* Includes ------------------------------------------------------------------*/
//#include "los_typedef.h"
#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#include "lcd.h"


/* Exported typedef -----------------------------------------------------------*/
/**
 * @brief 小熊派物联网案例/应用场景枚举体
 * 
 */
typedef enum {
    E53_SC1, /*!< StreetLight 小熊派智慧路灯案例 */
    E53_IA1, /*!< Agriculture 小熊派智慧农业案例 */
    E53_ST1, /*!< Track 小熊派智慧物流案例 */
    E53_SF1  /*!< Smoke 小熊派智慧烟感案例 */
} Bearpi_Example;

/**
 * @brief 小熊派通讯模组枚举体
 * 
 */
typedef enum {
    COMM_WIFI,  /*!< Wi-Fi 通讯模组 */
    COMM_NB,    /*!< NB 通讯模组 */
    COMM_2G     /*!< 2G 通讯模组 */
} Bearpi_Communicate;


typedef struct {

    /* 迭代时增加必要的成员，如字符串的起始坐标、字体大小等 */
    
    uint8_t content[40]; /*!< 该行需要显示的内容 */

} LCD_String_TypeDef;



/* Exported constants --------------------------------------------------------*/
#define EXMPL_NUM 4
#define COMM_NUM 3
//#define TIPS_NUM 2

//#define LCD_LINE_NUM (EXAMPLE_NUM + COMM_NUM + TIPS_NUM )

#define KEY1_EXTI_IRQn EXTI2_IRQn
#define KEY2_EXTI_IRQn EXTI3_IRQn



/* Exported function -----------------------------------------------*/

UINT32 ChoiceKey_Interrupt(VOID);

#endif /* __USER_INTERFACE_H__ */ 
/********************************** END OF FILE *******************************/