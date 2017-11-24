#include <pic32mx.h>
#include <stdint.h>
#include "project.h"

#define DISPLAY_VDD PORTFbits.RF6
#define DISPLAY_VBATT PORTFbits.RF5
#define DISPLAY_COMMAND_DATA PORTFbits.RF4
#define DISPLAY_RESET PORTGbits.RG9


#define DISPLAY_VDD_PORT PORTF
#define DISPLAY_VDD_MASK 0x40
#define DISPLAY_VBATT_PORT PORTF
#define DISPLAY_VBATT_MASK 0x20
#define DISPLAY_COMMAND_DATA_PORT PORTF
#define DISPLAY_COMMAND_DATA_MASK 0x10
#define DISPLAY_RESET_PORT PORTG
#define DISPLAY_RESET_MASK 0x200

uint8_t pixels[512];

void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 0x01));
	return SPI2BUF;
}

void set_disp_cmd() {
	DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
}

void set_disp_data() {
	DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;
}

void io_init() {
	TRISD |= 0xfe0; // Set TRISD 11-5, i.e. 1111 111X XXXX
}

void display_init() {
	// Taken from hello-display

	DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
	delay(10);
	DISPLAY_VDD_PORT &= ~DISPLAY_VDD_MASK;
	delay(1000000);

	spi_send_recv(0xAE);
	DISPLAY_RESET_PORT &= ~DISPLAY_RESET_MASK;
	delay(10);
	DISPLAY_RESET_PORT |= DISPLAY_RESET_MASK;
	delay(10);

	spi_send_recv(0x8D);
	spi_send_recv(0x14);

	spi_send_recv(0xD9);
	spi_send_recv(0xF1);

	DISPLAY_VBATT_PORT &= ~DISPLAY_VBATT_MASK;
	delay(10000000);

	spi_send_recv(0xA1);
	spi_send_recv(0xC8);

	spi_send_recv(0xDA);
	spi_send_recv(0x20);

	spi_send_recv(0xAF);

	// Set page addressing mode to horizontal, written by us
	set_disp_cmd();
	spi_send_recv(0x20);
	spi_send_recv(0x00);
	set_disp_data();
}

void display_update() {
	int j;
	DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;

	for(j = 0; j < 512; j++) {
		spi_send_recv(pixels[j]);
	}
}

void set_pixel(int x, int y, int on) {
	uint8_t k;
	switch (y % 8) {
		case 0: k = 0x01; break;
		case 1: k = 0x02; break;
		case 2: k = 0x04; break;
		case 3: k = 0x08; break;
		case 4: k = 0x10; break;
		case 5: k = 0x20; break;
		case 6: k = 0x40; break;
		case 7: k = 0x80; break;
	}

	int i = (y / 8) * 128 + x;

	if (on) {
		pixels[i] |= k;
	} else {
		pixels[i] &= ~k;
	}
}

void clear_disp() {
	int x, y;
	for (x = 0; x < 32; x++) {
		for (y = 0; y < 128; y++) {
			set_pixel(x, y, 0);
		}
	}
	display_update();
}


void init() {
	/* Set up peripheral bus clock */
	OSCCON &= ~0x180000;
	OSCCON |= 0x080000;

	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;

	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;

	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);

	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;

	/* Clear SPIROV*/
	SPI2STATCLR &= ~0x40;
	/* Set CKP = 1, MSTEN = 1; */
        SPI2CON |= 0x60;

	/* Turn on SPI */
	SPI2CONSET = 0x8000;
}

int main(void) {
	init();
	display_init();
	io_init();
	clear_disp();

	struct Line player;
	player.pos[0] = 64;
	player.pos[1] = 0;
	player.direction = 1;

	int gameon = 1;
	while(gameon) {
		move(&player);
		display_update();
	}

	for(;;) ;
	return 0;
}
