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
	display_update();
	int x = 35;
	int y = 10;
	if(id==1){
		write_p1(&x,y);
	} else if(id==2){
		write_p2(&x,y);
	} else if(id==3){
		write_draw(&x,y);
		return;
	} else {
		write_Achtung(&x,y); //Something went wrong
	}
	x = 55;
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

/*
		if (line->lives <= 0) {
			gameon = 0;
		} else {
			start(&player1, &player2);
		}
		*/

		//Player has died:
		return 1;
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

	int x = 30;
	int y = 5;
	write_startscreen(&x, y);
	x = 30;
	y = 22;
	write_press(&x, y);
	x = 70;
	write_to_start(&x, y);
	display_update();

	volatile int startGame = 0;
	while (startGame == 0) {
		startGame = getbtns12() | getbtns34();
		delay(10);
	}

	//Lights on:
	volatile int* p = (volatile int*) 0xbf886100; // Tris E
	*p &= ~0xff; // Set Tris E 7-0 to output
	volatile uint8_t* pe = (volatile uint8_t*) 0xbf886110; // Port E
	*pe = 0x00; //pointer to LED output.
	(*pe) = 0xe7; //11100111

	clear_disp();
	delay(10000);
	int i = 0;
	int flickers = 6;
	for (i = 0; i < flickers; i++) {
		x = 5;
		y = 5;
		write_p1(&x,y);
		x = 110;
		y = 20;
		write_p2(&x,y);
		display_update();
		delay(1000000);
		clear_disp();
		display_update();
		delay(100000);
	}
	PORTD = 0x0; //Reset buttons

	gameon = 1;
	while(gameon) {
		move(&player1);
		move(&player2);
		int p1 = check_death(&player1, pe); // value 1 means p1 has died.
		int p2 = check_death(&player2, pe);
		if (player1.lives == 0 | (player2.lives == 0)) {
			//Match is over
			gameon = 0;
		} else if ((p1 == 1) | (p2 == 1)) {
			//If either has died, restart game
			start(&player1, &player2);
		}
		set_next_line(&player1, 1);
		set_next_line(&player2, 1);
		display_update();
		delay(200000);
	}
	//Go by LEDs instead of player.lives
	int id; //Which name to print (winner)
	int lives = *pe;
	int p1Lives = lives >> 5; //Three most significant
	int p2Lives = lives & 0x7; //Three least significant
	if(lives == 0) {
		//Draw. Both lost the match at the same time.
		id = 3;
	} else if(p2Lives == 0) {
		id = 1; //P2 loss --> P1 win and vice versa
	} else if(p1Lives == 0) {
		id = 2;
	} else {
		id = 4; //Something went wrong
	}
	endscreen(id);
	display_update();
	for(;;) ;
	return 0;
}
