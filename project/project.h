/// Header file
/// Direction values: 0 == UP, 1 == RIGHT, 2 == DOWN, 3 == LEFT.

#include <pic32mx.h>
#include <stdint.h>

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

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

void set_pixel(int, int, int);

int getbtns12();

uint8_t spi_send_recv(uint8_t);

void display_update();

void set_disp_data();

void clear_disp();

void move();

void bug();

int mod(int, int);

typedef struct {
        int xpos;
        int ypos;
        int direction;
        int id;
        int clicked;
        int lives;
} Line;

typedef struct {
        int x;
        int y;
} textpointer;

void check_death(Line *line);
