/* mipslabwork.c
   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall
   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):
   This file modified 2017-04-31 by Ture Teknolog
   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

#define TMR2PERIOD ((80000000 / 256) / 10)
#if TMR2PERIOD > 0xffff
#error "TMR2PERIOD is too big"
#endif

int mytime = 0x5957;
int timeoutcount = 0;
int prime = 1234567;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr (void) {


	if (IFS(0) & 0x100) {

		timeoutcount++;
		IFS(0) = 0;

		if (timeoutcount == 10) {

		time2string(textstring, mytime);
		display_string(3, textstring);
		display_update();
		tick( &mytime);
		timeoutcount = 0;
		}

	}
	if (IFS(0) & (1 << 15)){

		IFS(0) = 0;
		(*porte)++;
	}

}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int * porte = (volatile int *) 0xbf886110;
  volatile int * trise = (volatile int *) 0xbf886100;
  // initialize Port E so that bits 7 through 0 of Port E are set as outputs(0)
  // Register TRISE has address 0xbf886100
  * porte = 0x0;
  // least 8 bits are 0
  * trise = * trise & 0xff00;
  //initialize port D so that bits 11 through 5 of Port D are set as inputs(1)
  TRISD = TRISD & 0x0fe0;
  PR2 = TMR2PERIOD; //for a timeout value of 100 ms
  TMR2 = 0; //reset the counter
  T2CON = 0x70; // 0111 0000 is for 1:256
  T2CONSET = 0x8000; //start the timer

  // Enable interrupts from Timer 2
  IPC(2) = 4;	// set priority
  IEC(0) = 0x100;	//  enable bit 8 for interrupt
  enable_interrupt();
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
 void user_isr( void ) {
 time2string( textstring, mytime );
 display_string( 3, textstring );
 display_update();
 tick( &mytime )
}

