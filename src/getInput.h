#include"cell.h"

#ifndef BOOL
#define BOOL int
#define FALSE 0
#define TRUE 1
#endif

#ifndef GETINPUT_H
#define GETINPUT_H

BOOL isKeyPressed();
char getChar();
void flushInput();

BOOL playerSelectedCell(char pressedKey, enum Cell *cell);

#endif
