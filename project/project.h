/// Header file
/// Direction values: 0 == UP, 1 == RIGHT, 2 == DOWN, 3 == LEFT.

#include <stdint.h>

void set_pixel(int, int, int);

uint8_t spi_send_recv(uint8_t);

void display_update();

void set_disp_data();

void clear_disp();

void move();

void bug();

int mod(int, int);

void check_death(int, int);

struct Line {
        int xpos;
        int ypos;
        int direction;
        int id;
        int clicked;
        int lives;
};
