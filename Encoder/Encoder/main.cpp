/*
 * Encoder.cpp
 *
 * Created: 22-12-2023 17:58:31
 * Author : Kot
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define OUT_A 2
#define OUT_B 3
#define INCREMENT 0
#define DECREMENT 1


int main(){
	DDRB &= ~((1<<0)|(1<<1));//1 и 2 нога на вход
	PORTB |= (1<<0)|(1<<1);// подтянем питание
	DDRB |= (1<<OUT_A)|(1<<OUT_B);//3 и 4 ноги на выход
	PORTB &= ~((1<<OUT_A)|(1<<OUT_B)); //ивыставим 0 уровень
    
    while (1){
		if (!(PINB & (1<<INCREMENT))){
			while(!(PINB & (1<<INCREMENT)));
			PORTB |= (1<<OUT_A);
			_delay_ms(200);
			PORTB |= (1<<OUT_B);
			_delay_ms(200);
			PORTB &= ~(1<<OUT_A);
			_delay_ms(200);
			PORTB &= ~(1<<OUT_B);
			//_delay_ms(1);
		}
		if (!(PINB & (1<<DECREMENT))){
			while(!(PINB & (1<<DECREMENT)));
			PORTB |= (1<<OUT_B);
			_delay_ms(200);
			PORTB |= (1<<OUT_A);
			_delay_ms(200);
			PORTB &= ~(1<<OUT_B);
			_delay_ms(200);
			PORTB &= ~(1<<OUT_A);
			//_delay_ms(1);
		}
    }
}

