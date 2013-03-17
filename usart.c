#include "stm32f10x.h"
#include "stm32_eval.h"
#include "usart.h"


#define Buffer_Size    128

u8 Data_Frame[Buffer_Size];
u8 GO_ON_Flag = 0x00;

void USART_Configuration (void);
void GPIO_Configuration(void);
void RCC_Configuration(void);
void NVIC_Configuration(void);

void USART1_Init(void)
{
  RCC_Configuration();
  GPIO_Configuration();
  USART_Configuration ();
  NVIC_Configuration();
}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC , &GPIO_InitStructure);
    
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC , &GPIO_InitStructure);
    
    GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
}

void USART_Configuration (void)
{
  USART_InitTypeDef USART_InitStructure;
  USART_DeInit(USART3);
  USART_InitStructure.USART_BaudRate = 230400;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  
  USART_Init(USART3 , &USART_InitStructure); 
  USART_Cmd(USART3 , ENABLE); 
  USART_ClearITPendingBit(USART3,USART_IT_RXNE);
  USART_ClearITPendingBit(USART3,USART_IT_TXE);
  USART_ITConfig( USART3 ,USART_IT_RXNE, ENABLE); 
}

void RCC_Configuration(void)
{
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1| RCC_APB2Periph_GPIOA , ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
}

void NVIC_Configuration(void)
{
  
    NVIC_InitTypeDef NVIC_InitStructure;
    
#ifdef  VECT_TAB_RAM  
   
    NVIC_SetVectorTable(NVIC_VectTab_RAM , 0x0); 
#else 
    NVIC_SetVectorTable(NVIC_VectTab_FLASH , 0x0);   
#endif
   
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	
    
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
