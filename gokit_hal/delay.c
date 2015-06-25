#include "delay.h"
#include "fsl_debug_console.h"

static uint8_t  fac_us=0;																		//us��ʱ������
static uint32_t fac_ms=0;																		//ms��ʱ������

void Delay_Init(uint8_t SYSCLK)
{
	//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	SysTick->CTRL = ((SysTick->CTRL & ~SysTick_CTRL_CLKSOURCE_Msk)
                                     | 1<< SysTick_CTRL_CLKSOURCE_Pos);
	fac_us=SYSCLK; //Ӳ��1��Ƶ,fac_us�ó���ֵ��Ҫ�������ʱ�Ӻ����õ�  
	fac_ms =fac_us*1000; 	
}	

		    								   
int Delay_us(uint32_t nus)
{		
		uint32_t temp;  
		temp = nus*fac_us;  //��ʱ10us�Ļ�����  10*120=120,װ��load�Ĵ����� 
		if(temp > 0xFFFFFF)	//SysTick��24λ�ļ�����������Ƿ�Խ�硣max us 139810us
			return -1;
		SysTick->LOAD = temp;
		SysTick->VAL=0U;//��������0,��Ϊcurrrent�ֶα��ֶ�����ʱ,load���Զ���װ��VAL��  
		SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk |SysTick_CTRL_CLKSOURCE_Msk;
		//SysTick->CTRL = 0x5U;
 
		while(!(SysTick->CTRL &(1<<16))); //��ѯ  	
		SysTick->CTRL = 0x4U;  //�رռ�����  
		SysTick->VAL = 0U;   //���val      																//��ռ�����	 
		return 0;
}


void Delay_ms(uint16_t nms)		//max delay ms = 139
{	 		  	  
		SysTick->LOAD =nms*fac_ms;
		SysTick->VAL=0U;//��������0,��Ϊcurrrent�ֶα��ֶ�����ʱ,load���Զ���װ��VAL��  
		SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk |SysTick_CTRL_CLKSOURCE_Msk;
	
		while(!(SysTick->CTRL &(1<<16))); //��ѯ  	
		SysTick->CTRL = 0x4U;  //�رռ�����  
		SysTick->VAL = 0U;   //���val      																//��ռ�����	 
} 
