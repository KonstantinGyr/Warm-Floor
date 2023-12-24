/*
 * display.h
 *
 * Created: 24-12-2023 18:33:07
 *  Author: Kot
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "main.h"
#define PointLeg 7

void InitDisplay();

void TemperDisplay (unsigned char temper);

void SetupDisplay (uint8_t t_setup, uint8_t t_current);

void ErrorDisplay (int error);

int convert (unsigned char temper);

#endif /* DISPLAY_H_ */