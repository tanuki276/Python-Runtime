#define _POSIX_C_SOURCE 200809L
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 24
#define MAX_PARTICLES 100

typedef struct {
    float x, y;
    float vx, vy;
    int color;
    int alive;
} Particle;

Particle particles[MAX_PARTICLES];

void clear_screen() {
    printf("\033[2J\033[H");
}

void hide_cursor() {
    printf("\033[?25l");
}

void show_cursor() {
    printf("\033[?25h");
}

void move_cursor(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void set_color(int color) {
    printf("\033[38;5;%dm", color);
}

void reset_color() {
    printf("\033[0m");
}

void init_particles() {
    for(int i=0; i<MAX_PARTICLES; i++) {
        particles[i].alive = 0;
    }
}

void launch_firework() {
    int base_x = rand() % (WIDTH - 10) + 5;
    int base_y = HEIGHT - 1;

    for(int i=0; i<MAX_PARTICLES; i++) {
        if(!particles[i].alive) {
            particles[i].x = base_x;
            particles[i].y = base_y;
            float angle = ((float)(rand() % 360)) * 3.14159f / 180.0f;
            float speed = ((float)(rand() % 50))/20.0f + 2.0f;
            particles[i].vx = cos(angle)*speed;
            particles[i].vy = sin(angle)*speed - 3.5f; // 上方向に強い初速
            particles[i].color = 31 + (rand() % 7); // 赤〜黄系
            particles[i].alive = 1;
            break;
        }
    }
}

void update_particles() {
    for(int i=0; i<MAX_PARTICLES; i++) {
        if(particles[i].alive) {
            particles[i].x += particles[i].vx * 0.1f;
            particles[i].y += particles[i].vy * 0.1f;
            particles[i].vy += 0.15f; // 重力加速度

            // 地面に落ちたら消える
            if(particles[i].y >= HEIGHT-1) {
                particles[i].alive = 0;
            }
        }
    }
}

void draw_particles() {
    clear_screen();
    for(int i=0; i<MAX_PARTICLES; i++) {
        if(particles[i].alive) {
            int px = (int)particles[i].x;
            int py = (int)particles[i].y;
            if(px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
                move_cursor(px+1, py+1);
                set_color(particles[i].color);
                printf("*");
                reset_color();
            }
        }
    }
    fflush(stdout);
}

static PyObject* fireworks(PyObject* self, PyObject* args) {
    int repeat = 5;
    if(!PyArg_ParseTuple(args, "|i", &repeat)) return NULL;

    srand(time(NULL));
    hide_cursor();
    init_particles();

    for(int r=0; r<repeat; r++) {
        for(int t=0; t<100; t++) {
            if(t % 20 == 0) {
                launch_firework();
            }
            update_particles();
            draw_particles();
            usleep(50000);
        }
    }

    clear_screen();
    show_cursor();

    Py_RETURN_NONE;
}

static PyMethodDef MyExtMethods[] = {
    {"fireworks", fireworks, METH_VARARGS, "Run colorful fireworks animation."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef myextmodule = {
    PyModuleDef_HEAD_INIT,
    "myext",
    "Colorful fireworks C extension",
    -1,
    MyExtMethods
};

PyMODINIT_FUNC PyInit_myext(void) {
    return PyModule_Create(&myextmodule);
}