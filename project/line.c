#include "project.h"
#include <pic32mx.h>
#include <stdint.h>


int getbtns34() {
	int read = (PORTD >> 6);
	read &= 0x3;
	return read;
}

int getbtns12() {
	int btn1 = (PORTF >> 1) & 1;
	int btn2 = (PORTD >> 4) & 2;
	return btn2 | btn1;
}

void move_right(struct Line *line) {
        line->xpos += 1;
}

void move_left(struct Line *line) {
        line->xpos -= 1;
}

void move_up(struct Line *line) {
        line->ypos -= 1;
}

void move_down(struct Line *line) {
        line->ypos += 1;
}

void turn(struct Line *line) {
	int read;
	if (line->id == 1) {
		read = getbtns34();
	} else if (line->id == 2) {
		read = getbtns12();
	}

        if (read == 0) {
                line->clicked = 0;
                return;
        }

	if (!line->clicked) {
		if (read == 1) {
	                line->direction++;
	                line->clicked = 1;
	        } else if (read == 2) {
	                line->direction--;
			line->clicked = 1;
	        }
	}


}

void bug() {
        int i;
        for (i = 0; i < 32; i++) {
                set_pixel(127, i, 1);
        }
        display_update();
};

int mod(int n, int N) {
	int r = n % N;
	return (r < 0) ? (r + N) : r;
}

void move(struct Line *line) {
        turn(line);


        switch (mod(line->direction, 4)) {
                case 0: move_up(line); break;
                case 1: move_right(line); break;
                case 2: move_down(line); break;
                case 3: move_left(line); break;
                default: bug();
                        // Hopefully never get here
                        return;
        }

	check_death(line->xpos, line->ypos);
	set_next_line(line, 1);
}
