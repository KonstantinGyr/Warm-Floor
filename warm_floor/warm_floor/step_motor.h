/*
 * step_motor.h
 *
 * Created: 24-12-2023 13:04:44
 *  Author: Kot
 */ 


#ifndef STEP_MOTOR_H_
#define STEP_MOTOR_H_

#include <util/delay.h>
#include <avr/io.h>

#include "main.h"

#define MOTOR_WIRE_A 2
#define MOTOR_WIRE_B 3
#define MOTOR_WIRE_C 4
#define MOTOR_WIRE_D 5
#define ENDER_OPEN     3
#define ENDER_CLOSE    4

void MotorInitial ();
void StepForward ();
void StepRewers();
void StartPosition ();

#endif /* STEP_MOTOR_H_ */