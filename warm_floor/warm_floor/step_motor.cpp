/*
 * step_motor.cpp
 *
 * Created: 24-12-2023 14:35:22
 *  Author: Kot
 */
#include "step_motor.h"

//ноги для мотора на выход
void MotorInitial (){
	DDRC |= (1<<MOTOR_WIRE_A)|(1<<MOTOR_WIRE_B)|(1<<MOTOR_WIRE_C)|(1<<MOTOR_WIRE_D); 
}

void StepForward (){
	PORTC = 0b101000;
	_delay_ms(1);
	PORTC = 0b011000;
	_delay_ms(1);
	PORTC = 0b010100;
	_delay_ms(1);
	PORTC = 0b100100;
	_delay_ms(1);
}	

void StepRewers(){
	PORTC |= 0b101000;
	_delay_ms(1);
	PORTC |= 0b100100;
	_delay_ms(1);
	PORTC |= 0b010100;
	_delay_ms(1);
	PORTC |= 0b011000;
	_delay_ms(1);
}

void StartPosition (){
	DDRD &= ~((1<<ENDER_OPEN)|(1<<ENDER_CLOSE));//нога концевика на вход
	PORTD |= (1<<ENDER_OPEN)|(1<<ENDER_CLOSE);//подтянем "+"
	while(PIND & (1<<ENDER_CLOSE)){
		StepForward();	
	}
	PORTC = 0x00;
}