#include "stm32f10x.h"                  // Device header
#include "Delay.h"
uint16_t CountSensor_Count;

void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//打开GPIO时钟	
	
	
	//初始化GPIO口
	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//设置为上拉输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;//打开第14脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//设置输入速度50MHz
	GPIO_Init(GPIOB,&GPIO_InitStructure);//初始化
	
}