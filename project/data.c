#include "project.h"

void write_A(int *x, int y) {
        int i;
        for (i = 1; i < 7; i++) {
                set_pixel((*x), y + i, 1);
                set_pixel((*x) + 3, y + i, 1);
                set_pixel((*x) + 4, y + i, 1);
        }

        for (i = 1; i < 3; i++) {
                set_pixel((*x) + i, y, 1);
                set_pixel((*x) + i, y + 1, 1);
                set_pixel((*x) + i, y + 4, 1);
        }

        set_pixel((*x) + 3, y, 1);

        (*x) += 6;
}

void write_c(int *x, int y) {
        int i;
        for (i = 2; i < 7; i++) {
                set_pixel((*x), y + i, 1);
        }

        for (i = 1; i < 3; i++) {
                set_pixel((*x) + i, y + 2, 1);
                set_pixel((*x) + i, y + 6, 1);
        }

        (*x) += 4;
}

void write_h(int *x, int y) {
        int i;
        for (i = 0; i < 7; i++) {
                set_pixel((*x), y + i, 1);
        }

        set_pixel((*x) + 1, y + 2, 1);

        for (i = 2; i < 7; i++) {
                set_pixel((*x) + 2, y + i, 1);
        }

        set_pixel((*x) + 3, y + 6, 1);

        (*x) += 4;
}

void write_t(int *x, int y) {
        int i;
        for (i = 0; i < 3; i += 2) {
                set_pixel((*x) + i, y + 2, 1);
        }

        for (i = 1; i < 7; i++) {
                set_pixel((*x) + 1, y + i, 1);
        }

        set_pixel((*x) + 2, y + 6, 1);

        (*x) += 4;
}

void write_u(int *x, int y) {
        int i;
        for (i = 2; i < 7; i++) {
                set_pixel((*x), y + i, 1);
                set_pixel((*x) + 2, y + i, 1);
        }

        set_pixel((*x) + 1, y + 6, 1);
        set_pixel((*x) + 3, y + 6, 1);

        (*x) += 5;
}

void write_n(int *x, int y) {
        int i;
        for (i = 2; i < 7; i++) {
                set_pixel((*x), y + i, 1);
                set_pixel((*x) + 2, y + i, 1);
        }

        set_pixel((*x) + 1, y + 2, 1);
        set_pixel((*x) + 3, y + 6, 1);

        (*x) += 5;
}

void write_g(int *x, int y) {
        int i;
        for (i = 2; i < 7; i++) {
                set_pixel((*x), y + i, 1);
                set_pixel((*x) + 2, y + i, 1);
        }

        for (i = 0; i < 3; i++) {
                set_pixel((*x) + i, y + 8, 1);
        }

        set_pixel((*x) + 1, y + 2, 1);
        set_pixel((*x) + 1, y + 6, 1);
        set_pixel((*x) + 2, y + 7, 1);

        (*x) += 4;
}

void write_comma(int *x, int y) {
        set_pixel((*x) + 1, y + 5, 1);
        set_pixel((*x) + 1, y + 6, 1);
        set_pixel((*x), y + 7, 1);

        (*x) += 6;
}

void write_d(int *x, int y) {
        int i;
        for (i = 2; i < 7; i++) {
                set_pixel((*x), y + i, 1);
        }

        set_pixel((*x) + 1, y + 2, 1);
        set_pixel((*x) + 1, y + 6, 1);

        for (i = 0; i < 7; i++) {
                set_pixel((*x) + 2, y + i, 1);
        }

        (*x) += 4;
}

void write_i(int *x, int y) {
        int i;
        for (i = 2; i < 7; i++) {
                set_pixel((*x), y + i, 1);
        }

        set_pixel((*x), y, 1);

        (*x) += 2;
}

void write_e(int *x, int y) {
        int i;
        for (i = 2; i < 7; i++) {
                set_pixel((*x), y + i, 1);
        }

        set_pixel((*x) + 1, y + 2, 1);
        set_pixel((*x) + 1, y + 4, 1);
        set_pixel((*x) + 1, y + 6, 1);

        set_pixel((*x) + 2, y + 2, 1);
        set_pixel((*x) + 2, y + 3, 1);
        set_pixel((*x) + 2, y + 4, 1);
        set_pixel((*x) + 2, y + 6, 1);

        (*x) += 4;
}

void write_k(int *x, int y) {
        int i;
        for (i = 0; i < 7; i++) {
                set_pixel((*x), y + i, 1);
        }

        set_pixel((*x) + 1, y + 3, 1);

        for (i = 2; i < 6; i++) {
                set_pixel((*x) + 2, y + i, 1);
        }

        set_pixel((*x) + 3, y + 2, 1);
        set_pixel((*x) + 3, y + 6, 1);

        set_pixel((*x) + 4, y + 6, 1);

        (*x) += 6;
}

void write_r(int *x, int y) {
        int i;
        for (i = 2; i < 7; i++) {
                set_pixel((*x), y + i, 1);
        }

        set_pixel((*x) + 1, y + 2, 1);

        set_pixel((*x) + 2, y + 2, 1);
        set_pixel((*x) + 2, y + 3, 1);

        (*x) += 4;
}

void write_w(int *x, int y) {
        set_pixel((*x), y + 2, 1);
        set_pixel((*x) + 6, y + 2, 1);

        int i;
        for (i = 2; i < 7; i++) {
                set_pixel((*x) + 1, y + i, 1);
                set_pixel((*x) + 3, y + i, 1);
                set_pixel((*x) + 5, y + i, 1);
        }

        set_pixel((*x) + 2, y + 6, 1);
        set_pixel((*x) + 4, y + 6, 1);

        (*x) += 8;
}

void write_p(int *x, int y) {
        int i;
        for (i = 2; i < 9; i++) {
                set_pixel(*x, y + i, 1);
        }

        set_pixel(*x + 1, y + 2, 1);
        set_pixel(*x + 1, y + 6, 1);

        for (i = 2; i < 7; i++) {
                set_pixel(*x + 2, y + i, 1);
        }

        (*x) += 4;
}

void write_s(int *x, int y) {
        set_pixel(*x, y + 3, 1);
        set_pixel(*x, y + 4, 1);
        set_pixel(*x, y + 6, 1);

        set_pixel(*x + 1, y + 2, 1);
        set_pixel(*x + 1, y + 4, 1);
        set_pixel(*x + 1, y + 6, 1);

        set_pixel(*x + 2, y + 2, 1);
        set_pixel(*x + 2, y + 5, 1);

        (*x) += 4;
}

void write_a(int *x, int y) {
        int i;
        for (i = 0; i < 3; i++) {
                set_pixel(*x + i, y + 2, 1);
                set_pixel(*x + i, y + 4, 1);
                set_pixel(*x + i, y + 6, 1);
        }

        set_pixel(*x + 2, y + 3, 1);
        set_pixel(*x, y + 5, 1);
        set_pixel(*x + 2, y + 5, 1);
        set_pixel(*x + 3, y + 6, 1);

        (*x) += 5;
}

void write_o(int *x, int y) {
        int i;
        for (i = 2; i < 7; i++) {
                set_pixel(*x, y + i, 1);
                set_pixel(*x + 2, y + i, 1);
        }

        set_pixel(*x + 1, y + 2, 1);
        set_pixel(*x + 1, y + 6, 1);

        (*x) += 4;
}

write_excl(int *x, int y) {
        int i;
        for (i = 0; i < 5; i++) {
                set_pixel((*x), y + i, 1);
        }

        set_pixel((*x), y + 6, 1);
}

void write_Achtung(int *x, int y) {
        write_A(x, y);
        write_c(x, y);
        write_h(x, y);
        write_t(x, y);
        write_u(x, y);
        write_n(x, y);
        write_g(x, y);
        write_comma(x, y);
}

void write_die(int *x, int y) {
        write_d(x, y);
        write_i(x, y);
        write_e(x, y);

        (*x) += 4;
}

void write_kurwe(int *x, int y) {
        write_k(x, y);
        write_u(x, y);
        write_r(x, y);
        write_w(x, y);
        write_e(x, y);
}

void write_press(int *x, int y) {
        write_p(x, y);
        write_r(x, y);
        write_e(x, y);
        write_s(x, y);
        write_s(x, y);
}

void write_to_start(int *x, int y) {
        write_t(x, y);
        write_o(x, y);
        *x += 4;

        write_s(x, y);
        write_t(x, y);
        write_a(x, y);
        write_r(x, y);
        write_t(x, y);
}

write_startscreen(int *x, int y) {
        write_Achtung(x, y);
        write_die(x, y);
        write_kurwe(x, y);
        write_excl(x, y);
}
