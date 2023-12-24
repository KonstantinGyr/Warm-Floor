/*
 * ds18b20.h
 *
 * Created: 24-12-2023 13:17:22
 *  Author: Kot
 */ 


#ifndef DS18B20_H_
#define DS18B20_H_

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "main.h"

#define LegTerm 7
#define LegTerm_IN DDRD&=~(1<<7)
#define LegTerm_OUT DDRD|=(1<<7)
#define LegTermLevel_0 PORTD&=~(1<<7)
#define LegTermLevel_1 PORTD|=(1<<7)
#define NOID 0xCC//Пропустить идентификацию
#define T_CONVERT 0x44 //Код измерения температуры
#define READ_DATA 0xBE //Передача байтов ведущему
#define WRITE_MEMORY 0x4E

bool DS18B20_init();
void write_18b20 (unsigned char command_byte);
unsigned char read_18b20();
uint8_t RequestTemper();
void SetupTermometr();

#endif /* DS18B20_H_ */