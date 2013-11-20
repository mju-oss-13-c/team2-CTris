#ifdef _WIN32
#include<Windows.h>
#else
#include<ncurses.h>
#endif

#include"trisGame.h"

#include"mainMenu.h"
#include"playTris.h"

#include<stdlib.h>
#include<time.h>

#define VIDEOBUFFER_SIZE consoleBase*consoleHigh

//stati per il gioco
enum TrisGameStates {mainMenu, inGame};

//variabili di stato
int consoleBase, consoleHigh;
enum TrisGameStates state;
char *videoBuffer0, *videoBuffer1; //stringhe non NULL termined perchè tanto non serve
#ifdef _WIN32
HANDLE outHandle;
#endif

void swapVideoBuffer();

void initializeTrisGame(int consoleB, int consoleH, void *consoleHandle)
{
	int i;

	consoleBase = consoleB;
	consoleHigh = consoleH;
#ifdef _WIN32
	outHandle = consoleHandle;
	system( "cls" );
#else
	clear();
#endif

	state = mainMenu;
	mainMenuInitialize(consoleBase, consoleHigh, 0, FALSE);
	
	videoBuffer0 = (char*)malloc(sizeof(char)*VIDEOBUFFER_SIZE);
	videoBuffer1 = (char*)malloc(sizeof(char)*VIDEOBUFFER_SIZE);
	for(i = 0; i < VIDEOBUFFER_SIZE; i++)
	{
		videoBuffer0[i] = ' ';
		videoBuffer1[i] = ' ';
	}

	srand((unsigned int)time(0));
}
void destroyTrisGame()
{
	free(videoBuffer0);
	free(videoBuffer1);
	if(state == mainMenu)
		mainMenuDestroy();
	else
		playTrisDestroy();
}

BOOL updateTrisGame(int deltaT)
{
	BOOL exit = FALSE;
	int command;

	switch(state)
	{
	case mainMenu:
		command = mainMenuUpdate(deltaT);
		switch(command)
		{
		case -1:
			exit = TRUE;
			break;
		case 1:
		case 2:
			mainMenuDestroy();
			state = inGame;
			playTrisInitialize(consoleBase, consoleHigh, videoBuffer0, local, (command == 1 ? AI : human), human);
			break;
		}
		break;

	case inGame:
		command = playTrisUpdate(deltaT);
		if(command == -1)
		{
			playTrisDestroy();
			state = mainMenu;
			mainMenuInitialize(consoleBase, consoleHigh, videoBuffer0, TRUE);
		}
		break;
	}

	return exit;
}
void drawTrisGame()
{
	int i;

	switch(state)
	{
	case mainMenu:
		mainMenuDraw(videoBuffer0);
		break;
	case inGame:
		playTrisDraw(videoBuffer0);
		break;
	}

#ifndef _WIN32
	move(0,0);
#endif

	for(i = 0; i < VIDEOBUFFER_SIZE-1; i++)
	{
#ifdef _WIN32
		int row = i / consoleBase,
			column = i % consoleBase;
		if(videoBuffer0[i] != videoBuffer1[i])
		{
			DWORD writenChar;
			COORD coord;
			coord.Y = row;
			coord.X = column;
			SetConsoleCursorPosition(outHandle, coord);

			WriteFile(outHandle, videoBuffer0 + i, 1, &writenChar, NULL);
		}
#else
		addch(*(videoBuffer0 + i));
#endif
	}

	//scambio videoBuffer
	swapVideoBuffer();

#ifndef _WIN32
	refresh();
#endif
}

/* Scambia i due video buffer
 */
void swapVideoBuffer()
{
	char *tempVideoBuffer = videoBuffer0;
	videoBuffer0 = videoBuffer1;
	videoBuffer1 = tempVideoBuffer;
}