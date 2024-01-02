/*
 * main.h
 *
 * Created: 24-12-2023 13:10:14
 *  Author: Kot
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>


#define DDRCatod DDRC
#define PortCatod PORTC
#define PinCatod_1 1
#define PinCatod_10 0
#define E 0x79
#define O 0X3F
#define SENSOR_ERROR 1
#define COOLANT_LOW 2

#endif /* MAIN_H_ */