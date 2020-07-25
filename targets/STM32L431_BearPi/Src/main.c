/*----------------------------------------------------------------------------
 * Copyright (c) <2016-2018>, <Huawei Technologies Co., Ltd>
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Notice of Export Control Law
 * ===============================================
 * Huawei LiteOS may be subject to applicable export control laws and regulations, which might
 * include those applicable to Huawei LiteOS of U.S. and the country in which you are located.
 * Import, export and usage of Huawei LiteOS in any manner by you shall be in compliance with such
 * applicable export control laws and regulations.
 *---------------------------------------------------------------------------*/
#include "main.h"
#include "sys_init.h"

#include "los_base.h"
#include "los_task.ph"
#include "los_typedef.h"
#include "los_sys.h"

char s_resp_buf[14] = {0};
uint32_t reply_sem;
E53_SC1_Data_TypeDef E53_SC1_Data;

VOID HardWare_Init(VOID)
{
	HAL_Init();
	/* Configure the system clock */
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART1_UART_Init();
	dwt_delay_init(SystemCoreClock);
	LCD_Init();					
	LCD_Clear(WHITE);		   	
	POINT_COLOR = RED;			
	LCD_ShowString(10, 50, 240, 24, 24, "Welcome to IoTCluB!");
	LCD_ShowString(20, 90, 240, 16, 16, "BearPi IoT Develop Board");
	LCD_ShowString(20, 130, 240, 16, 16, "Powerd by Huawei LiteOS!");
	LCD_ShowString(10, 170, 240, 16, 16, "Please wait for system init");
}

void JumpAPP_test(void) {
    
    typedef  void (*iapfun)(void); /* 函数指针实现APP工程寻址与程序跳转 */

	uint32_t JUMP_ADDR = 0x08004000; /* APP程序基地址 */
	uint32_t STACK_ADDR = 0x20000000; /* APP程序栈地址 */
	uint32_t RESET_IRQ_ADDR = JUMP_ADDR + 4; /* 中断向量表地址 */

	iapfun jump2app; /* 声明跳转函数 */

	jump2app = (iapfun)*(volatile uint32_t *)RESET_IRQ_ADDR; /* APP地址赋值 */
	__set_MSP(STACK_ADDR); /* 设置APP的栈顶 */
	__disable_irq(); /* 失能中断 */

    printf("APP Jump above \n");

	jump2app(); /* APP程序跳转 */

}

int main(void)
{
    // UINT32 uwRet = LOS_OK;
    HardWare_Init();

    printf("BootLoader Project test \n");

    HAL_Delay(2000);

    JumpAPP_test();

    printf("APP Jump below \n");

    // uwRet = LOS_KernelInit();
    // if (uwRet != LOS_OK)
    // {
    //     return LOS_NOK;
    // }

    // extern UINT32 create_work_tasks(VOID);
    // uwRet = create_work_tasks();
    // if (uwRet != LOS_OK)
    // {
    //     return LOS_NOK;
    // }

    // (void)LOS_Start();
    return 0;
}