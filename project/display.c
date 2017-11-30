#include <pic32mx.h>
#include <stdint.h>
#include "project.h"

uint8_t pixels[512];

uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
        while(!(SPI2STAT & 0x01));
	return SPI2BUF;
}

void display_update() {
	int j;
	set_disp_data();

	for(j = 0; j < 512; j++) {
		spi_send_recv(pixels[j]);
	}
}

void set_pixel(int x, int y, int on) {
	int i = (y / 8) * 128 + x;

	uint8_t k = 1 << (y % 8);

	if (on) {
		pixels[i] |= k;
	} else {
		pixels[i] &= ~k;
	}
}

int get_pixel(int x, int y) {
        x = mod(x, 128);
        y = mod(y, 32);
        int i = (y / 8) * 128 + x;
        return (pixels[i] >> (y % 8)) & 0x1;
}

void clear_disp() {
	int x, y;
	for (y = 0; y < 32; y++) {
		for (x = 0; x < 128; x++) {
			set_pixel(x, y, 0);
		}
	}
	display_update();
}
