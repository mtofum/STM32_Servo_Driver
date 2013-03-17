
#include "servo.h"
#include "stm32f10x.h"

void Servo::Timer1Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  
  TIM_DeInit(TIM1);
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); 
  
  TIM_TimeBaseStructure.TIM_Period = 12000-1;   //计数周期12000*1us=12ms  舵机驱动周期 12ms 1.5ms高电平的时候是0°
  TIM_TimeBaseStructure.TIM_Prescaler = 24-1;  //分频以后 给定时器的输入时钟周期为1us
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;   
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//管脚输出模式：翻转(TIM输出比较触发模式)
  TIM_OCInitStructure.TIM_Pulse = 1500;;   //翻转周期
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM输出比较极性低,TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputState	= TIM_OutputState_Enable;//输出使能
  TIM_OCInitStructure.TIM_OutputNState  = TIM_OutputNState_Disable;
  // TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  // TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);//使能TIMx在CCR1上的预装载寄存器
  
  TIM_OCInitStructure.TIM_Pulse = 1500;; 
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
  
  TIM_OCInitStructure.TIM_Pulse = 1500;; 
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
  
  TIM_OCInitStructure.TIM_Pulse = 1500;; 
  TIM_OC4Init(TIM1, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);
  
  TIM_Cmd(TIM1, ENABLE);
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void Servo::Timer1IOCfg(void) 
{ 
  GPIO_InitTypeDef GPIO_InitStructure; 
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIO A的时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void Servo::Timer2Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  TIM_DeInit(TIM2);
  
  TIM_TimeBaseStructure.TIM_Period = 12000-1;   //计数周期12000*1us=12ms  舵机驱动周期 12ms 1.5ms高电平的时候是0°
  TIM_TimeBaseStructure.TIM_Prescaler = 24-1;  //分频以后 给定时器的输入时钟周期为1us
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;   
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//管脚输出模式：翻转(TIM输出比较触发模式)
  TIM_OCInitStructure.TIM_Pulse = 1500;;   //翻转周期
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM输出比较极性低,TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputState	= TIM_OutputState_Enable;//输出使能
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);//使能TIMx在CCR1上的预装载寄存器
  
  TIM_OCInitStructure.TIM_Pulse = 1500;; 
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
  
  TIM_OCInitStructure.TIM_Pulse = 1500;; 
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
  
  TIM_OCInitStructure.TIM_Pulse = 1500;; 
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
  
  TIM_Cmd(TIM2, ENABLE);
}

void Servo::Timer2IOCfg(void) 
{ 
  GPIO_InitTypeDef GPIO_InitStructure; 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIO A的时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
} 

void Servo::Timer3Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  TIM_DeInit(TIM3);
  
  TIM_TimeBaseStructure.TIM_Period = 12000-1;   //计数周期12000*1us=12ms  舵机驱动周期 12ms 1.5ms高电平的时候是0°
  TIM_TimeBaseStructure.TIM_Prescaler = 24-1;  //分频以后 给定时器的输入时钟周期为1us
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;   
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//管脚输出模式：翻转(TIM输出比较触发模式)
  TIM_OCInitStructure.TIM_Pulse = 1500;   //翻转周期
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM输出比较极性低,TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputState	= TIM_OutputState_Enable;//输出使能
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//使能TIMx在CCR1上的预装载寄存器
  
  TIM_OCInitStructure.TIM_Pulse = 1500; 
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
  
  TIM_OCInitStructure.TIM_Pulse = 1500; 
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
  
  TIM_OCInitStructure.TIM_Pulse = 1500; 
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
  
  TIM_Cmd(TIM3, ENABLE);
}

void Servo::Timer3IOCfg(void) 
{ 
  GPIO_InitTypeDef GPIO_InitStructure; 
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIO A的时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能GPIO A的时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
} 

void Servo::Timer4Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
  TIM_DeInit(TIM4);
  
  TIM_TimeBaseStructure.TIM_Period = 12000-1;   //计数周期12000*1us=12ms  舵机驱动周期 12ms 1.5ms高电平的时候是0°
  TIM_TimeBaseStructure.TIM_Prescaler = 24-1;  //分频以后 给定时器的输入时钟周期为1us
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;   
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//管脚输出模式：翻转(TIM输出比较触发模式)
  TIM_OCInitStructure.TIM_Pulse = 1500;   //翻转周期
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//TIM输出比较极性低,TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OutputState	= TIM_OutputState_Enable;//输出使能
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);//使能TIMx在CCR1上的预装载寄存器
  
  TIM_OCInitStructure.TIM_Pulse = 1500; 
  TIM_OC2Init(TIM4, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
  
  TIM_OCInitStructure.TIM_Pulse = 1500; 
  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
  
  TIM_OCInitStructure.TIM_Pulse = 1500; 
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
  
  TIM_Cmd(TIM4, ENABLE);
}

void Servo::Timer4IOCfg(void) 
{ 
  GPIO_InitTypeDef GPIO_InitStructure; 
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能GPIO A的时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
} 

void Servo::Delay(unsigned int i)
{
  while(i--)
  {
  }
}

Servo::Servo()
{
  Timer1Init();
  Timer1IOCfg();
  
  Timer2Init();
  Timer2IOCfg();
  
  Timer3Init();
  Timer3IOCfg();
  
  Timer4Init();
  Timer4IOCfg();
}

Servo::Servo(char num)
{
  servoNo=num;
  currentAngle=100;
}

void Servo::operator = (char angle)
{
  if(angle>=10 && angle<=190) 
  {
    currentAngle=angle;
    switch (servoNo)//按照舵机号对定时器进行操作
    {
      
    case 0: TIM_SetCompare2(TIM1,(2400-10*(currentAngle-10))); break; //反向安装的舵机
    case 1: TIM_SetCompare3(TIM1,(600+10*(currentAngle-10))); break;  //正向安装的舵机
    case 2: TIM_SetCompare4(TIM1,(600+10*(currentAngle-10))); break;
    case 3: TIM_SetCompare1(TIM4,(2400-10*(currentAngle-10))); break;
    
    case 4: TIM_SetCompare2(TIM4,(600+10*(currentAngle-10))); break;
    case 5: TIM_SetCompare3(TIM4,(2400-10*(currentAngle-10))); break;
    case 6: TIM_SetCompare4(TIM4,(2400-10*(currentAngle-10))); break;
    case 7: TIM_SetCompare1(TIM1,(2400-10*(currentAngle-10))); break;
    
    case 8: TIM_SetCompare4(TIM3,(600+10*(currentAngle-10))); break;
    case 9: TIM_SetCompare3(TIM3,(600+10*(currentAngle-10))); break;
    case 10: TIM_SetCompare2(TIM3,(600+10*(currentAngle-10))); break;
    case 11: TIM_SetCompare1(TIM3,(600+10*(currentAngle-10))); break;
    
    case 12: TIM_SetCompare4(TIM2,(2400-10*(currentAngle-10))); break;
    case 13: TIM_SetCompare3(TIM2,(2400-10*(currentAngle-10))); break;
    case 14: TIM_SetCompare2(TIM2,(600+10*(currentAngle-10))); break;
    case 15: TIM_SetCompare1(TIM2,(2400-10*(currentAngle-10))); break;
    } 
  }
}
