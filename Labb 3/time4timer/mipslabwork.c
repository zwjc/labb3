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

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  // initialize Port E so that bits 7 through 0 of Port E are set as outputs(0)
  // Register TRISE has address 0xbf886100
  volatile int * trise = (volatile int *) 0xbf886100;
  // least 8 bits are 0
  * trise = * trise & 0xff00;
  //initialize port D so that bits 11 through 5 of Port D are set as inputs(1)
  TRISD = TRISD & 0x0fe0;

  T2CON = 0x70; // 0111 000 is for 1:256
  PR2 = TMR2PERIOD; // for a timeout value of 100 ms
  TMR2 = 0; // reset the counter
  T2CONSET = 0x8000; // start the timer
  return;
}

/**
void labinit( void ) {

	// Set *E to address of TRISE.
	volatile int *E = (volatile int *) 0xbf886100;

	// Set last 8 bits to zero, i.e. sets them as output pins.
	*E = *E & 0xff00;

	// Initialize port D, set bits 11-5 as inputs.
	TRISD = TRISD & 0x0fe0;

	/*
	Set 0x70, 0111 000 for 1:256 prescaling.
	Set timeperiod.
	Reset timer.
	Start the timer by setting the 'ON' bit to '1', bit #15
	in T2CON.
	Heavily inspired byexercise 2, question 4.
	/
	T2CONSET = 0x70;
	PR2 = TMR2PERIOD;
	TMR2 = 0;
	T2CONSET = 0x8000;

	return;
}
**/

/* This function is called repetitively from the main program */
void labwork( void )
{
  volatile int * porte = (volatile int *) 0xbf886110;
  * porte = 0x0; // for LED outputs
  int btns;
  int sw;

    //for button 2
    if(btns & 1 ){
      mytime = (sw << 4) | (mytime & 0xff0f);
    }
    // for button 3
    if(btns & 2 ){
      mytime = (sw << 8) | (mytime & 0xf0ff);
    }
    // for button 4
    if(btns & 4){
      mytime = (sw << 12) | (mytime & 0x0fff);
    }

    if (IFS(0) & 0x100) {

		// Reset all event flags. (Not so elegant)
		IFS(0) = 0;
		timeoutcount++;

		if (timeoutcount == 10) {

		time2string( textstring, mytime );
		display_string( 3, textstring );
		display_update();
		tick( &mytime );
		display_image(96, icon);

		timeoutcount = 0;
		}
	}
}

