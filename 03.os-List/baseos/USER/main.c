#include <stdio.h>
#include <string.h>

#include "bsp.h"
#include "app_cfg.h"
#include "bsp_beep.h"
#include "bsp_led.h"
#include "bsp_uart.h"
#include "keyboard.h"

#include "vos.h"

#if( configSUPPORT_STATIC_ALLOCATION == 1 )
static StackType_t AppTaskRootStk[APP_TASK_ROOT_STK_SIZE];
static StackType_t AppTaskMainStk[APP_TASK_MAIN_STK_SIZE];
static StackType_t AppTaskSecondStk[APP_TASK_SECOND_STK_SIZE];

static StaticTask_t AppTaskRootControl;
static StaticTask_t AppTaskMainControl;
static StaticTask_t AppTaskSecondControl;
#endif

static vosThreadDef_t  vosRootThread;
static vosThreadDef_t  vosMainThread;
//static vosThreadDef_t  vosSecondThread;

List_t TestList;		//�������б�
ListItem_t ListItem1;	//�������б���1
ListItem_t ListItem2;	//�������б���2
ListItem_t ListItem3;	//�������б���3

static void Main_Task(void const *parameter)
{	
    vListInitialise(&TestList);
    vListInitialiseItem(&ListItem1);
    vListInitialiseItem(&ListItem2);
    vListInitialiseItem(&ListItem3);

    ListItem1.xItemValue=40;            //ListItem1�б���ֵΪ40
    ListItem2.xItemValue=60;            //ListItem2�б���ֵΪ60
    ListItem3.xItemValue=50;            //ListItem3�б���ֵΪ50


    printf("/*******************�б���б����ַ*******************/\r\n");
    printf("��Ŀ                              ��ַ                  \r\n");
    printf("TestList                          %#x                   \r\n",(int)&TestList);
    printf("TestList->pxIndex                 %#x                   \r\n",(int)TestList.pxIndex);
    printf("TestList->xListEnd                %#x                   \r\n",(int)(&TestList.xListEnd));
    printf("ListItem1                         %#x                   \r\n",(int)&ListItem1);
    printf("ListItem2                         %#x                   \r\n",(int)&ListItem2);
    printf("ListItem3                         %#x                   \r\n",(int)&ListItem3);
    printf("/************************����**************************/\r\n");
    printf("����KEY_UP������!\r\n\r\n\r\n");
    
    while(Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN)!=KEYSTATE_PRESSED) delay_ms(10);   

    vListInsert(&TestList,&ListItem1);      //�����б���ListItem1
    printf("/******************����б���ListItem1*****************/\r\n");
    printf("��Ŀ                              ��ַ                  \r\n");
    printf("TestList->xListEnd->pxNext        %#x                   \r\n",(int)(TestList.xListEnd.pxNext));
    printf("ListItem1->pxNext                 %#x                   \r\n",(int)(ListItem1.pxNext));
    printf("/*******************ǰ�������ӷָ���********************/\r\n");
    printf("TestList->xListEnd->pxPrevious    %#x                   \r\n",(int)(TestList.xListEnd.pxPrevious));
    printf("ListItem1->pxPrevious             %#x                   \r\n",(int)(ListItem1.pxPrevious));
    printf("/************************����**************************/\r\n");
    printf("����KEY_UP������!\r\n\r\n\r\n");
    
    while(Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN)!=KEYSTATE_PRESSED) delay_ms(10);   

    vListInsert(&TestList,&ListItem2);  //�����б���ListItem2
    printf("/******************����б���ListItem2*****************/\r\n");
    printf("��Ŀ                              ��ַ                  \r\n");
    printf("TestList->xListEnd->pxNext        %#x                   \r\n",(int)(TestList.xListEnd.pxNext));
    printf("ListItem1->pxNext                 %#x                   \r\n",(int)(ListItem1.pxNext));
    printf("ListItem2->pxNext                 %#x                   \r\n",(int)(ListItem2.pxNext));
    printf("/*******************ǰ�������ӷָ���********************/\r\n");
    printf("TestList->xListEnd->pxPrevious    %#x                   \r\n",(int)(TestList.xListEnd.pxPrevious));
    printf("ListItem1->pxPrevious             %#x                   \r\n",(int)(ListItem1.pxPrevious));
    printf("ListItem2->pxPrevious             %#x                   \r\n",(int)(ListItem2.pxPrevious));
    printf("/************************����**************************/\r\n");
    printf("����KEY_UP������!\r\n\r\n\r\n");
    
    while(Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN)!=KEYSTATE_PRESSED) delay_ms(10);   
    
    //���岽�����б�TestList����б���ListItem3����ͨ�����ڴ�ӡ����
    //�б����г�Ա����pxNext��pxPrevious��ֵ��ͨ��������ֵ�۲��б�
    //�����б��е����������
    vListInsert(&TestList,&ListItem3);  //�����б���ListItem3
    printf("/******************����б���ListItem3*****************/\r\n");
    printf("��Ŀ                              ��ַ                  \r\n");
    printf("TestList->xListEnd->pxNext        %#x                   \r\n",(int)(TestList.xListEnd.pxNext));
    printf("ListItem1->pxNext                 %#x                   \r\n",(int)(ListItem1.pxNext));
    printf("ListItem3->pxNext                 %#x                   \r\n",(int)(ListItem3.pxNext));
    printf("ListItem2->pxNext                 %#x                   \r\n",(int)(ListItem2.pxNext));
    printf("/*******************ǰ�������ӷָ���********************/\r\n");
    printf("TestList->xListEnd->pxPrevious    %#x                   \r\n",(int)(TestList.xListEnd.pxPrevious));
    printf("ListItem1->pxPrevious             %#x                   \r\n",(int)(ListItem1.pxPrevious));
    printf("ListItem3->pxPrevious             %#x                   \r\n",(int)(ListItem3.pxPrevious));
    printf("ListItem2->pxPrevious             %#x                   \r\n",(int)(ListItem2.pxPrevious));
    printf("/************************����**************************/\r\n");
    printf("����KEY_UP������!\r\n\r\n\r\n");
    
    while(Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN)!=KEYSTATE_PRESSED) delay_ms(10);   
    
    //��������ɾ��ListItem2����ͨ�����ڴ�ӡ�����б����г�Ա����pxNext��
    //pxPrevious��ֵ��ͨ��������ֵ�۲��б������б��е����������
    uxListRemove(&ListItem2);                       //ɾ��ListItem2
    printf("/******************ɾ���б���ListItem2*****************/\r\n");
    printf("��Ŀ                              ��ַ                  \r\n");
    printf("TestList->xListEnd->pxNext        %#x                   \r\n",(int)(TestList.xListEnd.pxNext));
    printf("ListItem1->pxNext                 %#x                   \r\n",(int)(ListItem1.pxNext));
    printf("ListItem3->pxNext                 %#x                   \r\n",(int)(ListItem3.pxNext));
    printf("/*******************ǰ�������ӷָ���********************/\r\n");
    printf("TestList->xListEnd->pxPrevious    %#x                   \r\n",(int)(TestList.xListEnd.pxPrevious));
    printf("ListItem1->pxPrevious             %#x                   \r\n",(int)(ListItem1.pxPrevious));
    printf("ListItem3->pxPrevious             %#x                   \r\n",(int)(ListItem3.pxPrevious));
    printf("/************************����**************************/\r\n");
    printf("����KEY_UP������!\r\n\r\n\r\n");
    
    while(Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN)!=KEYSTATE_PRESSED) delay_ms(10);   
    
    //���߲���ɾ��ListItem2����ͨ�����ڴ�ӡ�����б����г�Ա����pxNext��
    //pxPrevious��ֵ��ͨ��������ֵ�۲��б������б��е����������
    TestList.pxIndex=TestList.pxIndex->pxNext;          //pxIndex�����һ�����pxIndex�ͻ�ָ��ListItem1��
    vListInsertEnd(&TestList,&ListItem2);               //�б�ĩβ����б���ListItem2
    printf("/***************��ĩβ����б���ListItem2***************/\r\n");
    printf("��Ŀ                              ��ַ                  \r\n");
    printf("TestList->pxIndex                 %#x                   \r\n",(int)TestList.pxIndex);
    printf("TestList->xListEnd->pxNext        %#x                   \r\n",(int)(TestList.xListEnd.pxNext));
    printf("ListItem2->pxNext                 %#x                   \r\n",(int)(ListItem2.pxNext));
    printf("ListItem1->pxNext                 %#x                   \r\n",(int)(ListItem1.pxNext));
    printf("ListItem3->pxNext                 %#x                   \r\n",(int)(ListItem3.pxNext));
    printf("/*******************ǰ�������ӷָ���********************/\r\n");
    printf("TestList->xListEnd->pxPrevious    %#x                   \r\n",(int)(TestList.xListEnd.pxPrevious));
    printf("ListItem2->pxPrevious             %#x                   \r\n",(int)(ListItem2.pxPrevious));
    printf("ListItem1->pxPrevious             %#x                   \r\n",(int)(ListItem1.pxPrevious));
    printf("ListItem3->pxPrevious             %#x                   \r\n",(int)(ListItem3.pxPrevious));
    printf("/************************����**************************/\r\n\r\n\r\n");

    while (1)
    {        
        LED_On(LED_2);     
        delay_xms(1000);
        LED_Off(LED_2);
        delay_xms(1000);        
    }
}

void MainInit(void)
{
    BeepInit();
    UartCmdInit();
    LED_BSP_Init();
    KeyBoardInit();

}

static  void  AppTaskRoot (void const *p_arg)
{
    (void)p_arg;
       
    MainInit();

    /* create Main_Task */
#if( configSUPPORT_STATIC_ALLOCATION == 1 )
    memset(&AppTaskMainControl,0,sizeof(AppTaskMainControl));
    vosMainThread.pTaskTcb = &AppTaskMainControl;
    vosMainThread.pBuffer  = AppTaskMainStk;
#endif

    vosMainThread.name = "Main_Task";
    vosMainThread.pthread = Main_Task;
    vosMainThread.tpriority = APP_TASK_MAIN_PRIO;
    vosMainThread.stacksize = APP_TASK_MAIN_STK_SIZE;
    vosMainThread.handle = VOS_ThreadCreate(&vosMainThread,NULL);

    if (NULL != vosMainThread.handle)
        printf("create Main_Task success!\r\n");
        
#if 0
     /*create Second_Task */
#if( configSUPPORT_STATIC_ALLOCATION == 1 )
    memset(&AppTaskSecondControl,0,sizeof(AppTaskSecondControl));
    vosSecondThread.pTaskTcb = &AppTaskSecondControl;
    vosSecondThread.pBuffer  = AppTaskSecondStk;
#endif
     vosSecondThread.name = "Second_Task";
     vosSecondThread.pthread = Second_Task;
     vosSecondThread.tpriority = APP_TASK_SECOND_PRIO;
     vosSecondThread.stacksize = APP_TASK_SECOND_STK_SIZE;
     vosSecondThread.handle = VOS_ThreadCreate(&vosSecondThread,NULL);
     
     if (NULL != vosSecondThread.handle)
         printf("create Second_Task success!\r\n");
#endif

     VOS_ThreadTerminate(vosRootThread.handle);


}

int main(void)
{
		  
    //NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0); 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    
    BSP_Init(); 
    
#if( configSUPPORT_STATIC_ALLOCATION == 1 )
    memset(&AppTaskRootControl,0,sizeof(AppTaskRootControl));
    vosRootThread.pTaskTcb = &AppTaskRootControl;
    vosRootThread.pBuffer  = AppTaskRootStk;
#endif

    vosRootThread.name = "Root";
    vosRootThread.pthread = AppTaskRoot;
    vosRootThread.tpriority = tskIDLE_PRIORITY+1; // in freeRTOS, task priority is from 0 up to max_prio,prio 0 is the idle task
    vosRootThread.stacksize = APP_TASK_ROOT_STK_SIZE;
    vosRootThread.handle    = VOS_ThreadCreate( &vosRootThread, NULL );

    if (vosRootThread.handle != NULL)
        vTaskStartScheduler();
    

    while(1);
}

