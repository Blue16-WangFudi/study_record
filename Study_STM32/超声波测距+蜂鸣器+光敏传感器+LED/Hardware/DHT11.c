#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#include "DHT11.h"

#define DHT11_GPIO GPIOB
#define DHT11_PIN GPIO_Pin_9



 
//初始化为输出
 
void DHT11_GPIO_OUT(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);    //开启挂载GPIO的总线APB2
		
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出，输入也是有效
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);		

}


//初始化为输入
 
 
void DHT11_GPIO_IN(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入，不可以输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);					
}



uint8_t DHT11_ReadByte(void)
{
	uint8_t temp;
	uint8_t ReadDat=0;
	
	uint8_t retry = 0;	
	uint8_t i;
	//二进数除以十即为数据
	
	
	
	for(i=0;i<8;i++)
	{
		//消耗准备信号低电平50us
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==0&&retry<100)
		{
			Delay_us(1);	
			retry++;		
		}
		retry=0;
		
		
		//虽然0信号持续时间为28us，retry循环非常巧妙，
		//避免问题,相当于如果一直是0的话可以避免延时带来的多出时间
		Delay_us(30);//如果是0，那temp=0起作用，非0，仍然在高电平时间内
		
		//因为如果数据是0的话持续时间短，故先预置0，简化代码。
		
		temp=0;//数字信号0，temp=0
		//数字0信号高电平持续28us，数字1信号高电平70us，延时30us以确认数字0或1
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==1) 
		{
			temp=1;
		}			
			//数字1信号高电平剩余40us
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==1&&retry<100)
		{		
			Delay_us(1);
			retry++;
		}
		retry=0;
		//<<=左移赋值符号，|=先或再赋值，得到1位数据，即8bit
		ReadDat<<=1;
		ReadDat|=temp;
	}	
	return ReadDat;


}

void DHT11_ReadData(uint8_t *temp, uint8_t *humi)
{
    uint8_t i,data[5];
		uint8_t retry=0;
    
	
	
	//stm32 PB14设置为输出，发送开始信号低电平18ms，高电平40us
	DHT11_GPIO_OUT();
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);//拉低引脚输出电平
	Delay_ms(18);//保证dht11能收到起始信号
	
	
	
	GPIO_SetBits(GPIOB,GPIO_Pin_9);//拉高引脚输出电平
	Delay_us(40);//延时40us，等待dht11响应信号
	
	
	//stm32 PB14设置为输入，检查并接收响应信号低电平80us，高电平80us
	DHT11_GPIO_IN();//可以不切换，直接输出高电平，输入也是开启的
	Delay_us(20);
	//延时20us，dht11响应低电平80us，还剩60us，检查是否是低电平以确定是否有响应信号

		
		
		
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==0)
	{	//第一个循环消耗响应低电平60us
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==0&&retry<100)//接收响应信号低电平剩余60us
		{
			Delay_us(1);
			retry++;		
		}
		
		
		retry=0;//超过100us自动向下运行，以免卡死
		//消耗dht11拉高80us
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==1&&retry<100)//接收响应信号高电平80us
		{
			Delay_us(1);
			retry++;			
		}
		retry=0;
		
		//接收8字节数据,每传送1bit之前先进行拉低50us
		//接收了5位数据，40bit
		for(i=0;i<5;i++)
		{
			data[i]=DHT11_ReadByte();
		}
		Delay_us(50);//DHT11拉低总线50us作为一字节结束信号，或者使用以下语句
        if ((data[0] + data[1] + data[2] + data[3]) == data[4])
        {
            *humi = data[0];
            *temp = data[2];
        }	
				
		

	}

}

