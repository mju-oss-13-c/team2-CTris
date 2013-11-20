#include"gameResult.h"

#ifndef BOOL
#define BOOL int
#define TRUE 1
#define FALSE 0
#endif

#ifndef GAMEHISTORY_H
#define GAMEHISTORY_H

#define GAMEHISTORY_SIZE 24
#define GAMEHISTORY_IMAGE_SIZE_B 48
#define GAMEHISTORY_IMAGE_SIZE_H 8

struct GameHistory
{
	struct GameResult *history;
	int arrayPointer;

	unsigned int totalGameCounter;
};

struct GameHistory createGameHistory();
void deleteGameHistory(struct GameHistory history);
struct GameHistory copyGameHistory(struct GameHistory history);

//restituisce quanti record sono stati inseriti in totale (non necessariamente ancora presenti)
int getGameHistoryTotalCounter(struct GameHistory history);

//restituisce la buona riuscita o meno dell'operazione
BOOL getGameResult(struct GameHistory history, int id, struct GameResult *result);
void addGameResult(struct GameHistory *history, struct GameResult result);

void swapPlayersGameHistory(struct GameHistory *history);

//crea l'immagine dello storico
void printGameHistory(struct GameHistory history, char** imageGameHistory, int bAlloc, int hAlloc);

#endif