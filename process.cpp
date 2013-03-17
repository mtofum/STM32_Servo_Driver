#include "process.h"
#include "usart.h"
#include "stm32f10x_it.h"

extern u8 Data_Frame[Buffer_Size];
extern u8 GO_ON_Flag;

Process::Process()
{
  for(char i=0;i<16;i++)
    servo[i]=Servo(i);
  for(char i=0;i<16;i++)
    servo[i]=10+10*i;
  USART1_Init();
}

void Process::exec()
{
  ErroNoTypeDef erroNo;
  while(1)
  {
    if(GO_ON_Flag&0x01!=0)
    {
     switch(Data_Frame[4])
      {
      case SERVO :
        erroNo=SERVOcmd();
        break;
      }
      GO_ON_Flag&=~GO_ON_Flag;
    }
  }
}

ErroNoTypeDef Process::SERVOcmd()
{
  if(Data_Frame[5]>MAX_SERVO_No)  //  �궨�������������������������ʱ ���� 1
    return ERRO_SERVO_No;
  if(Data_Frame[6]>190||(Data_Frame[6]<10&&Data_Frame[6]>0))  //����Ƕȴ���190 С��10 ����2 ����Ƕ�Ϊ0��ʾ���ֵ�ǰ�ǶȲ���
    return ERRO_ANGLE;
  servo[Data_Frame[5]]=Data_Frame[6];
  return 0;
}