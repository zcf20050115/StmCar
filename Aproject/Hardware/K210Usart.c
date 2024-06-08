#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

uint8_t Cx,Cy,Cz;
     
void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &USART_InitStructure);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART2, ENABLE);
}

void USART2_IRQHandler(void)			 
{
		u8 com_data; 
		u8 i;
		static u8 RxCounter1 = 0;
		static u16 RxBuffer1[6] = {0};
		static u8 RxState = 0;	

		if( USART_GetITStatus(USART2,USART_IT_RXNE) == RESET)  	 
		{
			
				USART_ClearITPendingBit(USART2,USART_IT_RXNE);   
				com_data = USART_ReceiveData(USART2);
				if(RxState==0&&com_data==0x2C)  //0x2c帧头
				{
					
					RxState=1;
					RxBuffer1[RxCounter1++]=com_data;
				}
		
				else if(RxState==1&&com_data==0x12)  //0x12帧头
				{
					RxState=2;
					RxBuffer1[RxCounter1++]=com_data;
				}
		
				else if(RxState==2)
				{
					RxBuffer1[RxCounter1++]=com_data;

					if(RxCounter1==6 && com_data == 0x5B)       
					{
						
						Cx=RxBuffer1[RxCounter1-4];
						Cy=RxBuffer1[RxCounter1-3];
						Cz=RxBuffer1[RxCounter1-2];
						RxCounter1 = 0;
						RxState = 0;	
					}
					else if(RxCounter1 > 6)
					{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<6;i++)
						{
								RxBuffer1[i]=0x00;     
						}
					
					}
				}
				else   
				{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<6;i++)
						{
								RxBuffer1[i]=0x00;      
						}
				}

		}
		
}
