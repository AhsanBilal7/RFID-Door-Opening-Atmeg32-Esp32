/*

	ATmega 16 UART using interrupt
	http://www.electronicwings.com

*/ 

#define F_CPU 8000000UL			/* Define frequency here its 8MHz */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define LCD_Data_Dir DDRB		/* Define LCD data port direction */
#define LCD_Command_Dir DDRA		/* Define LCD command port direction register */
#define LCD_Data_Port PORTB		/* Define LCD data port */
#define LCD_Command_Port PORTA		/* Define LCD data port */
#define RS PA5				/* Define Register Select (data/command reg.)pin */
#define RW PA6			/* Define Read/Write signal pin */
#define EN PA7				/* Define Enable signal pin */
	unsigned char ch;
void LCD_Command(unsigned char cmnd)
{
	LCD_Data_Port= cmnd;
	LCD_Command_Port &= ~(1<<RS);	/* RS=0 command reg. */
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 Write operation */
	LCD_Command_Port |= (1<<EN);	/* Enable pulse */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(3);
}
 

void LCD_Char (unsigned char char_data)	/* LCD data write function */
{
	LCD_Data_Port= char_data;
	LCD_Command_Port |= (1<<RS);	/* RS=1 Data reg. */
	LCD_Command_Port &= ~(1<<RW);	/* RW=0 write operation */
	LCD_Command_Port |= (1<<EN);	/* Enable Pulse */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(1);
}

void LCD_Init (void)			/* LCD Initialize function */
{
	LCD_Command_Dir = 0xFF;		/* Make LCD command port direction as o/p */
	LCD_Data_Dir = 0xFF;		/* Make LCD data port direction as o/p */
	_delay_ms(20);			/* LCD Power ON delay always >15ms */
	
	LCD_Command (0x38);		/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Command (0x0C);		/* Display ON Cursor OFF */
	LCD_Command (0x06);		/* Auto Increment cursor */
	LCD_Command (0x01);		/* Clear display */
	LCD_Command (0x80);		/* Cursor at home position */
}

void LCD_String (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);
	}
}

void LCD_String_xy (char row, char pos, char *str)/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	LCD_String(str);		/* Call LCD string function */
}

void LCD_Clear()
{
	LCD_Command (0x01);		/* clear display */
	LCD_Command (0x80);		/* cursor at home position */
}


int main()
{
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)

	ICR1=4999;  //fPWM=50Hz (Period = 20ms Standard).
	DDRD = 0XFF;
    DDRC = 0X00;
	while(1)
	{
		
	//	OCR1B=425;   //0 degree	    ----------For the checking purpose
		if ((PINC &= 0b00000001))   // check if 0 pin of port C  is high or not
		{
			OCR1A=316;  //90 degree
			PORTD = 0X04;
			LCD_Init();			/* Initialize LCD */
			LCD_String("Authorized");	/* write string on 1st line of LCD*/
			LCD_Command(0xC0);	/* Go to 2nd line*/
		    LCD_String("Welcome Ahsan");	/* Write string on 2nd line*/
			_delay_ms(400);
			 OCR1A=97;   //0 degree
		}
		else if ((PINC &= 0b00000010))
		{
			OCR1A=316;  //90 degree
			PORTD = 0X04;
			LCD_Init();			/* Initialize LCD */
			LCD_String("Authorized");	/* write string on 1st line of LCD*/
			LCD_Command(0xC0);		/* Go to 2nd line*/
			LCD_String("Welcome Fiza");	/* Write string on 2nd line*/
			_delay_ms(400);
			 OCR1A=97;   //0 degree
			}
			else
			{
			PORTD = 0X08;
		    OCR1A=97;   //0 degree
			LCD_Init();			/* Initialize LCD */
			LCD_String("Sorry");	/* write string on 1st line of LCD*/
			LCD_Command(0xC0);		/* Go to 2nd line*/
			LCD_String("Not Authorized");	/* Write string on 2nd line*/
			_delay_ms(400);
			}
		
	};
}