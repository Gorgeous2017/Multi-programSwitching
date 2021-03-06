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

#include "app_bearpi.h"


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


/**
 * @brief 模块选择结构体
 * 
 */
typedef struct {

	/* 迭代时增加必要的成员，如字符串的起始坐标、字体大小等 */
	uint16_t start_x;				/*!< 字符串起始横坐标 */
	uint16_t start_y;				/*!< 字符串起始纵坐标 */

	UINT32 (*creat_task)(void);		/*!< 该模块的功能函数 */

	char content[40]; 				/*!< 该行需要显示的字符串 */

} MODULE_CB_S;

/**
 * @brief 程序选择控制结构体
 * 
 */
typedef struct {

	uint8_t module_num;					/*!< 循环选择的模块数目 */
	MODULE_CB_S *module_select_area;	/*!< 模块选择区域 */
	void (*schedue_func)(void);			/*!< 调度函数 */

} UI_SCHEDUE_S;



/* Exported constants --------------------------------------------------------*/
#define EXMPL_NUM 4	/*!< Bearpi_Example 枚举体中的案例数目 */
#define COMM_NUM 3	/*!< Bearpi_Communicate 枚举体中的通讯方式数目 */
#define TIPS_NUM 2 /* 按键提示提示信息行数 */

//#define LCD_LINE_NUM (EXAMPLE_NUM + COMM_NUM + TIPS_NUM )

#define LCD_START_X     0
#define LCD_START_Y     0
#define LCD_WIDTH       240
#define LCD_HEIGHT      20
#define LCD_FRONT_SIZE  16

#define LCD_POINT_COLOR 			LIGHTBLUE
#define LCD_BACK_COLOR				BLACK
#define LCD_HIHTLIGHT_POINT_COLOR	DARKBLUE
#define LCD_HIHTLIGHT_BACK_COLOR	WHITE


#define KEY1_EXTI_IRQn EXTI2_IRQn
#define KEY2_EXTI_IRQn EXTI3_IRQn



/* Exported function -----------------------------------------------*/

UINT32 SelectKey_Interrupt(VOID);
//UINT32 creat_it_test_task();
void UI_DisplayAllMsg(void);

void UI_SwitchingModuleSelectArea(void);
void UI_RunUserApp(void);
void UI_HighlightChooseItem(MODULE_CB_S *taget_select_area, uint8_t module_num);
void UI_DisplayModuleMsg(MODULE_CB_S *taget_select_area, uint8_t module_num);

#endif /* __USER_INTERFACE_H__ */ 
/********************************** END OF FILE *******************************/