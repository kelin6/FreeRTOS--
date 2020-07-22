/***********************************************************************
文件名称：main.C
功    能：板子上的 3个LED轮流闪烁 
实验平台：基于STM32F107VCT6 开发板
库版本  ：ST3.1.2  
***********************************************************************/
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
static void LED1_Task(void* parameter);/* LED1Task任务 */
static void LED2_Task(void* parameter);/* LED1Task任务 */

 /* 创建任务句柄 */
static TaskHandle_t LED1Task_Handle = NULL;
static TaskHandle_t LED2Task_Handle = NULL;

void System_Setup(void);
	

int main(void)
{
	 
 BaseType_t xReturn = pdPASS;/* 定义一个创建信息标志,默认pdPASS */  
 SystemInit();	// 配置系统时钟为72M 	
 LED_GPIO_Config(); //LED 端口初始化 

	
	 /* 创建LEDTaskCreate任务 */
  xReturn = xTaskCreate((TaskFunction_t )LED1_Task,  /* 任务入口函数 */
                        (const char*    )"LED1_Task",/*任务名称 */
                        (uint16_t       )512,  /* 任务堆栈大小 */
                        (void*          )NULL,/* 任务入口函数参数 */
                        (UBaseType_t    )1, /* 任务优先级 */
                        (TaskHandle_t*  )&LED1Task_Handle);/* 任务控制块指针 */ 
												
	xReturn = xTaskCreate((TaskFunction_t )LED2_Task,  /* 任务入口函数 */
                        (const char*    )"LED2_Task",/*任务名称 */
                        (uint16_t       )512,  /* 任务堆栈大小 */
                        (void*          )NULL,/* 任务入口函数参数 */
                        (UBaseType_t    )1, /* 任务优先级 */
                        (TaskHandle_t*  )&LED2Task_Handle);/* 任务控制块指针 */ 									
												
  /* 启动任务调度 */           
  if(pdPASS == xReturn)
    vTaskStartScheduler();   /* 开启任务,开启任务调度 */
  else
    return -1;  
  
  while(1);   /* 正常不会执行到这里 */    
	
  
}



static void LED1_Task(void* parameter)
{	
    while (1)
    {
        LED1_ON;
        vTaskDelay(1000);   /* 延时500 个tick */
        LED1_OFF;     
        vTaskDelay(1000);  
    }
}


static void LED2_Task(void* parameter)
{	
    while (1)
    {
        LED2_ON;
        vTaskDelay(500);   /* 延时500 个tick */
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
