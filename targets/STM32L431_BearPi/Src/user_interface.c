/**
 * ******************************************************************************
 * @file user_interface.c
 * @author Gump
 * @version V0.1
 * @date 2020-08-06
 * @brief 用户多程序选择交互源文件
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

// }

// void UI_DisplayComm(uint8_t curr_choice) {

// }

// static void Example_Exti0_Init()
// {
//     /*add your IRQ init code here*/

//     return;

// }

static VOID Key1_IRQHandler(void)
{
    printf("\r\n Key1 IRQ test\r\n");

	LCD_ShowString(20, 90, 240, 16, 16, " ChoiceKey_Interrupt ");

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

/********************************** END OF FILE *******************************/