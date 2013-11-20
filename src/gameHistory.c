#include"gameHistory.h"
#include"integerManip.h"
#include<stdlib.h>

const char *CellLineNames[8] = {"R1", "R2", "R3", "C1", "C2", "C3", "D1", "D2"};

struct GameHistory createGameHistory()
{
	int i;
	struct GameHistory history;
	history.arrayPointer = 0;
	history.totalGameCounter = 0;
	history.history = (struct GameResult *)malloc(sizeof(struct GameResult) * GAMEHISTORY_SIZE);
	for(i = 0; i < GAMEHISTORY_SIZE; i++)
		history.history[i] = createGameResult();
	
	return history;
}
void deleteGameHistory(struct GameHistory history)
{
	int i;
	for(i = 0; i < GAMEHISTORY_SIZE; i++)
		deleteGameResult(history.history[i]);
	free(history.history);
}
struct GameHistory copyGameHistory(struct GameHistory history)
{
	int i;
	struct GameHistory newHistory;
	newHistory.arrayPointer = history.arrayPointer;
	newHistory.totalGameCounter = history.totalGameCounter;
	newHistory.history = (struct GameResult *)malloc(sizeof(struct GameResult) * GAMEHISTORY_SIZE);
	for(i = 0; i < GAMEHISTORY_SIZE; i++)
		newHistory.history[i] = copyGameResult(history.history[i]);

	return newHistory;
}

int getGameHistoryTotalCounter(struct GameHistory history)
{
	return history.totalGameCounter;
}

BOOL getGameResult(struct GameHistory history, int id, struct GameResult *result)
{
	if(id >= getGameHistoryTotalCounter(history) ||
		id < getGameHistoryTotalCounter(history) - GAMEHISTORY_SIZE)
		return FALSE;
	else
	{
		int idPointer = history.arrayPointer + id - getGameHistoryTotalCounter(history);
		if(idPointer < 0)
			idPointer += GAMEHISTORY_SIZE;
		deleteGameResult(*result);
		*result = copyGameResult(history.history[idPointer]);
		return TRUE;
	}
}
void addGameResult(struct GameHistory *history, struct GameResult result)
{
	deleteGameResult(history->history[history->arrayPointer]);
	history->history[history->arrayPointer] = copyGameResult(result);
	history->arrayPointer = (history->arrayPointer + 1) % GAMEHISTORY_SIZE;
	history->totalGameCounter++;
}

void swapPlayersGameHistory(struct GameHistory *history)
{
	int i;
	for(i = 0; i < GAMEHISTORY_SIZE; i++)
		if(history->history[i].winner == circle)
			history->history[i].winner = cross;
		else if(history->history[i].winner == cross)
			history->history[i].winner = circle;
}

//crea l'immagine dello storico
void printGameHistory(struct GameHistory history, char** imageGameHistory, int bAlloc, int hAlloc)
{
	int i, j;
	int maxLengthID = countIntegerDigits(getGameHistoryTotalCounter(history) - 1);

	//disegna la tabella
	for(i = 0; i < hAlloc; i++)
		for(j = 0; j < bAlloc; j++)
			if(i < GAMEHISTORY_IMAGE_SIZE_H && j < GAMEHISTORY_IMAGE_SIZE_B) //se sei nella tabella
			{
				int columnOfRecord = j/16;
				int currentRecordID = (getGameHistoryTotalCounter(history) - 1) - (columnOfRecord*8 + i); //identifica l'ID del record corrente
				if(currentRecordID >= 0)
				{
					int stringPositionOnRecord = j%16;
					if(stringPositionOnRecord < maxLengthID) //se deve stampare l'ID
					{
						int countIDDigits = countIntegerDigits(currentRecordID);
						int IDDigitPosition = countIDDigits - maxLengthID + stringPositionOnRecord;
						if(IDDigitPosition >= 0) //se non è uno spazio bianco
						{
							char *IDString = (char*)malloc(sizeof(char)*countIDDigits);
							integerToString(currentRecordID, IDString, countIDDigits);
							imageGameHistory[i][j] = IDString[IDDigitPosition];
							free(IDString);
						}
						else
							imageGameHistory[i][j] = ' ';
					}
					else if(stringPositionOnRecord == maxLengthID) //se deve stampare ':'
						imageGameHistory[i][j] = ':';
					else //se deve stampare la parte riguardo al risultato
					{
						enum Players winner;
						enum CellLine winningLine;
						struct GameResult IDResult = createGameResult();
						getGameResult(history, currentRecordID, &IDResult);
						getGameResultState(IDResult, &winner, &winningLine);
						deleteGameResult(IDResult);

						if(stringPositionOnRecord == maxLengthID + 2) //se deve stampare il vincitore
							switch(winner)
							{
							case noPlayer: imageGameHistory[i][j] = '-'; break;
							case circle: imageGameHistory[i][j] = 'O'; break;
							case cross: imageGameHistory[i][j] = 'X';
							}
						else if(stringPositionOnRecord >= maxLengthID + 4 && //se deve stampare la riga vincente
							stringPositionOnRecord < maxLengthID + 10 &&     //quindi è dentro ad esempio in "on: D1"
							winner != noPlayer)
						{
							if(stringPositionOnRecord < maxLengthID + 8) //se deve stampare una parte di "on: "
							{
								char *baseStr = "on: ";
								imageGameHistory[i][j] = baseStr[stringPositionOnRecord - (maxLengthID + 4)];
							}
							else //se deve stampare il nome della riga
								imageGameHistory[i][j] = CellLineNames[winningLine][stringPositionOnRecord - (maxLengthID + 8)];
						}
						else //altrimenti è uno spazio bianco
							imageGameHistory[i][j] = ' ';
					}
				}
				else
					imageGameHistory[i][j] = ' ';
			}
			else
				imageGameHistory[i][j] = '\0';
}