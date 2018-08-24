/******************************************************************************

* file Name : r_ostm.c

* version   : 0.1

* Argument      : andy

* data  : 2018/8/24

* describe: os timer

******************************************************************************/
#include	<string.h>
#include 	"r_typedefs.h"
#include 	"ree_types.h"
#include 	"iodefine.h"
#include 	"r_ostm.h"
#include    	"rlin3_api.h"
uint32_t OSTM0_Tick=0;
const uint32_t OSTM_1MS =40000; //40000 1ms , 4000 10ms 

/******************************************************************************

* Function Name : void OSTM0_Init( uint32_t )

* Description   : This function initializes the  os clock.

* Argument      : value

* Return Value  : none

******************************************************************************/
void OSTM0_Init(uint32_t value)
{
	/*OSTMn Control Register
	 *b7:b2 - Reserved set to 0
	 b1	-Specifies the operating mode for the counter
	 b0	-Controls the generation of OSTMTINT interrupt requests at the start of counting*/
	//OSTM0.CTL=0x00;
	OSTM0.CTL &=~ (1<<1);
	OSTM0.CTL &=~ (1<<0);
	/*OSTMnCMP — OSTMn Compare Register*/
	OSTM0.CMP=value;
	
	//ICOSTM0 =0x0007;		//set OSTM0 to lowest level interrupt priority
	//ICOSTM0&=0xFFF0; 		//set OSTM0 to highest level interrupt priority

	RFOSTM0 =0;				//clear interrupt flag
	MKOSTM0 =1;				//disable interrupt 
	TBOSTM0 =1;				//set interrupt mode to table reference mode 
	MKOSTM0 =0;				//enable interrupt
}
/******************************************************************************

* Function Name : void OSTM0_Start( void )

* Description   : This function Start the  os clock.

* Argument      : none

* Return Value  : none

******************************************************************************/
void OSTM0_Start(void)
{
	/*OSTMnTS — OSTMn Count Start Trigger Register
	 *b7:b1 - Reserved set to 0
	 b0	-Starts the counte*/
	OSTM0.TS=0x01;
}
/******************************************************************************

* Function Name : void OSTM0_Stop( void )

* Description   : This function Start the  os clock.

* Argument      : none

* Return Value  : none

******************************************************************************/
void OSTM0_Stop(void)
{
	/*OSTMnTT — OSTMn Count Stop Trigger Register
	 *b7:b1 - Reserved set to 0
	 b0	-Stops the counte*/
	OSTM0.TT=0x01;
}
/******************************************************************************

* Function Name : uint32_t OSTM0_Get_Tick( void )

* Description   : This function Tick the  os clock.

* Argument      : none

* Return Value  : OSTM0_Tick

******************************************************************************/
uint32_t  OSTM0_Get_Tick(void)
{
	return OSTM0_Tick;
}
/******************************************************************************

* Function Name : uint8_t OSTM0_Delay( uint32_t )

* Description   : This function Tick the  os clock.

* Argument      : none

* Return Value  : 1

******************************************************************************/
uint8_t  OSTM0_Delay(uint32_t Delay_ms)
{
	uint32_t tickstart = 0;
	tickstart = OSTM0_Get_Tick();
  	while((OSTM0_Get_Tick() - tickstart) < Delay_ms){
	}
	return 1;
}





