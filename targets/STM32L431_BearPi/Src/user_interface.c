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
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


// void UI_DisplayExmpl(uint8_t curr_choice) {
	/* 场景区块和通讯区块仅循环计数的最大数目不同 */
// }

// void UI_DisplayComm(uint8_t curr_choice) {

// }

// static uint8_t UI_FindAimIndex(UI_LoopChoose_TypeDef lc)
// {

// 	uint8_t result;

// 	if(lc.current_choose >= lc.model_num)
// 	{
// 		lc.current_choose -= lc.model_num
// 	}


// 	return result;

// }

// static void Example_Exti0_Init()
// {
//     /*add your IRQ init code here*/

//     return;

// }

LCD_String_TypeDef exmpl_string[EXMPL_NUM + 1];
LCD_String_TypeDef comm_string[COMM_NUM + 1];

void UI_MsgInit(void) 
{
	strcpy(exmpl_string[0].content, "Please choose your example");
	strcpy(exmpl_string[1].content, "E53_SC1");
	strcpy(exmpl_string[2].content, "E53_IA1");
	strcpy(exmpl_string[3].content, "E53_ST1");
	strcpy(exmpl_string[4].content, "E53_SF1");

	strcpy(comm_string[0].content, "Please choose communicate method");
	strcpy(comm_string[1].content, "Wi-Fi");
	strcpy(comm_string[2].content, "NB");
	strcpy(comm_string[3].content, "2G");

}


LCD_String_TypeDef *taget_string = exmpl_string;

void UI_DisplayModelMsg(LCD_String_TypeDef *taget_string, uint8_t model_num)
{
	uint8_t i;

	for(i = 0; i < model_num; i++)
	{
		LCD_ShowString(5, 40 + i * (LCD_FRONT_SIZE+4), LCD_WIDTH, LCD_HEIGHT, LCD_FRONT_SIZE, taget_string[i].content);

	}


}



void UI_DisplayAllMsg(void) 
{
	UI_MsgInit();

	LCD_ShowString(0, 0, LCD_WIDTH, LCD_HEIGHT, LCD_FRONT_SIZE, "Press F1 to select");
	LCD_ShowString(0, 16, LCD_WIDTH, LCD_HEIGHT, LCD_FRONT_SIZE, "Press F2 to confirm");

	UI_DisplayModelMsg(exmpl_string, EXMPL_NUM + 1);



}

static VOID Key1_IRQHandler(void)
{
	printf("\r\n Key1 IRQ test\r\n");

	LCD_ShowString(20, 90, 240, 16, 16, " ChoiceKey_Interrupt ");

	creat_it_test_task();


	__HAL_GPIO_EXTI_CLEAR_FLAG(GPIO_PIN_2);

	return;

}

UINT32 ChoiceKey_Interrupt(VOID)
{
	UINTPTR uvIntSave;
	uvIntSave = LOS_IntLock();
	
	//Example_Exti0_Init();
	
	LOS_HwiCreate(KEY1_EXTI_IRQn, 0, 0, Key1_IRQHandler, 0); //创建中断
	
	LOS_IntRestore(uvIntSave);
	
	return LOS_OK;
}  

VOID dynamic_tasks_it_create(VOID)
{
	UINT32 uwRet = LOS_OK;
						
	while (1)
	{

		LCD_ShowString(20, 130, 240, 16, 16, " dynamic task!!!!!!!");

	}
}
UINT32 creat_it_test_task()
{
	UINT32 uwRet = LOS_OK;
	UINT32 TskHandle;
	TSK_INIT_PARAM_S task_init_param;

	task_init_param.usTaskPrio = 0;
	task_init_param.pcName = "dynamic_tasks_it_create";
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)dynamic_tasks_it_create;
	task_init_param.uwStackSize = 0x800;

	uwRet = LOS_TaskCreate(&TskHandle, &task_init_param);
	if(LOS_OK != uwRet)
	{
		return uwRet;
	}
	return uwRet;
}


/********************************** END OF FILE *******************************/