// LCM8x2
// pin1 Vss:						           (to Gnd)
// pin2 Vcc: to +5V					       (to +5V)
// pin3 Vee : brightness control 	 (to Gnd)
// pin4 RS : 1=Data, 0=Instruction (to GPA0)
// pin5 RW : 1=Read, 0=Write 		   (to GPA1)
// pin6 E  : Chip Enable			     (to GPA2)
// pin7~14 : D0~D7					       (to GPE0~7)
#include <stdio.h>
#include <string.h>
#include "NUC1xx.h"
#include "GPIO.h"
#include "SYS.h"

#define LCD_DATA  GPIOE->DOUT   		      // D0~7 pin = GPE0~7 
#define LCD_RS_HI DrvGPIO_SetBit(E_GPA,0) // RS   pin = GPA0
#define LCD_RS_LO DrvGPIO_ClrBit(E_GPA,0)
#define LCD_RW_HI DrvGPIO_SetBit(E_GPA,1) // RW   pin = GPA1 	  
#define LCD_RW_LO DrvGPIO_ClrBit(E_GPA,1)
#define LCD_E_HI  DrvGPIO_SetBit(E_GPA,2) // E    pin = GPA2 	  
#define LCD_E_LO  DrvGPIO_ClrBit(E_GPA,2)

void init_GPIO(void)
{
  DrvGPIO_Open(E_GPA, 0, E_IO_OUTPUT);
  DrvGPIO_Open(E_GPA, 1, E_IO_OUTPUT);
  DrvGPIO_Open(E_GPA, 2, E_IO_OUTPUT);
  DrvGPIO_ClrBit(E_GPA, 0);
  DrvGPIO_ClrBit(E_GPA, 1);
  DrvGPIO_ClrBit(E_GPA, 2);
}

void  lcdWriteData(unsigned  char wdata)
{
   LCD_DATA=wdata | 0xFF00;
   LCD_RS_HI;
   LCD_RW_LO;
   LCD_E_HI;
   DrvSYS_Delay(1000);
   LCD_E_LO;
}

void  lcdWriteCommand(unsigned  char wdata)
{
   LCD_DATA=wdata;
   LCD_RS_LO;
   LCD_RW_LO;
   LCD_E_HI;
   DrvSYS_Delay(1000);
   LCD_E_LO;
}

void  init_LCM8x2(void)
{
	init_GPIO();
	LCD_DATA=0;
	DrvSYS_Delay(37);// wait time >40ms after Vcc>4.5V
	lcdWriteCommand(0x38);
	DrvSYS_Delay(37);
	lcdWriteCommand(0x38);
	DrvSYS_Delay(37);
	lcdWriteCommand(0x38);
	DrvSYS_Delay(37);
	lcdWriteCommand(0x0C);
	DrvSYS_Delay(37);
	lcdWriteCommand(0x01);
	DrvSYS_Delay(1520);
	lcdWriteCommand(0x06);	   	
	DrvSYS_Delay(37);
}

void  lcdSetAddr(uint8_t x,uint8_t y)
{ 
  if(y==1)  x+=0x40;
  x+=0x80;
	lcdWriteCommand(x);
}

void printC(uint8_t x, uint8_t y, unsigned  char dat)
{
	lcdSetAddr(x,y);
	lcdWriteData(dat);
}

void print_Line(int8_t line, char text[])
{
	int8_t i;
	for (i=0;i<strlen(text);i++) 
		printC(i*8,line*16,text[i]);
}

void printS(int16_t x, int16_t y, char text[])
{
	int8_t i;
	for (i=0;i<strlen(text);i++) 
		printC(x+i*8, y,text[i]);
}
