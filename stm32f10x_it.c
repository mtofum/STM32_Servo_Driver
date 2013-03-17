/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.3.0
  * @date    04/16/2010
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"

extern u8 Data_Frame[Buffer_Size];
extern u8 GO_ON_Flag ;
u8 Data_Len;

u8 dwPolynomial = 0xb7;
u8 cal_crc (u8 *ptr, int len)
{
	u8 xbit;
	u8 data;
	u8 crc = 0xff;
	u8 bits ;
	while(len --)
	{
		xbit = 1 << 7;
		data = *(ptr ++);
		for (bits = 0; bits < 8; bits ++)
		{
			if(crc & 0x80)
			{
				crc <<= 1;
				crc ^= dwPolynomial;
			}
			else 
			{
				crc <<= 1;
			}

			if (data & xbit)
				crc ^= dwPolynomial;

			xbit >>= 1;
		}
	}

	return crc;
}

static u8 i = 0;
u8 crc = 0xff;
void USART3_IRQHandler (void) 
{
   if(USART_GetITStatus(USART3 , USART_IT_RXNE) == SET)
   {
     Data_Frame[i] = USART_ReceiveData(USART3);  
      if(i == 0)
       {
         if( Data_Frame[i] != 0xfe)
         {
           i = 0;
           return;
         }
       }
       
       if(i == 1)
       {
         if( Data_Frame[i] != 0x55)
         {
           i = 0;
           return;
         }
       }
       
       if(i == 2)
       {
         if( Data_Frame[i] != 0xaa)
         {
           i = 0;
           return;
         }
       }
      
      if(i == 3)
      {
        Data_Len =  Data_Frame[i];
      }
       if (i == Data_Len + 5)
       {
         
         crc = cal_crc (Data_Frame, i + 1);
         i = 0;
         if (crc == 0)
         {
           crc = 0xff;
           USART_SendData(USART3 , 0x66);//USART_SendData(USART1 , 0x66);
           while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);//while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
           GO_ON_Flag |= 0x01;
         }
         return;
       }
       
        i ++;
 
     USART_ClearITPendingBit(USART3,USART_IT_RXNE);//USART_ClearITPendingBit(USART1,USART_IT_RXNE);
   }
}

void DMA1_Channel6_IRQHandler(void)
{   

}


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}


/**
  * @brief  This function handles TIM5 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM4_IRQHandler(void)
{
  /* www.armjishu.com ARMºº ı¬€Ã≥ */
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
