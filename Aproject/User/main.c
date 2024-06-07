#include "stm32f10x.h"  
//#include "LED.h"
#include "OLED.h"
#include "Delay.h"
//#include "KEY.h"
#include "stdint.h"
//#include "CountSensor.h"
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



uint8_t RxDatas;
uint8_t ID;								
int16_t AX, AY, AZ, GX, GY, GZ;


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
	
	  GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
		Delay_ms(100);							
		GPIO_SetBits(GPIOB, GPIO_Pin_12);	
	  Delay_ms(100);
	  GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
		Delay_ms(100);							
		GPIO_SetBits(GPIOB, GPIO_Pin_12);	
	  Delay_ms(2000);
	
		SendByte(0x01);
	  SendByte(ID);  
	
	
		while(1)
	{
		
		int Distance_mm = sonar_mm();			
		int Distance_m = Distance_mm/1000;	
		int Distance_m_p = Distance_mm%1000;	
		OLED_ShowNum(1, 6,Distance_m,numlen(Distance_m));	
		OLED_ShowChar(1, 6+numlen(Distance_m), '.');		
		
		if(Distance_m_p<100)
		{			
			OLED_ShowChar(1, 6+numlen(Distance_m)+1,'0');								
			OLED_ShowNum(1, 6+numlen(Distance_m)+2,Distance_m_p,numlen(Distance_m_p));	
			OLED_ShowChar(1, 6+numlen(Distance_m)+2+numlen(Distance_m_p), 'm');			
		}
		
			else																			
		{
			OLED_ShowNum(1, 6+numlen(Distance_m)+1,Distance_m_p,numlen(Distance_m_p));	
			OLED_ShowChar(1, 6+numlen(Distance_m)+1+numlen(Distance_m_p), 'm');			
		}
		
		
		if(Distance_m_p < 100)
		{
			
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
		Delay_ms(100);							
		GPIO_SetBits(GPIOB, GPIO_Pin_12);		
		Delay_ms(100);				
			
		}
		
		
	  OLED_ShowString(1, 1, "ID");		
	  ID = MPU6050_GetID();				
	  OLED_ShowHexNum(1, 3, ID, 2);	
		
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		OLED_ShowSignedNum(2, 1, AX, 5);					
		OLED_ShowSignedNum(3, 1, AY, 5);
		OLED_ShowSignedNum(4, 1, AZ, 5);
		OLED_ShowSignedNum(2, 8, GX, 5);
		OLED_ShowSignedNum(3, 8, GY, 5);
		OLED_ShowSignedNum(4, 8, GZ, 5);
		
		
		
		if(GetRxFlag() == 1)
		{
			
			RxDatas = GetRxData();
			
			SendByte(RxDatas);
			
			
			if(RxDatas == 0x31)
			{
				
				Motor_ForWard(30);
				OLED_ShowString(1,13,"F");
				GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
		    Delay_ms(100);							
		    GPIO_SetBits(GPIOB, GPIO_Pin_12);	
	      
			}
			
			else if(RxDatas == 0x32)
			{
				
				Motor_BackWard(30);
				OLED_ShowString(1,13,"B");
				GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
		    Delay_ms(100);							
		    GPIO_SetBits(GPIOB, GPIO_Pin_12);	
	      
			}
			
			else if(RxDatas == 0x33)
			{
				
				Motor_Turn_Right(21);
				OLED_ShowString(1,13,"R");
				GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
		    Delay_ms(100);							
	    	GPIO_SetBits(GPIOB, GPIO_Pin_12);	
	      
			}
			
			else if(RxDatas == 0x34)
			{
			
				Motor_Turn_Left(21);
				OLED_ShowString(1,13,"L");
				GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
		    Delay_ms(100);							
		    GPIO_SetBits(GPIOB, GPIO_Pin_12);	
	      
			}
			
			else if(RxDatas == 0x35)
			{
				
				OLED_Clear();
				Motor_Stop(0);
			  OLED_ShowString(1,13,"S");
				GPIO_ResetBits(GPIOB, GPIO_Pin_12);		
		    Delay_ms(100);							
		    GPIO_SetBits(GPIOB, GPIO_Pin_12);	
			}
			
		}
		
	}
	
 }

