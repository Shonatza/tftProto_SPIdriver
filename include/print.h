#ifndef PRINT_H
#define PRINT_H

#include"config_and_spi.h"
#include "tft_colors.h"

extern const int X_origin;
extern const int Y_origin;
extern const int X_size ;
extern const int Y_size;

extern uint16_t background_color;
extern uint16_t last_background_color;
extern uint16_t color;

extern int x_String;
extern int y_String;
extern int rerun;

int get_bit(unsigned char byte, int n);
uint16_t get_color(int pick);
void printArea(int x1, int y1, int x2, int y2, int fill);
void printChar(char *buffer);
void printScreen();
void printIMG(const char *filename);

#endif