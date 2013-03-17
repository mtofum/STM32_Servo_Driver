
#include "stm32f10x.h"

class Servo
{
  vu8 currentAngle;  //当前写入舵机的高电平宽度
  vu8 servoNo;      //记录舵机号
  
  void Timer1Init(void);
  void Timer1IOCfg(void);
  void Timer2Init(void);
  void Timer2IOCfg(void);
  void Timer3Init(void);
  void Timer3IOCfg(void);
  void Timer4Init(void);
  void Timer4IOCfg(void);
  
  void Delay(unsigned int i);
  
  
public:
  void operator = (char angle);
  Servo(void);
  Servo(char);
};

