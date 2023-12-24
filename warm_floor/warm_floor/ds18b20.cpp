/*
 * ds18b20.cpp
 *
 * Created: 24-12-2023 13:17:59
 *  Author: Kot
 */ 


#include "ds18b20.h"


//Инициализация DS18B20
bool DS18B20_init(){
	cli();
	bool OK_Flag = false;
	LegTerm_OUT;
	LegTermLevel_0;
	_delay_us(600);
	LegTermLevel_1;
	_delay_us(50);
	LegTerm_IN;
	if(!(PIND & (1 << LegTerm )))OK_Flag = true; // Ловим импульс присутствия датчика
	_delay_us(240);
	LegTerm_OUT;
	LegTermLevel_1;
	_delay_us(300);
	return OK_Flag;
	sei();
}

unsigned char read_18b20(){
	unsigned char  data = 0;
	cli();
	LegTerm_OUT;
	for(unsigned char i = 0; i < 8; i++){
		LegTermLevel_0;
		data >>= 1;
		_delay_us(3);
		LegTermLevel_1;
		LegTerm_IN;
		_delay_us(12);
		if(PIND & (1 << LegTerm)) data |= 0x80;
		LegTerm_OUT;
		LegTermLevel_1;
		_delay_us(45);
		_delay_us(5);
	}
	return data;
	sei();
}

void write_18b20 (unsigned char command_byte){
	cli();
	for(int i = 0; i<8; i++){
		LegTermLevel_0;
		_delay_us(15);
		if(command_byte & 0x01 ) LegTermLevel_1;
		else LegTermLevel_0;
		_delay_us(45);
		command_byte >>=1;
		LegTermLevel_1;
		_delay_us(2);
	}
	sei();
}

uint8_t RequestTemper(){
	uint8_t temper;
	DS18B20_init();
	write_18b20(NOID);
	write_18b20(T_CONVERT);
	_delay_ms(100);
	DS18B20_init();
	write_18b20(NOID);
	write_18b20(READ_DATA);
	temper = read_18b20()>>3;
	temper |= read_18b20()<<5;
	return temper;
}

void SetupTermometr(){
	DS18B20_init();
	write_18b20(NOID);
	write_18b20(WRITE_MEMORY);
	write_18b20(0x00);//Настройка регистра Th
	write_18b20(0x00);//Настройка регистра Tl
	write_18b20(0x00);//Настройка разрешения (0,5)
}