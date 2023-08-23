//cw-1 phase excitation
#include<stdio.h>
#include<avr/io.h>
#include<util/delay.h>

#define F_CPU 16000000UL
void main()
{
	DDRC=0XFF;
	while(1){ 
		// This is for the clockwise movement
// 		PORTC=0x08;//CW- phase excitation //45 Degree
// 		_delay_ms(4000);
// 		PORTC=0x04;//135 Degree
// 		_delay_ms(4000);
// 		PORTC=0x02;//225 Degree
// 		_delay_ms(4000);
// 		PORTC=0x01;//315 Degree
// 	_delay_ms(4000);
			PORTC=0x04;//135 Degree
     		_delay_ms(4000);
			 PORTC=0x09;//0 Degree
			 _delay_ms(4000);
	///////////////////////////////////////////
	
			// This is for the Anticlockwise movement
// PORTC=0x01;//ACW- phase excitation
// _delay_ms(4000);
// PORTC=0x02;
// _delay_ms(4000);
// PORTC=0x04;
// _delay_ms(4000);
// PORTC=0x08;
// _delay_ms(4000);
	
	}
}