#include"getInput.h"

#ifdef _WIN32
#include<conio.h>

BOOL isKeyPressed()
{
	return _kbhit();
}
char getChar()
{
	return _getch();
}

#else
#include <ncurses.h>

BOOL isKeyPressed()
{
	int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return TRUE;
    } else {
        return FALSE;
    }
}
char getChar()
{
	return getch();
}

#endif

void flushInput()
{
	while(isKeyPressed())
		getChar();
}

BOOL playerSelectedCell(char pressedKey, enum Cell *cell)
{
	switch(pressedKey)
	{
	case 'q': case 'Q': case '7':
		*cell = cellA1;
		return TRUE;
	case 'w': case 'W': case '8':
		*cell = cellA2;
		return TRUE;
	case 'e': case 'E': case '9':
		*cell = cellA3;
		return TRUE;
	case 'a': case 'A': case '4':
		*cell = cellB1;
		return TRUE;
	case 's': case 'S': case '5':
		*cell = cellB2;
		return TRUE;
	case 'd': case 'D': case '6':
		*cell = cellB3;
		return TRUE;
	case 'z': case 'Z': case '1':
		*cell = cellC1;
		return TRUE;
	case 'x': case 'X': case '2':
		*cell = cellC2;
		return TRUE;
	case 'c': case 'C': case '3':
		*cell = cellC3;
		return TRUE;
	}

	return FALSE;
}