
/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Jonatan Cervall and John Nilsson  

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int prime = 1234567;
volatile uint8_t* pe = (volatile uint8_t*) 0xbf886110; // Port E
int mytime = 0x5957;
int timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr (void) {
  if(((IFS(0) >> 8) & 0x1) == 1) {
    //TxIF bit for interrupt, interrupt enable TxIE = 1
    IFS(0) &= ~0x100; //acknowledge
    timeoutcount++;

    if (timeoutcount >= 10) {
      timeoutcount = 0;
      time2string(textstring, mytime);
      display_string(3,textstring);
      display_update();
      tick(&mytime);
    }
  } else if(((IFS(0) >> 7) & 0x1) == 1) {
    IFS(0) &= ~0x80;
    (*pe)++;
  }
}

/* Lab-specific initialization goes here */
void labinit (void) {
  volatile int* p = (volatile int*) 0xbf886100; // Tris E is the LEDs
  *p &= ~0xff;    // Set Tris E 7-0 to output
  *pe = 0x00;     // Output zero to PORTE at startup
  TRISD |= 0xfe0; // Set TRISD 11-5, i.e. 1111 111X XXXX  Buttons 2-4 and switches 1-4

  //Type B timer, Timer 2 (80 MHz): 16 bit
  T2CON = 0x00070; //Stop 32 bit timer and clear control register
                   //bits 6-4 is 1:64, bit 1 is clock source

  //INTERRUPT ENABLING
  IFS(0) &= ~0x100;       //Clear interrupt flags
  IEC(0) |= 0x100;        //Interrupt enabling controller is ON for timer2
  IPC(2) = 0x1F;//0x1f000000; //Interrupt priority is MAX

  //SURPRISE INTERRUPT ENABLING
  IFS(0) &= ~0x80;
  IEC(0) |= 0x80;
  IPC(1) |= 0x1F000000;//Set priority 1 lower than above 24,25,26,27,28

  enable_interrupt();     //Enable interrupts globally

  TMR2 = 0x0;      //Reset timer register
  PR2 = 0x7A12;    //Load period register, 31250 dec

  T2CON |= 0x8000; //Start the bloody timer, bit 15
}

/* This function is called repetitively from the main program */
void labwork (void) {
  prime = nextprime(prime);
  display_string(0,itoaconv(prime));
  display_update();
}