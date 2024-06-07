#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	
	//GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//切换内部时钟模式
	TIM_InternalClockConfig(TIM2);
	
	//时钟计时器结构体
	TIM_TimeBaseInitTypeDef TIM_TimBaseInitStructure;
	TIM_TimBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimBaseInitStructure.TIM_Period = 100 - 1;
	TIM_TimBaseInitStructure.TIM_Prescaler = 720- 1;
	TIM_TimBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimBaseInitStructure);
	
	//PWM比较结构体
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	
	TIM_OC3Init(TIM2,&TIM_OCInitStructure);
	TIM_OC4Init(TIM2,&TIM_OCInitStructure);
	
	//计时器使能
	TIM_Cmd(TIM2,ENABLE);
	
}
void PWM_SetCompare3(uint16_t Compare)
{
	
  TIM_SetCompare3(TIM2, Compare);
	
}

void PWM_SetCompare4(uint16_t Compare)
{
	
  TIM_SetCompare4(TIM2, Compare);
	
}
