/*
 * ATmega16_RFID_Project_File.c
 *
 * http://www.electronicwings.com
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <string.h>
#include "USART_RS232_H_file.h"	/* add USART library */
#include "LCD16x2_4bit.h"		/* add LDC16x2 library */
#include <util/delay.h>

int main()
{DDRA = 0xff;
	char test[13]= "111111222222";
	char RFID[15];
	USART_Init(9600);			/* initialize USART with 9600 baud rate */
	lcdinit();					/* initialize LCD16x2 display */
	lcd_clear();
	lcd_gotoxy(0,0);			/* Set row and column position at 0,0 */		
	memset(RFID,0,15);
	lcd_print("1 AHSAN RFID:");
	while(1)
	{	
		for (int i=0;i<12;i++)
		{
			RFID[i]=USART_RxChar();
		}
		
		_delay_us(10);
		lcd_gotoxy(0,1);
		//lcd_print("Ahsan");
		lcd_print(RFID);

//		lcd_print(RFID);		/* print 12 digit tag number on LCD */
	}  
return 0;
}