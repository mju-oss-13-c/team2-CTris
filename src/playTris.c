#include"playTris.h"
#include"grid.h"
#include"getInput.h"
#include"gameHistory.h"
#include"AI.h"
#include"integerManip.h"
#include<stdlib.h>

#define VIDEOBUFFER_SIZE consoleBase*consoleHigh

#define ENTER_SCREEN_ANIM_TIME 400

#define IA_LATENCY 1000
#define CELL_DRAW_MIN_TIME 100
#define CELL_DRAW_MAX_TIME 400
#define END_GAME_WAIT 1000

#define INSTRUCTION_ANIM_TIME 200

#define IMAGE_SIZE_H 24
#define IMAGE_SIZE_B 79
#define INSTRUCTION_SIZE_H 18
#define INSTRUCTION_SIZE_B 54

enum GameMode playTrisGameMode;

BOOL playTrisEnterScrAnim;
char *playTrisPreviousScreen;

unsigned long int playTrisTotalTimeElapsed;
unsigned long int playTrisTimeLastMovement;

enum Players playTrisTurn;
const char *humanString = "Human";
const char *AIString =    "  AI ";
enum PlayerTypes playTrisCircleIntelligence;
enum PlayerTypes playTrisCrossIntelligence;
int playTrisCircleWinCounter;
int playTrisCrossWinCounter;

Grid playTrisGrid;
char **playTrisGridImage;
int playTrisCurrentCellDrawTime;
enum Cell playTrisLastCellSigned;

int consoleBase, consoleHigh;
char playTrisBaseImage[IMAGE_SIZE_H][IMAGE_SIZE_B+1] =
{"                                                         ******                ",
 " ***** X vs.  O *****    _____      _          _  ____   ******                ",
 "**********************     |  |   || \\|\\  |   / \\ |      ******                ",
 "**********************     |  |   ||_/| \\ |  |   ||--  O ******                ",
 "**********************     |   \\_/ | \\|  \\|   \\_/ |    O ******                ",
 "**********************                                                         ",
 "**********************                                                         ",
 "**********************    SCORES:   X -> ****                                  ",
 "**********************              O -> ****                                  ",
 "**********************                                                         ",
 "**********************    Last plays:                                          ",
 "**********************                                                         ",
 "**********************    ************************************************     ",
 "**********************    ************************************************     ",
 "**********************    ************************************************     ",
 "**********************    ************************************************     ",
 "**********************    ************************************************     ",
 "**********************    ************************************************     ",
 "**********************    ************************************************     ",
 "**********************    ************************************************     ",
 "**********************   ----------------------------------------------------  ",
 "**********************    press 'i' to show the instructions                   ",
 "**********************    press 'p' to invert signs of players                 ",
 "**********************    press 'm' to return to the main menu                 "};

struct GameHistory playTrisGameHistory;
char **playTrisGameHistoryImage;

BOOL showInstruction;
int instructionPosition; //da 0 (nascosto) a 100 (visibile)
char instructionImage[INSTRUCTION_SIZE_H][INSTRUCTION_SIZE_B+1] =
{"----------------------------------------------------  ",
 " Instruction to play:                                 ",
 "   Put your sign in a line of three.                  ",
 " Keys:                                                ",
 "   Use the numeric keypad or the normal keyboard to   ",
 "   put your signs into the grid. Use keys like a cell:",
 "        q w e      7 8 9                              ",
 "   use  a s d  or  4 5 6                              ",
 "        z x c      1 2 3                              ",
 " Lines symbols:                                       ",
 "   When a player win a match, winning line is showed  ",
 "   in the \"Last plays\" table. The Line is represented ",
 "   by one of these symbols:                           ",
 "   R1 R1 R1     C1 C2 C3     D1 .. ..     .. .. D2    ",
 "   R2 R2 R2     C1 C2 C3     .. D1 ..     .. D2 ..    ",
 "   R3 R3 R3     C1 C2 C3     .. .. D1     D2 .. ..    ",
 "                                                      ",
 " press the 'i' key to hide the instructions           "};

BOOL humanTryToSetCell(enum Cell cell);
void swapPlayers();

void playTrisInitialize(int consoleB, int consoleH, char *prevScreen, enum GameMode gameMode,
	enum PlayerTypes circleIntelligence, enum PlayerTypes crossIntelligence)
{
	int i;

	playTrisGameMode = gameMode;

	playTrisEnterScrAnim = prevScreen != 0;
	if(playTrisEnterScrAnim)
	{
		playTrisPreviousScreen = (char*)malloc(sizeof(char)*VIDEOBUFFER_SIZE);
		for(i = 0; i < VIDEOBUFFER_SIZE; i++)
			playTrisPreviousScreen[i] = prevScreen[i];
	}

	playTrisTotalTimeElapsed = 0;
	playTrisTimeLastMovement = 0;

	playTrisTurn = (rand() % 2 == 0 ? circle : cross);
	playTrisCircleIntelligence = circleIntelligence;
	playTrisCrossIntelligence = crossIntelligence;
	playTrisCircleWinCounter = 0;
	playTrisCrossWinCounter = 0;

	playTrisGrid = createGrid();
	playTrisGridImage = (char**)malloc(sizeof(char*)*GRID_IMAGE_SIZE_H);
	for(i = 0; i < GRID_IMAGE_SIZE_H; i++)
		playTrisGridImage[i] = (char*)malloc(sizeof(char)*GRID_IMAGE_SIZE_B);
	
	consoleBase = consoleB;
	consoleHigh = consoleH;

	playTrisGameHistory = createGameHistory();
	playTrisGameHistoryImage = (char**)malloc(sizeof(char*)*GAMEHISTORY_IMAGE_SIZE_H);
	for(i = 0; i < GAMEHISTORY_IMAGE_SIZE_H; i++)
		playTrisGameHistoryImage[i] = (char*)malloc(sizeof(char)*GAMEHISTORY_IMAGE_SIZE_B);

	showInstruction = FALSE;
	instructionPosition = 0;
}
void playTrisDestroy()
{
	int i;
	deleteGrid(playTrisGrid);
	deleteGameHistory(playTrisGameHistory);
	for(i = 0; i < GRID_IMAGE_SIZE_H; i++)
		free(playTrisGridImage[i]);
	free(playTrisGridImage);
	for(i = 0; i < GAMEHISTORY_IMAGE_SIZE_H; i++)
		free(playTrisGameHistoryImage[i]);
	free(playTrisGameHistoryImage);
	if(playTrisEnterScrAnim)
		free(playTrisPreviousScreen);
}

int playTrisUpdate(int deltaT)
{
	char key = '\0';
	BOOL enteringAnim;

	playTrisTotalTimeElapsed += deltaT;

	if(isKeyPressed())
	{
		key = getChar();
		flushInput();
	}

	enteringAnim = playTrisEnterScrAnim && playTrisTotalTimeElapsed < ENTER_SCREEN_ANIM_TIME;

	if(!enteringAnim) //se è finita l'introduzione iniziale
	{
		struct GameResult gameResult = createGameResult();

		//input generali
		switch(key)
		{
		case 'i':
		case 'I':
			showInstruction = !showInstruction;
			break;
		case 'p':
		case 'P':
			swapPlayers();
			break;
		case 'm':
		case 'M':
			return -1;
		}

		//se qualcuno ha vinto o se la griglia è comunque piena
		if(won(playTrisGrid, &gameResult) || fullGrid(playTrisGrid))
		{
			if(playTrisTotalTimeElapsed - playTrisTimeLastMovement >= END_GAME_WAIT)
			{
				enum Players winner;
				enum CellLine winningLine;
				addGameResult(&playTrisGameHistory, gameResult); //inserisci nello storico la partita
				getGameResultState(gameResult, &winner, &winningLine);

				if(winner == circle)
					playTrisCircleWinCounter++;
				if(winner == cross)
					playTrisCrossWinCounter++;

				//resetta e prepara per una nuova partita
				playTrisTimeLastMovement = playTrisTotalTimeElapsed;
				deleteGrid(playTrisGrid);
				playTrisGrid = createGrid();
			}
		}
		else //se c'è ancora da giocare
		{
			BOOL correctlyMoved = FALSE;
			enum Cell selectedCell;
			
			//turno dell'uomo
			if((playTrisTurn == circle && playTrisCircleIntelligence == human) ||
				(playTrisTurn == cross && playTrisCrossIntelligence == human))
			{
				if(playerSelectedCell(key, &selectedCell))
					correctlyMoved = humanTryToSetCell(selectedCell);
			}
			else if(playTrisTotalTimeElapsed - playTrisTimeLastMovement >= IA_LATENCY) //turno dell'IA
			{
				nextMoveAI(playTrisGrid, playTrisTurn, &selectedCell);
				setCell(playTrisGrid, selectedCell, playTrisTurn);
				correctlyMoved = TRUE;
			}

			if(correctlyMoved)
			{
				playTrisLastCellSigned = selectedCell;
				playTrisTurn = (playTrisTurn == circle ? cross : circle);
				playTrisTimeLastMovement = playTrisTotalTimeElapsed;
				playTrisCurrentCellDrawTime = (rand() % (CELL_DRAW_MAX_TIME - CELL_DRAW_MIN_TIME)) + CELL_DRAW_MIN_TIME;
			}
		}
		deleteGameResult(gameResult);
	}

	//aggiorna istruzioni
	if(showInstruction)
	{
		instructionPosition += deltaT * 100 / INSTRUCTION_ANIM_TIME;
		if(instructionPosition > 100)
			instructionPosition = 100;
	}
	else
	{
		instructionPosition -= deltaT * 100 / INSTRUCTION_ANIM_TIME;
		if(instructionPosition < 0)
			instructionPosition = 0;
	}

	return 0;
}
void playTrisDraw(char *videoBuffer)
{
	int i, j;
	int instructionHigh = instructionPosition * 18 / 100;
	printGrid(playTrisGrid, playTrisLastCellSigned, playTrisTotalTimeElapsed - playTrisTimeLastMovement, playTrisCurrentCellDrawTime,
		playTrisGridImage);
	printGameHistory(playTrisGameHistory, playTrisGameHistoryImage, GAMEHISTORY_IMAGE_SIZE_B, GAMEHISTORY_IMAGE_SIZE_H);

	//cls
	for(i = 0; i < VIDEOBUFFER_SIZE; i++)
		videoBuffer[i] = ' ';

	//composizione di tutta la scena
	for(i = 0; i < VIDEOBUFFER_SIZE; i++)
	{
		int row = i / consoleBase,
			column = i % consoleBase;
		if(column < IMAGE_SIZE_B && row < IMAGE_SIZE_H)
		{
			if(row == 1 && column >= 1 && column < 6) //se deve stampare il tipo di intelligenza di X
			{
				if(playTrisCrossIntelligence == human)
					videoBuffer[i] = humanString[column - 1];
				else
					videoBuffer[i] = AIString[column - 1];
			}
			else if(row == 1 && column >= 16 && column < 21) //se deve stampare il tipo di intelligenza di O
			{
				if(playTrisCircleIntelligence == human)
					videoBuffer[i] = humanString[column - 16];
				else
					videoBuffer[i] = AIString[column - 16];
			}
			else if(row >= 2 && row < 24 && column < 22) //se è nella griglia stampa la griglia
				videoBuffer[i] = playTrisGridImage[row-2][column];
			else if(row < 5 && column >= 57 && column < 63) //se visualizza il giocatore attuale
				videoBuffer[i] = (playTrisTurn == circle ? imageCircleCell[row][column-57] : imageCrossCell[row][column-57]);
			else if(row >= 24 - instructionHigh && row < 24 && column >= 25 && column < 79) //se deve stampare le istruzioni
			{
				videoBuffer[i] = instructionImage[row + instructionHigh - 24][column - 25];
			}
			else if(row >= 7 && row < 9 && column >= 41 && column < 45) //se deve stampare il punteggio di X o di O
			{
				int score = (row == 7 ? playTrisCrossWinCounter : playTrisCircleWinCounter);
				int digitToFind = countIntegerDigits(score) - column + 40;
				if(digitToFind >= 0)
				{
					char *scoreStr = (char *)malloc(sizeof(char)*4);
					integerToString(score, scoreStr, 4);
					videoBuffer[i] = scoreStr[countIntegerDigits(score) - 1 - digitToFind];
					free(scoreStr);
				}
				else
					videoBuffer[i] = ' ';
			}
			else if(row >= 12 && row < 20 && column >= 26 && column < 74) //se deve stampare lo storico delle partite
				videoBuffer[i] = playTrisGameHistoryImage[row-12][column-26];
			else if(row < 24 && column < 80) //stampa dall'immagine base
				videoBuffer[i] = playTrisBaseImage[row][column];
		}
		else
			videoBuffer[i] = ' ';
	}

	//shifting eventuale per l'ingresso della nuova schermata
	if(playTrisTotalTimeElapsed < ENTER_SCREEN_ANIM_TIME)
	{
		int shift = consoleBase * (ENTER_SCREEN_ANIM_TIME - playTrisTotalTimeElapsed) / ENTER_SCREEN_ANIM_TIME;
		for(i = VIDEOBUFFER_SIZE - 1; i >= 0; i--)
			if(i%consoleBase < shift)
				videoBuffer[i] = playTrisPreviousScreen[i + consoleBase - shift];
			else
				videoBuffer[i] = videoBuffer[i - shift];
	}
}

BOOL humanTryToSetCell(enum Cell cell)
{
	if(getCell(playTrisGrid, cell) == noPlayer)
	{
		setCell(playTrisGrid, cell, playTrisTurn);
		return TRUE;
	}
	return FALSE;
}
void swapPlayers()
{
	int i, scoreTemp;
	enum PlayerTypes intelligenceTemp;

	scoreTemp = playTrisCircleWinCounter;
	playTrisCircleWinCounter = playTrisCrossWinCounter;
	playTrisCrossWinCounter = scoreTemp;

	intelligenceTemp = playTrisCircleIntelligence;
	playTrisCircleIntelligence = playTrisCrossIntelligence;
	playTrisCrossIntelligence = intelligenceTemp;

	swapPlayersGameHistory(&playTrisGameHistory);

	if(playTrisTurn == circle)
		playTrisTurn = cross;
	else
		playTrisTurn = circle;

	for(i = 0; i < 9; i++)
	{
		CellState cellSt = getCell(playTrisGrid, (enum Cell)i);
		if(cellSt != noPlayer)
			if(cellSt == circle)
				setCell(playTrisGrid, (enum Cell)i, cross);
			else
				setCell(playTrisGrid, (enum Cell)i, circle);
	}
}