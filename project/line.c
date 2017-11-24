#include "project.h"
#include <pic32mx.h>


int getbtns() {
	int read = (PORTD >> 6);
	read &= 0x3;
	return read;
}

void set_next_pixel(struct Line *line) {
        set_pixel(line->pos[0] % 128, line->pos[1] % 32, 1);
}

void move_right(struct Line *line) {
        line->pos[0] += 1;
        set_next_pixel(line);
}

void move_left(struct Line *line) {
        line->pos[0] -= 1;
	set_next_pixel(line);
}

void move_up(struct Line *line) {
        line->pos[1] -= 1;
	set_next_pixel(line);
}

void move_down(struct Line *line) {
        line->pos[1] += 1;
	set_next_pixel(line);
}

void turn(struct Line *line) {
        int read = getbtns();

        if (read == 1) {
                line->direction++;
        } else if (read == 2) {
                line->direction--;
        }
}

void bug() {
        int i;
        for (i = 0; i < 32; i++) {
                set_pixel(127, i, 1);
        }
        display_update();
};

void move(struct Line *line) {
        turn(line);

        switch (line->direction % 4) {
                case 0: move_up(line); break;
                case 1: move_right(line); break;
                case 2: move_down(line); break;
                case 3: move_left(line); break;
                default: bug();
                        // Hopefully never get here
                        return;
        }
}
