//#define F_CPU 1000000UL

#include "main.h"
#include "ds18b20.h"
#include "step_motor.h"
#include "display.h"

#define IN_ENCODER_A 5
#define IN_ENCODER_B 6

unsigned char T_setup = 0x48;

//void TemperDisplay(unsigned char t_setpoint);
 
 ISR(INT0_vect){
	 for(int i = 0; i < 100; i++){
		if(!(PIND & (1 << 2))) return; 
		if(PIND & (1 << IN_ENCODER_A)){
			if (PIND & (1 << IN_ENCODER_B)){
				T_setup--;
				i = 0;
			}
			else if(!(PIND & (1 << IN_ENCODER_B))) {
				T_setup++;
				i = 0;
			}
		}
		while(PIND & (1 << IN_ENCODER_A));
		TemperDisplay(T_setup);
	 }
 }

int main(){
	unsigned char T_current ;
	InitDisplay();
	LegTerm_IN;
	LegTermLevel_1;
	while(!DS18B20_init()){
		for(uint8_t i = 0; i < 50; i++){
			ErrorDisplay(SENSOR_ERROR);
		}
		_delay_ms(300);
	}
	MotorInitial();
	StartPosition();
	SetupTermometr();//Настройка разрешения (0,5)
	DDRD &= ~((1<<IN_ENCODER_A)|(1<<IN_ENCODER_B));//вход от Энкодера
	EICRA |=(1 << ISC01);//прерывание по нисходящему фронту на INT0
	EIMSK |=(1 << INT0);
	PORTD |= (1<<2); //подтянем питание к ноге прерывания
	sei();
    while (1) {
	    T_current = RequestTemper();
	    while(convert(T_current) - convert(T_setup) > 2){
		    for(uint8_t i = 0; i < 10; i++){
			    for(uint8_t j = 0; j< 5; j++){
				    StepForward();
			    }
			    while(!(PIND & (1<<ENDER_CLOSE))){
				    ErrorDisplay(2);
			    }
		    }
		    SetupDisplay (T_setup, T_current);
	    }
	    while(convert(T_setup) - convert(T_current) > 2){
		    for(uint8_t i = 0; i < 10; i++){
			    for(uint8_t j = 0; j< 5; j++){
				    StepRewers();
			    }
			    while(!(PIND & (1<<ENDER_OPEN))){
				    ErrorDisplay(COOLANT_LOW);
			    }
		    }
		    SetupDisplay ( T_setup, T_current);
	    }
		for(uint8_t i = 0; i < 100; i++){
			TemperDisplay(T_current);
		}
    }
}

