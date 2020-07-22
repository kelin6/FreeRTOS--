/***********************************************************************
�ļ����ƣ�main.C
��    �ܣ������ϵ� 3��LED������˸ 
ʵ��ƽ̨������STM32F107VCT6 ������
��汾  ��ST3.1.2  
***********************************************************************/
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
static void LED1_Task(void* parameter);/* LED1Task���� */
static void LED2_Task(void* parameter);/* LED1Task���� */

 /* ���������� */
static TaskHandle_t LED1Task_Handle = NULL;
static TaskHandle_t LED2Task_Handle = NULL;

void System_Setup(void);
	

int main(void)
{
	 
 BaseType_t xReturn = pdPASS;/* ����һ��������Ϣ��־,Ĭ��pdPASS */  
 SystemInit();	// ����ϵͳʱ��Ϊ72M 	
 LED_GPIO_Config(); //LED �˿ڳ�ʼ�� 

	
	 /* ����LEDTaskCreate���� */
  xReturn = xTaskCreate((TaskFunction_t )LED1_Task,  /* ������ں��� */
                        (const char*    )"LED1_Task",/*�������� */
                        (uint16_t       )512,  /* �����ջ��С */
                        (void*          )NULL,/* ������ں������� */
                        (UBaseType_t    )1, /* �������ȼ� */
                        (TaskHandle_t*  )&LED1Task_Handle);/* ������ƿ�ָ�� */ 
												
	xReturn = xTaskCreate((TaskFunction_t )LED2_Task,  /* ������ں��� */
                        (const char*    )"LED2_Task",/*�������� */
                        (uint16_t       )512,  /* �����ջ��С */
                        (void*          )NULL,/* ������ں������� */
                        (UBaseType_t    )1, /* �������ȼ� */
                        (TaskHandle_t*  )&LED2Task_Handle);/* ������ƿ�ָ�� */ 									
												
  /* ����������� */           
  if(pdPASS == xReturn)
    vTaskStartScheduler();   /* ��������,����������� */
  else
    return -1;  
  
  while(1);   /* ��������ִ�е����� */    
	
  
}



static void LED1_Task(void* parameter)
{	
    while (1)
    {
        LED1_ON;
        vTaskDelay(1000);   /* ��ʱ500 ��tick */
        LED1_OFF;     
        vTaskDelay(1000);  
    }
}


static void LED2_Task(void* parameter)
{	
    while (1)
    {
        LED2_ON;
        vTaskDelay(500);   /* ��ʱ500 ��tick */
        LED2_OFF;     
        vTaskDelay(500);  
    }
}





#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
