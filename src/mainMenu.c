#include"mainMenu.h"
#include"grid.h"
#include"AI.h"
#include"getInput.h"

#include<stdio.h>
#include<stdlib.h>

#define VIDEOBUFFER_SIZE consoleBase*consoleHigh

#define INTR_ANIM_TIME 10000
#define ENTER_SCREEN_ANIM_TIME 400

#define IA_LATENCY 1000
#define CELL_DRAW_MIN_TIME 100
#define CELL_DRAW_MAX_TIME 400

#define IMAGE_SIZE_H 24
#define IMAGE_SIZE_B 75

BOOL skIntro;
BOOL mainMenuEnterScrAnim;
char *mainMenuPreviousScreen;

unsigned long int mainMenuTotalTimeElapsed;
unsigned long int mainMenuTimeLastMovement;

enum Players mainMenuPlayTurn;
Grid mainMenuGrid;
char **mainMenuGridImage;
enum Cell mainMenuLastCellSigned;
int mainMenuCurrentCellDrawTime;

int consoleBase, consoleHigh;
char mainMenuBaseImage[IMAGE_SIZE_H][IMAGE_SIZE_B+1] =
{"                         Welcome to:                                       ",
 "   AI  X vs.  O   AI       _______ ___     ____     ___                ____",
 "**********************        |    |  \\ | /        /       /\\   |\\  /| |   ",
 "**********************        |    |__/ | \\___    |  __   /  \\  | \\/ | |__ ",
 "**********************        |    |\\   |     \\   |    | |____| |    | |   ",
 "**********************   my   |    | \\  | ____/    \\__/  |    | |    | |___",
 "**********************                                                     ",
 "**********************                        developed by Mirko Da Corte  ",
 "**********************                                                     ",
 "**********************   What do you want to do?                           ",
 "**********************                                                     ",
 "**********************   1) Play a Single Player game                      ",
 "**********************                                                     ",
 "**********************   2) Play a Multi Player game                       ",
 "**********************                                                     ",
 "**********************   q) quit the game                                  ",
 "**********************                                                     ",
 "**********************                                                     ",
 "**********************          ------------------------------------       ",
 "**********************          |  ARE YOU SURE YOU WANT TO QUIT?  |       ",
 "**********************          |                                  |       ",
 "**********************          |               Y/N                |       ",
 "**********************          ------------------------------------       ",
 "**********************                                                     "};

BOOL exitQuest;

void mainMenuInitialize(int consoleB, int consoleH, char *prevScreen, BOOL skipIntro)
{
	int i;
	
	consoleBase = consoleB;
	consoleHigh = consoleH;

	mainMenuTotalTimeElapsed = mainMenuTimeLastMovement = 0;
	mainMenuGrid = createGrid();
	mainMenuGridImage = (char**)malloc(sizeof(char*)*GRID_IMAGE_SIZE_H);
	for(i = 0; i < GRID_IMAGE_SIZE_H; i++)
		mainMenuGridImage[i] = (char*)malloc(sizeof(char)*(GRID_IMAGE_SIZE_B));
	mainMenuPlayTurn = (rand() % 2 == 0 ? circle : cross);

	skIntro = skipIntro;

	mainMenuEnterScrAnim = skipIntro && prevScreen != 0;
	if(mainMenuEnterScrAnim)
	{
		mainMenuPreviousScreen = (char*)malloc(sizeof(char)*VIDEOBUFFER_SIZE);
		for(i = 0; i < VIDEOBUFFER_SIZE; i++)
			mainMenuPreviousScreen[i] = prevScreen[i];
	}
	
	exitQuest = FALSE;
}
void mainMenuDestroy()
{
	int i;
	for(i = 0; i < GRID_IMAGE_SIZE_H; i++)
		free(mainMenuGridImage[i]);
	free(mainMenuGridImage);
	if(mainMenuEnterScrAnim)
		free(mainMenuPreviousScreen);
}

int mainMenuUpdate(int deltaT)
{
	char key = '\0';
	BOOL introductionAnim, enteringAnim;

	mainMenuTotalTimeElapsed += deltaT;

	if(isKeyPressed())
	{
		key = getChar();
		flushInput();
	}

	introductionAnim = !skIntro && mainMenuTotalTimeElapsed < INTR_ANIM_TIME;
	enteringAnim = mainMenuEnterScrAnim && mainMenuTotalTimeElapsed < ENTER_SCREEN_ANIM_TIME;

	if(introductionAnim && (key == 'q' || key == 'Q'))
		skIntro = TRUE;

	//interpreta input utente
	if(!introductionAnim && !enteringAnim)
	{
		switch(key)
		{
		case '1':
		case '2':
			return (int)(key - '0'); //ritorna rispettivamente 1 o 2
		case 'q':
		case 'Q':
			if(!exitQuest)
				exitQuest = TRUE;
			break;
		case 'y':
		case 'Y':
			if(exitQuest)
				return -1;
			break;
		case 'n':
		case 'N':
			exitQuest = FALSE;
			break;
		}
	}

	//aggiorna IA vs. IA
	if(!introductionAnim && !enteringAnim &&
		mainMenuTotalTimeElapsed - mainMenuTimeLastMovement >= IA_LATENCY)
	{
		if(!won(mainMenuGrid, NULL) && !fullGrid(mainMenuGrid))
		{
			enum Cell move;
			nextMoveAI(mainMenuGrid, mainMenuPlayTurn, &move);
			setCell(mainMenuGrid, move, (CellState)mainMenuPlayTurn);
			
			mainMenuLastCellSigned = move;
			mainMenuCurrentCellDrawTime = (rand() % (CELL_DRAW_MAX_TIME - CELL_DRAW_MIN_TIME)) + CELL_DRAW_MIN_TIME;

			if(mainMenuPlayTurn == cross)
				mainMenuPlayTurn = circle;
			else
				mainMenuPlayTurn = cross;
		}
		else
		{
			deleteGrid(mainMenuGrid);
			mainMenuGrid = createGrid();
		}

		mainMenuTimeLastMovement = mainMenuTotalTimeElapsed;
	}

	return 0;
}
void mainMenuDraw(char *videoBuffer)
{
	int i;

	//cls sul videoBuffer
	for(i = 0; i < VIDEOBUFFER_SIZE; i++)
		videoBuffer[i] = ' ';

	//stampa griglia
	printGrid(mainMenuGrid, mainMenuLastCellSigned, mainMenuTotalTimeElapsed - mainMenuTimeLastMovement,
		mainMenuCurrentCellDrawTime, mainMenuGridImage);

	//composizione di tutta la scena su videoBuffer
	for(i = 0; i < VIDEOBUFFER_SIZE; i++)
	{
		int row = i / consoleBase,
			column = i % consoleBase;
		if(column < IMAGE_SIZE_B && row < IMAGE_SIZE_H)
		{
			if(row >= 2 && column < 22 && row < 24)			//se è nella griglia stampa la griglia
				videoBuffer[i] = mainMenuGridImage[row-2][column];
			else if(row >= 18 && row < 23 && !exitQuest)	//se ci si trova dove chiede di uscire e non si vuole uscire
				videoBuffer[i] = ' ';
			else											//in tutti gli altri casi
				videoBuffer[i] = mainMenuBaseImage[row][column];
		}
	}

	//mostra animazioni
	//animazione iniziale
	if(!skIntro && mainMenuTotalTimeElapsed < INTR_ANIM_TIME)
	{
		/* Animazione introduttiva:
		 * Il cursore lampeggia per tutta la durata. Intanto
		 *  Sec.
		 * - 0
		 * |	Stop
		 * - 2
		 * |	Avanzo di 36 caratteri sino a stampare il Welcome
		 * - 5
		 * |	Stop
		 * - 7
		 * |	Completo il resto della schermata
		 * - 10
		 */

		int printedChar = 0;
		//faccio rimanere nella scena solamente la parte prevista dall'animazione
		if(mainMenuTotalTimeElapsed >= 2000 && mainMenuTotalTimeElapsed < 5000)			//avanzamento stampa del Welcome
			printedChar = (mainMenuTotalTimeElapsed - 2000) * 36 / 3000;
		else if(mainMenuTotalTimeElapsed >= 5000 && mainMenuTotalTimeElapsed < 7000)	//fermo su welcome
			printedChar = 36;
		else if(mainMenuTotalTimeElapsed >= 7000)										//avanzamento stampa del resto
			printedChar = (mainMenuTotalTimeElapsed - 7000) * (consoleBase*IMAGE_SIZE_H - 36) / 3000 + 36;

		if(mainMenuTotalTimeElapsed % 1000 < 500 && printedChar < VIDEOBUFFER_SIZE)
			videoBuffer[printedChar++] = '_';

		for(; printedChar < VIDEOBUFFER_SIZE; printedChar++)
			videoBuffer[printedChar] = ' ';
	}
	//shifting eventuale per l'ingresso della nuova schermata
	if(mainMenuEnterScrAnim && mainMenuTotalTimeElapsed < ENTER_SCREEN_ANIM_TIME)
	{
		int shift = consoleBase * (ENTER_SCREEN_ANIM_TIME - mainMenuTotalTimeElapsed) / ENTER_SCREEN_ANIM_TIME;
		for(i = 0; i < VIDEOBUFFER_SIZE; i++)
		{
			int column = i % consoleBase;
			if(column + shift < consoleBase)
				videoBuffer[i] = videoBuffer[i + shift];
			else
				videoBuffer[i] = mainMenuPreviousScreen[i - consoleBase + shift];
		}
	}
}
