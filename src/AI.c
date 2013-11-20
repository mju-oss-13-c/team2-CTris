#include"AI.h"
#include<stdlib.h>

BOOL checkWinPossibility(Grid grid, enum Players sign, enum Cell *move);

//restituisce la cella dove l'IA intende fare la prossima mossa
//Funzionamento:
//-da priorità alle celle dove può creare un tris
//-se non ci sono tris da creare fornisce priorità alle celle nelle quali è necessario bloccare un tris
//-se non ci sono celle dove può creare un tris, allora viene scelta una cella in maniera casuale, ma con probabilità pesata:
//		 -----       /
//      |2|1|2|     /
//      |-|-|-|    /
//      |1|4|1|   /  16
//      |-|-|-|  /
//      |2|1|2| /
//       ----- /
//Ritorno:
//Ritorna TRUE o FALSE nel caso in cui l'operazione sia riuscita o meno. L'operazione non riesce nel caso in cui:
// 1) non ci sia più spazio per effettuare una mossa
// 2) qualcuno ha già vinto la partita
// 3) la griglia non sia una griglia valida (vedere eccezioni gestite dalla funzione won in grid.h)
//L'operazione riesce in tutti gli altri casi
BOOL nextMoveAI(Grid grid, enum Players AISign, enum Cell *move)
{
	//controllo se qualcuno ha già vinto oppure se la griglia è piena
	if(won(grid, NULL) || fullGrid(grid))
		return FALSE;

	if(checkWinPossibility(grid, AISign, move) ||								//controlla se può vincere la IA
		checkWinPossibility(grid, (AISign == circle ? cross : circle), move))	//controlla se può impedire al nemico di vincere
		return TRUE;

	//altrimenti scegli una cella a caso tra le disponibili
	while(1)
	{
		enum Cell redirect[] = {cellA1, cellA1,
								cellA2,
								cellA3, cellA3,
								cellB1,
								cellB2, cellB2, cellB2, cellB2,
								cellB3,
								cellC1, cellC1,
								cellC2,
								cellC3, cellC3};
		int index = rand()%16;
		if(getCell(grid, redirect[index]) == noPlayer)
		{
			*move = redirect[index];
			return TRUE;
		}
	}
}

BOOL checkWinPossibility(Grid grid, enum Players sign, enum Cell *move)
{
	int i;
	for(i = 0; i < 9; i++)
		if(getCell(grid, (enum Cell)i) == noPlayer)
		{
			BOOL win;
			Grid newGrid = copyGrid(grid);
			setCell(newGrid, (enum Cell)i, sign);
			win = won(newGrid, NULL);
			deleteGrid(newGrid);
			if(win)
			{
				*move = (enum Cell)i;
				return TRUE;
			}
		}

	return FALSE;
}