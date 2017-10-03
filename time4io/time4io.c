// time4io.c
#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

/*Return value: The four least significant bits of the return value should contain data from switches
SW4, SW3, SW2, and SW1. SW1 corresponds to the least significant bit. All other bits of the return
value must be zero */
int getsw(void) {
	int read = (PORTD >> 8);
	read &= 0xf;
	return read;
}

int getbtns(void) {
	int read = (PORTD >> 5);
	read &= 0x7;
	return read;
}