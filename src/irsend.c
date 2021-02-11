#include "gd32e23x.h"

void send_ir1(uint32_t cmd){
	
	timer_disable(TIMER2);
	timer_counter_value_config(TIMER2, 0);
	timer_enable(TIMER2);
	delay_1us(9000);
	timer_disable(TIMER2);
	delay_1us(4500);
	
	for(int i=31;i>=0;i--){
		
		if((cmd&(1<<i))!=0){
			timer_counter_value_config(TIMER2, 0);
			timer_enable(TIMER2);
			delay_1us(560);
			timer_disable(TIMER2);
			delay_1us(1690);
			
		}else{
			timer_counter_value_config(TIMER2, 0);
			timer_enable(TIMER2);
			delay_1us(560);
			timer_disable(TIMER2);
			delay_1us(560);
		}
		
	}
	timer_counter_value_config(TIMER2, 0);
	timer_enable(TIMER2);
	delay_1us(560);
	timer_disable(TIMER2);
	delay_1us(1690);
}

//发送红外
void send_ir(){
	send_ir1(0x1fe807f);
}


//生成38KHZ红外载波
void timer_config(void)
{

	gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_7);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_7);
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_7);
	
    timer_oc_parameter_struct timer_ocinitpara;
    timer_parameter_struct timer_initpara;

    /* enable the TIMER clock */
    rcu_periph_clock_enable(RCU_TIMER2);
    /* deinit a TIMER */
    timer_deinit(TIMER2);
    /* initialize TIMER init parameter struct */
    timer_struct_para_init(&timer_initpara);
    /* TIMER2 configuration */
    timer_initpara.prescaler         = 71;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 25;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER2, &timer_initpara);

    /* initialize TIMER channel output parameter struct */
    timer_channel_output_struct_para_init(&timer_ocinitpara);
    /* configure TIMER channel output function */
    timer_ocinitpara.outputstate  = TIMER_CCX_ENABLE;
    timer_ocinitpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocinitpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    timer_ocinitpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocinitpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocinitpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

    timer_channel_output_config(TIMER2, TIMER_CH_1, &timer_ocinitpara);

    /* CH1 configuration in PWM mode0, duty cycle 50% */
    timer_channel_output_pulse_value_config(TIMER2, TIMER_CH_1, 12);
    timer_channel_output_mode_config(TIMER2, TIMER_CH_1, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER2, TIMER_CH_1, TIMER_OC_SHADOW_DISABLE);


    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER2);
     /* TIMER2 counter enable */
    timer_disable(TIMER2);
}