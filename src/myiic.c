#include "myiic.h"
/* 软件模拟IIC引脚初始化
 * IIC_SCL --> PB6
 * IIC_SDA --> PB7 */
void IIC_Init(void)
{

	/* 配置IIC_SCL引脚为推挽输出 */ 
    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_11);
	/* 配置IIC_SDA引脚为推挽输出 */ 
    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_12);

    gpio_bit_set(GPIOA, GPIO_PIN_11);
	gpio_bit_set(GPIOA, GPIO_PIN_12);
} 

/* 描述：启动I2C总线,即发送I2C起始条件. 
 * 参数：  无
 * 返回值：无						*/
void IIC_Start(void)
{
	SDA_OUT();
	IIC_SDA(1);
	IIC_SCL(1);
	delay_1us(4);	
	IIC_SDA(0);
	delay_1us(4); 
	IIC_SCL(0);
}
 
/* 描述：结束I2C总线,即发送I2C结束条件.  
 * 参数：  无
 * 返回值：无						*/
void IIC_Stop(void)
{
	SDA_OUT();
	IIC_SCL(0);
	IIC_SDA(0);  
	delay_1us(4);	
	IIC_SCL(1);
	delay_1us(4);
	IIC_SDA(1);
	delay_1us(4);
}
 
/* 描述：发送应答 ACK 
 * 参数：  无
 * 返回值：无		*/
void IIC_ACK(void)
{
	SDA_OUT();
	IIC_SCL(0);
	delay_1us(2); 
	IIC_SDA(0);
	delay_1us(2);     
	IIC_SCL(1);
	delay_1us(2);                  
	IIC_SCL(0);                     
	delay_1us(1);    
}

/* 描述：发送非应答 NACK 
 * 参数：  无
 * 返回值：无		*/
void IIC_NACK(void)
{
	SDA_OUT();
	IIC_SCL(0);
	delay_1us(2); 
	IIC_SDA(1);
	delay_1us(2);      
	IIC_SCL(1);
	delay_1us(2);                   
	IIC_SCL(0);                     
	delay_1us(1);    
}

/* 描述：等待ACK 
 * 参数：  无
 * 返回值：等待应答返回0，没有等待到应答返回1	*/
uint8_t IIC_wait_ACK(void)
{
    uint8_t t = 200;
    SDA_OUT();
    IIC_SDA(1);		
    delay_1us(1);
    IIC_SCL(0);
    delay_1us(1); 
    SDA_IN();		/* 数据发送完后释放数据线，准备接收应答位 */
    delay_1us(1); 
    while(READ_SDA)	/* 等待IIC应答*/
    {
		t--;
		delay_1us(1); 
		if(t==0)
		{
			IIC_SCL(0);
			return 1;
		}
		delay_1us(1); 
    }
    delay_1us(1);      
    IIC_SCL(1);
    delay_1us(1);
    IIC_SCL(0);             
    delay_1us(1);    
    return 0;	
}

/* 描述：一个字节数据发送函数               
 * 参数：  无
 * 返回值：无		*/
void IIC_SendByte(uint8_t byte)
{
	uint8_t BitCnt;
	SDA_OUT();
	IIC_SCL(0);
	for(BitCnt=0;BitCnt<8;BitCnt++) /* 要传送的数据长度为8位 */
	{
		if(byte&0x80) IIC_SDA(1);	/* 判断发送位 */
		else IIC_SDA(0); 
		byte<<=1;
		delay_1us(2); 
		IIC_SCL(1);
		delay_1us(2);
		IIC_SCL(0);
		delay_1us(2);
	}
}

/* 描述：一个字节数据接收函数               
 * 参数：  无
 * 返回值：接收到的字节数据		*/   
uint8_t IIC_RcvByte(void)
{
	uint8_t retc;
	uint8_t BitCnt;
	retc=0; 
	SDA_IN();			/* 设置数据线为输入方式 */
	delay_1us(1);                    
	for(BitCnt=0;BitCnt<8;BitCnt++)
	{  
		IIC_SCL(0);		/* 设置时钟线为低，准备接收数据位	*/
		delay_1us(2);               
		IIC_SCL(1);		/* 设置时钟线为高使数据线上数据有效  */              
		retc=retc<<1;
		if(READ_SDA) retc |=1;	/* 读数据位,接收的数据位放入retc中 */
		delay_1us(1);
	}
	IIC_SCL(0);    
	return(retc);
}
