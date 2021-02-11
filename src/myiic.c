#include "myiic.h"
/* ���ģ��IIC���ų�ʼ��
 * IIC_SCL --> PB6
 * IIC_SDA --> PB7 */
void IIC_Init(void)
{

	/* ����IIC_SCL����Ϊ������� */ 
    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_11);
	/* ����IIC_SDA����Ϊ������� */ 
    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, GPIO_PIN_12);

    gpio_bit_set(GPIOA, GPIO_PIN_11);
	gpio_bit_set(GPIOA, GPIO_PIN_12);
} 

/* ����������I2C����,������I2C��ʼ����. 
 * ������  ��
 * ����ֵ����						*/
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
 
/* ����������I2C����,������I2C��������.  
 * ������  ��
 * ����ֵ����						*/
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
 
/* ����������Ӧ�� ACK 
 * ������  ��
 * ����ֵ����		*/
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

/* ���������ͷ�Ӧ�� NACK 
 * ������  ��
 * ����ֵ����		*/
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

/* �������ȴ�ACK 
 * ������  ��
 * ����ֵ���ȴ�Ӧ�𷵻�0��û�еȴ���Ӧ�𷵻�1	*/
uint8_t IIC_wait_ACK(void)
{
    uint8_t t = 200;
    SDA_OUT();
    IIC_SDA(1);		
    delay_1us(1);
    IIC_SCL(0);
    delay_1us(1); 
    SDA_IN();		/* ���ݷ�������ͷ������ߣ�׼������Ӧ��λ */
    delay_1us(1); 
    while(READ_SDA)	/* �ȴ�IICӦ��*/
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

/* ������һ���ֽ����ݷ��ͺ���               
 * ������  ��
 * ����ֵ����		*/
void IIC_SendByte(uint8_t byte)
{
	uint8_t BitCnt;
	SDA_OUT();
	IIC_SCL(0);
	for(BitCnt=0;BitCnt<8;BitCnt++) /* Ҫ���͵����ݳ���Ϊ8λ */
	{
		if(byte&0x80) IIC_SDA(1);	/* �жϷ���λ */
		else IIC_SDA(0); 
		byte<<=1;
		delay_1us(2); 
		IIC_SCL(1);
		delay_1us(2);
		IIC_SCL(0);
		delay_1us(2);
	}
}

/* ������һ���ֽ����ݽ��պ���               
 * ������  ��
 * ����ֵ�����յ����ֽ�����		*/   
uint8_t IIC_RcvByte(void)
{
	uint8_t retc;
	uint8_t BitCnt;
	retc=0; 
	SDA_IN();			/* ����������Ϊ���뷽ʽ */
	delay_1us(1);                    
	for(BitCnt=0;BitCnt<8;BitCnt++)
	{  
		IIC_SCL(0);		/* ����ʱ����Ϊ�ͣ�׼����������λ	*/
		delay_1us(2);               
		IIC_SCL(1);		/* ����ʱ����Ϊ��ʹ��������������Ч  */              
		retc=retc<<1;
		if(READ_SDA) retc |=1;	/* ������λ,���յ�����λ����retc�� */
		delay_1us(1);
	}
	IIC_SCL(0);    
	return(retc);
}
