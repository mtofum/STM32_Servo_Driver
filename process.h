#ifndef __PROCESS_H
#define __PROCESS_H

#include "servo.h"

#define MAX_SERVO_No 16
#define SERVO 0xbc

#define ERRO_SERVO_No 1
#define ERRO_ANGLE 2

typedef unsigned char ErroNoTypeDef;
class Process
{
private:
Servo servo[16];
  ErroNoTypeDef SERVOcmd();
public:
  Process();
  void exec();
};
#endif