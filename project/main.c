#include <pic32mx.h>
#include <stdint.h>
#include "project.h"
#include "init.h"

int game_array[64][16];

struct Line player1;
struct Line player2;

void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

void start(struct Line *player1, struct Line *player2) {
	player1->xpos = 0;
	player1->ypos = 0;
	player1->direction = 1;
	player1->id = 1;

	player2->xpos = 127;
	player2->ypos = 31;
	player2->direction = 3;
	player2->id = 2;

	clear_disp();
	delay(1000000);
}

void check_death(int x, int y) {
	if (get_pixel(x, y)) {
		start(&player1, &player2);
	}
}

void set_next_line(struct Line *line, int width) {
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

	int gameon = 1;
	while(gameon) {
		move(&player1);
		move(&player2);
		set_next_line(&player1, 1);
		set_next_line(&player2, 1);
		display_update();
		delay(100000);
	}

	for(;;) ;
	return 0;
}
