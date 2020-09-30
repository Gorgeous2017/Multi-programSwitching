/**
 * ******************************************************************************
 * @file app_bearpi.h
 * @author Gump
 * @version V0.1
 * @date 2020-09-28
 * @brief 
 * 
 * 
 * ******************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_BEARPI_H__
#define __APP_BEARPI_H__ 

/* Includes ------------------------------------------------------------------*/
#include "los_base.h"
#include "los_task.ph"
#include "los_typedef.h"
#include "los_sys.h"

#include "E53_SC1.h"
#include "E53_IA1.h"
#include "E53_ST1.h"
#include "E53_SF1.h"

/* Exported typedef -----------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported function -----------------------------------------------*/
UINT32 creat_sc1_collection_task();
UINT32 creat_ia1_collection_task();


#endif /* __APP_BEARPI_H__ */ 
/********************************** END OF FILE *******************************/