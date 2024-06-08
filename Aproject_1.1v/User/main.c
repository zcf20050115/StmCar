#include "stm32f10x.h"  
//#include "LED.h"
#include "OLED.h"
#include "Delay.h"
//#include "KEY.h"
#include "stdint.h"
#include "CountSensor.h"
//#include "Encoder.h"
#include "Timer.h"
#include "Motor.h"
//#include "Servo.h"
//#include "PWM.h"
#include "Bluetooth.h"
#include "MyI2C.h"
#include "MPU6050.h"
//#include "HDL_WS2812B.h"
#include "HCSR04.h"
#include "Beep.h"
#include "Temperature.h"
#include "K210Usart.h"

uint8_t RxDatas;
uint8_t ID;								
int16_t AX, AY, AZ, GX, GY, GZ;
uint8_t Sensor; 



uint64_t numlen(uint64_t num)
{
    uint64_t len = 1;        
    for(; num > 9; ++len)    
        num /= 10;	         
    return len;              
}




int main(void)
{
	  OLED_Init();
	  Motor_Init();
	  Bluetooth_Init();
	  MPU6050_Init();	
	  HC_SR04_Init();
    Timer_Init();
	  BEEP_Init();
	  CountSensor_Init();
	  DS18B20_Init();
	  Serial_Init();
	
	  GPIO_ResetBits(GPIOB, GPIO_Pin_12);	
	  Delay_ms(1000);
    GPIO_SetBits(GPIOB, GPIO_Pin_12);	
	  Delay_ms(2000);
	  GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
		Delay_ms(100);							
		GPIO_SetBits(GPIOB, GPIO_Pin_12);	
	  Delay_ms(100);
	  GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
		Delay_ms(100);							
		GPIO_SetBits(GPIOB, GPIO_Pin_12);	
	  Delay_ms(500);
	
		SendByte(0x01);
		ID = MPU6050_GetID();				
		SendByte(ID);
	
	
		while(1)
	{
		
		OLED_ShowFNum(1, 1, DS18B20_Get_Temp(), 3, 1);	
		OLED_ShowChar(1, 6, 'T');
		
		int Distance_mm = sonar_mm();			
		int Distance_m = Distance_mm/1000;	
		int Distance_m_p = Distance_mm%1000;	
		OLED_ShowNum(1, 9,Distance_m,numlen(Distance_m));	
		OLED_ShowChar(1, 9+numlen(Distance_m), '.');		
		
		if(Distance_m_p<100)
		{		
			OLED_ShowChar(1, 9+numlen(Distance_m)+1,'0');								
			OLED_ShowNum(1, 9+numlen(Distance_m)+2,Distance_m_p,numlen(Distance_m_p));	
			OLED_ShowChar(1, 9+numlen(Distance_m)+2+numlen(Distance_m_p), 'm');			
		}
			else																			
		{
			OLED_ShowNum(1, 9+numlen(Distance_m)+1,Distance_m_p,numlen(Distance_m_p));	
			OLED_ShowChar(1, 9+numlen(Distance_m)+1+numlen(Distance_m_p), 'm');			
		}
		
		if(Distance_m_p < 100)
		{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
		Delay_ms(100);							
		GPIO_SetBits(GPIOB, GPIO_Pin_12);					
		}
		
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		OLED_ShowSignedNum(2, 1, AX, 5);					
		OLED_ShowSignedNum(3, 1, AY, 5);
		OLED_ShowSignedNum(4, 1, AZ, 5);
		OLED_ShowSignedNum(2, 8, GX, 5);
		OLED_ShowSignedNum(3, 8, GY, 5);
		OLED_ShowSignedNum(4, 8, GZ, 5);
		
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
			
		 GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
		 Delay_ms(100);							
		 Motor_Stop(0);
		 OLED_ShowString(1,16,"S");
		 Delay_ms(1000);
		 GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
		 Delay_ms(100);							
		 GPIO_SetBits(GPIOB, GPIO_Pin_12);
		 Motor_BackWard(72);
		 OLED_ShowString(1,16,"B");
		 Delay_ms(2000);
		 Motor_Stop(0);
		 Delay_ms(100);
			
		}
		
	  OLED_ShowNum(2,15,Cx,2);
		OLED_ShowNum(3,15,Cy,2);
		OLED_ShowNum(4,15,Cz,2);
		
		if(GetRxFlag() == 1)
		{
			
			RxDatas = GetRxData();
			SendByte(RxDatas);
			
			
			if(RxDatas == 0x31)
			{
				
				Motor_ForWard(72);
				OLED_ShowString(1,16,"F");
				GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
		    Delay_ms(100);							
		    GPIO_SetBits(GPIOB, GPIO_Pin_12);	
	      
			}
			
			else if(RxDatas == 0x32)
			{
				
				Motor_BackWard(72);
				OLED_ShowString(1,16,"B");
				GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
		    Delay_ms(100);							
		    GPIO_SetBits(GPIOB, GPIO_Pin_12);	
	      
			}
			
			else if(RxDatas == 0x33)
			{
				
				Motor_Turn_Right(36);
				OLED_ShowString(1,16,"R");
				GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
		    Delay_ms(100);							
	    	GPIO_SetBits(GPIOB, GPIO_Pin_12);	
	      
			}
			
			else if(RxDatas == 0x34)
			{
			
				Motor_Turn_Left(36);
				OLED_ShowString(1,16,"L");
				GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
		    Delay_ms(100);							
		    GPIO_SetBits(GPIOB, GPIO_Pin_12);	
	      
			}
			
			else if(RxDatas == 0x35)
			{
				Motor_Stop(0);
			  OLED_ShowString(1,16,"S");
				GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
		    Delay_ms(100);							
		    GPIO_SetBits(GPIOB, GPIO_Pin_12);	
			}
			
		}
		
	}
	
}

