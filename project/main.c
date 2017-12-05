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
	display_update();

	delay(100);
}

void endscreen(int id) {
	// TODO
}

void check_death(Line *line) {
	if (get_pixel(line->xpos, line->ypos)) {
		line->lives--;
		if (line->lives <= 0) {
			startscreen();
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

	gameon = 1;
	while(gameon) {
		move(&player1);
		move(&player2);
		set_next_line(&player1, 1);
		set_next_line(&player2, 1);
		display_update();
		delay(200000);
	}

	for(;;) ;
	return 0;
}
