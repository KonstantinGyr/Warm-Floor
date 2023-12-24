/*
 * display.cpp
 *
 * Created: 24-12-2023 18:33:38
 *  Author: Kot
 */ 

#include "display.h"

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
	DDR_DISPLAY = 0xFF; // Порт B - выход
	PORT_DISPLAY = 0x00;
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
		PORT_DISPLAY = SEGMENTS[IntegerTemper % 10];
		if(HalfTemper)PORT_DISPLAY |= (1 << PointLeg);
		PortCatod = 0b01;
		_delay_ms(5);
		PortCatod = 0b11;
		_delay_ms(1);
		PORT_DISPLAY = SEGMENTS[IntegerTemper / 10];
		PortCatod = 0b10;
		_delay_ms(5);
		PortCatod = 0b11;
		_delay_ms(1);
	}
// 	PORT_DISPLAY = 0x00;
// 	PortCatod = 0x00;
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
			PORT_DISPLAY = SEGMENTS[error];
			PortCatod = 0b01;
			_delay_ms(5);
			PortCatod = 0b11;
			_delay_ms(1);
			PORT_DISPLAY = E;
			PortCatod = 0b10;
			_delay_ms(5);
			PortCatod = 0b11;
			_delay_ms(1);
		}
// 		PORT_DISPLAY = 0x00;
// 		PortCatod = 0x00;
}