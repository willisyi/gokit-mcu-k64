#include "delay.h"
#include "fsl_debug_console.h"

static uint8_t  fac_us=0;																		//us��ʱ������
static uint32_t fac_ms=0;																		//ms��ʱ������
extern void SysTick_Handler(void);


void SysTick_Handler(void)
{	
	//PRINTF("SysTick_Handler \r\n");
	//TimingDelay_Decrement(); 
	SysTick->VAL =0U; 
}
void Delay_Init(uint8_t SYSCLK)
{
	//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	SysTick->CTRL = ((SysTick->CTRL & ~SysTick_CTRL_CLKSOURCE_Msk)
                                     | 1<< SysTick_CTRL_CLKSOURCE_Pos);
	fac_us=SYSCLK; //Ӳ��1��Ƶ,fac_us�ó���ֵ��Ҫ�������ʱ�Ӻ����õ�  
	fac_ms =fac_us*1000; 	
}	

		    								   
void Delay_us(uint32_t nus)
{		
	Delay_Init(120);
		uint32_t temp;  
		SysTick->LOAD = nus*fac_us;  //��ʱ10us�Ļ�����  10*9=90,װ��load�Ĵ�����  
		SysTick->VAL=0U;//��������0,��Ϊcurrrent�ֶα��ֶ�����ʱ,load���Զ���װ��VAL��  
		//SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk |SysTick_CTRL_CLKSOURCE_Msk;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk;
		do  
		{  
			 temp = SysTick->CTRL;  //ʱ�䵽��֮��,��λ����Ӳ����1,������ѯ���Զ���0  
		}  
		while(temp & 0x01 && !(temp &(1<<16))); //��ѯ  	
		SysTick->CTRL = 0U;  //�رռ�����  
		SysTick->VAL = 0U;   //���val      																//��ռ�����	 
}


void Delay_ms(uint16_t nms)
{	 		  	  
	Delay_Init(120);	
	uint32_t temp;  
		SysTick->LOAD = nms*fac_ms;  //��ʱ10us�Ļ�����  10*9=90,װ��load�Ĵ�����  
		SysTick->VAL=0U;//��������0,��Ϊcurrrent�ֶα��ֶ�����ʱ,load���Զ���װ��VAL��  
		SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk;
		do  
		{  
			 temp = SysTick->CTRL;  //ʱ�䵽��֮��,��λ����Ӳ����1,������ѯ���Զ���0  
		}  
		while(temp & 0x01 && !(temp &(1<<16))); //��ѯ  
	
		SysTick->CTRL =0U;  //�رռ�����  
		SysTick->VAL = 0U;   //���val   	  	    
} 
