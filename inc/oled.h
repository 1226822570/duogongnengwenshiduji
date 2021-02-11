//===================================================================================================
/* ����: 
   ����: 
   ע�����
   �������������ӽ�Ƽ����޹�˾   ��2008-2020 ��Ȩ���У�����ؾ���
	 ��˾��վ�� www.sun-lcm.com
	 �Ա���վ�� https://shop151604432.taobao.com/index.htm?spm=a1z10.5-c.w5002-14603162597.2.4c2619d6w9oYgh
	 ����֧��:�QQQ:3085638545
	 ҵ����ѯ�绰��13509671256
	 //  ��������   : OLED 4�ӿ���ʾ����
//              ˵��: 
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   ��PB13��SCL��
//              D1   ��PB15��SDA��
//              RES  ��PB11
//              DC   ��PB10
//              CS   ��P12               
//              ----------------------------------------------------------------
 */ 
//====================================================================================================

//******************************************************************************/
#ifndef __OLED_H
#define __OLED_H			  	 
#include "gd32e23x.h"
#include "stdlib.h"	    	
//OLEDģʽ����
//0:4�ߴ���ģʽ
//1:����8080ģʽ
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    

//-----------------����LED�˿ڶ���---------------- 
#define LED_ON ;
#define LED_OFF ;

//-----------------OLED�˿ڶ���----------------  					   


#define OLED_SCLK_Clr() gpio_bit_reset (GPIOB, GPIO_PIN_3);
#define OLED_SCLK_Set() gpio_bit_set (GPIOB, GPIO_PIN_3);

#define OLED_SDIN_Clr() gpio_bit_reset (GPIOB, GPIO_PIN_4);
#define OLED_SDIN_Set() gpio_bit_set (GPIOB, GPIO_PIN_4);

#define OLED_RST_Clr() gpio_bit_reset (GPIOB, GPIO_PIN_5);
#define OLED_RST_Set() gpio_bit_set (GPIOB, GPIO_PIN_5);

#define OLED_DC_Clr() gpio_bit_reset (GPIOB, GPIO_PIN_6);
#define OLED_DC_Set() gpio_bit_set (GPIOB, GPIO_PIN_6);
 		     
#define OLED_CS_Clr()  gpio_bit_reset (GPIOB, GPIO_PIN_7);
#define OLED_CS_Set()  gpio_bit_set (GPIOB, GPIO_PIN_7);

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����


//OLED�����ú���
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x,uint8_t y,uint8_t t);
void OLED_Fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size);
void OLED_ShowString(uint8_t x,uint8_t y, uint8_t *p);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
#endif  
	 



