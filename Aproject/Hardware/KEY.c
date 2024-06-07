#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void KEY_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
	
uint8_t KEY_GetNum(void)
{
	
	uint8_t KEYNUMBER = 0;
	
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == 0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == 1);
		Delay_ms(20);
		KEYNUMBER = 1;
		
	}
	
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8) == 0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8) == 1);
		Delay_ms(20);
		KEYNUMBER = 2;
		
	}
	
	return KEYNUMBER;
	
}
