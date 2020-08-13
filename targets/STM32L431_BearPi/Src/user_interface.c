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
 *     3.1. 模块选择交互
 *         - 成员下标自增以及循环计数
 *         - 刷新先前的选择
 *         - 高亮当前选择
 *     3.2. 模块确认交互
 *         - 重新赋值模块数目
 * 4. 屏蔽按键中断
 *     - 用户应用程序可重新实现中断响应函数
 * 5. 执行用户选择的任务
 *     5.1. 赋值函数指针
 * 
 * ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "user_interface.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
LCD_String_TypeDef exmpl_string[EXMPL_NUM + 1];
LCD_String_TypeDef comm_string[COMM_NUM + 1];
LCD_String_TypeDef *taget_string = exmpl_string;

UI_LoopChoose_TypeDef lp = {
	.current_index = 0,
	.module_num = EXMPL_NUM
};

/* Private function prototypes -----------------------------------------------*/
extern UINT32 creat_collection_task();
extern UINT32 creat_ia1_collection_task();

/* Private functions ---------------------------------------------------------*/


// void UI_DisplayExmpl(uint8_t curr_choice) {
	/* 场景区块和通讯区块仅循环计数的最大数目不同 */
// }

// void UI_DisplayComm(uint8_t curr_choice) {

// }

// static uint8_t UI_FindAimIndex(UI_LoopChoose_TypeDef lc)
// {

// 	uint8_t result;

// 	if(lc.current_choose >= lc.module_num)
// 	{
// 		lc.current_choose -= lc.module_num
// 	}


// 	return result;

// }

// static void Example_Exti0_Init()
// {
//     /*add your IRQ init code here*/

//     return;

// }



/**
 * @brief 初始化各个字符串的参数
 * 
 */
void UI_MsgInit(void) 
{
	exmpl_string[0].start_y = 40;

	exmpl_string[1].start_y = 60;
	exmpl_string[2].start_y = 80;
	exmpl_string[3].start_y = 100;
	exmpl_string[4].start_y = 120;

	exmpl_string[1].creat_task = creat_collection_task;
	exmpl_string[2].creat_task = creat_ia1_collection_task;

	strcpy(exmpl_string[0].content, "Please choose your example");
	strcpy(exmpl_string[1].content, "E53_SC1");
	strcpy(exmpl_string[2].content, "E53_IA1");
	strcpy(exmpl_string[3].content, "E53_ST1");
	strcpy(exmpl_string[4].content, "E53_SF1");

	comm_string[0].start_y = 150;
	strcpy(comm_string[0].content, "Choose communicate module");
	strcpy(comm_string[1].content, "Wi-Fi");
	strcpy(comm_string[2].content, "NB");
	strcpy(comm_string[3].content, "2G");

}

/**
 * @brief 显示一个模块的信息
 * 
 * @param[in] taget_string 存储模块信息的数组
 * @param[in] module_num 该模块数组内所含模块的数量
 */
void UI_DisplayModuleMsg(LCD_String_TypeDef *taget_string, uint8_t module_num)
{
	uint8_t i;

	for(i = 0; i < module_num; i++)
	{
		LCD_ShowString(5, 
						taget_string[0].start_y + i * LCD_HEIGHT/*(LCD_FRONT_SIZE+4)*/,
						LCD_WIDTH, 
						LCD_HEIGHT, 
						LCD_FRONT_SIZE, 
						taget_string[i].content);
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
	UI_DisplayModuleMsg(exmpl_string, EXMPL_NUM + 1);

	/* 显示小熊派通讯模块选择信息 */
	UI_DisplayModuleMsg(comm_string, COMM_NUM + 1);

}

/**
 * @brief 高亮显示用户当前所选模块
 * 
 * @param taget_string 用户当前所处的选择模块
 * @param lp 程序选择结构体
 */
void UI_HighlightChooseItem(LCD_String_TypeDef *taget_string, UI_LoopChoose_TypeDef lp) 
{
	/* 重新显示一遍信息，覆盖掉上次高亮的区域 */
	UI_DisplayModuleMsg(taget_string, lp.module_num + 1);

	/* 高亮所选目标 */
	/* 设置高亮字符颜色 */
	POINT_COLOR = LCD_HIHTLIGHT_POINT_COLOR;
	BACK_COLOR = LCD_HIHTLIGHT_BACK_COLOR;

	LCD_ShowString(	5, 
					taget_string[lp.current_index].start_y,
					LCD_WIDTH, 
					LCD_HEIGHT, 
					LCD_FRONT_SIZE, 
					taget_string[lp.current_index].content);

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
	lp.current_index++;
	if(lp.current_index > lp.module_num)
	{
		lp.current_index = 1;
	}

	/* 高亮所选项 */
	UI_HighlightChooseItem(taget_string, lp);

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

	/* 创建所选模块对应的任务 */
	exmpl_string[lp.current_index].creat_task();

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
	
	LOS_HwiCreate(KEY1_EXTI_IRQn, 0, 0, Key1_IRQHandler, 0); //创建中断
	
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
	
	LOS_HwiCreate(KEY2_EXTI_IRQn, 0, 0, Key2_IRQHandler, 0); //创建中断
	
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