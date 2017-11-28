//
// Smpl_LCD_DrawBmp : Draw different size of bitmap
//
// bmp2asm to convert into byte array
#include <stdio.h>	
#include <string.h>																										 
#include "NUC1xx.h"
#include "SYS.h"
#include "LCD.h"
#include "Scankey.h"

//bitmap 8x8
//Byte0......7
//    00011000 bit0 (LSB)
//    00100100
//    01000010
//    11111111
//    00011000
//    00011000
//    00011000
//    00000000 bit7 (MSB)
unsigned char bmp8x8[8] = {
	0x08,0x0C,0x0A,0x79,0x79,0x0A,0x0C,0x08};

//bitmap 16x8
//Byte0...............15
//    00000011,11000000, bit0 (LSB)
//    00001111,11110000,
//    00011111,11111000,
//    00110101,10101100,
//    01111111,01111110,
//    00111001,10011100,
//    00010000,00001000,
//    00000000,00000000, bit7 (MSB)
unsigned char bmp16x8[16] = {
	0x00,0x10,0x38,0x7C,0x36,0x1E,0x17,0x3F,0x3F,0x17,0x1E,0x36,0x7C,0x38,0x10,0x00};

unsigned char bmp16x16[32] = {
	0x00,0x00,0x40,0xE0,0xE0,0xE0,0xE0,0x70,0x7C,0xFE,0xF8,0x80,0x80,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x03,0x7F,0x3E,0x1E,0x07,0x07,0x07,0x03,0x03,0x02,0x00
};

unsigned char bmp16x32[64] = {
	0x00,0x00,0x40,0xE0,0xE0,0xE0,0xE0,0x70,0x7C,0xFE,0xF8,0x80,0x80,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x03,0x7F,0x3E,0x1E,0x07,0x07,0x07,0x03,0x03,0x02,0x00,
	0x00,0x00,0x40,0xE0,0xE0,0xE0,0xE0,0x70,0x7C,0xFE,0xF8,0x80,0x80,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x03,0x7F,0x3E,0x1E,0x07,0x07,0x07,0x03,0x03,0x02,0x00
};

unsigned char bmp16x48[96] = {
	0x00,0x00,0x40,0xE0,0xE0,0xE0,0xE0,0x70,0x7C,0xFE,0xF8,0x80,0x80,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x03,0x7F,0x3E,0x1E,0x07,0x07,0x07,0x03,0x03,0x02,0x00,
	0x00,0x00,0x40,0xE0,0xE0,0xE0,0xE0,0x70,0x7C,0xFE,0xF8,0x80,0x80,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x03,0x7F,0x3E,0x1E,0x07,0x07,0x07,0x03,0x03,0x02,0x00,
	0x00,0x00,0x40,0xE0,0xE0,0xE0,0xE0,0x70,0x7C,0xFE,0xF8,0x80,0x80,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x03,0x7F,0x3E,0x1E,0x07,0x07,0x07,0x03,0x03,0x02,0x00
};

unsigned char bmp16x64[128] = {
	0x00,0x00,0x40,0xE0,0xE0,0xE0,0xE0,0x70,0x7C,0xFE,0xF8,0x80,0x80,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x03,0x7F,0x3E,0x1E,0x07,0x07,0x07,0x03,0x03,0x02,0x00,
	0x00,0x00,0x40,0xE0,0xE0,0xE0,0xE0,0x70,0x7C,0xFE,0xF8,0x80,0x80,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x03,0x7F,0x3E,0x1E,0x07,0x07,0x07,0x03,0x03,0x02,0x00,
	0x00,0x00,0x40,0xE0,0xE0,0xE0,0xE0,0x70,0x7C,0xFE,0xF8,0x80,0x80,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x03,0x7F,0x3E,0x1E,0x07,0x07,0x07,0x03,0x03,0x02,0x00,
	0x00,0x00,0x40,0xE0,0xE0,0xE0,0xE0,0x70,0x7C,0xFE,0xF8,0x80,0x80,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x03,0x7F,0x3E,0x1E,0x07,0x07,0x07,0x03,0x03,0x02,0x00
};

unsigned char bmp32x16[64] = {
	0x00,0x00,0x40,0xE0,0xE0,0xE0,0xE0,0x70,0x7C,0xFE,0xF8,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x40,0xE0,0xE0,0xE0,0xE0,0x70,0x7C,0xFE,0xF8,0x80,0x80,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x03,0x7F,0x3E,0x1E,0x07,0x07,0x07,0x03,0x03,0x02,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x7F,0x3E,0x1E,0x07,0x07,0x07,0x03,0x03,0x02,0x00
};

unsigned char bmp32x32[128] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0xF0,0xF8,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x10,0x10,0x70,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0x3E,0x1F,0x1F,0x1F,0x3F,0x7F,0xFF,0xE0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x07,0xFF,0xFF,0xFC,0xF8,0xF8,0xF8,0x3C,0x1E,0x1F,0x1F,0x1F,0x0F,0x0F,0x0F,0x0E,0x0E,0x0C,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x1F,0x0F,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

unsigned char bmp32x48[192] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0xF0,0xF8,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x10,0x10,0x70,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0x3E,0x1F,0x1F,0x1F,0x3F,0x7F,0xFF,0xE0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x07,0x0F,0x1F,0x3C,0xF8,0xF8,0xF8,0xFC,0x7E,0x3F,0x1F,0x0F,0x07,0x07,0x03,0x02,0x02,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x40,0x40,0xC0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xF8,0x7C,0x7F,0x7F,0xFC,0xF8,0xF0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x07,0x0F,0x1F,0xFF,0xFF,0xF0,0xE0,0xE0,0xE0,0xF0,0x79,0x7F,0x7F,0x7F,0x3F,0x3E,0x3C,0x38,0x38,0x30,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x7F,0x3F,0x0F,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

unsigned char bmp32x64[256] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0xF0,0xF8,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x10,0x10,0x70,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0x3E,0x1F,0x1F,0x1F,0x3F,0x7F,0xFF,0xE0,0xC0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x07,0xFF,0xFF,0xFC,0xF8,0xF8,0xF8,0x3C,0x1E,0x1F,0x1F,0x1F,0x0F,0x0F,0x0F,0x0E,0x0E,0x0C,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x1F,0x0F,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xF0,0xF8,0xFC,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x08,0x08,0x38,0x7C,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0x1F,0x0F,0x0F,0x0F,0x1F,0x3F,0xFF,0xF0,0xE0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0xFF,0xFF,0xFE,0xFC,0xFC,0x7C,0x1E,0x0F,0x0F,0x0F,0x0F,0x07,0x07,0x07,0x07,0x07,0x06,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x0F,0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

unsigned char bmp64x64[512] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xE0,0xF8,0xFC,0xFE,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xC0,0xC0,0xE0,0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x03,0x03,0x17,0x3F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xDF,0xDF,0x1F,0x07,0x03,0x03,0x01,0x01,0x01,0x01,0x03,0x03,0x07,0x0F,0x3F,0xFF,0xFF,0xFC,0xF8,0xF0,0xF0,0xE0,0xC0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x07,0x0F,0x0F,0x1F,0xFF,0xFF,0xFF,0xF8,0xF0,0xE0,0xC0,0x80,0xC0,0xC0,0xC0,0xC0,0xE0,0xE0,0xF8,0xFC,0xFD,0xFF,0xFB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,0xFC,0x78,0x70,0x60,0x40,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x1F,0x0F,0x03,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0x7F,0x3F,0x0F,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

unsigned char blank[32]={
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

int32_t main (void)
{
	char TEXT[16];
	int i;
	int8_t x,y;
	int8_t keyin=0;

	UNLOCKREG();
  DrvSYS_Open(50000000);
	LOCKREG();

	init_LCD();  
	clear_LCD();
	OpenKeyPad();

	print_Line(0,"LCD_BmpDraw");
	print_Line(1,"press Keypad 1~9");
	print_Line(2,"to Draw Bitmap !");
	
	while(keyin==0) keyin=ScanKey(); // wait till key is pressed
	clear_LCD();                     // clear LCD
	
	//draw_Bmp8x8(0,0,FG_COLOR, BG_COLOR, bmp8x8);
	//draw_Bmp16x8(0,0,FG_COLOR, BG_COLOR, bmp8x8);
	
	while(1) {
  keyin=ScanKey(); // Scan 3x3 keypad 
  switch(keyin){   // input 1~9 to select bitmap to draw
		case 1:	draw_Bmp16x16(0,0,FG_COLOR,BG_COLOR,bmp16x16); break;
		case 2: draw_Bmp16x32(0,0,FG_COLOR,BG_COLOR,bmp16x32); break;
		case 3:	draw_Bmp16x48(0,0,FG_COLOR,BG_COLOR,bmp16x48); break;
		case 4:	draw_Bmp16x64(0,0,FG_COLOR,BG_COLOR,bmp16x64); break;
		case 5:	draw_Bmp32x16(0,0,FG_COLOR,BG_COLOR,bmp32x16); break;
		case 6: draw_Bmp32x32(0,0,FG_COLOR,BG_COLOR,bmp32x32); break;
		case 7: draw_Bmp32x48(0,0,FG_COLOR,BG_COLOR,bmp32x48); break;
		case 8: draw_Bmp32x64(0,0,FG_COLOR,BG_COLOR,bmp32x64); break;
		case 9: draw_Bmp64x64(0,0,FG_COLOR,BG_COLOR,bmp64x64); break;
		default:clear_LCD(); break; // clear LCD when key is not pressed
		}
	}
}