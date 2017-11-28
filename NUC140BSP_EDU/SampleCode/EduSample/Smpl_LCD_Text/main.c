//
// Smpl_LCD_Text: display 4 lines of Text on LCD
//
#include <stdio.h>
#include "NUC1xx.h"
#include "SYS.h"
#include "GPIO.h"
#include "LCD.h"

int main(void)
{ 
	UNLOCKREG();
	DrvSYS_Open(48000000); // set to 48MHz
	LOCKREG(); 

	init_LCD(); 
	clear_LCD();
	
	print_Line(0,"CortexM0");
	print_Line(1,"Nuvoton");
	print_Line(2,"NUC140");
	print_Line(3,"NTOU");    	

	printS(64,0*16,"CortexM0");
	printS(68,1*16,"Nuvoton");
	printS(72,2*16,"NUC140");
	printS(76,3*16,"NTOU");		
}

