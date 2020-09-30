/**
 * ******************************************************************************
 * @file app_bearpi.c
 * @author Gump
 * @version V0.1
 * @date 2020-09-28
 * @brief 
 * 
 * 
 * ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "app_bearpi.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern char t_report_buf[];


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

VOID sc1_data_report_collection(VOID)
{
	UINT32 uwRet = LOS_OK;
	
	Init_E53_SC1();									
	while (1)
  {

		E53_SC1_Read_Data();	
		printf("\r\n******************************Lux Value is  %d\r\n",(int)E53_SC1_Data.Lux);
		// LCD_ShowString(10, 200, 200, 16, 16, "Lux Value is:");
		// LCD_ShowNum(140, 200, (int)E53_SC1_Data.Lux, 5, 16);

        LCD_ShowString(70, 100, 200, 16, 16, "Lux Value is:");
	    LCD_ShowNum(180, 100, (int)E53_SC1_Data.Lux, 5, 24);

		sprintf(t_report_buf + 2,"%04X", (int)E53_SC1_Data.Lux);
		uwRet=LOS_TaskDelay(2000);
		if(uwRet !=LOS_OK)
		return;
	
  }
}

VOID ia1_data_report_collection(VOID)
{
	UINT32 uwRet = LOS_OK;
	
	Init_E53_IA1();	
    while (1)
    {
        E53_IA1_Read_Data();
        printf("\r\n******************************BH1750 Value is  %d\r\n", (int)E53_IA1_Data.Lux);
        printf("\r\n******************************Humidity is  %d\r\n",(int)E53_IA1_Data.Humidity);
        printf("\r\n******************************Temperature is  %d\r\n", (int)E53_IA1_Data.Temperature);
        sprintf(t_report_buf + 2, "%02X%02X%04X", (int)E53_IA1_Data.Temperature, (int)E53_IA1_Data.Humidity, (int)E53_IA1_Data.Lux);
        
        LCD_ShowString(70, 100, 200, 16, 16, "Temp Value is:");
	    LCD_ShowNum(180, 100, (int)E53_IA1_Data.Temperature, 5, 24);

        uwRet=LOS_TaskDelay(2000);
        if(uwRet !=LOS_OK)
        return;

    }
}

UINT32 creat_sc1_collection_task()
{
		UINT32 uwRet = LOS_OK;
		TSK_INIT_PARAM_S task_init_param;
		UINT32 TskHandle;
		task_init_param.usTaskPrio = 0;
		task_init_param.pcName = "sc1_data_report_collection";
		task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)sc1_data_report_collection;
		task_init_param.uwStackSize = 0x800;

    uwRet = LOS_TaskCreate(&TskHandle, &task_init_param);
    if(LOS_OK != uwRet)
    {
        return uwRet;
    }
    return uwRet;
}

UINT32 creat_ia1_collection_task()
{
		UINT32 uwRet = LOS_OK;
		TSK_INIT_PARAM_S task_init_param;
		UINT32 TskHandle;
		task_init_param.usTaskPrio = 0;
		task_init_param.pcName = "ia1_data_report_collection";
		task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)ia1_data_report_collection;
		task_init_param.uwStackSize = 0x800;

    uwRet = LOS_TaskCreate(&TskHandle, &task_init_param);
    if(LOS_OK != uwRet)
    {
        return uwRet;
    }
    return uwRet;
}

VOID app_data_report_collection(VOID)
{
	UINT32 uwRet = LOS_OK;
	
	Init_E53_ST1();	
	while (1)
	{
			E53_ST1_Read_Data();
			printf("\r\n******************************Longitude Value is  %.6f\r\n", E53_ST1_Data.Longitude);
			printf("\r\n******************************Latitude is  %.6f\r\n", E53_ST1_Data.Latitude);
			
			uwRet=LOS_TaskDelay(2000);
			if(uwRet !=LOS_OK)
			return;

	}
}


/********************************** END OF FILE *******************************/