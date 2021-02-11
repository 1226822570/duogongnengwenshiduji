//===================================================================================================
/* 函数: 
   描述: 
   注意事项：
   申明：深圳尚视界科技有限公司   （2008-2020 版权所有，盗版必究）
	 公司网站： www.sun-lcm.com
	 淘宝网站： https://shop151604432.taobao.com/index.htm?spm=a1z10.5-c.w5002-14603162597.2.4c2619d6w9oYgh
	 技术支持:QQ:3085638545
	 业务咨询电话：13509671256
	 //  功能描述   : OLED 4接口演示例程
//              说明: 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   接PB13（SCL）
//              D1   接PB15（SDA）
//              RES  接PB11
//              DC   接PB10
//              CS   接P12               
//              ----------------------------------------------------------------
 */ 
//====================================================================================================

//******************************************************************************/
#ifndef __OLED_H
#define __OLED_H			  	 
#include "gd32e23x.h"
#include "stdlib.h"	    	
//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define OLED_MODE 0
#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    

//-----------------测试LED端口定义---------------- 
#define LED_ON ;
#define LED_OFF ;

//-----------------OLED端口定义----------------  					   


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

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//OLED控制用函数
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
	 



