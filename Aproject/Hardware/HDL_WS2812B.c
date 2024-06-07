#include "HDL_WS2812B.h"
#include "Delay.h"	


uint16_t Single_LED_Buffer[DATA_SIZE*LED_NUM];


void PWM_WS2812B_Init(uint16_t arr)
{

	GPIO_InitTypeDef  GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);				
	

	GPIO_InitStructure.GPIO_Pin = WS2812B_PIN;					
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			                         
	GPIO_Init(WS2812B_PORT,&GPIO_InitStructure);			
	

	TIM_TimeBaseStructure.TIM_Prescaler=0;											
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;	
	TIM_TimeBaseStructure.TIM_Period=arr;											
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;			
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);						
	

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 					
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	//TIM_OCInitStructure.TIM_Pulse = 0;													
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 		
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);  										

	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  						
	
	TIM_Cmd(TIM2, DISABLE);  									
	
	TIM_DMACmd(TIM2, TIM_DMA_CC2, ENABLE);		
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(TIM2->CCR2); 	
  	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Single_LED_Buffer;				
 	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;													
 	DMA_InitStructure.DMA_BufferSize = DATA_SIZE; 														
  	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 						
  	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;											
  	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	
  	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;				
  	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;															
  	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;											
  	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; 																
  	DMA_Init(DMA1_Channel7, &DMA_InitStructure);																
    
  	DMA_Cmd(DMA1_Channel7, DISABLE);				
}

void WS2812B_Reset(void)
{
	TIM_Cmd(TIM2, DISABLE);
	WS2812B_LOW;
	Delay_ms(1);	
}

void PWM_WS2812B_Write_24Bits(uint16_t num,uint32_t GRB_Data)
{
  uint8_t i,j;
  for(j = 0; j < num; j++)
  {
  	for(i = 0; i < DATA_SIZE; i++)
	{
	
		Single_LED_Buffer[i] = ((GRB_Data << i) & 0x800000) ? T1H : T0H;
	}
  }
}

void PWM_WS2812B_Show(uint16_t num)
{

  	DMA_SetCurrDataCounter(DMA1_Channel7, num*DATA_SIZE);
  	DMA_Cmd(DMA1_Channel7, ENABLE);
  	TIM_Cmd(TIM2, ENABLE);
  	while(DMA_GetFlagStatus(DMA1_FLAG_TC7) != SET);
  	DMA_Cmd(DMA1_Channel7, DISABLE);
  	DMA_ClearFlag(DMA1_FLAG_TC7);
  	TIM_Cmd(TIM2, DISABLE);
}


void PWM_WS2812B_Red(uint16_t num)
{
	PWM_WS2812B_Write_24Bits(num,0x00ff00);
	PWM_WS2812B_Show(num);
}

void PWM_WS2812B_Green(uint16_t num)
{
	PWM_WS2812B_Write_24Bits(num,0xff0000);
	PWM_WS2812B_Show(num);
}

void PWM_WS2812B_Blue(uint16_t num)
{
	PWM_WS2812B_Write_24Bits(num,0x0000ff);
	PWM_WS2812B_Show(num);
}

