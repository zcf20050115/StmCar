#ifndef _HDL_WS2812B_H
#define _HDL_WS2812B_H

#include "stm32f10x.h"

#define WS2812B_PIN    GPIO_Pin_1
#define WS2812B_PORT   GPIOA
#define WS2812B_HIGH   GPIO_SetBits(WS2812B_PORT,WS2812B_PIN)
#define WS2812B_LOW	   GPIO_ResetBits(WS2812B_PORT,WS2812B_PIN)

#define WS2812B_ARR 90		
#define T0H 30			
#define T1H 60				


#define LED_NUM  100		
#define DATA_SIZE  24 	    

void PWM_WS2812B_Init(uint16_t arr);
void WS2812B_Reset(void);
void PWM_WS2812B_Write_24Bits(uint16_t num,uint32_t GRB_Data);
void PWM_WS2812B_Show(uint16_t num);
void PWM_WS2812B_Red(uint16_t num);
void PWM_WS2812B_Green(uint16_t num);
void PWM_WS2812B_Blue(uint16_t num);

#endif
