# FreeRTOS移植
用于测试移植学习FreeRTOS<br>
开发环境Keil5.1;STM32F107;<br>
 
1.从官网下载https://www.freertos.org/a00104.html ;对应FreeRTOS版本10.3.1<br>
2.从下载的FreeRTOS上选取源码source/portable/RVDS/ARM_CM3文件中的port.c   (根据芯片类型  选择对应的)<br>
                          source/portable/MemMang文件中的heap1.c   (涉及到内存管理，总共有几种策略 ，选择其中一种就可)<br>
                          source中其他的文件（必要的）<br>
                          从demo文件中找出一个FreeRTOSConfig.h （负责进行FreeRTOS 相关的配置）<br>
3.需要注意的是需要根据硬件实际修改FreeRTOSConfig.h 配置文件 ；例如CPU工作频率；<br>
4.FreeRTOS中三个中断函数与 启动代码中的中断向量名称不一样，需要替换或者 #define  A  B方式替换；也可以修改中断向量表中的名称，总之要保留统一名称<br>
    xPortSysTickHandler();         SysTick_Handler(void)<br>
    vPortSVCHandler();             SVC_Handler(void)<br>
    xPortPendSVHandler();          PendSV_Handler(void)这三个是重要的函数，注意****<br>
5.在main（）函数进行编写创建任务<br>
      例如<br>
  static void LED1_Task(void* parameter);/* 声明任务入口函数 */<br>
  /* 创建任务句柄*/<br>
static TaskHandle_t LED1Task_Handle = NULL;<br>
   
   
   //FressRTOS <br>
	 /* 创建任务 */<br>
  xReturn = xTaskCreate((TaskFunction_t )LED1_Task,  /* 任务入口函数名 */<br>
                        (const char*    )"LED1_Task",/*任务名称 */<br>
                        (uint16_t       )512,  /* 任务堆栈大小 */<br>
                        (void*          )NULL,/* 任务入口函数参数*/<br>
                        (UBaseType_t    )1, /* 任务优先级 */<br>
                        (TaskHandle_t*  )&LED1Task_Handle);/* 任务控制块指针*/ <br>
												
  /* 启动任务调度 */<br>           
  if(pdPASS == xReturn)<br>
    vTaskStartScheduler();   /* 开启任务，开启任务调度*/<br>
  else<br>
    return -1; <br> 
  <br>
  while(1);   <br>
   
