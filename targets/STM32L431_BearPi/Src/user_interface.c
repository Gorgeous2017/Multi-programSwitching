/**
 * ******************************************************************************
 * @file user_interface.c
 * @author Gump
 * @version V0.1
 * @date 2020-08-06
 * @brief 用户多程序选择交互源文件
 * 
 * @details 
 * 多程序选择UI开发思路
 * 1. 将需要显示的LCD信息按功能进行划分
 * 2. 初始化LCD各行的字符串信息
 * 3. 编写交互逻辑，即按键中断响应
 * 3.1. 模块选择交互
 * 	- 成员下标自增以及循环计数
 * 	- 刷新先前的选择
 * 	- 高亮当前选择
 * 3.2. 模块确认交互
 * 	- 重新赋值模块数目
 * 4. 屏蔽按键中断
 * 	- 用户应用程序可重新实现中断响应函数
 * 5. 执行用户选择的任务
 * 5.1. 赋值函数指针
 * 
 * ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "user_interface.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

UI_SCHEDUE_S ui_schedue[2] = {
	{
		.module_num = EXMPL_NUM,
		.schedue_func = UI_SwitchingModuleSelectArea
	},
	{
		.module_num = COMM_NUM,
		.schedue_func = UI_RunUserApp
	}
}; /*!< 循环选择控制流 */

volatile uint8_t current_index = 0;
UI_SCHEDUE_S *curr_schedue = &(ui_schedue[0]);
UINT32 (*user_select_task)();

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void UI_SwitchingModuleSelectArea(void)
{
	printf("Function: UI_SwitchingModuleSelectArea in \n");

	/* 检验下标是否合法 */
	if(current_index == 0)
	{
		return;
	}

	user_select_task = curr_schedue->module_select_area[current_index].creat_task;

	UI_DisplayModuleMsg(curr_schedue->module_select_area, curr_schedue->module_num + 1);

	LCD_ShowString(	10 * LCD_FRONT_SIZE / 2, 
				curr_schedue->module_select_area[current_index].start_y,
				LCD_WIDTH, 
				LCD_HEIGHT, 
				LCD_FRONT_SIZE, 
				"<<===");

	/* 切换模块区域 */
	curr_schedue = &(ui_schedue[1]);

	/* 复位模块选择下标 */
	current_index = 1;
	UI_HighlightChooseItem(curr_schedue->module_select_area, curr_schedue->module_num);

}

void UI_RunUserApp(void)
{
	printf("Function: UI_RunUserApp in \n");

	/* 通讯方式切换 */


	/* 用户已经选择完成，清屏 */
	LCD_Clear(LCD_BACK_COLOR);

	/* 创建所选模块对应的任务 */
	user_select_task();

	/* 关闭按键中断 */
	LOS_HwiDelete(KEY1_EXTI_IRQn);
	LOS_HwiDelete(KEY2_EXTI_IRQn);

}

/**
 * @brief 初始化各个字符串的参数
 * 
 */
void UI_MsgInit(void) 
{
	static MODULE_CB_S exmpl_select_area[EXMPL_NUM + 1]; /*!< 小熊派物联网案例选择区域 */
	static MODULE_CB_S comm_select_area[COMM_NUM + 1]; /*!< 小熊派通讯模块选择区域 */

	exmpl_select_area[0].start_y = 40;

	exmpl_select_area[1].start_y = 60;
	exmpl_select_area[2].start_y = 80;
	exmpl_select_area[3].start_y = 100;
	exmpl_select_area[4].start_y = 120;

	exmpl_select_area[1].creat_task = creat_sc1_collection_task;
	exmpl_select_area[2].creat_task = creat_ia1_collection_task;

	strcpy(exmpl_select_area[0].content, "Please choose your example");
	strcpy(exmpl_select_area[1].content, "E53_SC1");
	strcpy(exmpl_select_area[2].content, "E53_IA1");
	strcpy(exmpl_select_area[3].content, "E53_ST1");
	strcpy(exmpl_select_area[4].content, "E53_SF1");

	comm_select_area[0].start_y = 150;
	comm_select_area[1].start_y = 170;
	comm_select_area[2].start_y = 190;
	comm_select_area[3].start_y = 210;
	strcpy(comm_select_area[0].content, "Choose communicate module");
	strcpy(comm_select_area[1].content, "Wi-Fi");
	strcpy(comm_select_area[2].content, "NB");
	strcpy(comm_select_area[3].content, "2G");

	ui_schedue[0].module_select_area = exmpl_select_area;
	ui_schedue[1].module_select_area = comm_select_area;


}

/**
 * @brief 显示一个模块的信息
 * 
 * @param[in] taget_select_area 存储模块信息的数组
 * @param[in] module_num 该模块数组内所含模块的数量
 */
void UI_DisplayModuleMsg(MODULE_CB_S *taget_select_area, uint8_t module_num)
{
	uint8_t i;

	for(i = 0; i < module_num; i++)
	{
		LCD_ShowString(5, 
						taget_select_area[i].start_y,
						LCD_WIDTH, 
						LCD_HEIGHT, 
						LCD_FRONT_SIZE, 
						taget_select_area[i].content);
	}

}

/**
 * @brief 显示程序选择UI的所有信息
 * 
 */
void UI_DisplayAllMsg(void) 
{
	/* 初始化字符串参数 */
	UI_MsgInit();

	/* 显示按键功能的提示信息 */
	LCD_ShowString(10, 0, LCD_WIDTH, LCD_HEIGHT, LCD_FRONT_SIZE, "Press F1 to select");
	LCD_ShowString(10, 16, LCD_WIDTH, LCD_HEIGHT, LCD_FRONT_SIZE, "Press F2 to confirm");

	/* 显示小熊派案例选择信息 */
	UI_DisplayModuleMsg(ui_schedue[0].module_select_area, ui_schedue[0].module_num + 1);

	/* 显示小熊派通讯模块选择信息 */
	UI_DisplayModuleMsg(ui_schedue[1].module_select_area, ui_schedue[0].module_num + 1);

}

/**
 * @brief 高亮显示用户当前所选模块
 * 
 * @param taget_select_area 用户当前所处的选择模块
 * @param module_num 程序选择结构体
 */
void UI_HighlightChooseItem(MODULE_CB_S *taget_select_area, uint8_t module_num) 
{
	/* 重新显示一遍信息，覆盖掉上次高亮的区域 */
	UI_DisplayModuleMsg(taget_select_area, module_num + 1);

	/* 高亮所选目标 */
	/* 设置高亮字符颜色 */
	POINT_COLOR = LCD_HIHTLIGHT_POINT_COLOR;
	BACK_COLOR = LCD_HIHTLIGHT_BACK_COLOR;

	LCD_ShowString(	5, 
					taget_select_area[current_index].start_y,
					LCD_WIDTH, 
					LCD_HEIGHT, 
					LCD_FRONT_SIZE, 
					taget_select_area[current_index].content);

	/* 还原默认字符颜色 */
	POINT_COLOR = LCD_POINT_COLOR;
	BACK_COLOR = LCD_BACK_COLOR;

}

/**
 * @brief 按键一中断处理函数
 * @details 循环选择模块
 * 
 * @return VOID 
 */
static VOID Key1_IRQHandler(void)
{
	printf("\r\n Key1 IRQ test\r\n");

	/* 选择指向下标自增 */
	current_index++;
	if(current_index > curr_schedue->module_num)
	{
		current_index = 1;
	}

	/* 高亮所选项 */
	UI_HighlightChooseItem(curr_schedue->module_select_area, curr_schedue->module_num);

	/* 清除中断标志位 */
	__HAL_GPIO_EXTI_CLEAR_FLAG(GPIO_PIN_2);

	return;

}

/**
 * @brief 按键二中断处理函数
 * @details 根据用户所选择的模块执行对应的任务
 * 
 * @return VOID 
 */
static VOID Key2_IRQHandler(void)
{
	printf("\r\n Key2 IRQ test\r\n");

	/* 执行被选择模块的调度任务 */
	curr_schedue->schedue_func();

	/* 清除中断标志位 */
	__HAL_GPIO_EXTI_CLEAR_FLAG(GPIO_PIN_3);

	return;

}

/**
 * @brief 创建选择按键中断
 * 
 * @return UINT32 
 */
UINT32 SelectKey_Interrupt(VOID)
{
	UINTPTR uvIntSave;
	uvIntSave = LOS_IntLock();
	
	/* 创建中断 */
	LOS_HwiCreate(KEY1_EXTI_IRQn, 0, 0, Key1_IRQHandler, 0); 
	
	LOS_IntRestore(uvIntSave);
	
	return LOS_OK;
}

/**
 * @brief 创建确认按键中断
 * 
 * @return UINT32 
 */
UINT32 ConfirmKey_Interrupt(VOID)
{
	UINTPTR uvIntSave;
	uvIntSave = LOS_IntLock();
	
	/* 创建中断 */
	LOS_HwiCreate(KEY2_EXTI_IRQn, 0, 0, Key2_IRQHandler, 0);
	
	LOS_IntRestore(uvIntSave);
	
	return LOS_OK;
}  

// UINT32 creat_it_test_task()
// {
// 	UINT32 uwRet = LOS_OK;
// 	UINT32 TskHandle;
// 	TSK_INIT_PARAM_S task_init_param;

// 	task_init_param.usTaskPrio = 0;
// 	task_init_param.pcName = "dynamic_tasks_it_create";
// 	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)dynamic_tasks_it_create;
// 	task_init_param.uwStackSize = 0x800;

// 	uwRet = LOS_TaskCreate(&TskHandle, &task_init_param);
// 	if(LOS_OK != uwRet)
// 	{
// 		return uwRet;
// 	}
// 	return uwRet;
// }


/********************************** END OF FILE *******************************/