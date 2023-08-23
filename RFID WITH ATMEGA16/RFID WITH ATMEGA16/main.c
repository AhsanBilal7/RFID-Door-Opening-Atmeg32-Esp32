/*
 * main.c
 * 
 * 
 *
 */
 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "lcd.c"
#include "utils.h"


#include "mfrc522.h"
#include "spi.h"
#include "mfrc522.c"
#include "spi.c"

uint8_t SelfTestBuffer[64];

int main()
{
	uint8_t byte;
	uint8_t str[MAX_LEN];
	_delay_ms(50);
	LCDInit(LS_BLINK);
	LCDWriteStringXY(2,0,"Hello RFID");
	LCDWriteStringXY(5,1,VERSION_STR);
	
	
	spi_init();
	_delay_ms(1500);
	LCDClear();
	_delay_ms(1500);
	LCDWriteStringXY(2,0,"SPI Init done");
	_delay_ms(1500);
	LCDClear();
	_delay_ms(1500);
	//init reader
	mfrc522_init();
	byte = 0x55;       //just to check that byte is getting loaded and printed
	LCDHexDumpXY(0,0,byte);
	_delay_ms(1500);
	//check version of the reader
	byte = mfrc522_read(VersionReg);
	LCDHexDumpXY(0,0,byte);
	_delay_ms(1500);
	if(byte == 0x92)
	{
		LCDWriteStringXY(2,0,"MIFARE RC522v2");
		LCDWriteStringXY(4,1,"Detected");
	}else if(byte == 0x91 || byte==0x90)
	{
		LCDWriteStringXY(2,0,"MIFARE RC522v1");
		LCDWriteStringXY(4,1,"Detected");
	}else
	{
		LCDWriteStringXY(0,0,"No reader found");
	}
	
	byte = mfrc522_read(ComIEnReg);
	mfrc522_write(ComIEnReg,byte|0x20);
	byte = mfrc522_read(DivIEnReg);
	mfrc522_write(DivIEnReg,byte|0x80);

	_delay_ms(1500);
	LCDClear();
	
	while(1){
		byte = mfrc522_request(PICC_REQALL,str);
		LCDHexDumpXY(0,0,byte);
		_delay_ms(1000);
	}
}