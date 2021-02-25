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

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  //c
  // initialize Port E so that bits 7 through 0 of Port E are set as outputs(0)
  // Register TRISE has address 0xbf886100
  volatile int * trise = (volatile int *) 0xbf886100;
  // least 8 bits are 0
  * trise = * trise & 0xff00;

  //e
  //initialize port D so that bits 11 through 5 of Port D are set as inputs(1)
  TRISD = TRISD & 0x0fe0;
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  volatile int * porte = (volatile int *) 0xbf886110;
  * porte = 0x0; // for LED outputs
  int btns;
  int sw;

  while(1) {
    delay( 1000 );
    //h
    btns = getbtns();
    sw = getsw();

    /*
	Checks if bit 1(001) is pressed and 2(010) and so on ..
	sw is a number 0-f, shift it into the right position and
	OR it with the correct zeroed byte of mytime.
	*/

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
//d
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    display_image(96, icon);
    // for LEDs ticking
     * porte =  * porte + 0x1;
  }
}

