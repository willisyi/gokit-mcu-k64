#include <stdint.h>
#include <stdbool.h>
#include "board.h"
#include "fsl_lptmr_driver.h"


/******************************************************************************
 * Code
 *****************************************************************************/
/* LPTMR IRQ handler that would cover the same name's APIs in startup code */
//extern Pro_Wait_AckTypeDef           	  Wait_AckStruct;
//extern uint32_t                         SystemTimeCount ;
extern uint8_t 													KeyCountTime;
//extern uint32_t ReportTimeCount;
/******************************************************************************/
/*             KEY1 :����  RESET WIFI, KEY2 :�̰�  ����WiFi��                 */
/*             ��ʱ��3�жϷ������                                            */
/******************************************************************************/
void lptmr_call_back()
{
//			SystemTimeCount++;
//			Wait_AckStruct.SendTime ++;
		KeyCountTime++;
		LED1_TOGGLE;
//			ReportTimeCount++;
}
void LPTMR0_IRQHandler(void)
{
    LPTMR_DRV_IRQHandler(0U);
}
