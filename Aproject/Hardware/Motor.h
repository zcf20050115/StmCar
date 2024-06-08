#ifndef __MOTOR_H
#define __MOTOR_H
#include "stdint.h"

void Motor_Init(void);
void Motor_ForWard(int8_t speed);
void Motor_BackWard(int8_t speed);
void Motor_Turn_Left(int8_t speed);
void Motor_Turn_Right(int8_t speed);
void Motor_Stop(int8_t speed);
#endif