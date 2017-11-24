/// Header file
/// Direction values: 0 == UP, 1 == RIGHT, 2 == DOWN, 3 == LEFT.

void set_pixel(int, int, int);

void display_update();

void clear_disp();

void move();

void bug();

struct Line {
        int pos[2];
        int direction;
};
