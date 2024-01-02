/*
 * display.cpp
 *
 * Created: 24-12-2023 18:33:38
 *  Author: Kot
 */ 

#include "display.h"
#define SEG_A 0
#define SEG_B 1
#define SEG_C 2
#define SEG_D 3
#define SEG_E 4
#define SEG_F 5
#define SEG_G 1
#define SEG_POINT 0

unsigned char SEGMENTS[] =
{
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x6F, // 9
	0x79 // E
};

void InitDisplay(){
	DDRB |= (1<<SEG_A)|(1<<SEG_B)|(1<<SEG_C)|(1<<SEG_D)|(1<<SEG_E)|(1<<SEG_F) ; // Порт B - выход с 0 по 5
	DDRD |= (1<<SEG_POINT)|(1<<SEG_G); //порт D выход 0 и 1
	
	DDRCatod |= (1<<PinCatod_10)|(1<<PinCatod_1); // ноги катодов на выход
	PortCatod = (1<<PinCatod_10)|(1<<PinCatod_1); // высокий уровень на ноги катодов
}

int power (int a,int b){
	int res = 1;
	for(int i = 0; i<b; i++){
		res *=a;
	}
	return res;
}

int convert (unsigned char temper){
	int IntegerTemper = 0;
	for(int i = 0; i <8; i++){
		if(temper & (1 << i)) IntegerTemper += power(2,i);
	}
	return IntegerTemper;
}

void TemperDisplay (unsigned char temper){
	bool HalfTemper = false;
	if(temper & 1<<0) HalfTemper = true;
	temper>>=1;
	int IntegerTemper = convert(temper);
	for(int i = 0;i < 10;i++){
		PORTD |= SEGMENTS[IntegerTemper % 10] << 6;
		PORTB |= SEGMENTS[IntegerTemper % 10] >>1;
		if(HalfTemper)PORTD |= (1 << SEG_POINT);
		PortCatod = 0b01;
		_delay_ms(5);
		PortCatod = 0b11;
		_delay_ms(1);
		PORTD |= SEGMENTS[IntegerTemper / 10] << 6;
		PORTB |= SEGMENTS[IntegerTemper / 10] >>1;
		PortCatod = 0b10;
		_delay_ms(5);
		PortCatod = 0b11;
		_delay_ms(1);
	}
 	PortCatod = 0x00;
}

void SetupDisplay (uint8_t T_setup, uint8_t T_current){
	for(uint8_t i = 0; i < 5; i++){
		_delay_ms(200);
		TemperDisplay(T_setup);
		_delay_ms(200);
		TemperDisplay(T_setup);
		_delay_ms(200);
		TemperDisplay(T_setup);
		for(uint8_t j=0; j<3; j++){
			TemperDisplay(T_current);
		}
	}
}

void ErrorDisplay (int error){
		for(int i = 0;i < 5;i++){
			PORTD |= SEGMENTS[error] << 6;
			PORTB |= SEGMENTS[error] >>1;
			PortCatod = 0b01;
			_delay_ms(5);
			PortCatod = 0b11;
			_delay_ms(1);
			PORTD |= (1<<SEG_G);
			PORTB |= 0x39;
			PortCatod = 0b10;
			_delay_ms(5);
			PortCatod = 0b11;
			_delay_ms(1);
		}
		PortCatod = 0x00;
}