#include "stm32f10x.h"
#include "Delay.h"

#define Echo GPIO_Pin_13		
#define Trig GPIO_Pin_5		

uint64_t time=0;			
uint64_t time_end=0;		

void HC_SR04_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	
	GPIO_InitTypeDef GPIO_InitStructure;					
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		
	GPIO_InitStructure.GPIO_Pin = Trig;						
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_Init(GPIOB,&GPIO_InitStructure);					
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;			
	GPIO_InitStructure.GPIO_Pin = Echo;						
	GPIO_Init(GPIOB,&GPIO_InitStructure);					
	GPIO_WriteBit(GPIOB,GPIO_Pin_5,0);						
	Delay_us(15);											
}

int16_t sonar_mm(void)									
{
	uint32_t Distance,Distance_mm = 0;
	GPIO_WriteBit(GPIOB,Trig,1);						
	Delay_us(15);										
	GPIO_WriteBit(GPIOB,Trig,0);						
	while(GPIO_ReadInputDataBit(GPIOB,Echo)==0);		
	time=0;											
	while(GPIO_ReadInputDataBit(GPIOB,Echo)==1);		
	time_end=time;										
	if(time_end/100<38)									
	{
		Distance=(time_end*346)/2;						
		Distance_mm=Distance/100;						
	}
	return Distance_mm;									
}

float sonar(void)									
{
	uint32_t Distance,Distance_mm = 0;
	float Distance_m=0;
	GPIO_WriteBit(GPIOB,Trig,1);					
	Delay_us(15);
	GPIO_WriteBit(GPIOB,Trig,0);					
	while(GPIO_ReadInputDataBit(GPIOB,Echo)==0);
	time=0;
	while(GPIO_ReadInputDataBit(GPIOB,Echo)==1);
	time_end=time;
	if(time_end/100<38)
	{
		Distance=(time_end*346)/2;
		Distance_mm=Distance/100;
		Distance_m=Distance_mm/1000;
	}
	return Distance_m;
}

void TIM3_IRQHandler(void)			
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)		
	{
		time++;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);			
	}
}
