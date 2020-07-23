# FreeRTOS移植
 用于测试移植学习FreeRTOS10.
 开发环境Keil5.1;STM32F107;
 
1.从官网下载https://www.freertos.org/a00104.html ;对应FreeRTOS版本10.3.1
2.从下载的FreeRTOS上选取源码source/portable/RVDS/ARM_CM3文件中的port.c   (根据芯片类型  选择对应的)
                          source/portable/MemMang文件中的heap1.c   (涉及到内存管理，总共有几种策略 ，选择其中一种就可)
                          source中其他的文件（必要的）
                          从demo文件中找出一个FreeRTOSConfig.h （负责进行FreeRTOS 相关的配置）
3.需要注意的是需要根据硬件实际修改FreeRTOSConfig.h 配置文件 ；例如CPU工作频率；
4.FreeRTOS中三个中断函数与 启动代码中的中断向量名称不一样，需要替换或者 #define  A  B方式替换；也可以修改中断向量表中的名称，总之要保留统一名称
    xPortSysTickHandler();         SysTick_Handler(void)
    vPortSVCHandler();             SVC_Handler(void)
    xPortPendSVHandler();          PendSV_Handler(void)
 这三个是重要的函数，注意****
5.在main（）函数进行编写创建任务
   例如
 static void LED1_Task(void* parameter);/* 声明任务入口函数 */
 /* 创建任务句柄*/
static TaskHandle_t LED1Task_Handle = NULL;
   
   
   //FressRTOS 
	 /* 创建任务 */
  xReturn = xTaskCreate((TaskFunction_t )LED1_Task,  /* 任务入口函数名 */
                        (const char*    )"LED1_Task",/*任务名称 */
                        (uint16_t       )512,  /* 任务堆栈大小 */
                        (void*          )NULL,/* 任务入口函数参数*/
                        (UBaseType_t    )1, /* 任务优先级 */
                        (TaskHandle_t*  )&LED1Task_Handle);/* 任务控制块指针*/ 
												
  /* 启动任务调度 */           
  if(pdPASS == xReturn)
    vTaskStartScheduler();   /* 开启任务，开启任务调度*/
  else
    return -1;  
  
  while(1);   
   
