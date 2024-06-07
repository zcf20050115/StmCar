//#include "stm32f10x.h"                  // Device header
//#include "Delay.h"
//uint16_t CountSensor_Count;

//void CountSensor_Init(void)
//{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//打开GPIO时钟	
//	
//	
//	//初始化GPIO口
//	GPIO_InitTypeDef GPIO_InitStructure;//定义结构体
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//设置为上拉输入模式
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;//打开第14脚
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//设置输入速度50MHz
//	GPIO_Init(GPIOB,&GPIO_InitStructure);//初始化
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);///打开AFIO数字选择器时钟
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);//AFIO选择器设置EXIT中断口为14脚，与GPIO_Pin14连接
//	
//	//初始化EXTI外部中断
//	EXTI_InitTypeDef 	EXTI_InitStructure;//定义EXTI结构体
//	EXTI_InitStructure.EXTI_Line = EXTI_Line14;//设置中断线路为14脚
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//启用中断
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//设置中断模式为产生中断（产生中断/产生事件）
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//设置触发模式为下降沿触发（上升沿/下降沿/双边沿）
//	EXTI_Init(&EXTI_InitStructure);//初始化
//	
//	//初始化外部中断优先级
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置外部中断优先级组为2组
//	
//	NVIC_InitTypeDef NVIC_InitStructure;//定义NVIC结构体
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//设置选择通道
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//启用选择
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//设置抢占优先级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//设置响应优先级
//	NVIC_Init(&NVIC_InitStructure);//初始化
//}

//uint16_t CountSensor_Get()
//{
//	return CountSensor_Count;
//}


//void EXTI15_10_IRQHandler(void)
//{
//	
//	if(EXTI_GetITStatus(EXTI_Line14) == SET)
//	{
//		Delay_ms(20);
//		CountSensor_Count++;
//		Delay_ms(20);
//		EXTI_ClearITPendingBit(EXTI_Line14);
//		
//	}
//	
//}
