#ifndef teigi_H
#define teigi_H

#include <stdint.h>

#define BAUDRATE 38400       //serial baudrate

#define DATA_N 11
enum {AF, LX, LY, R_X, RY, L2, R2, BA1, BA2, SUM, ED};

#define SQUARE 0x01
#define CROSS 0x02
#define CIRCLE 0x04
#define TRIANGLE  0x08

#define UP 0x10
#define RIGHT 0x20
#define DOWN 0x40
#define LEFT 0x80


#define L1 0x01
#define L3 0x02
#define R1 0x04
#define R3 0x08
#define Share 0x10
#define Options 0x20
#define PS 0x40

#endif
