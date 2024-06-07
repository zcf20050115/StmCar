#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void Motor_Init(void)
{
	PWM_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}

void Motor_ForWard(int8_t speed)
{
	  GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		
		GPIO_SetBits(GPIOA,GPIO_Pin_6);
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
		
		PWM_SetCompare3(speed);
		PWM_SetCompare4(speed);
	
}
void Motor_BackWard(int8_t speed)
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
	
	  GPIO_ResetBits(GPIOA,GPIO_Pin_6);
		GPIO_SetBits(GPIOA,GPIO_Pin_7);
		
		
		PWM_SetCompare3(speed);
		PWM_SetCompare4(speed);
}
void Motor_Turn_Left(int8_t speed)
{
	  GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	
	  GPIO_SetBits(GPIOA,GPIO_Pin_6);
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
		
		
		PWM_SetCompare3(speed);
		PWM_SetCompare4(speed);
}
void Motor_Turn_Right(int8_t speed)
{
	  GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	
	  GPIO_ResetBits(GPIOA,GPIO_Pin_6);
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
		
		
		PWM_SetCompare3(speed);
		PWM_SetCompare4(speed);
}
void Motor_Stop(int8_t speed)
{
	  GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	
	  GPIO_ResetBits(GPIOA,GPIO_Pin_6);
		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
		
		
		PWM_SetCompare3(speed);
		PWM_SetCompare4(speed);
}
