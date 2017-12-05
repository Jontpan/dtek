#include <pic32mx.h>
#include <stdint.h>
#include "project.h"
#include "init.h"

Line player1;
Line player2;

int gameon;

void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

void start(Line *player1, Line *player2) {
	player1->xpos = 0;
	player1->ypos = 0;
	player1->direction = 1;
	player1->id = 1;

	player2->xpos = 127;
	player2->ypos = 31;
	player2->direction = 3;
	player2->id = 2;

	delay(10000000);

	clear_disp();
}

void startscreen() {
	clear_disp();
	int x = 30;
	int y = 5;
	write_startscreen(&x, y);
	x = 30;
	y = 22;
	write_press(&x, y);
	x = 70;
	write_to_start(&x, y);
}

void endscreen(int id) {
	clear_disp();
	int x = 35;
	int y = 10;
	if(id==2){
		write_p1(&x,y);
	}
	if(id==1){
		write_p2(&x,y);
	}
	x = 50;
	write_wins(&x,y);
}

int check_death(Line *line, volatile uint8_t *pe) {
	if (get_pixel(line->xpos, line->ypos)) {
		line->lives--;
		//Update lights
		int player = line->id;
		int lives = line->lives;
		int off;
		switch(lives) {
			case 0:
			if (player == 1) {
				//turn off light X0000???
				off = 0x80;
				break;
			} else if (player == 2){
				//turn off light ???0000X
				off = 0x01;
				break;
			}
			case 1:
			if (player == 1) {
				//turn off light 1X000???
				off = 0x40;
				break;
			} else if (player == 2){
				//turn off light ???000X1
				off = 0x02;
				break;
			}
			case 2:
			if (player == 1) {
				//turn off light 11X00???
				off = 0x20;
				break;
			} else if (player == 2){
				//turn off light ???00X11
				off = 0x04;
				break;
			}
		}
		(*pe) &= ~off;

		if (line->lives <= 0) {
			gameon = 0;
		} else {
			start(&player1, &player2);
		}
	}
}

void set_next_line(Line *line, int width) {
	int x = mod(line->xpos, 128 / width);
	int y = mod(line->ypos, 32 / width);

	int i, j;
	for (i = 0; i < width; i++) {
		for (j = 0; j < width; j++) {
			set_pixel(x * width + i, y * width + j, 1);
		}
	}
}

int main(void) {
	init();
	clear_disp();

	start(&player1, &player2);
	player1.lives = 3;
	player2.lives = 3;

	//Lights on:
	volatile int* p = (volatile int*) 0xbf886100; // Tris E
  *p &= ~0xff; // Set Tris E 7-0 to output
	volatile uint8_t* pe = (volatile uint8_t*) 0xbf886110; // Port E
  *pe = 0x00; //pointer to LED output.
	(*pe) = 0xe7; //11100111

	int x = 30;
	int y = 5;
	write_startscreen(&x, y);
	x = 30;
	y = 22;
	write_press(&x, y);
	x = 70;
	write_to_start(&x, y);
	display_update();

	volatile int start = 0;
	while (start == 0) {
		start = getbtns12() | getbtns34();
		delay(10);
	}
	clear_disp();
	delay(2000);

	gameon = 1;
	while(gameon) {
		move(&player1);
		move(&player2);
		check_death(&player1, pe);
		check_death(&player2, pe);
		set_next_line(&player1, 1);
		set_next_line(&player2, 1);
		display_update();
		delay(200000);
	}
	int id;
	if(player1.lives == 0) {
		id = 1;
	}
	if(player2.lives == 0) {
		id = 2;
	}
	endscreen(id);
	display_update();
	for(;;) ;
	return 0;
}
