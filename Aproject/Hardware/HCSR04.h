#ifndef __HCSR04_H
#define __HCSR04_H
#include "stdint.h"

void HC_SR04_Init(void);
int16_t sonar_mm(void);
float sonar(void);

#endif
