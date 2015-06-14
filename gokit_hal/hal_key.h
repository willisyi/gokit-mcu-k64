#ifndef _HAL_KEY_H
#define _HAL_KEY_H

#include <stdio.h>
#include "fsl_gpio_driver.h"
#include "fsl_lptmr_driver.h"

//#define GPIO_KEY1_PORT   GPIOB
//#define GPIO_KEY1_PIN    GPIO_Pin_10

//#define GPIO_KEY2_PORT   GPIOA
//#define GPIO_KEY2_PIN    GPIO_Pin_8

//#define GPIO_KEY3_PORT   GPIOC
//#define GPIO_KEY3_PIN    GPIO_Pin_13

enum _arduino_pins_pinNames{
  kGokitKey1    = GPIO_MAKE_PIN(GPIOC_IDX, 2U),//k64 arduino
  kGokitKey2    = GPIO_MAKE_PIN(GPIOC_IDX, 3U),//k64 arduino
	kGokitKey3    = GPIO_MAKE_PIN(GPIOC_IDX, 6U) //FRDM K64 onboard sw2
};  


#define PRESS_KEY1   0x01
#define PRESS_KEY2   0x02
#define PRESS_KEY3   0x04

#define NO_KEY       0x00
#define KEY_DOWN     0x10  	
#define KEY_UP    	 0x20   
#define KEY_LIAN     0x40   
#define KEY_LONG     0x80



#define KEY_CLICK_DELAY    10

#define KEY1_Long_Action      0x01         
#define KEY2_Long_Action      0x02

void KEY_GPIO_Init(void);
uint8_t Read_KEY_State(void);
uint8_t Get_Key(void);
void KEY_Handle(void);
void KEY_LongHandle(uint8_t KeyAction);

#endif /*_HAL_KEY_H*/

