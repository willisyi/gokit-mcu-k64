/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

///////////////////////////////////////////////////////////////////////////////
//  Includes
///////////////////////////////////////////////////////////////////////////////
// SDK Included Files
#include "board.h"
#include "fsl_lptmr_driver.h"
#include "fsl_debug_console.h"
#include "gokit_hal/hal_key.h"
#include "gokit_hal/hal_rgb_led.h"
#include "gokit_hal/hal_motor.h"


////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
#define TMR_PERIOD    2000U	//LPTMR delay time in us

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
/*!
 * @brief LPTMR interrupt call back function.
 * The function is used to toggle LED1.
 */
extern void lptmr_call_back(void);
/*!
 * @brief Main function
 */
inline void LPTMR_Init()
{
	    // LPTMR configurations
    lptmr_user_config_t lptmrConfig =
    {
        .timerMode = kLptmrTimerModeTimeCounter,
        .freeRunningEnable = false,
        .prescalerEnable = true,
        .prescalerClockSource = kClockLptmrSrcLpoClk,
        .prescalerValue = kLptmrPrescalerDivide2,
        .isInterruptEnabled = true,
    };
    // LPTMR driver state information
    lptmr_state_t lptmrState;
		    // Initialize LPTMR
    LPTMR_DRV_Init(LPTMR0_IDX, &lptmrState, &lptmrConfig);
		int ret;
    // Set timer period for TMR_PERIOD seconds
    ret = LPTMR_DRV_SetTimerPeriodUs(LPTMR0_IDX, TMR_PERIOD);
		PRINTF("LPTMR ret=%d \n",ret);
    // Install interrupt call back function for LPTMR
    LPTMR_DRV_InstallCallback(LPTMR0_IDX, lptmr_call_back);
    // Start LPTMR
    LPTMR_DRV_Start(LPTMR0_IDX);

}
void gokit_hal_init()
{
		KEY_GPIO_Init();
		RGB_LED_Init();
		Motor_Init();
}
int main (void)
{
    // RX buffers
    //! @param receiveBuff Buffer used to hold received data
    uint8_t receiveBuff;
    // Initialize standard SDK demo application pins
    hardware_init();
	
		LPTMR_Init();		
		gokit_hal_init();
    // Initialize LED1
    LED1_EN;

    // Print the initial banner
    PRINTF("\r\nHello World!\n\n\r");

    while(1)
    {
        // Main routine that simply echoes received characters forever

        // First, get character
       // receiveBuff = GETCHAR();
				KEY_Handle();		
        // Now echo the received character
       // PUTCHAR(receiveBuff);
    }
}
