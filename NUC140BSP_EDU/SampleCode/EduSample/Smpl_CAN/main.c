//
// Smpl_CAN : 
// TX: generate message with ID=0x777 & Data = 5 bytes
// RX: set Mask Filter to receive ID=700~7FF, and show Msg Data
//
#include <stdio.h>
#include "NUC1xx.h"
#include "SYS.h"
#include "GPIO.h"
#include "CAN.h"
#include "LCD.h" 

char TEXT0[16] = "CAN :           ";
char TEXT1[16] = "ID  :           ";
char TEXT2[16] = "Data:           ";
char TEXT3[16] = "                ";

void CAN_ShowMsg(STR_CANMSG_T* Msg);

STR_CANMSG_T rrMsg;

// Interrupt Service Routine/Callback Function
void CAN_CallbackFn(uint32_t u32IIDR)
{
    if(u32IIDR==1)
    {
	    //printf("Msg-0 INT and Callback\n");
        DrvCAN_ReadMsgObj(0,TRUE,&rrMsg);
        CAN_ShowMsg(&rrMsg);
    }
    if(u32IIDR==5+1)
    {
	    //printf("Msg-5 INT and Callback \n");
        DrvCAN_ReadMsgObj(5,TRUE,&rrMsg);
        CAN_ShowMsg(&rrMsg);
    }
    if(u32IIDR==31+1)
    {
	    //printf("Msg-31 INT and Callback \n");
        DrvCAN_ReadMsgObj(31,TRUE,&rrMsg);
        CAN_ShowMsg(&rrMsg);
    }
}

// Display Message on LCD
void CAN_ShowMsg(STR_CANMSG_T* Msg)
{
  uint8_t i;
	sprintf(TEXT1+6,"%x", Msg->Id);
	print_Line(1,TEXT1);

  for(i=0;i<Msg->DLC;i++) 	
	sprintf(TEXT2+6+i,"%c", Msg->Data[i]);
	print_Line(2,TEXT2);
}

// TX send ID & Data
void CAN_TX(int8_t number)
{
    STR_CANMSG_T tMsg;

	  tMsg.FrameType= DATA_FRAME;
	  tMsg.IdType   = CAN_STD_ID; // send 11-bit ID
	  tMsg.Id 	  = 0x777;        // ID = 0x777
	  tMsg.DLC	  = 5;		      	// data length = 4 bytes
		
	// Convert ADC value to 4 digits ASCII code
		tMsg.Data[0]  = 'N';
		tMsg.Data[1]  = 'U';
		tMsg.Data[2]  = 'C';
		tMsg.Data[3]  = ' ';
		tMsg.Data[4]  = 0x30+number;
	
    	if(DrvCAN_SetTxMsgObj(MSG(1),&tMsg) < 0) // Confiugre Msg RAM
	    {
		    //printf("Set Tx Msg Object failed\n");
		    return;
	    }
	    DrvCAN_SetTxRqst(MSG(1));

        DrvSYS_Delay(100000);
    
    //printf("Transfer Done\n"); 
}

// RX set Mask Filter
void SetMaskFilter()
{
  STR_CANMASK_T MaskMsg;

	DrvCAN_EnableInt(CAN_CON_IE);
 	DrvCAN_InstallCallback(CALLBACK_MSG, (CAN_CALLBACK)CAN_CallbackFn);
	
	/* Set b'0' means don't care*/
	/* Set Messge Object No.0 mask ID */
	MaskMsg.u8Xtd    = 1;
	MaskMsg.u8Dir    = 1;
	MaskMsg.u8IdType = 0;     /* 1:EXT or 0:STD */
	MaskMsg.u32Id 	 = 0x700;
	DrvCAN_SetMsgObjMask(MSG(0),&MaskMsg);
	DrvCAN_SetRxMsgObj(MSG(0), CAN_STD_ID, 0x7FF , TRUE);
    //printf("If there is a message-ID 0x700~0x70F,\n ONLY 0x707/0x70F can pass acceptance filter.\n");
    //printf("Waiting Message\n");
	DrvSYS_Delay(100000);

//	DrvCAN_UninstallCallback(CALLBACK_MSG);
//  DrvCAN_DisableInt(CAN_CON_IE);
}

int main (void)
{
	int32_t CAN_speed = 1000; // Kbps 
	int32_t i32Err =0; 
	int8_t  number=0;
		
  UNLOCKREG();
  DrvSYS_SetOscCtrl(E_SYS_XTL12M,1);
  DrvSYS_Delay(5000);	/* Delay for Xtal stable */
  DrvSYS_SelectHCLKSource(0);
  LOCKREG();

	init_LCD();
	clear_LCD();

// 	DrvGPIO_Open(E_GPD,14,E_IO_OUTPUT);// LCD backlight   
//  DrvGPIO_ClrBit(E_GPD,14);
 	DrvGPIO_Open(E_GPB,12,E_IO_OUTPUT);  // CAN Transceiver setting
  DrvGPIO_ClrBit(E_GPB,12);

	/* Select CAN Multi-Function */
	DrvGPIO_InitFunction(E_FUNC_CAN0);
  DrvCAN_Init();

  i32Err = DrvCAN_Open(CAN_speed);    // set CAN speed
  //if(i32Err<0) printf("Set CAN bit rate is fail\n");

	sprintf(TEXT0+5,"%d Kbps", CAN_speed); 
	print_Line(0,TEXT0);

 	SetMaskFilter();               // set receiving message
	sprintf(TEXT3,"SetMaskFilter");	
	print_Line(3,TEXT3);

	while(1) {			
		CAN_TX(number);
		number++;
		if(number>=16) number=0;
	}      
//	DrvCAN_Close(); 
}







