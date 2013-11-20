/*
   Client per C-Tris

   Sviluppato da Mirko Da Corte
   Matricola: 100687
*/

#ifdef _WIN32
#include<Windows.h>
#else
#include<unistd.h>
#include<sys/ioctl.h>
#include<ncurses.h> //sudo apt-get install libncurses-dev build-essential
#endif

#include"trisGame.h"

//velocità di refresh dello schermo misurato in Frames Per Second
#define FPS 30

int main()
{
	int cycleDeltaT = (int)(1000/FPS); //milliseconds
	int consoleBase, consoleHigh;
	void *consoleHandle = 0;

#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
	CONSOLE_CURSOR_INFO cursorInfo;

	//riceve l'handle della console corrente
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//riceve le dimensioni della console
	GetConsoleScreenBufferInfo(consoleHandle, &scrBufferInfo);
	consoleBase = scrBufferInfo.dwSize.X;
	consoleHigh = scrBufferInfo.dwSize.Y;

	//nasconde il cursore nella console
	cursorInfo.dwSize = 10;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
#else
	initscr();
	cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);
	curs_set(0);

#ifdef TIOCGSIZE
    struct ttysize ts;
    ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
    consoleBase = ts.ts_cols;
    consoleHigh = ts.ts_lines;
#elif defined(TIOCGWINSZ)
    struct winsize ts;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
    consoleBase = ts.ws_col;
    consoleHigh = ts.ws_row;
#endif

#endif

	initializeTrisGame(consoleBase, consoleHigh, consoleHandle);

	while(!updateTrisGame(cycleDeltaT))
	{
		drawTrisGame();

#ifdef _WIN32
		Sleep(cycleDeltaT); 
#else
		usleep(cycleDeltaT*1000);
#endif
	};

	destroyTrisGame();

#ifndef _WIN32
	endwin();
#endif

	return 0;
}
