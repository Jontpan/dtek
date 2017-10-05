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
int timeoutcount = 0;
volatile uint8_t* pe = (volatile uint8_t*) 0xbf886110; // Port E

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr (void) {
  return;
}

/* Lab-specific initialization goes here */
void labinit (void) {
  volatile int* p = (volatile int*) 0xbf886100; // Tris E
  *p &= ~0xff; // Set Tris E 7-0 to output
  *pe = 0x00;
  TRISD |= 0xfe0; // Set TRISD 11-5, i.e. 1111 111X XXXX

  //Type B timer, Timer 2 (80 MHz): 16 bit
  T2CON = 0x00070; //Stop 32 bit timer and clear control register
                   //bits 6-4 is 1:64, bit 1 is clock source
  TMR2 = 0x0;      //Reset timer register
  PR2 = 0x7A12;     //Load period register, 31250 dec
  T2CON |= 0x8000; //Start the bloody timer, bit 15
}

/* This function is called repetitively from the main program */
void labwork (void) {
  int read = getbtns();
  int i = 1;
  for (i; i < 4; i++) { //Button 2 through 4
    if ((read & 0x1) == 1) { // If least significant is 1...
      //Update mytime value i with SW4-SW1
      int switches = getsw();
      mytime &= ~(0xf << i * 4); // Change digit with index i-1
      mytime |= (switches << (i * 4));
    }
    read = read >> 1; //Shift down
  }
    
  if(((IFS(0) >> 8) & 0x1) == 0x1) {
    IFS(0) &= ~0x100;
    timeoutcount++;

    if (timeoutcount == 10) {
      timeoutcount = 0;

      time2string( textstring, mytime );
      display_string( 3, textstring );
      display_update();
      tick( &mytime );
      (*pe)++;
      display_image(96, icon);
    }
  }
}
